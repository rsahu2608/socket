#!/usr/bin/bash
cd /home/e1092427/study/socket/
rm fileNames.txt
touch fileNames.txt
find *.txt > fileNames.txt
./client

