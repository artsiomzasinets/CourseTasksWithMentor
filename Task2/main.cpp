#include <iostream>
#include <random>
#include "Tree.h"


template<typename T>
void generator(Tree<T>& obj,size_t size){
    std::mt19937 engine;
    std::random_device device;
    engine.seed(device());
    std::uniform_int_distribution<int> distribution(0, 1000000);
    for(size_t i = 0; i < size; ++i){
        obj.insert(distribution(engine));
    }
}



int main() {
    size_t size = 10000;
    Tree<size_t> obj(size );
    generator(obj, size);
    for(int i = 1; i < size * 10; i++){
        obj.remove(i);
    }


    return 0;
}
