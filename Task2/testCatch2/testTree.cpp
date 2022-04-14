#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"
#include "Tree.h"





TEST_CASE("Check insert method and remove of Black-red tree int variables","[tree test]"){
    size_t size = 1000000;
    Tree<int> obj(size);

    std::mt19937 engine;
    std::random_device device;
    engine.seed(device());
    std::uniform_int_distribution<int> distribution(0, 1000000);
    for(size_t i = 0; i < size; ++i){
        obj.insert(distribution(engine));
    }
    for(size_t i = 0; i < size; ++i){
        obj.remove(distribution(engine));
    }

}

