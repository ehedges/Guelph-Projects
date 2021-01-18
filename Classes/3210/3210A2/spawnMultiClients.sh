#!/bin/bash

serverIP=127.0.0.1
portNumber=12057

for (( i=1; i <= 10; i++ )); do
    rm file$i.txt
done

for (( i=1; i <= 10; i++ )); do
    { echo ./testFiles/pi.txt; echo file$i.txt; } | ./bin/client $serverIP:$portNumber &
done
