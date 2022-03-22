#include <iostream>
#include <random>

#include "Tree.h"



void generator(Tree& obj,size_t size){
    std::mt19937 engine;
    std::random_device device;
    engine.seed(device());
    std::uniform_int_distribution<unsigned> distribution(0, 100000);
    for(size_t i = 0; i < size; ++i){
        obj.insert(distribution(engine));
    }
}



int main() {
    Tree obj(1000);

    generator(obj, 10000);

    for(size_t i = 0; i < 10000; i++){
        obj.remove(i);
    }
    obj.printAll();


    return 0;
}
