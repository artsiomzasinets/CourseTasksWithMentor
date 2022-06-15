//
// Created by artom on 10.06.2022.
//

#include "strSet.h"


auto strSet::insert(const std::string & str){
    stringSetField.insert(str);
}

bool strSet::contains(const std::string &str){
    return stringSetField.count(str) > 0 ? true: false;
}

void strSet::erase(const std::string &str){
    stringSetField.erase(str);
}

void strSet::downloadFromFile(std::string filename){
    std::ifstream fin(filename);
    if(fin.is_open()){
        std::string buf;
        buf.reserve(11);

        std::istreambuf_iterator<char> iter(fin);

        for(;*iter != '#'; iter++){// end character
            if(*iter == '\n'){//end of line  character
                switch(buf.front()){
                    case '+':
                        buf.erase(buf.begin(), buf.begin() + 2);// erasing the first two elements
                        stringSetField.insert(buf);
                        break;
                    case '-':
                        buf.erase(buf.begin(), buf.begin() + 2);// erasing the first two elements
                        stringSetField.erase(buf);
                        break;
                    case '?':
                        buf.erase(buf.begin(), buf.begin() + 2);// erasing the first two elements
                        stringSetField.count(buf) > 0 ? std::cout << "Yes" << std::endl : std::cout << "No" << std::endl;
                        break;
                }
                buf.clear();
            }else{
                buf.push_back(*iter);
            }
        }
    }else{
        std::cout << "Something goes wrong. Can't open file" << std::endl;
    }
}

auto strSet::find(const std::string &){
    return nullptr;
}

