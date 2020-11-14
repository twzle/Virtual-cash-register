#include "mainwindow.h"
#include "tests.h"
#include <windows.h>

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    Test::run();
    Test::run2();
    Test::run3();
    Queue b;
    std::cout << std::endl;
    Purchase un(11);
    Purchase tw(178);
//    Purchase(2,{20,20,20});
//    b.push(Purchase(21,{8,14,20}));
//    b.push(Purchase(9,{8,14,19}));
//    b.push(Purchase(89,{10,4,2}));
    Card Sber(b, "123456789012");
    Sber.setPrice(45.4);
//    Sber.setTime(0,8,20);
    Sber.setTelephoneNumber("+7891245678");
    Sber.Pay(un);
    Sber.Pay(tw);
//    std::cout << Sber.getTime() << std::endl;
    for (auto x : Sber.getHistory()){
        std::cout << "Price: " <<x.getPrice() << std::endl << "Time: " << x.getTime() << std::endl << std::endl;
    }
//    Date d;
//    std::cout << d.day << "." << d.month << "." << d.year << std::endl;
    return a.exec();
}
