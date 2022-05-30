# net loader

This is a project for learn, cause I plan to implement net stack of chromium.

The project use [cocoyaxi](https://github.com/idealvin/cocoyaxi) as coroutine lib.

## build
```c++
git clone https://github.com/hc-tec/tit-netloader --recursive
cd tit-netloader

cd third_party
sudo sh install.sh
cd ..

mkdir build && cd build
cmake ..
make
```

## run test
```c++
cd bin
./core
```
