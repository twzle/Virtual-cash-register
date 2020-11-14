#include "thirdwindow.h"
#include "ui_thirdwindow.h"
#include "cardfinder.h"
#include "purchases.h"
#include <QFileDialog>
#include <QMessageBox>
#include <vector>
#include <iostream>
#include <map>
#include <sstream>
#include <fstream>

std::map<std::string,Card> storage_2;
std::vector<std::string> usual_2;
std::vector<std::string> limited_2;
std::vector<std::string> products_bought_2;
bool purchase_made_2 =false;
float amount_2=0;
Purchase pur_2;

Thirdwindow::Thirdwindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Thirdwindow)
{
    ui->setupUi(this);
    FillVectors();
    Input_prod(ui);
    Input_lim_prod(ui);
    usual_2.clear();
    limited_2.clear();

    connect(ui->pushButton_add_prod, SIGNAL(clicked()), this, SLOT(AddToCheck()));
    connect(ui->pushButton_add_prod_2, SIGNAL(clicked()), this, SLOT(AddToCheck2()));
    connect(ui->pushButton_add_prod_3, SIGNAL(clicked()), this, SLOT(DeleteFromCheck()));
    connect(ui->pushButton_pay, SIGNAL(clicked()), this, SLOT(Pay()));
    connect(ui->pushButton_choose, SIGNAL(clicked()), this, SLOT(ChooseCard()));
}

Thirdwindow::~Thirdwindow()
{
    delete ui;
}

void Thirdwindow::FillVectors(){
    usual_2.push_back("Bread\t 50.1");
    usual_2.push_back("Water\t 15.25");
    usual_2.push_back("Salt\t 24.21");
    usual_2.push_back("Milk\t 20.2");
    usual_2.push_back("Meat\t 45.4");
    usual_2.push_back("Sugar\t 12.5");
    usual_2.push_back("Sausages\t 34.99");
    usual_2.push_back("Vegetables\t 29.7");
    usual_2.push_back("Tomato\t 17.8");
    usual_2.push_back("Apple\t 27.1");
    usual_2.push_back("Banana\t 24.99");
    usual_2.push_back("Flour\t 44.99");
    //limited
    limited_2.push_back("Caviar\t 120.11");
    limited_2.push_back("Fish\t 98.12");
    limited_2.push_back("Wine\t 99.1");
    limited_2.push_back("Chocolate\t 74.5");
    limited_2.push_back("Grapefruit\t 69.11");
    limited_2.push_back("Cake\t 115.29");
    limited_2.push_back("Noodle\t 89.71");
    limited_2.push_back("Rice\t 85.46");
    limited_2.push_back("Salad\t 90.16");
    limited_2.push_back("Cream\t 125.29");
    limited_2.push_back("Powder\t 98.19");
}

void Thirdwindow::Input_prod(Ui::Thirdwindow *ui)
{
     for (auto item: usual_2)
     {
       ui->listWidget_prod->addItem(QString::fromStdString(item));
     }
}

void Thirdwindow::Input_lim_prod(Ui::Thirdwindow *ui)
{
     for (auto item: limited_2)
     {
       ui->listWidget_prod_2->addItem(QString::fromStdString(item));
     }
}

void Thirdwindow::AddToCheck(){
    if(ui->listWidget_prod->currentItem() && ui->listWidget_prod->currentItem()->isSelected()){
        std::string tmp = ui->listWidget_prod->currentItem()->text().toStdString();
        std::istringstream s(tmp);
        std::string name;
        s >> name;
        float price;
        s >> price;
//        std::cout << price;
        amount_2 = amount_2 +price;
        amount_2=round(amount_2*1000)/1000;
        ui->label_amount->setNum(amount_2);
        ui->listWidget_check->addItem(ui->listWidget_prod->currentItem()->text());
    }
}

void Thirdwindow::AddToCheck2(){
    if (ui->listWidget_prod_2->currentItem() && ui->listWidget_prod_2->currentItem()->isSelected()){
        std::string tmp = ui->listWidget_prod_2->currentItem()->text().toStdString();
        std::istringstream s(tmp);
        std::string name;
        s >> name;
        float price;
        s >> price;
//        std::cout << price;
        amount_2 = amount_2 +price;
        amount_2=round(amount_2*1000)/1000;
        ui->label_amount->setNum(amount_2);
        ui->listWidget_check->addItem(ui->listWidget_prod_2->currentItem()->text());
    }
}

void Thirdwindow::DeleteFromCheck(){
    if (ui->listWidget_check->currentItem()){
        std::string tmp = ui->listWidget_check->currentItem()->text().toStdString();
        std::istringstream s(tmp);
        std::string name;
        s >> name;
        float price;
        s >> price;
//        std::cout << price;
        amount_2 = amount_2 -price;
        amount_2=round(amount_2*1000)/1000;
        ui->label_amount->setNum(amount_2);
        qDeleteAll(ui->listWidget_check->selectedItems());
    }
}

void Thirdwindow::Pay(){
    if (ui->listWidget_check->count()!=0){
        std::time_t t = std::time(0);
        std::tm* now = std::localtime(&t);
        int h = now->tm_hour;
        int m = now->tm_min;
        int s = now->tm_sec;
        std::cout << h << ":" << m << ":" << s << std::endl;
        pur_2.setPrice(amount_2);
        pur_2.setTime(h,m,s);
        purchase_made_2 = true;
        products_bought_2.clear();
        for(int i = 0; i < ui->listWidget_check->count(); ++i)
        {
            std::string tmp = ui->listWidget_check->item(i)->text().toStdString();
            products_bought_2.push_back(tmp);
        }
        QMessageBox::information(this, "Information", "Credit card used\nYour purchase cost " + QString::number(amount_2));
        ui->listWidget_check->clear();
        amount_2=0;
        ui->label_amount->setNum(amount_2);
        setStatus(0);
    }
    else{
        QMessageBox::critical(this, "Error", "No products was chosen\nUnable to pay for nothing");
    }
}

void Thirdwindow::ChooseCard(){
    Cardfinder window(ui->label_amount);
    window.exec();
    if (purchase_made_2){
        amount_2-=amount_2;
        ui->label_amount->setNum(amount_2);
        ui->listWidget_check->clear();
        setStatus(0);
    }
}

float Thirdwindow::getAmount(){
    return amount_2;
}

std::map<std::string,Card>& Thirdwindow::getStorage(){
    return storage_2;
}

void Thirdwindow::setStorage(std::map<std::string,Card>& other){
    storage_2=other;
}

void Thirdwindow::setStatus(const bool& _st){
    purchase_made_2=_st;
}

void Thirdwindow::setDiscountedLabel(const float& _am){
    ui->label_amount->setNum(_am);
}
