#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include "collection.h"
#include "card.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void Hide();

private:
    Ui::MainWindow *ui;

private slots:
    void Create_Purchase();
    void Show_Purchase();
    void AddToQueue();
    void DeleteFromQueue();
    void EraseQueue();
    void Print();
    void Write();
    void Read();
    void DoValidation();
    void Size();
    void Summary();
    void BuyItem();
    void BuyWhole();
    void OpenSecondWindow();
    void OpenThirdWindow();
};
#endif // MAINWINDOW_H
