/* File: TCPclient.h
Author: Matt Sampson 0888047/Evan Hedges 0898140
Assignment 2
Course: CIS*3210 F17
Creation Date: October 3rd, 2017
Description: Contains includes and definitions of helper functions*/

#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>

/*this function parses the filename provided by the user to make sure it is valid.
if valid, opens dile and returns it, else returns NULL*/
bool checkValidFileExtension(char *fileName);

/*this function clears the user input buffer*/
void clearInputBuffer(char buffer[], int bufferSize);

/*this function is used to loop the confirmation of overwrite until a valid input is recieved*/
bool confirmOverwrite();

#endif
