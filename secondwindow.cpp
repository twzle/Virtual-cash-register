#include "secondwindow.h"
#include "ui_secondwindow.h"
#include "purchases.h"
#include <QFileDialog>
#include <QMessageBox>
#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>
#include <ctime>

std::vector<std::string> usual;
std::vector<std::string> limited;
std::vector<std::string> products_bought;
float amount = 0;
bool purchase_made =false;
Purchase pur;

Secondwindow::Secondwindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Secondwindow)
{
    ui->setupUi(this);
    FillVectors();
    Input_prod(ui);
    Input_lim_prod(ui);
    usual.clear();
    limited.clear();

    connect(ui->pushButton_add_prod, SIGNAL(clicked()), this, SLOT(AddToCheck()));
    connect(ui->pushButton_add_prod_2, SIGNAL(clicked()), this, SLOT(AddToCheck2()));
    connect(ui->pushButton_add_prod_3, SIGNAL(clicked()), this, SLOT(DeleteFromCheck()));
    connect(ui->pushButton_pay, SIGNAL(clicked()), this, SLOT(Pay()));
    connect(ui->pushButton_save_check, SIGNAL(clicked()), this, SLOT(SaveCheck()));
}


Secondwindow::~Secondwindow()
{
    delete ui;
}

void Secondwindow::FillVectors(){
    usual.push_back("Bread\t 50.1");
    usual.push_back("Water\t 15.25");
    usual.push_back("Salt\t 24.21");
    usual.push_back("Milk\t 20.2");
    usual.push_back("Meat\t 45.4");
    usual.push_back("Sugar\t 12.5");
    usual.push_back("Sausages\t 34.99");
    usual.push_back("Vegetables\t 29.7");
    usual.push_back("Tomato\t 17.8");
    usual.push_back("Apple\t 27.1");
    usual.push_back("Banana\t 24.99");
    usual.push_back("Flour\t 44.99");
    //limited
    limited.push_back("Caviar\t 120.11");
    limited.push_back("Fish\t 98.12");
    limited.push_back("Wine\t 99.1");
    limited.push_back("Chocolate\t 74.5");
    limited.push_back("Grapefruit\t 69.11");
    limited.push_back("Cake\t 115.29");
    limited.push_back("Noodle\t 89.71");
    limited.push_back("Rice\t 85.46");
    limited.push_back("Salad\t 90.16");
    limited.push_back("Cream\t 125.29");
    limited.push_back("Powder\t 98.19");
}

void Secondwindow::Input_prod(Ui::Secondwindow *ui)
{
     for (auto item: usual)
     {
       ui->listWidget_prod->addItem(QString::fromStdString(item));
     }
}

void Secondwindow::Input_lim_prod(Ui::Secondwindow *ui)
{
     for (auto item: limited)
     {
       ui->listWidget_prod_2->addItem(QString::fromStdString(item));
     }
}

void Secondwindow::AddToCheck(){
    if(ui->listWidget_prod->currentItem() && ui->listWidget_prod->currentItem()->isSelected()){
        std::string tmp = ui->listWidget_prod->currentItem()->text().toStdString();
        std::istringstream s(tmp);
        std::string name;
        s >> name;
        float price;
        s >> price;
//        std::cout << price;
        amount = amount +price;
        amount=round(amount*1000)/1000;
//        ui->label_amount->setText(QString::number(amount,'f',3));
        ui->label_amount->setNum(amount);
        ui->listWidget_check->addItem(ui->listWidget_prod->currentItem()->text());
    }
}

void Secondwindow::AddToCheck2(){
    if (ui->listWidget_prod_2->currentItem() && ui->listWidget_prod_2->currentItem()->isSelected()){
        std::string tmp = ui->listWidget_prod_2->currentItem()->text().toStdString();
        std::istringstream s(tmp);
        std::string name;
        s >> name;
        float price;
        s >> price;
//        std::cout << price;
        amount = amount +price;
        amount=round(amount*1000)/1000;
        ui->label_amount->setNum(amount);
        ui->listWidget_check->addItem(ui->listWidget_prod_2->currentItem()->text());
    }
}

void Secondwindow::DeleteFromCheck(){
    if (ui->listWidget_check->currentItem() && ui->listWidget_check->currentItem()->isSelected()){
        std::string tmp = ui->listWidget_check->currentItem()->text().toStdString();
        std::istringstream s(tmp);
        std::string name;
        s >> name;
        float price;
        s >> price;
//        std::cout << price;
        amount = amount -price;
        amount=round(amount*1000)/1000;
//        ui->label_amount->setText(QString::number(amount,'f',3));
        ui->label_amount->setNum(amount);
        qDeleteAll(ui->listWidget_check->selectedItems());
    }
}

void Secondwindow::Pay(){
    if (ui->listWidget_check->count()!=0){
        std::time_t t = std::time(0);
        std::tm* now = std::localtime(&t);
        int h = now->tm_hour;
        int m = now->tm_min;
        int s = now->tm_sec;
        std::cout << h << ":" << m << ":" << s << std::endl;
        pur.setPrice(amount);
        pur.setTime(h,m,s);
        purchase_made = true;
        products_bought.clear();
        for(int i = 0; i < ui->listWidget_check->count(); ++i)
        {
            std::string tmp = ui->listWidget_check->item(i)->text().toStdString();
            products_bought.push_back(tmp);
        }
        QMessageBox::information(this, "Information", "Cash used\nYour purchase cost " + QString::number(amount));
        ui->listWidget_check->clear();
        amount=0;
        ui->label_amount->setNum(amount);
    }
    else{
        QMessageBox::critical(this, "Error", "No products was chosen\nUnable to pay for nothing");
    }
}

void Secondwindow::SaveCheck(){
    if (purchase_made){
        QString path = QFileDialog::getOpenFileName(this, "Choose a file", "C://", tr("Text Files (*.txt)"));
        std::cout << path.toStdString() << std::endl;
        std::ofstream output;
        output.open(path.toStdString());
        if (output.is_open()){
            output << "CHECK\n\n";
            for(auto i : products_bought)
            {
                output << i << std::endl;
            }
                output << "\nResult: " << pur.getPrice() << std::endl;
                output << "Time: " << pur.getTime() << std::endl;
                Date today;
                output << "Date: " << today.day << "." << today.month << "." << today.year;
        }
        output.close();
        QMessageBox::information(this, "Information", "Your check was saved\n" + path);
        purchase_made=0;
    }
    else{
        QMessageBox::critical(this, "Error", "Unable to save check");
    }
}
