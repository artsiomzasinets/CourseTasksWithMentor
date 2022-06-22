//
// Created by artom on 29.04.2022.
//

#ifndef CURRENCY_H_
#define CURRENCY_H_
#include <iostream>
#include <map>


enum class Value:short{USD = 1,EUR,BYR, RUB, UAH,PLN};

class Currency{
public:
    Currency(Value);
    Currency(Value,double );
    Currency(const Currency&) noexcept;
    Currency& operator=(const Currency&)noexcept;

    Currency operator+(const Currency&) const;
    Currency operator-(const Currency&) const;

    static void showRatioOfCurrency();//one USD, print ratioOfCurrency
    static std::string convertor(double, Value);// arguments 10 EUR
    void show();//just print typeOfCurrency and numberOfCurrency

    static void printTypeOfCurrency(Value);
    static double convertCurrency(Value,Value,double);
public:
    static std::map<Value, double> ratioOfCurrency;
private:
    Value typeOfCurrency;
    double numberOfCurrency;
};


#endif //CURRENCY_H_
