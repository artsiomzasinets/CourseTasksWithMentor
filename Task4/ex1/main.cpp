#include "strSet.h"


int main(){
    const char* file = "../data.txt";

    strSet obj;
    obj.downloadFromFile(file);

    return 0;
}

