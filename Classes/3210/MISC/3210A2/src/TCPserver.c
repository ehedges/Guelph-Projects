/* File: TCPserver.c
Author: Matt Sampson 0888047/Evan Hedges 0898140
Assignment 2
Course: CIS*3210 F17
Creation Date: October 3rd, 2017
Description: This file is based off the example file provided by Prof. Nikitenko. It creates a server to recieve a text file from a client.
allows user to choose port number.*/

#include "TCPserver.h"

//Create a queue and initilize its mutex
int numthreads;
MessageQueue* createMessageQueue()
{
    MessageQueue* q = (MessageQueue*)malloc(sizeof(MessageQueue));
    q->head = q->tail = NULL;
    q->length = 0;
    q->mysocket = 0;
    pthread_mutex_init(&q->mutex, NULL);
    return q;
}

//"Send" a message - append it onto the queue
void sendMessage(MessageQueue* q, int fileSize, int chunkSize, char *fileName)
{
    MessageNode* node = (MessageNode*)malloc(sizeof(MessageNode));
    node->msg.fileSize = fileSize;
    node->msg.chunkSize = chunkSize;
    strcpy(node->msg.fileName, fileName);
    node->next = NULL;

    // critical section
    pthread_mutex_lock(&q->mutex);
    if (q->tail != NULL) {
        q->tail->next = node;       // append after tail
        q->tail = node;
    } else {
        q->tail = q->head = node;   // first node
    }
    q->length++;
    numthreads++;
    //Signal the consumer thread woiting on this condition variable
    pthread_cond_signal(&q->cond);
    pthread_mutex_unlock(&q->mutex);
}

int removeMessage(MessageQueue* q,char fileName[21])
{

    int success = 0;
    MessageNode* tempNode = q->head;
    MessageNode* prevNode = NULL;

    pthread_mutex_lock(&q->mutex);

    while (tempNode != NULL && success == 0) {
        if(strcmp(fileName,tempNode->msg.fileName) == 0){

            success = 1;
            if(prevNode != NULL)
            {

                prevNode->next = tempNode->next;

            }

            if(prevNode == NULL)
            {

                q->head = tempNode->next;

            }
            if(tempNode->next == NULL)
            {

                q->tail = prevNode;

            }
            free(tempNode);
            q->length--;
            numthreads--;

        }
        else{

            prevNode = tempNode;
            tempNode = tempNode->next;

        }

    }
    numthreads--;
    pthread_cond_signal(&q->cond);
    pthread_mutex_unlock(&q->mutex);
    return(success);

}
//*****************************************************************************

pthread_t* threads;

int exitType = 0;

int main(int argc, char *argv[])
{

    int maxthread = 30;
    int err;

    MessageQueue* livingQueue = createMessageQueue();

    struct sockaddr_in serv; // socket info about our server
    int mysocket, portNumber;            // socket used to listen for incoming connections
    exitType = 0;
    memset(&serv, 0, sizeof(serv));           // zero the struct before filling the fields

    if (argc < 2) {
        printf("Too few arguments, expected usage is ./server port-number\n");
        return -1;
    }

    //convert port number to integer
    portNumber = atoi(argv[1]);
    if (portNumber < 0) {
        printf("invalid port number, default value is 12057\n");
        portNumber = 12057;
    }

    serv.sin_family = AF_INET;                // Use the IPv4 address family
    serv.sin_addr.s_addr = htonl(INADDR_ANY); // Set our address to any interface
    serv.sin_port = htons(portNumber);           // Set the server port number

    /* Create a socket.
   	   The arguments indicate that this is an IPv4, TCP socket
    */
    mysocket = socket(AF_INET, SOCK_STREAM, 0);
    livingQueue->mysocket = mysocket;
    threads = malloc(sizeof(pthread_t)*100);

    for (int i = 0; i < 100; i++) {

        threads[i] = 0;

    }

    // bind serv information to mysocket
    printf("Creating UI.\n");
    threads[0] = pthread_create(&threads[0], NULL,&serverUi,(void*)livingQueue);
    printf("Done UI.\n");
    numthreads++;
    err = bind(mysocket, (struct sockaddr *)&serv, sizeof(struct sockaddr));
    if (err < 0) {
        perror("Error");
        return EXIT_FAILURE;
    }

    // start listening, allowing a queue of up to 1 pending connection
    while (exitType == 0) {
        //If exitTypes changed afterwards. It may still wait for one last receive to exit.

        error = listen(mysocket, SOMAXCONN);

        livingQueue->mysocket = mysocket;
        if(numthreads == maxthread)
        {
            int temp = numthreads;
            threads = realloc(threads,sizeof(threads)+sizeof(pthread_t)*10);
            for (int i = 0; i < temp; i++) {

                threads[i+temp+1] = 0;

            }
            maxthread += 10;
        }

        for (int i = 0; i < maxthread; i++) {

            if(threads[i] == 0)
            {

                pthread_create(&threads[i],NULL,&downloadServer,(void*)livingQueue);

            }

        }


        close(mysocket);

    }

    if(exitType == 2)
    {

        exit(0);

    }

    for (int i = 0; i < maxthread; i++) {

        pthread_join(threads[i],NULL);

    }

    return EXIT_SUCCESS;
}

