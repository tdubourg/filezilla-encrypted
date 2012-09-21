#!/bin/sh

cd cryptopp && make
cd ../
# g++ -c test.cpp -o test.o -Icryptopp
# g++ -o test cryptopp/cryptlib.o cryptopp/osrng.o cryptopp/sha.o cryptopp/aes.o cryptopp/hex.o cryptopp/integer.o cryptopp/pwdbased.o cryptopp/modes.o
g++ -g3 -ggdb -O0 -o test test.cpp -lcryptopp -Icryptopp