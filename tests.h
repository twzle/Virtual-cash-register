#pragma once

#ifndef TESTS_H
#define TESTS_H

#include <float.h>
#include <fstream>
#include <random>
#include <assert.h>
#include "collection.h"
#include "card.h"

bool CompareFiles(const std::string& fl1, const std::string& fl2){
    std::ifstream fin1(fl1+".txt", std::ios::binary);
    std::ifstream fin2(fl2+".txt", std::ios::binary);
    if (fin2 && fin2)
    {
        char ch1, ch2;
        bool result = true;
        while (fin1.get(ch1) && fin2.get(ch2))
        {
            if (ch1 != ch2)
            {
                result = false;
                break;
            }
        }
        return result;
    }
    else
        return true;
}


namespace Random {

    double realNumber(double from = -DBL_MAX / 2, double to = DBL_MAX / 2) {
        return from + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (to - from)));
    }

    int integer(int from = INT_MIN, int to = INT_MAX) {
        return rand() % to + from;
    }

}

namespace Test
{
    void assertValidity(const Purchase &object)
    {
        assert(object.getPrice() >= MIN_PARAM1_VALUE);
        assert(object.getPrice() < MAX_PARAM1_VALUE);

        assert(object.getTime().hours >= MIN_TIME_VALUE);
        assert(object.getTime().hours < MAX_HOURS_VALUE);

        assert(object.getTime().minutes >= MIN_TIME_VALUE);
        assert(object.getTime().minutes < MAX_TIME_VALUE);

        assert(object.getTime().seconds >= MIN_TIME_VALUE);
        assert(object.getTime().seconds < MAX_TIME_VALUE);
    }

    void assertEquality(const Purchase &first, const Purchase &second)
    {
        assert(first.getPrice() == second.getPrice());

        assert(first.getTime().hours == second.getTime().hours);
        assert(first.getTime().minutes == second.getTime().minutes);
        assert(first.getTime().seconds == second.getTime().seconds);
    }

    void assertStability(Purchase &object)
    {
        double value1 = Random::realNumber(MIN_PARAM1_VALUE, MAX_PARAM1_VALUE);
        object.setPrice(value1);
        assert(object.getPrice() == value1);
        double error1 = Random::realNumber(MAX_PARAM1_VALUE);
        object.setPrice(error1);
        assert(object.getPrice() != error1);
        assert(object.getPrice() == value1);

        int value2_h = Random::integer(MIN_TIME_VALUE, MAX_HOURS_VALUE);
        int value2_m = Random::integer(MIN_TIME_VALUE, MAX_TIME_VALUE);
        int value2_s = Random::integer(MIN_TIME_VALUE, MAX_TIME_VALUE);
        object.setTime(value2_h, value2_m, value2_s);
        assert(object.getTime().hours == value2_h);
        assert(object.getTime().minutes == value2_m);
        assert(object.getTime().seconds == value2_s);
        int error2_h = Random::integer(MAX_HOURS_VALUE);
        int error2_m = Random::integer(MAX_TIME_VALUE);
        int error2_s = Random::integer(MAX_TIME_VALUE);
        object.setTime(error2_h, error2_m, error2_s);
        assert(object.getTime().hours != error2_h);
        assert(object.getTime().minutes != error2_m);
        assert(object.getTime().seconds != error2_s);
        object.setTime(error2_h, error2_m, error2_s);
        assert(object.getTime().hours == value2_h);
        assert(object.getTime().minutes == value2_m);
        assert(object.getTime().seconds == value2_s);
    }

