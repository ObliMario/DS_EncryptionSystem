#!/bin/bash  

gcc -march=native decodeany.c -o decode.exe -lm

./decode.exe $1


