
#include <iostream>

#include "co/co.h"

int main(int argc, char** argv) {
    flag::init(argc, argv);
    FLG_cout = true;


    go([](){
        co::sleep(100);
        LOG << "11";
    });
    go([](){
        while (1);
    });

//    co::sleep(1);
//    LOG << "33";

    char ch;
    std::cin >> ch;
    return 0;
}