    void assertInitialization(){
        Queue collection;
        assert(collection.getSize()==0);
        assert(collection.front()==nullptr);
        Purchase object1(400.21,{21,15,56});
        Queue collection2(object1);
        assert(collection2.getSize()==1);
        assert(collection2.empty()==0);
        assert(collection2.front()->d.getTime().hours==object1.getTime().hours);
        assert(collection2.front()->d.getTime().minutes==object1.getTime().minutes);
        assert(collection2.front()->d.getTime().seconds==object1.getTime().seconds);
        assert(collection2.front()->d.getPrice()==object1.getPrice());
        Queue collection3(collection2);
        assert(collection2.getSize()==collection3.getSize());
        assert(collection2.front()!=collection3.front());
        assert(collection2.front()->d.getTime().hours==collection3.front()->d.getTime().hours);
        assert(collection2.front()->d.getTime().minutes==collection3.front()->d.getTime().minutes);
        assert(collection2.front()->d.getTime().seconds==collection3.front()->d.getTime().seconds);
        assert(collection2.front()->d.getPrice()==collection3.front()->d.getPrice());
    }

    void assertMethods() {
        Queue collection;
        Purchase object1(400.21, {21, 15, 56});
        //push
        collection.push(object1);
        assert(collection.getSize() == 1);
        assert(collection.empty() == 0);
        //front
        assert(collection.front()->d.getTime().hours == object1.getTime().hours);
        assert(collection.front()->d.getTime().minutes == object1.getTime().minutes);
        assert(collection.front()->d.getTime().seconds == object1.getTime().seconds);
        assert(collection.front()->d.getPrice() == object1.getPrice());
        assert(collection.front()->next==nullptr);
        collection.push(object1);
        assert(collection.front()->next!=nullptr);
        //clear
        collection.clear();
        assert(collection.getSize() == 0);
        assert(collection.empty() == 1);
        assert(collection.front() == nullptr);
        //pop
        collection.push(object1);
        collection.pop();
        assert(collection.getSize() == 0);
        assert(collection.empty() == 1);
        assert(collection.front() == nullptr);
    }

    void assertTimeValidity() {
        Queue collection;
        Purchase object1(400.21, {21, 15, 56});
        collection.push(object1);
        collection.push(object1);
        assert(collection.front()->d.getTime() >= collection.front()->next->d.getTime());
        assert(collection.empty() == 0);
        assert(collection.getSize()==2);
        Purchase object2(20.54, {17,18,19});
        collection.push(object2);
        assert(collection.front()->next->d.getTime() >= object2.getTime());
        assert((object2.getTime()>=collection.front()->next->d.getTime())==0);
        assert(collection.getSize()==2);
    }

    void assertIterator() {
        Queue collection;
        //*
        Purchase object1(400.21, {21, 15, 56});
        collection.push(object1);
        Queue::Iterator it(collection);
        assert((*it).getPrice()==object1.getPrice());
        assert((*it).getTime().hours==object1.getTime().hours);
        assert((*it).getTime().minutes==object1.getTime().minutes);
        assert((*it).getTime().seconds==object1.getTime().seconds);
        //++
        Purchase object2(2.14, {22, 15, 56});
        auto tmp = it;
        assert((++tmp)==nullptr);
        collection.push(object2);
        ++it;
        assert((*it).getPrice()==object2.getPrice());
        assert((*it).getTime().hours==object2.getTime().hours);
        assert((*it).getTime().minutes==object2.getTime().minutes);
        assert((*it).getTime().seconds==object2.getTime().seconds);
        //!=
        assert(tmp!=it);
        //==
        Queue::Iterator it2(it);
        assert(it2==it);
    }

    void assertPrint() {
        Queue collection;
        Purchase object1(400.21, {14, 25, 1});
        Purchase object2(24.21, {13, 15, 56});
        Purchase object3(89.17, {15, 25, 22});
        collection.push(object1);
        collection.push(object2);
        collection.push(object3);
        PrintQueue(collection);
        collection.WriteToFile("original");
        Queue collection2;
        ReadFromFile("original", collection2);
        assert(collection2.Compare(collection)==1);
        collection2.WriteToFile("copy");
        assert(CompareFiles("original", "copy")==1);
    }

