#!/bin/bash
if [ ! -f "./bin/atm" ]
then
echo "Compiling..."
gcc src/*.c -I./include -lncursesw -o ./bin/atm
fi
cd bin
touch users.csv
./atm
