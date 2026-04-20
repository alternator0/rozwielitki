#!/bin/bash

cmake -S . -B ./build/
cmake --build ./build/ -j $(nproc)
cd ./build/
time ./rozwielitki ../simulationCez.mac | grep -E "SYMULACJI|masa"
cd ..
./licz_energie.sh ./build/WynikiSymulacji.root
