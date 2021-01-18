/* File: TCPserver.h
Author: Matt Sampson 0888047/Evan Hedges 0898140
Assignment 2
Course: CIS*3210 F17
Creation Date: October 3rd, 2017
Description: Contains includes and definitions of helper functions*/

#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <time.h>
#include <pthread.h>

//Message struct
typedef struct {
    int fileSize;
    int chunkSize;
    char fileName[21];
} Message;

//Message node
typedef struct message_node {
    Message msg;
    struct message_node* next;
} MessageNode;

//Message queue - a singly linked list
//Remove from head, add to tail
typedef struct {
    MessageNode* head;
    MessageNode* tail;
    int length;
    int mysocket;
    pthread_mutex_t mutex;
    pthread_cond_t cond;
} MessageQueue;

typedef struct {


} socketInformation;

MessageQueue* createMessageQueue();
void sendMessage(MessageQueue* q, int fileSize, int chunkSize, char *fileName);
int removeMessage(MessageQueue* q,char fileName[21]);
void* serverDownload();
void printMenu();
void* serverUi();
void* downloadServer();

#endif
