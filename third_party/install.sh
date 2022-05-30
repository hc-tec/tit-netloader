
sudo cp lib* /usr/local/lib

cd http-parser
make
sudo make install
cd ..

cd cocoyaxi
mkdir "build" && cd build
cmake ..
make
sudo make install
cd ..
