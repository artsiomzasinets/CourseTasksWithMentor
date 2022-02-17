#include<string>
#include<list>
#include<random>
#include<algorithm>
#include <iostream>

enum class PayType:short{Card, Cash, BonusCard};

struct UserDetail{
    typedef unsigned short us;

    std::string destination;
    us flightNumber;
    std::string FullNameOfPassenger;

    struct {//for date and time
        us hours: 8;
        us minutes:8;
        us day: 8;
        us month:8;
        us year:16;
    }departureDate;

    PayType paymentType;

};

UserDetail generator(){
    UserDetail tempUser;
    std::mt19937 engine;
    std::random_device device;
    engine.seed(device());
    std::uniform_int_distribution<unsigned> distributionOfFullnameOfPassenger(0, 22);
    std::uniform_int_distribution<unsigned> distributionOfFlightNumber(1, 10000);
    std::uniform_int_distribution<unsigned> distributionOfHours(0, 24);
    std::uniform_int_distribution<unsigned> distributionOfMinute(0, 60);
    std::uniform_int_distribution<unsigned> distributionOfDays(1, 31);
    std::uniform_int_distribution<unsigned> distributionOfMonth(1, 12);
    std::uniform_int_distribution<unsigned> distributionOfPayment(0, 2);

    for(short i = 0; i < 10; i++){
        tempUser.destination += 'a' + distributionOfFullnameOfPassenger(engine);
        tempUser.FullNameOfPassenger += 'a' + distributionOfFullnameOfPassenger(engine);
    }
    tempUser.flightNumber = distributionOfFlightNumber(engine);

    tempUser.departureDate.hours = distributionOfHours(engine);
    tempUser.departureDate.minutes = distributionOfMinute(engine);
    tempUser.departureDate.day = distributionOfDays(engine);
    tempUser.departureDate.month = distributionOfMonth(engine);
    tempUser.departureDate.year = 2021;

    tempUser.paymentType = static_cast<PayType>(distributionOfPayment(engine));

    return  tempUser;
}

void printAll(const std::list<UserDetail>& list){
    std::for_each(list.begin(), list.end(), [](const UserDetail& detail){
        std::cout << "Destination= " << detail.destination << '\n';
        std::cout <<  "Flight Number= " << detail.flightNumber << '\n';
        std::cout << "Full name of Passenger= " << detail.FullNameOfPassenger << '\n';
        std::cout << "Payment type= ";
        switch (detail.paymentType) {
            case PayType::BonusCard: std::cout << "BonusCard" << '\n';break;
            case PayType::Card: std::cout << "Card" << '\n';break;
            case PayType::Cash: std::cout << "Cash" << '\n';break;
        }
        std::cout << "Departure date= Time:" << detail.departureDate.hours << ':' << detail.departureDate.minutes << " Date:"<<
        detail.departureDate.day << '.' << detail.departureDate.month << '.' << detail.departureDate.year << '\n'
        << std::endl;

    });
}

int main(){
    std::list<UserDetail> requests;
    for(size_t i  = 0; i < 10; i++){
        requests.push_back(generator());
    }
    requests.pop_back();
    printAll(requests);

    return 0;
}
