#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialog.h"
#include <Qstring>
#include <iostream>
#include<fstream>

using namespace std;

QStringList hLabels;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableWidget->setRowCount(10);
    ui->tableWidget->setColumnCount(4);

    hLabels << "Member Name" <<"Member ID"<<"Membership Level"<<"Total " ;
    ui->tableWidget->setHorizontalHeaderLabels(hLabels);

    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    connect(ui->tabWidget,SIGNAL(currentChanged(int)),this,SLOT(give()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

MainWindow:: getInfo(string fileName)
{
    ifstream file(fileName.c_str());
    string grab;
    string temp(" ");
    QString read;
    QString again;

    date.clear();
    memberID.clear();
    item.clear();
    price.clear();

    int line = 0;
    int npos = 0;
    string look;

    while(getline(file,grab))
    {
        if(line%4 == 0)
        {
            read = QString::fromStdString(grab);
            date.push_back(read);

        }

        if(line%4 == 1)
        {
            read = QString::fromStdString(grab);
            memberID.push_back(read);

        }

        if(line%4 == 2)
        {
            read = QString::fromStdString(grab);
            item.push_back(read);

        }

        if(line%4 == 3)
        {
            //look = grab.substr(4,(grab.length()-1));
            look = grab;
            read = QString::fromStdString(grab);
            price.push_back(read);



            again = QString::fromStdString(look);
            quantity.push_back(again);




         }

        ++line;
    }


}

MainWindow::display()
{
    for(int i = 0; i < memberID.size();++i)
    {
        if(memberID[i] == QString::fromStdString("12345"))
        {
            ui->tableWidget->setItem(i,0, new QTableWidgetItem("Sally Shopper"));
            ui->tableWidget->setItem(i,2, new QTableWidgetItem("Basic"));

        }
        if(memberID[i] == QString::fromStdString("67899"))
        {
            ui->tableWidget->setItem(i,0, new QTableWidgetItem("Fred Frugal"));
            ui->tableWidget->setItem(i,2,new QTableWidgetItem("Basic"));
        }

        if(memberID[i] == QString::fromStdString("12899"))
        {
            ui->tableWidget->setItem(i,0, new QTableWidgetItem("Betty Buysalot"));
            ui->tableWidget->setItem(i,2,new QTableWidgetItem("Prefered"));

        }
        if(memberID[i] == QString::fromStdString("88888"))
        {
            ui->tableWidget->setItem(i,0, new QTableWidgetItem("Larry Largefamily"));
            ui->tableWidget->setItem(i,2,new QTableWidgetItem("Basic"));

        }
        if(memberID[i] == QString::fromStdString("35647"))
        {
            ui->tableWidget->setItem(i,0, new QTableWidgetItem("Linda Livesalone"));
            ui->tableWidget->setItem(i,2,new QTableWidgetItem("Basic"));

        }
        if(memberID[i] == QString::fromStdString("31311"))
        {
            ui->tableWidget->setItem(i,0, new QTableWidgetItem("Sam Single"));
            ui->tableWidget->setItem(i,2,new QTableWidgetItem("Preferred"));

        }

        if(memberID[i] == QString::fromStdString("12121"))
        {
            ui->tableWidget->setItem(i,0, new QTableWidgetItem("Kathy Havealotsofkids"));
            ui->tableWidget->setItem(i,2,new QTableWidgetItem("Basic"));

        }

        if(memberID[i] == QString::fromStdString("77777"))
        {
            ui->tableWidget->setItem(i,0, new QTableWidgetItem("Vern Video"));
            ui->tableWidget->setItem(i,2,new QTableWidgetItem("Preffered"));

        }

        if(memberID[i] == QString::fromStdString("16161"))
        {
            ui->tableWidget->setItem(i,0, new QTableWidgetItem("Benjamin Business"));
            ui->tableWidget->setItem(i,2,new QTableWidgetItem("Basic"));

        }

        if(memberID[i] == QString::fromStdString("61616"))
        {
            ui->tableWidget->setItem(i,0, new QTableWidgetItem("Sam Saddleback"));
            ui->tableWidget->setItem(i,2,new QTableWidgetItem("Basic"));

        }


        ui->tableWidget->setItem(i,1, new QTableWidgetItem(memberID[i]));

        if(ui->tabWidget->currentIndex() != 0)
        {
            ui->tableWidget->setItem(i,3, new QTableWidgetItem(item[i]));
            ui->tableWidget->setItem(i,4, new QTableWidgetItem(price[i]));
            //ui->tableWidget->setItem(1,5, new QTableWidgetItem(quantity[i]));
        }
        else
        ui->tableWidget->setItem(i,3, new QTableWidgetItem(" "));


    }
  //ui->tableWidget->setRowCount(memberID.size());
}

void MainWindow::give()
{   int page;
    page = ui->tabWidget->currentIndex();

    if(page != 0)
    {

        ui->pushButton->hide();
        ui->pushButton_3->hide();
        ui->tableWidget->setRowCount(12);
        ui->tableWidget->setColumnCount(5);
        ui->tableWidget->setHorizontalHeaderItem(3, new QTableWidgetItem("Item Bought"));
        ui->tableWidget->setHorizontalHeaderItem(4, new QTableWidgetItem("Cost/Quantity"));
        //ui->tableWidget->setHorizontalHeaderItem(5, new QTableWidgetItem("Quantity"));
    }
    else
    {
        ui->pushButton->show();
        ui->pushButton_3->show();
        ui->tableWidget->setColumnCount(4);
        ui->tableWidget->setRowCount(10);
        ui->tableWidget->setHorizontalHeaderItem(3, new QTableWidgetItem("Total"));
        getInfo("shoppers.txt");
    }

    if(page == 1)
    getInfo("day1.txt");
    if(page == 2)
    getInfo("day2.txt");
    if(page == 3)
    getInfo("day3.txt");
    if(page == 4)
    getInfo("day4.txt");
    if(page == 5)
    getInfo("day5.txt");



    display();
}

void MainWindow::on_pushButton_3_clicked()
{
    Dialog win;
    win.setModal(true);
    win.exec();

    if(win.firstName.length() != 0)
    {
        ui->tableWidget->setRowCount(row);
        ui->tableWidget->setItem(row-1,0,new QTableWidgetItem(win.firstName+" "+win.lastName));
        ui->tableWidget->setItem(row-1,1,new QTableWidgetItem("78452"));

        if(win.basic)
            ui->tableWidget->setItem(row-1,2,new QTableWidgetItem("Basic"));
        if(win.pref)
            ui->tableWidget->setItem(row-1,2,new QTableWidgetItem("Preffered"));

        ++row;
    }

    win.firstName.clear();


}
