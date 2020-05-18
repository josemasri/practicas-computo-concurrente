#!/bin/bash

# $1 number of experiments
if [ -z "$1" ]; then
    echo "Please enter the number of executions as 2nd parameter"
    exit 1
fi

find . -type f ! -name "*.*" -delete
gcc ejercicio2a.c -o ejercicio2a
gcc ejercicio2b.c -o ejercicio2b -lpthread

echo "**************************************************************"
echo "******************* Matrix multiplication ********************"
echo "**************************************************************"

for ((i = 1; i <= $1; i++)); do
    echo "======= Experiment $i =========="
    echo "Secuential"
    time ./ejercicio2a &
    PID=$!
    i=1
    sp="/-\|"
    echo -n ' '
    while [ -d /proc/$PID ]; do
        printf "\b${sp:i++%${#sp}:1}"
    done
    echo ""
    echo "Parallel"
    time ./ejercicio2b &
    PID=$!
    i=1
    sp="/-\|"
    echo -n ' '
    while [ -d /proc/$PID ]; do
        printf "\b${sp:i++%${#sp}:1}"
    done
    echo ""
done
find . -type f ! -name "*.*" -delete
