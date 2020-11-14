#include "card.h"

Card::Card(){
    whole_price = 0;
    checkout_time ={0,0,0};
    card_number="None";
    telephone="None";
}

Card::Card(const Purchase& _p, const std::string& _number) {
    whole_price = _p.getPrice();
    checkout_time = _p.getTime();
    card_number = _number;
}

Card::Card(Queue& _q, const std::string& _number) {
    if (!_q.empty()) {
        whole_price = _q.Calculate(_q.front()->d.getTime(), _q.back()->d.getTime());
        checkout_time = _q.back()->d.getTime();
    }
    else {
        whole_price = 0;
        checkout_time = {0,0,0};
    }
    card_number = _number;
}

double Card::getPrice() const{
    return this->whole_price;
}

Time Card::getTime() const{
    return this->checkout_time;
}

void Card::setPrice(const double& _value){
    whole_price = _value;
}

void Card::setTime(const int& _hours, const int& _minutes, const int& _seconds){
    checkout_time = Time(_hours, _minutes, _seconds);
}

void Card::setCardNumber(const std::string & number){
    if (number.size()==12)
        this->card_number=number;
}

std::string& Card::getCardNumber(){
    return this->card_number;
}

void Card::setTelephoneNumber(const std::string & phone){
    if (phone[0]=='+' && phone[1]=='7' && phone.size()==12)
        this->telephone=phone;
    else{
        this->telephone="None";
    }
}

std::string& Card::getTelephoneNumber(){
    return this->telephone;
}

void Card::Pay(const Purchase &_purchase){
    whole_price += _purchase.getPrice();
    checkout_time = _purchase.getTime();
    history.push_back(_purchase);
}

std::vector<Purchase>& Card::getHistory(){
    return history;
}

bool Card::checkDiscount(const float& _price){
    return ((history.size()+1)%6==0 && _price>500 && telephone!="None");
}
