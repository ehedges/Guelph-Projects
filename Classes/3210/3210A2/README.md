# 3210A2

Author: Matt Sampson 0888047 & Evan Hedges 0898140
Assignment 2
Course: CIS*3210 F17
Creation Date: October 19th, 2017

This project creates a threaded server that accepts text messages from clients and a client that sends a file to the server and the server saves the file under the name 
provided by the user. If a file collision occurs, the server lets the client know, and the client is asked if they would like to overwrite the file. If yes, overwrites file,
otherwise it will prompt again for a file to send. We made this decision because we thought it would be less error prone and not too much of a hassle since it is only two prompts. Matt Sampson's A1 code was the basis for this assignment.
type make to compile both
the server and client and make client and make server to make either individually. Make clean gets rid of all object and executable files.

To run the client, use: ./client server-ip-address:port-number [buffer_length]
to run the server, use: ./server port-number

The bash script provided spawns multiple clients that send different text files to the server to test its ability to handle multiple connections.
To run the bash script, make sure it has execution privelage and then simply use ./spawnMultipleClients.sh. When using the script to send multiple 
files from different clients, it sometimes doesn't seem to be executing all the commands properly. Client will prompt user for a text
file during execution and will prompt until a valid file is provided. File must be of type txt. If client is run with an invalid server ip address
or port it will use the default values of 127.0.0.1 and 12057 respectively. If server is provided an invalid port number, it will also default to
12057. Client must provide host as an IP or it will not work.