    void assertCalculation() {
        Queue collection;
        Purchase object1(400.21, {14, 25, 1});
        Purchase object2(24.21, {13, 15, 56});
        Purchase object3(89.17, {15, 25, 2});
        collection.push(object1);
        assert(collection.Calculate({14,25,1},{23,59,59})==object1.getPrice());
        collection.push(object2);
        assert(collection.Calculate({0,0,0},{23,59,59})==object1.getPrice());
        assert(collection.Calculate({14,25,1},{23,59,59})!=object1.getPrice()+object2.getPrice());
        collection.push(object3);
        assert(collection.Calculate({0,0,0},{23,59,59})==object1.getPrice()+object3.getPrice());

    }

    void assertSinglePayment() {
        Purchase object1(400.21, {14, 25, 1});
        Card bonus_card(object1,"123456789012");
        assert(bonus_card.getPrice()==object1.getPrice());
        assert(bonus_card.getTime()==object1.getTime());
        assert(bonus_card.getCardNumber()=="123456789012");
        bonus_card.setTime(11,20,4);
        bonus_card.setPrice(12.99);
        assert(bonus_card.getPrice()==12.99);
        assert(bonus_card.getTime()==Time(11,20,4));
    }

    void assertMultiplePayment() {
        Queue collection;
        Purchase object1(100.21, {14, 25, 1});
        Purchase object2(24.21, {13, 15, 56});
        Purchase object3(89.17, {15, 25, 2});
        collection.push(object1);
        Card bonus_card(collection,"123456789012");
        assert(bonus_card.getPrice()==collection.Calculate(Time(0,0,0),Time(23,59,59)));
        assert(bonus_card.getPrice()==object1.getPrice());
        assert(bonus_card.getPrice()==100.21);
        assert(bonus_card.getTime()==collection.back()->d.getTime());
        assert(bonus_card.getTime()==object1.getTime());
        assert(bonus_card.getTime()==Time(14,25,1));
        assert(bonus_card.getCardNumber()=="123456789012");
        collection.push(object2);
        collection.push(object3);
        Card bonus_card2(collection,"210987654321");
        assert(bonus_card2.getPrice()==collection.Calculate(Time(0,0,0),Time(23,59,59)));
//        std::cout << bonus_card2.getPrice() << " " << object1.getPrice()+object2.getPrice()+object3.getPrice();
        assert(bonus_card2.getPrice()==(object1.getPrice()+object3.getPrice()));
        assert(bonus_card2.getPrice()!=(object1.getPrice()+object2.getPrice()+object3.getPrice()));
        assert(bonus_card2.getPrice()==189.38);
        assert(bonus_card2.getPrice()!=213.59);
        assert(bonus_card2.getTime()==collection.back()->d.getTime());
        assert(bonus_card2.getTime()==object3.getTime());
        assert(bonus_card2.getTime()==Time(15,25,2));
        assert(bonus_card2.getCardNumber()=="210987654321");
    }


    void run() {
        Purchase defaultObject;
        assertValidity(defaultObject);
        for (int i = 0; i < 1000; i++)
        {
            Purchase randomObject(Random::realNumber(MIN_PARAM1_VALUE,
                                                   MAX_PARAM1_VALUE),{
                                   Random::integer(MIN_TIME_VALUE,MAX_HOURS_VALUE),
                                   Random::integer(MIN_TIME_VALUE, MAX_TIME_VALUE),
                                   Random::integer(MIN_TIME_VALUE, MAX_TIME_VALUE)});
            assertValidity(randomObject);
            Purchase copyObject(randomObject);
            assertValidity(copyObject);
            assertEquality(randomObject, copyObject);
            assertStability(copyObject);
            assertValidity(copyObject);
        }
        std::cout << "STATUS: (First part) Tests completed\n\n";
    }


    void run2() {
        assertInitialization();
        assertMethods();
        assertTimeValidity();
        assertIterator();
        assertPrint();
        assertCalculation();
        std::cout << "\nSTATUS: (Second part) Tests completed\n";
    }

    void run3() {
        assertSinglePayment();
        assertMultiplePayment();
        std::cout << "\nSTATUS: (Third part) Tests completed\n";
    }
};

#endif // TESTS_H
