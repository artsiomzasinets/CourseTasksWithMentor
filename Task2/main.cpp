#include <iostream>
#include <random>

#include "Tree.h"



void generator(Tree& obj,size_t size){
    std::mt19937 engine;
    std::random_device device;
    engine.seed(device());
    std::uniform_int_distribution<unsigned> distribution(0, 1000000);
    for(size_t i = 0; i < size; ++i){
        obj.insert(distribution(engine));
    }
}



int main() {
    Tree obj(1000);

    generator(obj, 100);
    std::cout << obj.find(10000) << std::endl;
    obj.printAll();

    return 0;
}
