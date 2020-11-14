#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "secondwindow.h"
#include "thirdwindow.h"
#include <QRegExpValidator>
#include <QFileDialog>

Purchase p;
Queue q;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Hide();

//    QPushButton *but_1 = new QPushButton("E");
    QRegExp int_exp("[0-9]\\d{1}");
    QRegExp char_exp("[1-9][0-9]*.[0-9]*");
    QRegExp card_exp("[0-9]\\d{11}");
    ui->lineEdit->setValidator(new QRegExpValidator(char_exp, this));
    ui->lineEdit_2->setValidator(new QRegExpValidator(int_exp, this));
    ui->lineEdit_3->setValidator(new QRegExpValidator(int_exp, this));
    ui->lineEdit_4->setValidator(new QRegExpValidator(int_exp, this));
    ui->lineEdit_5->setValidator(new QRegExpValidator(int_exp, this));
    ui->lineEdit_6->setValidator(new QRegExpValidator(int_exp, this));
    ui->lineEdit_7->setValidator(new QRegExpValidator(int_exp, this));
    ui->lineEdit_8->setValidator(new QRegExpValidator(int_exp, this));
    ui->lineEdit_9->setValidator(new QRegExpValidator(int_exp, this));
    ui->lineEdit_10->setValidator(new QRegExpValidator(int_exp, this));
    ui->lineEdit_11->setValidator(new QRegExpValidator(card_exp, this));


    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(Create_Purchase()));
    connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(AddToQueue()));
    connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(DeleteFromQueue()));
    connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(EraseQueue()));
    connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(Print()));
    connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(Write()));
    connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(Read()));
    connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(DoValidation()));
    connect(ui->pushButton_9, SIGNAL(clicked()), this, SLOT(Size()));
    connect(ui->pushButton_10, SIGNAL(clicked()), this, SLOT(Summary()));
    connect(ui->pushButton_11, SIGNAL(clicked()), this, SLOT(BuyItem()));
    connect(ui->pushButton_12, SIGNAL(clicked()), this, SLOT(BuyWhole()));
    connect(ui->pushButton_13, SIGNAL(clicked()), this, SLOT(OpenSecondWindow()));
    connect(ui->pushButton_14, SIGNAL(clicked()), this, SLOT(OpenThirdWindow()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::Create_Purchase(){
    double pr=ui->lineEdit->text().toDouble();
    int h =ui->lineEdit_2->text().toInt();
    int m = ui->lineEdit_3->text().toInt();
    int s=ui->lineEdit_4->text().toInt();
    if (h >23 || m >59 || s>59){
        std::cout << "Неверный формат" << std::endl;
    }
    else{
        p.setTime(h,m,s);
        p.setPrice(pr);
        std::cout << "Цена: " << p.getPrice() << std::endl  << "Время: " << p.getTime();
        std::cout << std::endl;
        Show_Purchase();
    }
}

void MainWindow::Show_Purchase(){
    QString tmp = QString::fromUtf16( u"Cумма: ");
    QString t = QString::fromUtf16( u"Время: ");
    tmp.append(QString::fromStdString(QString::number(p.getPrice(), 'g').toStdString() + "\n"));
    tmp.append(t);
    if (p.getTime().hours>9)
        tmp.append(QString::fromStdString(std::to_string(p.getTime().hours) + ":"));
    else
        tmp.append(QString::fromStdString("0" + std::to_string(p.getTime().hours) + ":"));
    if (p.getTime().minutes>9)
        tmp.append(QString::fromStdString(std::to_string(p.getTime().minutes)+ ":"));
    else
        tmp.append("0" + QString::fromStdString(std::to_string(p.getTime().minutes)+ ":"));
    if (p.getTime().seconds>9)
        tmp.append(QString::fromStdString(std::to_string(p.getTime().seconds)));
    else
        tmp.append("0" + QString::fromStdString(std::to_string(p.getTime().seconds)));
    ui->label_current->setText(QString::fromStdString("Checkout\n").append(tmp));
}

void MainWindow::AddToQueue(){
    q.push(p);
}

void MainWindow::DeleteFromQueue(){
    q.pop();
}

void MainWindow::EraseQueue(){
    q.clear();
}

void MainWindow::Print(){
    if (!q.empty())
        PrintQueue(q);
    else
        std::cout << "EMPTY QUEUE" << std::endl;
}

void MainWindow::Write(){
    QString path = QFileDialog::getOpenFileName(this, "Choose a file", "C://", tr("Text Files (*.txt)"));
    int lastPoint = path.lastIndexOf(".");
    QString fileNameNoExt = path.left(lastPoint);
    std::cout << fileNameNoExt.toStdString() << std::endl;
    q.WriteToFile(fileNameNoExt.toStdString());
}

void MainWindow::Read(){
    QString path = QFileDialog::getOpenFileName(this, "Choose a file", "C://", tr("Text Files (*.txt)"));
    int lastPoint = path.lastIndexOf(".");
    QString fileNameNoExt = path.left(lastPoint);
    std::cout << fileNameNoExt.toStdString() << std::endl;
    ReadFromFile(fileNameNoExt.toStdString(),q);
}

void MainWindow::DoValidation(){
    if (q.Validate(p)){
        std::cout << "Validation complete\n";
        ui->label_current->setText(QString::fromStdString("Checkout\n").append("Validation complete"));
    }
    else{
        std::cout << "Validation failed\n";
        ui->label_current->setText(QString::fromStdString("Checkout\n").append("Validation failed"));
    }
}

void MainWindow::Size(){
    std::cout << "Size: " << q.getSize() << std::endl;
    QString size = (QString::fromUtf16( u"Размер очереди: ")).append(QString::fromStdString(std::to_string(q.getSize())));
    ui->label_current->setText(QString::fromStdString("Checkout\n").append(size));
}

void MainWindow::Summary(){
    int h1 =ui->lineEdit_5->text().toInt();
    int m1 = ui->lineEdit_6->text().toInt();
    int s1=ui->lineEdit_7->text().toInt();
    int h2 =ui->lineEdit_8->text().toInt();
    int m2 = ui->lineEdit_9->text().toInt();
    int s2=ui->lineEdit_10->text().toInt();
    if (h1 >23 || m1 >59 || s1>59 || h2>23 || m2>59 || s2>59 || Time(h1,m1,s1)>=Time(h2,m2,s2)){
        std::cout << "Неверный формат" << std::endl;
        ui->label_current->setText(QString::fromStdString("Checkout\n").append(QString::fromUtf16( u"Неверный формат")));
    }
    else{
        double sum= q.Calculate(Time(h1,m1,s1),Time(h2,m2,s2));
        QString text=QString::fromStdString(QString::number(sum, 'g').toStdString());
        std::cout << "Итог: " << sum << std::endl;
        ui->label_current->setText(QString::fromStdString("Checkout\n").append(QString::fromUtf16( u"Итог: ")).append(text));
    }
}

void MainWindow::BuyItem(){
    std::string n = ui->lineEdit_11->text().toStdString();
    if (n.size()==12){
        Card bonus_card(p,n);
        std::cout << "Card Number: " << bonus_card.getCardNumber() << std::endl;
        std::cout << "Price: " << bonus_card.getPrice() << std::endl;
        std::cout << "Time: " << bonus_card.getTime() << std::endl;
        QString text ="Checkout\n";
        text.append(QString::fromStdString("Card #: " + bonus_card.getCardNumber()+"\n"));
        text.append(QString::fromStdString("Price: " + std::to_string(bonus_card.getPrice()) +"\n"));
        text.append(QString::fromStdString("Time: "));
        if (bonus_card.getTime().hours>9)
            text.append(QString::fromStdString(std::to_string(bonus_card.getTime().hours) + ":"));
        else
            text.append(QString::fromStdString("0" + std::to_string(bonus_card.getTime().hours) + ":"));
        if (bonus_card.getTime().minutes>9)
            text.append(QString::fromStdString(std::to_string(bonus_card.getTime().minutes)+ ":"));
        else
            text.append("0" + QString::fromStdString(std::to_string(bonus_card.getTime().minutes)+ ":"));
        if (p.getTime().seconds>9)
            text.append(QString::fromStdString(std::to_string(bonus_card.getTime().seconds)));
        else
            text.append("0" + QString::fromStdString(std::to_string(bonus_card.getTime().seconds)));
        ui->label_current->setText(text);
    }
    else{
        std::cout << "Неверный номер карты\n";
        QString text ="Checkout\n";
        ui->label_current->setText(text+"Invalid card number");
    }
}

void MainWindow::BuyWhole(){
    std::string n = ui->lineEdit_11->text().toStdString();
    if (n.size()==12){
        Card bonus_card(q,n);
        std::cout << "Card Number: " << bonus_card.getCardNumber() << std::endl;
        std::cout << "Price: " << bonus_card.getPrice() << std::endl;
        std::cout << "Time: " << bonus_card.getTime() << std::endl;
        QString text ="Checkout\n";
        text.append(QString::fromStdString("Card #: " + bonus_card.getCardNumber()+"\n"));
        text.append(QString::fromStdString("Price: " + std::to_string(bonus_card.getPrice()) +"\n"));
        text.append(QString::fromStdString("Time: "));
        if (bonus_card.getTime().hours>9)
            text.append(QString::fromStdString(std::to_string(bonus_card.getTime().hours) + ":"));
        else
            text.append(QString::fromStdString("0" + std::to_string(bonus_card.getTime().hours) + ":"));
        if (bonus_card.getTime().minutes>9)
            text.append(QString::fromStdString(std::to_string(bonus_card.getTime().minutes)+ ":"));
        else
            text.append("0" + QString::fromStdString(std::to_string(bonus_card.getTime().minutes)+ ":"));
        if (p.getTime().seconds>9)
            text.append(QString::fromStdString(std::to_string(bonus_card.getTime().seconds)));
        else
            text.append("0" + QString::fromStdString(std::to_string(bonus_card.getTime().seconds)));
        ui->label_current->setText(text);
    }
    else{
        std::cout << "Неверный номер карты\n";
        QString text ="Checkout\n";
        ui->label_current->setText(text+"Invalid card number");
    }
}

void MainWindow::OpenSecondWindow(){
    Secondwindow window;
//    window.setModal(true);
    window.exec();
}

void MainWindow::OpenThirdWindow(){
    Thirdwindow window;
//    window.setModal(true);
    window.exec();
}

void MainWindow::Hide(){
    ui->label->hide();
    ui->label_2->hide();
    ui->label_3->hide();
    ui->label_4->hide();
    ui->label_5->hide();
    ui->label_6->hide();
    ui->label_7->hide();
    ui->label_8->hide();
    ui->label_9->hide();
    ui->label_10->hide();
    ui->label_11->hide();
    ui->label_12->hide();
    ui->label_13->hide();
    ui->label_14->hide();
    ui->label_15->hide();
    ui->label_16->hide();
    ui->label_17->hide();
    ui->lineEdit->hide();
    ui->lineEdit_2->hide();
    ui->lineEdit_3->hide();
    ui->lineEdit_4->hide();
    ui->lineEdit_5->hide();
    ui->lineEdit_6->hide();
    ui->lineEdit_7->hide();
    ui->lineEdit_8->hide();
    ui->lineEdit_9->hide();
    ui->lineEdit_10->hide();
    ui->lineEdit_11->hide();
    ui->pushButton->hide();
    ui->pushButton_2->hide();
    ui->pushButton_3->hide();
    ui->pushButton_4->hide();
    ui->pushButton_5->hide();
    ui->pushButton_6->hide();
    ui->pushButton_7->hide();
    ui->pushButton_8->hide();
    ui->pushButton_9->hide();
    ui->pushButton_10->hide();
    ui->pushButton_11->hide();
    ui->pushButton_12->hide();
//    ui->pushButton_13->hide();
//    ui->pushButton_14->hide();
//    this->resize(this->sizeHint());
    this->resize(480,180);
    this->setFixedSize(QSize(480, 180));
//   adjustSize();
}
