# net loader

This is a project for learn, cause I plan to implement net stack of chromium.
The project use [cocoyaxi](https://github.com/idealvin/cocoyaxi) as coroutine lib. So before you try the project,
you need install cocoyaxi into your device first.

## build
```c++
git clone https://github.com/hc-tec/tit-netloader
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
