
sudo cp lib* /usr/local/lib

cd http-parser
make
sudo make install
cd ..

cd cocoyaxi
make
sudo make install
cd ..
