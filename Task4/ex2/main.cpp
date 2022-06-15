//
// Created by artom on 10.06.2022.
//

#include <fstream>
#include <iostream>
#include <iterator>
#include <vector>
#include <algorithm>



void task2(){
    using US = unsigned short;
    const US lengthOfTheBus = 437;// cm
    std::ifstream fin("../input.txt");
    std::istream_iterator<US> iterIn(fin);
    std::istream_iterator<US> iterEnd;
    std::vector<US> buf(*iterIn);//reserve memory
    iterIn++;//skip number of bridges;
    std::copy(iterIn, iterEnd, buf.begin());

    std::ofstream fout("../output.txt");
    std::ostream_iterator<char> iterOut(fout);
    std::string messageCrash("Crash ");
    std::string messageNoCrash("No crash");


    for(size_t i  = 0; i < buf.size(); i++){
        if(lengthOfTheBus >= buf[i]){
            messageCrash += std::to_string(i+1);
            std::copy(messageCrash.begin(), messageCrash.end(), iterOut);
            break;
        }
        if(i + 1 == buf.size()){
            std::copy(messageNoCrash.begin(), messageNoCrash.end(), iterOut);
        }
    }
}


int main(int argc, char* argv[]){

    task2();

    return 0;
}