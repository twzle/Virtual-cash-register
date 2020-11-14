#include "cardfinder.h"
#include "ui_cardfinder.h"
#include "thirdwindow.h"
#include <QLineEdit>
#include <QInputDialog>
#include <QMessageBox>
#include <QFileDialog>
#include <sstream>
#include <fstream>
#include <map>

std::map<std::string,Card> storage;

Cardfinder::Cardfinder(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Cardfinder)
{
    special_label =dynamic_cast<QLabel*>(parent);
    ui->setupUi(this);
    Input_Cards(ui);

    connect(ui->pushButton_create, SIGNAL(clicked()), this, SLOT(CreateNew()));
    connect(ui->pushButton_delete, SIGNAL(clicked()), this, SLOT(Delete()));
    connect(ui->pushButton_pay, SIGNAL(clicked()), this, SLOT(PayByCard()));
    connect(ui->pushButton_history, SIGNAL(clicked()), this, SLOT(ShowHistory()));
}

Cardfinder::~Cardfinder()
{
    delete ui;
}

void Cardfinder::Input_Cards(Ui::Cardfinder *ui)
{
    Card vtb;
    if (Thirdwindow::getStorage().size()==0){
        vtb.setTelephoneNumber("+78918765423");
        vtb.setCardNumber("876545229876");
//        storage["123456789012"]=Card();
//        storage["923847527501"]=Card();
//        storage[vtb.getCardNumber()]=vtb;
        for (auto item: storage)
         {
           std::string tmp =item.first + "\t" + item.second.getTelephoneNumber();
           ui->listWidget_cards->addItem(QString::fromStdString(tmp));
         }
    }
    else{
        storage =Thirdwindow::getStorage();
        for(auto item: Thirdwindow::getStorage()){
            std::string tmp =item.first + "\t" + item.second.getTelephoneNumber();
            ui->listWidget_cards->addItem(QString::fromStdString(tmp));
        }
    }
}

void Cardfinder::CreateNew(){
    bool ok;
    QString text = QInputDialog::getText(this, tr("First visit"),
                                             tr("Please, write a telephone num to activate your b.c.:"), QLineEdit::Normal,
                                             "+7", &ok);
    if (ok && !text.isEmpty() && text.toStdString() != "+7" && text.toStdString().size() == 12){
        bool ok2;
        std::string phone_number=text.toStdString();
        std::string card_number;
        QString text_2 = QInputDialog::getText(this, tr("First visit"),
                                                 tr("Input bonus card number:"), QLineEdit::Normal,
                                                 "", &ok2);
        card_number=text_2.toStdString();
        if(storage.find(card_number)==storage.end() && card_number.size()==12 && ok2){
            Card tmp;
            tmp.setCardNumber(card_number);
            tmp.setTelephoneNumber(phone_number);
            storage[tmp.getCardNumber()]=tmp;
            Thirdwindow::setStorage(storage);
            ui->listWidget_cards->addItem(QString::fromStdString(tmp.getCardNumber()+ "\t" +tmp.getTelephoneNumber()));
            QMessageBox::information(this, "Information", "New bonus card was created and activated\nPhone number: " + text +"\nCard number: "+text_2);
        }
        else{
            QMessageBox::critical(this, "Error", "Invalid card number or process cancelled");
        }
    }
    else{
        QMessageBox::critical(this, "Error", "Invalid phone number or process cancelled");
    }
}

void Cardfinder::Delete(){
    if (ui->listWidget_cards->currentItem()->isSelected()){
        std::string current = ui->listWidget_cards->currentItem()->text().toStdString();
        std::istringstream full(current);
        std::string storage_key;
        full >> storage_key;
        std::cout << storage_key << std::endl;
        if (storage.find(storage_key)!=storage.end()){
            auto it = storage.find(storage_key);
            storage.erase(it);
            Thirdwindow::setStorage(storage);
        }
        qDeleteAll(ui->listWidget_cards->selectedItems());
    }
}

void Cardfinder::PayByCard(){
    if (ui->listWidget_cards->currentItem() && ui->listWidget_cards->currentItem()->isSelected()){
        std::string current = ui->listWidget_cards->currentItem()->text().toStdString();
        std::istringstream full(current);
        std::string storage_key;
        full >> storage_key;
//        std::cout << storage_key << std::endl;
        if (storage.find(storage_key)!=storage.end()){
            if (Thirdwindow::getAmount()!=0){
                float am=Thirdwindow::getAmount();
                if (storage.at(storage_key).checkDiscount(am)){
                    am=0.8*am;
                    Purchase tmp(am);
                    std::cout << "Оплачено cо скидкой 20%: " << am << std::endl;
//                    Thirdwindow::setDiscountedLabel(am);
//                    am=round(am*1000)/1000;
                    special_label->setText(QString::number(am,'f',2)+QString("\n-20% discount"));
                    storage.at(storage_key).Pay(tmp);
                    QMessageBox::information(this, "Information", "20% of discount received\nYour purchase cost " + QString::number(am));
                }
                else{
                    Purchase tmp(am);
                    std::cout << "Оплачено: " << am << std::endl;
                    special_label->setText(QString::number(am,'f',2)+QString("\n-0% discount"));
                    storage.at(storage_key).Pay(tmp);
                    QMessageBox::information(this, "Information", "No discount received\nYour purchase cost " + QString::number(am));
                }
                Thirdwindow::setStorage(storage);
                Thirdwindow::setStatus(1);
            }
            else{
                QMessageBox::critical(this, "Error", "No products was chosen\nUnable to pay for nothing");
            }
        }
    }
    else{
        QMessageBox::critical(this, "Error", "No card was chosen\nChoose a card to pay");
    }
}

void Cardfinder::ShowHistory(){
    if (ui->listWidget_cards->currentItem()->isSelected()){
        std::string current = ui->listWidget_cards->currentItem()->text().toStdString();
        std::istringstream full(current);
        std::string storage_key;
        full >> storage_key;
        std::cout << storage_key << std::endl;
        if (storage.find(storage_key)!=storage.end()){
            Card bc = storage.at(storage_key);
            if (!bc.getHistory().empty()){
                for (auto x : bc.getHistory()){
                    std::cout << x.getPrice()  << " " << x.getDate().day << "." << x.getDate().month << "." << x.getDate().year << " " << x.getTime() << std::endl;
                }
            }
            else{
                std::cout << "История пуста" << std::endl;
            }
            WriteHistoryToFile(bc);
        }
    }
}

void Cardfinder::WriteHistoryToFile(Card _bc){
    QString path = QFileDialog::getOpenFileName(this, "Choose a file", "C://", tr("Text Files (*.txt)"));
//    std::cout << path.toStdString() << std::endl;
    std::ofstream output;
    output.open(path.toStdString());
    if (output.is_open()){
        output << "CARD HISTORY\n\n";
        output << "Card number: " << _bc.getCardNumber() << "\nPhone number: " << _bc.getTelephoneNumber() << "\n\n";
        int count=0;
        float total=0;
        for(auto i : _bc.getHistory())
        {
            ++count;
            output << "#" << count << " " <<i.getPrice() << " " << i.getDate().day << "." << i.getDate().month << "." << i.getDate().year << " " << i.getTime() << std::endl;
            total+=i.getPrice();
        }
            output << "\nTotal: " << total << std::endl;
    }
    output.close();
}

