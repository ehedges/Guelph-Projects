#!/bin/bash

serverIP=127.0.0.1
portNumber=12057

echo Pride.txt | ./bin/client $serverIP:$portNumber
echo Alice.txt | ./bin/client $serverIP:$portNumber
echo first.txt | ./bin/client $serverIP:$portNumber
echo second.txt | ./bin/client $serverIP:$portNumber