void printMenu() {
    printf("Select an option from the list:\n");
    printf("1. Display active transfers [d]\n");
    printf("2. Soft shutdown [s]\n");
    printf("3. Hard shutdown [h]\n");
}

void printTransfers(MessageQueue *queue) {
    MessageNode *cursor = NULL;

    if (queue != NULL) {
        printf("Files currently being transfered:\n");

        // critical section
        pthread_mutex_lock(&queue->mutex);

        while(queue->head == NULL){
            pthread_cond_wait(&queue->cond, &queue->mutex);
        }

        cursor = queue->head;
        while (cursor != NULL) {
            //print information
            printf("File Name: %s File Size: %d Buffer Size: %d\n", cursor->msg.fileName, cursor->msg.fileSize, cursor->msg.chunkSize);
            cursor = cursor->next;
        }

        //Release lock
        pthread_mutex_unlock(&queue->mutex);
    }
}

void* serverUi(void*livingQueue)
{
    char userInputBuffer[200];
    printf("QUEUE\n");
    MessageQueue* tempQueue = (MessageQueue*) livingQueue;
    printf("HERE\n");
    printMenu();
    printf("NOTHERER\n");
    fgets(userInputBuffer, 200, stdin);
    //get rid of new line char
    userInputBuffer[strlen(userInputBuffer)-1] = '\0';
    while (strcmp(userInputBuffer, "h") != 0 && strcmp(userInputBuffer, "H") != 0 && strcmp(userInputBuffer, "3") != 0) {
        if (strcmp(userInputBuffer, "d") == 0 || strcmp(userInputBuffer, "D") == 0 || strcmp(userInputBuffer, "1") == 0) {
            printTransfers(tempQueue);
        }
        else if (strcmp(userInputBuffer, "s") == 0 || strcmp(userInputBuffer, "S") == 0 || strcmp(userInputBuffer, "2") == 0) {
            //call soft shutdown function here
        }
        else if (userInputBuffer[0] != '\0') {
            printf("invalid input, use character at end or number to select option\n");
        }
        for (int i = 0; i < 200; i++) {
            userInputBuffer[i] = '\0';
        }
        printMenu();
        fgets(userInputBuffer, 200, stdin);
        userInputBuffer[strlen(userInputBuffer)-1] = '\0';
    }
    //hard shutdown code/function goes here

    return(0);

}

void* downloadServer(void*livingQueue)
{

    MessageQueue* temp = (MessageQueue*)livingQueue;
    int tempSocket = temp->mysocket;
    struct sockaddr_in dest; // socket info about the machine connecting to us
    socklen_t socksize = sizeof(struct sockaddr_in);
    bool readyToRcv = false;
    char fileNameBuffer[21];
    int fileSize = 0, chunkSize = 0, len = 0;
    FILE *saveFile = NULL;
    int messageStatus;

    // Create a socket to communicate with the client that just connected
    int consocket = accept(tempSocket, (struct sockaddr *)&dest, &socksize);

    while (!readyToRcv) {
        for (int i = 0; i < 21; i++) {
            fileNameBuffer[i] = '\0';
        }
        // recieve file size from client
        recv(consocket, &fileSize, 8, 0);
        // recieve chunk size from client
        recv(consocket, &chunkSize, 8, 0);
        // recieve file name from client
        recv(consocket, fileNameBuffer, 21, 0);
        sendMessage(temp,fileSize,chunkSize,fileNameBuffer);
        //check if existing file
        saveFile = fopen(fileNameBuffer, "r");
        //file doesnt exist, set readyToRcv to true
        if (saveFile == NULL) {
            readyToRcv = true;
        }
        else {
            fclose(saveFile);
        }
        send(consocket, &readyToRcv, sizeof(bool), 0);
        recv(consocket, &readyToRcv, sizeof(bool), 0);
    }
    printf("TEST\n");
    messageStatus = removeMessage(temp,fileNameBuffer);
    if(messageStatus == 0)
    {

        printf("Error while downloading file.\n");

    }
    char buffer[chunkSize + 1];

    //open file for writing
    saveFile = fopen(fileNameBuffer, "w");
    // Receive data from the client
    len = recv(consocket, buffer, chunkSize, 0);
    buffer[len] = '\0';
    fprintf(saveFile, "%s", buffer);
    while (len != 0) {
        len = recv(consocket, buffer, chunkSize, 0);
        buffer[len] = '\0';
        fprintf(saveFile, "%s", buffer);
    }

    fclose(saveFile);

    //Close current connection
    close(consocket);
    //Continue listening for incoming connections
    return(0);

}
