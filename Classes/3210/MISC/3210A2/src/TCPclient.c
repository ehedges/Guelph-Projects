/* File: TCPclient.c
Author: Matt Sampson 0888047/Evan Hedges 0898140
Assignment 2
Course: CIS*3210 F17
Creation Date: October 3rd, 2017
Description: This file is based off the example file provided by Prof. Nikitenko. It creates a client to send a text file to a server.
allows user to choose address, port number, and file to send.*/
#include "TCPclient.h"

int main(int argc, char *argv[])
{
    char userInputBuffer[200];
    char fileNameBuffer[21];
    char *connectionInformation, *copyOfConnectionInformation;
    char *stringIPAddress, *stringPortNumber;
    int mysocket, err;
    int bufferSize = 1024;
    int fileSize = 0;
    int portNumber, amountRead;
    struct sockaddr_in dest; // socket info about the machine connecting to us
    FILE *fileToSend = NULL;
    bool validSaveName = false, readyToSend = false, confirmed = false;

    //TODO: ask about txt file only or multiple file types, ask about connecting to school server

    if (argc < 2) {
        printf("Too few arguments, expected usage is ./client server-ip-address:port-number [buffer_length]\n");
        return -1;
    }
    else if (argc > 3) {
        printf("Too many arguments, expected usage is ./client server-ip-address:port-number [buffer_length]\n");
        return -1;
    }

    if (argc == 3) {
        //parse value and make buffer appropriate size
        bufferSize = atoi(argv[2]);
        if (bufferSize < 0) {
            printf("invalid buffer size, default value is 1024\n");
            bufferSize = 1024;
        }
    }
    //plus 1 to add null terminator
    char buffer[bufferSize + 1];

    connectionInformation = malloc(sizeof(char) * strlen(argv[1]) + 1);
    copyOfConnectionInformation = malloc(sizeof(char) * strlen(argv[1]) + 1);
    if (connectionInformation == NULL || copyOfConnectionInformation == NULL) {
        printf("memory allocation error\n");
        return -1;
    }
    strcpy(connectionInformation, argv[1]);
    strcpy(copyOfConnectionInformation, connectionInformation);

    //strtok on colon to get ip address and port number
    stringIPAddress = strtok(connectionInformation, ":");
    if (strcmp(stringIPAddress, copyOfConnectionInformation) == 0) {
        printf("Invalid argument, expected usage of argument 1 is server-ip-address:port-number, using default values\n");
        stringIPAddress = malloc(sizeof(char)*10);
        if (stringIPAddress == NULL) {
            free(connectionInformation);
            free(copyOfConnectionInformation);
            printf("memory allocation error\n");
            return EXIT_FAILURE;
        }
        strcpy(stringIPAddress, "127.0.0.1");
        portNumber = 12057;
    }
    else {
        stringPortNumber = strtok(NULL, ":");

        //convert port number to integer
        portNumber = atoi(stringPortNumber);
        if (portNumber < 0) {
            printf("invalid port number, default value is 12057\n");
            portNumber = 12057;
        }
    }
    free(copyOfConnectionInformation);

    /* Create a socket.
       The arguments indicate that this is an IPv4, TCP socket
    */
    mysocket = socket(AF_INET, SOCK_STREAM, 0);

    memset(&dest, 0, sizeof(dest));                // zero the struct

    //Initialize the destination socket information
    dest.sin_family = AF_INET;					   // Use the IPv4 address family
    err = inet_pton(AF_INET, stringIPAddress, &dest.sin_addr);
    if (err <= 0) {
        printf("error converting IP address, using default value of 127.0.0.1\n");
        err = inet_pton(AF_INET, "127.0.0.1", &dest.sin_addr);
        if (err <= 0) {
            printf("error converting IP address\n");
            return EXIT_FAILURE;
        }
    }
    //dest.sin_addr.s_addr = htonl(INADDR_LOOPBACK); // Set destination IP number - localhost, 127.0.0.1
    dest.sin_port = htons(portNumber);                // Set destination port number

    // Connect to the server
    connect(mysocket, (struct sockaddr *)&dest, sizeof(struct sockaddr_in));
    
    while (!readyToSend) {
        clearInputBuffer(userInputBuffer, 200);
        clearInputBuffer(fileNameBuffer, 21);
        //get user input for name of file to send
        printf("Enter the name of the file to send: ");
        fgets(userInputBuffer, 200, stdin);
        //get rid of new line char
        userInputBuffer[strlen(userInputBuffer)-1] = '\0';
        if (checkValidFileExtension(userInputBuffer)) {
            fileToSend = fopen(userInputBuffer, "r");
        }
        while (fileToSend == NULL) {
            clearInputBuffer(userInputBuffer, 200);
            printf("Invalid file name, make sure file exists and is of type txt\n");
            printf("Enter the name of the file to send: ");
            fgets(userInputBuffer, 200, stdin);
            userInputBuffer[strlen(userInputBuffer)-1] = '\0';
            if (checkValidFileExtension(userInputBuffer)) {
                fileToSend = fopen(userInputBuffer, "r");
            }
        }
        
        //get file size and send to server
        fseek(fileToSend, 0L, SEEK_END);
        fileSize = ftell(fileToSend);
        rewind(fileToSend);
        printf("%d\n", fileSize);
        send(mysocket, &fileSize, 8, 0);
        //send buffer size to server
        send(mysocket, &bufferSize, 8, 0);
        //prompt for file name
        printf("Enter name to save file as (less than or equal to 20 characters): ");
        fgets(fileNameBuffer, 21, stdin);
        fileNameBuffer[strlen(fileNameBuffer)-1] = '\0';
        //NOTE: this was causing the client to send incorrect file names to server if file name was longer than 20 chars
        /*validSaveName = checkValidFileExtension(fileNameBuffer);
        while (!validSaveName) {
            clearInputBuffer(fileNameBuffer, 21);
            printf("Invalid file name, make sure file is of type txt\n");
            printf("Enter name to save file as (less than or equal to 20 characters): ");
            fgets(fileNameBuffer, 21, stdin);
            fileNameBuffer[strlen(fileNameBuffer)-1] = '\0';
            validSaveName = checkValidFileExtension(fileNameBuffer);
        }*/
        //send file name to server
        send(mysocket, fileNameBuffer, 21, 0);
        //check response of server to see if file name is in use
        recv(mysocket, &validSaveName, sizeof(bool), 0);
        if (!validSaveName) {
            printf("File already exists on server, would you like to overwrite it? [y/n]\n");
            confirmed = confirmOverwrite();
            send(mysocket, &confirmed, sizeof(bool), 0);
            if (confirmed) {
                break;
            }
            else {
                fclose(fileToSend);
                fileToSend = NULL;
                continue;
            } 
        }
        else {
            confirmed = true;
            //this send false to let the server know 
            send(mysocket, &confirmed, sizeof(bool), 0);
            break;
        }
    }

    amountRead = fread(buffer, sizeof(char), bufferSize, fileToSend);
    while (amountRead == bufferSize) {
        buffer[bufferSize] = '\0';
        send(mysocket, buffer, strlen(buffer), 0);
        amountRead = fread(buffer, sizeof(char), bufferSize, fileToSend);
    }

    if (feof(fileToSend) != 0) {
        buffer[amountRead] = '\0';
        send(mysocket, buffer, strlen(buffer), 0);
    }
    else if (ferror(fileToSend) != 0) {
        perror("Error");
        return EXIT_FAILURE;
    }

    close(mysocket);
    fclose(fileToSend);
    free(connectionInformation);
    return EXIT_SUCCESS;
}

