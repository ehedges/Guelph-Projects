#!/bin/bash

counter = 0
begin=$(date +%s) 
for counter in {1..2} 
do
	
	./client 127.0.0.1:12034 Alice&

done

./client 127.0.0.1:12034 Alice

