cd rendevox

rm -rf build
mkdir -p build
cd build
CC=/usr/local/bin/gcc-12 cmake -DCMAKE_BUILD_TYPE=Release ..
make
./rendevox