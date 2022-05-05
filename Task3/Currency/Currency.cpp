//
// Created by artom on 29.04.2022.
//

#include "Currency.h"

std::map<Value,double> Currency::ratioOfCurrency = {
        {Value::USD,1},
        {Value::EUR,0.9461},
        {Value::BYR, 2.6318},
        {Value::RUB,71.3167},
        {Value::UAH, 84.7557},
        {Value::PLN,4.7138}
};

Currency::Currency(Value value):typeOfCurrency(value), numberOfCurrency(1.0){
}

Currency::Currency(Value value, double number):typeOfCurrency(value){
    if(number <= 1000000000)
        numberOfCurrency = number;
    else
        numberOfCurrency = 1.0;
}

Currency::Currency(const Currency & outObj)noexcept{
    typeOfCurrency = outObj.typeOfCurrency;
    numberOfCurrency = outObj.numberOfCurrency;
}

Currency& Currency::operator=(const Currency & outObj) noexcept{
    typeOfCurrency = outObj.typeOfCurrency;
    numberOfCurrency = outObj.numberOfCurrency;
    return *this;
}

Currency Currency::operator+(const Currency &outObj) const{
    Currency temp(typeOfCurrency);
    temp.numberOfCurrency = numberOfCurrency +
            convertCurrency(outObj.typeOfCurrency, typeOfCurrency, outObj.numberOfCurrency);
    return temp;
}

Currency Currency::operator-(const Currency &outObj) const{
    Currency temp(typeOfCurrency);
    double converted = convertCurrency(outObj.typeOfCurrency, typeOfCurrency, outObj.numberOfCurrency);
    if(numberOfCurrency >= converted)
        temp.numberOfCurrency = numberOfCurrency - converted;
    return temp;
}



void Currency::showRatioOfCurrency(){
    for(auto i : ratioOfCurrency){
        std::cout << '\t' << i.second << "\t ";
        printTypeOfCurrency(i.first);
        std::cout << '\n';
    }
    std::cout << std::endl;
}



void Currency::convertor(double number, Value outObj){
    std::cout.setf(std::cout.fixed);
    std::cout.precision(3);
    std::cout.width(15);
    std::cout << number;
    std::cout << "\t|";
    printTypeOfCurrency(outObj);
    std::cout << '\n';

    for(auto i : ratioOfCurrency){
        if(outObj == i.first){
            continue;
        }
        std::cout.width(15);
        std::cout <<convertCurrency(outObj,i.first,number);
        std::cout << "\t|";
        printTypeOfCurrency(i.first);
        std::cout << '\n';
    }
    std::cout << std::endl;
}

void Currency::show(){
    convertor(numberOfCurrency,typeOfCurrency);
}

void Currency::printTypeOfCurrency(Value value){
    switch(value){
        case Value::USD: std::cout << "USD ";
            break;
        case Value::EUR: std::cout << "EUR ";
            break;
        case Value::BYR: std::cout << "BYR ";
            break;
        case Value::RUB: std::cout << "RUB ";
            break;
        case Value::PLN: std::cout << "PLN ";
            break;
        case Value::UAH: std::cout << "UAH ";
            break;
    }
}

double Currency::convertCurrency(Value typeToConvert, Value type, double number){
    auto elemOut = ratioOfCurrency.find(type);
    auto elemCurrent = ratioOfCurrency.find(typeToConvert);
    double result = elemOut->second/ elemCurrent->second * number;
    return result;
}
