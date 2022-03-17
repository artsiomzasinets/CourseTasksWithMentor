#include <iostream>

#include "Tree.h"




int main() {
    Tree obj(1000);

    for(size_t i = 1; i < 1100; ++i){
        if(i == 2)
            continue;
        obj.insert(i);
    }
    std::cout << obj.find(10000) << std::endl;
    obj.insert(2);
    obj.printAll();

    return 0;
}
