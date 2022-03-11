#include <iostream>

#include "Tree.h"




int main() {
    Tree obj(10000);

    for(size_t i = 1; i < 10000; ++i){
        obj.insert(i);
    }
    std::cout << obj.find(1000) << std::endl;

    return 0;
}
