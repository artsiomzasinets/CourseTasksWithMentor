#include <iostream>
#include "Tree.h"


int main() {
    const int size = 50;
    Tree<int> obj(size);
    for (int i = 0; i < size; ++i) {
        obj.insert(i);
    }
    obj.remove(3);
    std::cout << obj.findElem(45) << std::endl;
    obj.remove(45);
    std::cout << obj.findElem(45) << std::endl;
    return 0;
}
