#include "collection.h"
#include <fstream>

Queue::Queue() : ptr(nullptr),size(0){}

Queue::Queue(const Purchase &_other) : ptr(nullptr), size(0){
    this->push(_other);
}

Queue::Queue(const Queue& _other) : ptr(nullptr), size(0){
    Node* tmp = _other.front();
    while(tmp){
        this->push(tmp->d);
        tmp=tmp->next;
    }
}

Queue::~Queue() {
    this->clear();
}

double Queue::Calculate(const Time& _lower, const Time& _higher){
    double result = 0;
    Node* tmp = ptr;
    while (tmp){
        if(tmp->d.getTime()>=_lower && _higher>=tmp->d.getTime()){
            result+=tmp->d.getPrice();
        }
        tmp=tmp->next;
    }
    return result;
}

bool Queue::Validate(const Purchase& object){
    if (ptr)
        return (object.getTime())>=(back()->d.getTime());
    else
        return true;
}

bool Queue::Compare(const Queue &_other) {
    if (empty() && _other.empty()){
        return 1;
    }
    else if (getSize()==_other.getSize()){
        Node* tmp1 = front();
        Node* tmp2 = _other.front();
        while(tmp1 && tmp2){
            if (tmp1->d.getPrice()!=tmp2->d.getPrice() || tmp1->d.getTime()!=tmp2->d.getTime()){
                return 0;
            }
            tmp2=tmp2->next;
            tmp1=tmp1->next;
        }
        return 1;
    } else {
        return 0;
    }
}

void Queue::WriteToFile(const std::string& filename) {
    std::ofstream out;
    out.open(filename+".txt");
    if (out.is_open()){
        Node* tmp = front();
        while(tmp){
            out << "Price: " << tmp->d.getPrice();
            out << " Time: " << tmp->d.getTime() << std::endl;
            tmp=tmp->next;
        }
    }
    out.close();
}

Queue::Node* Queue::back() const{
    if (!this->empty()){
        Node* tmp=ptr;
        while (tmp->next){
            tmp=tmp->next;
        }
        return tmp;
    }
    exit(1);
}

Queue::Node* Queue::front() const {
    if (!this->empty())
        return ptr;
    return nullptr;
}


void Queue::push(const Purchase& d) {
    Node* e = new Node();
    e->d = d;
    Node* tmp = ptr;
    if(!tmp) {
        ptr=e;
        tmp = e;
        tmp->next = nullptr;
    } else {
        if (Validate(d)) {
            tmp=back();
            e->next = tmp->next;
            tmp = tmp->next = e;
        }
        else {
            --size;
            std::cout << "Invalid Time arguments to add\n";
        }
    }
    ++size;
}

void Queue::pop() {
    if(this->empty()) {
        return;
    }
    Node* tmp = ptr;
    ptr = ptr->next;
    delete tmp;
    --size;
    tmp = nullptr;
}

size_t Queue::getSize() const {
    return size;
}

bool Queue::empty() const {
    return (!ptr);
}

void Queue::clear() {
    while(!this->empty())
        this->pop();
}

void PrintQueue(Queue& _other){
    auto x = _other.front();
    int cnt =1;
    std::cout << "\n";
    while (x) {
        std::cout << "#" << cnt << std::endl;
        std::cout << "Price: " << x->d.getPrice() << std::endl;
        std::cout <<  "Time: " << x->d.getTime() << std::endl;
        std::cout << "\n";
        x=x->next;
        ++cnt;
    }
}

void ReadFromFile(const std::string& filename, Queue& _q) {
    std::ifstream file(filename+".txt");
    if (file.is_open()){
        if (file.peek()!=file.eof()){
            std::string s;
            while(getline(file, s)){
                double price;
                int hours, minutes, seconds;
                std::istringstream tmp(s);
                tmp.ignore(6,' ');
                tmp >> price;
                tmp.ignore(); tmp.ignore(5,' ');
                tmp >> hours; tmp.ignore(); tmp >> minutes; tmp.ignore(); tmp >> seconds;
                Purchase object(price,{hours, minutes, seconds});
                _q.push(object);
            }
            file.close();
            return;
        } else {
            file.close();
            std::cout << "File is empty" << std::endl;
            return;
        }
    } else {
        std::cout << "No matching file was found" << std::endl;
        return;
    }
}

//Iterator

Queue::Iterator::Iterator(const Queue& x) //с параметром
{
    obj = x.front();
}

Queue::Iterator::Iterator(const Queue::Iterator &x) {
    obj = x.obj;
}

Queue::Iterator::Iterator(Queue::Node *x) {
    obj=x;
}

Queue::Iterator Queue::begin(){
    return this->front();
}

Queue::Iterator Queue::end(){
    return this->back()->next;
}

Purchase* Queue::Iterator::operator++()//префиксный ++
{
    obj=obj->next;
    return &(obj->d);
}

Purchase& Queue::Iterator::operator*() // разыменование
{
    if (obj)
        return obj->d;
}

bool Queue::Iterator::operator==(Iterator& x)
{
    return (obj == x.obj);
}

bool Queue::Iterator::operator!=(Iterator& x)
{
    return (obj != x.obj);
}



