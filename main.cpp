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
    return a.exec();
}
