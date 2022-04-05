#include <iostream>
#include <random>
#include "Tree.h"


template<typename T>
void generator(Tree<T>& obj,size_t size){
    std::mt19937 engine;
    std::random_device device;
    engine.seed(device());
    std::uniform_int_distribution<unsigned> distribution(0, 10000000);
    for(size_t i = 0; i < size; ++i){
        obj.insert(distribution(engine));
    }
}



int main() {
    size_t size = 10000;
    Tree<int> obj(size );
    generator(obj, size);
    obj.print();


    return 0;
}
