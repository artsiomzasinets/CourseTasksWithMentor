#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"
#include "Tree.h"





TEST_CASE("Check insert method and remove of Black-red tree int variables","[tree test]"){
    const int size = 50;
    Tree<int> obj(size);
    for(int i = 0; i < size; ++i){
        obj.insert(i);
    }

    SECTION("Testing for deleting '3' "){
        obj.remove(3);
        REQUIRE(obj.thelatestRemovedElem == 3);
    }
    SECTION("Find element"){
        CHECK(obj.findElem(45) == true);
    }
    SECTION("Testing for deleting '45' "){
        obj.remove(45);
        REQUIRE(obj.findElem(45) == false);
    }



}

