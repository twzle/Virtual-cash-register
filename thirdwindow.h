#pragma once
#ifndef THIRDWINDOW_H
#define THIRDWINDOW_H

#include <QDialog>
#include <QListWidget>
#include <QLabel>
#include <ctime>
#include "card.h"
#include <map>


namespace Ui {
class Thirdwindow;
}

class Thirdwindow : public QDialog
{
    Q_OBJECT

public:
    explicit Thirdwindow(QWidget *parent = nullptr);
    ~Thirdwindow();
    void Input_prod(Ui::Thirdwindow *ui);
    void Input_lim_prod(Ui::Thirdwindow *ui);
    void FillVectors();
    static QListWidget* getListWidget();
    QLabel* getLabel();
    static float getAmount();
    static std::map<std::string,Card>& getStorage();
    static void setStorage(std::map<std::string,Card>& other);
    static void setStatus(const bool& _st);
    void setDiscountedLabel(const float& _am);

private:
    Ui::Thirdwindow *ui;
private slots:
    void AddToCheck();
    void AddToCheck2();
    void DeleteFromCheck();
    void Pay();
    void ChooseCard();
};

#endif // THIRDWINDOW_H
