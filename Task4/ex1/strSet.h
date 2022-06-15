//
// Created by artom on 10.06.2022.
//

#ifndef INC_C00CAFC6E31F481A9C6A67C9756FCE97
#define INC_C00CAFC6E31F481A9C6A67C9756FCE97
#include <iostream>
#include <fstream>
#include <algorithm>
#include <set>
#include <thread>

class strSet{
    std::set<std::string> stringSetField;
    const unsigned short maxSizeOfString = 10;

    auto insert(const std::string&);
    bool contains(const std::string&);
    void erase(const std::string&);
public:
    void downloadFromFile(std::string);
    auto find(const std::string&);
};


#endif //INC_C00CAFC6E31F481A9C6A67C9756FCE97
