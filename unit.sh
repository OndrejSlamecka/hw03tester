#!/bin/bash

cp ./unittest/main.c ./main.c
gcc -std=c99 -Wall -Wextra -Werror domtree.h domtree.c html.h html.c main.c -o ./hw03_unit
rm main.c

./hw03_unit < unittest/input.html

rm hw03_unit