bool checkValidFileExtension(char *fileName) {
    char *dupFileName;
    char *token, *nextToken;
    bool valid = false;
    /*ensure file ends in .txt file extension*/
    //duplicate string
    if (fileName != NULL) {
        dupFileName = malloc(sizeof(char)*strlen(fileName) + 1);
        if (dupFileName != NULL) {
            strcpy(dupFileName, fileName);
            //strtok till the end
            nextToken = strtok(dupFileName, ".");
            while(nextToken != NULL) {
                token = nextToken;
                nextToken = strtok(NULL, ".");
            }
            if (strcmp(token, "txt") == 0) {
                valid = true;
            }
            else {
                valid = false;
            }
            free(dupFileName);
        }
    }

    return valid;
}

void clearInputBuffer(char buffer[], int bufferSize) {
    for (int i = 0; i < bufferSize; i++) {
        buffer[i] = '\0';
    }
}

bool confirmOverwrite() {
    char overwriteConfirm[200];
    
    fgets(overwriteConfirm, 200, stdin);
    overwriteConfirm[strlen(overwriteConfirm)-1] = '\0';
    while (strcmp(overwriteConfirm, "y") != 0 && strcmp(overwriteConfirm, "Y") != 0 && strcmp(overwriteConfirm, "n") != 0 && strcmp(overwriteConfirm, "N") != 0) {
        printf("Invalid option, please use either \"y\" or \"n\"\n");
        fgets(overwriteConfirm, 200, stdin);
        overwriteConfirm[strlen(overwriteConfirm)-1] = '\0';
    }
    if (strcmp(overwriteConfirm, "y") == 0 || strcmp(overwriteConfirm, "Y") == 0) {
        return true;
    }
    else {
        return false;
    }
}
