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
    qDebug() << "Number of members:" << members.size();
    table->setRowCount(members.size());
    table->setColumnCount(4);

    QStringList hLabels;
    hLabels << "Member Name"<<"Member ID"<<"Membership Level"<<"Expiration Date";
    table->setHorizontalHeaderLabels(hLabels);
    table->setColumnWidth(0, 175);
    table->setColumnWidth(1, 100);
    table->setColumnWidth(2, 110);
    table->horizontalHeader()->setStretchLastSection(true);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->setSelectionMode(QAbstractItemView::SingleSelection);

    table1 = ui->tabWidget->widget(1)->findChild<QTableWidget*>();
    getSalesInfo("day1.txt");
    getSalesInfo("day2.txt");
    getSalesInfo("day3.txt");
    getSalesInfo("day4.txt");
    getSalesInfo("day5.txt");

    qDebug() << "Number of purchases:" << members.getAllPurchases().size();
    qDebug().nospace() << "Grand total: $" << members.getGrandTotal();
    table1->setRowCount(members.getAllPurchases().size());
    table1->setColumnCount(5);
    QStringList hLabels1;
    hLabels1 << "Transaction Date"<<"Member ID"<<"Item Name"<<"Price"<<"Quantity";
    table1->setHorizontalHeaderLabels(hLabels1);
    table1->setColumnWidth(0, 100);
    table1->setColumnWidth(1, 70);
    table1->setColumnWidth(2, 200);
    table1->setColumnWidth(3, 80);
    table1->setColumnWidth(4, 50);
    table1->horizontalHeader()->setStretchLastSection(true);
    table1->setSelectionBehavior(QAbstractItemView::SelectRows);
    table1->setSelectionMode(QAbstractItemView::SingleSelection);

    this->setGeometry(rec.width()/2-400, rec.height()/2-300, 800, 500);
    connect(ui->tabWidget,SIGNAL(currentChanged(int)),this,SLOT(give()));
    connect(ui->pushButton, SIGNAL(clicked(bool)),this,SLOT(profile()));
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
            for(int i = 0; i < 4; ++i)
            {
                table->item(row,i)->setFlags((table->item(row,i)->flags() ^ Qt::ItemIsEditable));
                table->item(row,i)->setTextAlignment(Qt::AlignCenter);
            }
            cursor = cursor->next;
            ++row;
        }
    }
    if(ui->tabWidget->currentIndex() == 1){
        node<memberPurchase>* memberPurchases = members.getAllPurchases().getTotalPurchases().begin();
        node<purchase>* cursor1 = memberPurchases->item.getPurchases().begin();
        int row1 = 0;
        while(memberPurchases != NULL){
            while(cursor1 != NULL)
            {
                table1->setItem(row1,0, new QTableWidgetItem(QString::fromStdString(cursor1->item.transactionDate)));
                table1->setItem(row1,1, new QTableWidgetItem(QString::fromStdString(memberPurchases->item.getMemberID())));
                table1->setItem(row1,2, new QTableWidgetItem(QString::fromStdString(cursor1->item.item.getItemName())));
                table1->setItem(row1,3, new QTableWidgetItem(QString::number(cursor1->item.item.getItemPrice(), 'f', 2)));
                table1->setItem(row1,4, new QTableWidgetItem(QString::number(cursor1->item.item.getItemQuantity())));
                for(int i = 0; i < 5; ++i)
                {
                    table1->item(row1,i)->setFlags((table1->item(row1,i)->flags() ^ Qt::ItemIsEditable));
                    table1->item(row1,i)->setTextAlignment(Qt::AlignCenter);
                }
                cursor1 = cursor1->next;
                ++row1;
            }
            memberPurchases = memberPurchases->next;
            if((memberPurchases))
                cursor1 = memberPurchases->item.getPurchases().begin();
        }
    }
}

void MainWindow::profile()
{
    int selectedRow = table->currentRow();
    QString id = table->item(selectedRow, 1)->text();
    node<member>* mem = members.search(id.toStdString());
    qDebug().nospace() << fixed << qSetRealNumberPrecision(2)
        << "Rebate: $" << mem->item.getRebateAmount()
        << "  Upgrade/downgrade: " << mem->item.shouldUpgradeOrDowngrade();
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

//    if(page == 1){
//    }
//    if(page == 2)
//        getSalesInfo("day2.txt");
//    if(page == 3)
//        getSalesInfo("day3.txt");
//    if(page == 4)
//        getSalesInfo("day4.txt");
//    if(page == 5)
//        getSalesInfo("day5.txt");

    display();
}
