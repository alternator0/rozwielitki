cd build 
make
time ./rozwielitki simulation.mac | grep masa
cd ..
./licz_energie.sh ./build/WynikiSymulacji.root
