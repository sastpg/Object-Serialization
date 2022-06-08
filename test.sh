#!/bin/bash

# build
mkdir ./build/
cd ./build/
cmake ..
make
cd ..

# test
mkdir ./test/
rm -f ./test/*
./bin/test.out &> ./messages.txt
