#pragma once

#include "purchases.h"
#include "collection.h"
#include <vector>

class Card : public Purchase{
public:
    Card();

    Card(const Purchase& _p, const std::string& _number);

    Card(Queue& _q, const std::string& _number);

    virtual double getPrice() const override;

    virtual Time getTime() const override;

    virtual void setPrice(const double& _value) override;

    virtual void setTime(const int& _hours, const int& _minutes, const int& _seconds) override;

    std::string& getCardNumber();
    std::string& getTelephoneNumber();
    void Pay(const Purchase & _purchase);
    std::vector<Purchase>& getHistory();
    void setTelephoneNumber(const std::string & phone);
    void setCardNumber(const std::string & number);
    bool checkDiscount(const float& _price);
private:
    std::vector<Purchase> history;
    double whole_price;
    Time checkout_time;
    std::string card_number;
    std::string telephone;
};
