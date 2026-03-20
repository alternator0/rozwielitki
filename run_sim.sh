#!/bin/bash

cmake -S . -B ./build/
cmake --build ./build/ -j $(nproc)
cd ./build/
time ./rozwielitki simulation.mac | grep masa
cd ..
./licz_energie.sh ./build/WynikiSymulacji.root
