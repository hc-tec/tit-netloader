//
// Created by titto on 2022/5/11.
//

#include <iostream>
#include <co/co.h>

int main() {
    go([]() {
       co::sleep(1000);
        std::cout << "run coroutine" << std::endl;
    });
    std::cout << "hello " << std::endl;
    co::sleep(1500);
}
