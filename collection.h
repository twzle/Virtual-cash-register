#pragma once

#include "purchases.h"

#include <iostream>
#include <string>
#include <sstream>



class Queue {
protected:
    struct Node {
        Purchase d;
        Node* next;
    };
public:
    class Iterator
    {
        Node *obj;
    public:
        Iterator(const Queue& x);
        Iterator(const Iterator& x);
        Iterator(Node* x);
        Purchase* operator++();
        Purchase& operator*();
        bool operator==(Iterator& x);
        bool operator!=(Iterator& x);
    };

    Queue();
    Queue(const Purchase& _other);
    Queue(const Queue& _other);
    ~Queue();

    Iterator begin();
    Iterator end();
    double Calculate(const Time& _lower, const Time& _higher);
    bool Validate(const Purchase& object);
    bool Compare(const Queue& _other);

    void WriteToFile(const std::string& filename);

    void push(const Purchase& d);
    void pop();
    size_t getSize() const;
    bool empty() const;
    void clear();

    Node* back() const;
    Node* front() const;

private:
    Node*  ptr;
    size_t size;
};

void ReadFromFile(const std::string& filename, Queue& _q);
void PrintQueue(Queue& _other);

