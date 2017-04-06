#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "member.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QRect rec = QApplication::desktop()->screenGeometry();
    this->show();

    table = ui->tabWidget->widget(0)->findChild<QTableWidget*>();
    getMemberInfo("shoppers.txt");
    qDebug() << "Members in list: " << members.size();
    table->setRowCount(members.size());
    table->setColumnCount(4);

    QStringList hLabels;
    hLabels << "Member Name"<<"Member ID"<<"Membership Level"<<"Expiration Date";
    table->setHorizontalHeaderLabels(hLabels);
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    this->setGeometry(rec.width()/2-400, rec.height()/2-300, 800, 500);
    connect(ui->tabWidget,SIGNAL(currentChanged(int)),this,SLOT(give()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::getMemberInfo(std::string filename)
{
    members.readMemberFile(filename);
}

void MainWindow::getSalesInfo(std::string filename)
{
    members.readSalesFile(filename);
}

void MainWindow::display()
{
    if(ui->tabWidget->currentIndex() == 0){
        node<member>* cursor = members.getMembers().begin();
        int row = 0;
        while(cursor != NULL)
        {
            table->setItem(row,0, new QTableWidgetItem(QString::fromStdString(cursor->item.getFullName())));
            table->setItem(row,1, new QTableWidgetItem(QString::fromStdString(cursor->item.getID())));
            table->setItem(row,2, new QTableWidgetItem(QString::fromStdString(cursor->item.getMembershipType())));
            table->setItem(row,3, new QTableWidgetItem(QString::fromStdString(cursor->item.getExpirationDate())));
            table->item(row,1)->setTextAlignment(Qt::AlignCenter);
            table->item(row,2)->setTextAlignment(Qt::AlignCenter);
            table->item(row,3)->setTextAlignment(Qt::AlignCenter);
            cursor = cursor->next;
            ++row;
        }
    }
}

void MainWindow::give()
{   int page;
    page = ui->tabWidget->currentIndex();

//    if(page != 0)
//    {
//        ui->tableWidget->setRowCount(12);
//        ui->tableWidget->setColumnCount(5);
//        ui->tableWidget->setHorizontalHeaderItem(3, new QTableWidgetItem("Item Bought"));
//        ui->tableWidget->setHorizontalHeaderItem(4, new QTableWidgetItem("Cost"));
//        //ui->tableWidget->setHorizontalHeaderItem(5, new QTableWidgetItem("Quantity"));
//    }
//    else
//    {
//        ui->tableWidget->setColumnCount(4);
//        ui->tableWidget->setRowCount(10);
//        ui->tableWidget->setHorizontalHeaderItem(3, new QTableWidgetItem("Total"));
//        getMemberInfo("shoppers.txt");
//    }

    if(page == 1){
//        getSalesInfo("day1.txt");
//        qDebug() << "Purchases in list: " << members.getAllPurchases().size();
        QTableWidget* table1 = ui->tabWidget->widget(1)->findChild<QTableWidget*>();
        table1->setRowCount(12);
        table1->setColumnCount(5);
        QStringList hLabels;
        hLabels << "Transaction Date"<<"Member ID"<<"Item Name"<<"Price"<<"Quantity";
        table1->setHorizontalHeaderLabels(hLabels);
        table1->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    }
    if(page == 2)
//        getSalesInfo("day2.txt");
    if(page == 3)
//        getSalesInfo("day3.txt");
    if(page == 4)
//        getSalesInfo("day4.txt");
    if(page == 5)
//        getSalesInfo("day5.txt");

    display();
}
