#pragma once
#ifndef CARDFINDER_H
#define CARDFINDER_H

#include "card.h"
#include <QDialog>
#include <QLabel>


namespace Ui {
class Cardfinder;
}

class Cardfinder : public QDialog
{
    Q_OBJECT

public:
    explicit Cardfinder(QWidget *parent = nullptr);
    ~Cardfinder();
    void Input_Cards(Ui::Cardfinder *ui);

private:
    Ui::Cardfinder *ui;
    QLabel *special_label;
private slots:
    void CreateNew();
    void Delete();
    void PayByCard();
    void ShowHistory();
    void WriteHistoryToFile(Card _bc);
};

#endif // CARDFINDER_H
