//
// Created by artom on 10.06.2022.
//

#include <fstream>
#include <iostream>
#include <iterator>
#include <algorithm>



void task3(){
    using US = unsigned char;
    std::ifstream fin("../input.txt");
    if(!fin.is_open()){
        std::cout << "Can't open file!" << std::endl;
        abort();
    }
    std::istream_iterator<US> iterIn(fin);
    std::istream_iterator<US> iterEnd;
    std::vector<US> buf(100);
    std::copy(iterIn, iterEnd, buf.begin());


    std::array<unsigned short,2> result{};

    US previousElem = buf[0];
    std::for_each(buf.begin() + 1 , buf.end(), [&result, &previousElem](US& elem){
        if(previousElem != elem){
            switch(previousElem){
                case '0':
                    result[1] += 1;// white day
                    break;
                case '1':
                    result[0] += 1;//black day
                    break;
            }
        }
        previousElem = elem;
    });
    std::ofstream fout("../output.txt");
    if(fout.is_open()){
        std::ostream_iterator<unsigned short > iterOut(fout,"|");
        std::copy(result.begin(), result.end(), iterOut);
    }else{
        std::cout << "Can't open file!" << std::endl;
    }


}


int main(int argc, char* argv[]){

    task3();

    return 0;
}