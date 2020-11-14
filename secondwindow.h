#ifndef SECONDWINDOW_H
#define SECONDWINDOW_H

#include <QDialog>

namespace Ui {
class Secondwindow;
}

class Secondwindow : public QDialog
{
    Q_OBJECT

public:
    explicit Secondwindow(QWidget *parent = nullptr);
    ~Secondwindow();
    void Input_prod(Ui::Secondwindow *ui);
    void Input_lim_prod(Ui::Secondwindow *ui);
    void FillVectors();
private:
    Ui::Secondwindow *ui;
private slots:
    void AddToCheck();
    void AddToCheck2();
    void DeleteFromCheck();
    void Pay();
    void SaveCheck();
};

#endif // SECONDWINDOW_H
