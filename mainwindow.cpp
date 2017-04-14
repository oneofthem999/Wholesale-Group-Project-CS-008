#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialog.h"
#include "member.h"
#include "dailyreport.h"
#include <QDebug>
#include <time.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QRect rec = QApplication::desktop()->screenGeometry();
    this->show();

    ui->groupBox->hide();
    ui->scrollArea->hide();

    table = ui->tabWidget->widget(0)->findChild<QTableWidget*>();
    getMemberInfo("warehouse shoppers.txt");
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

    table2 = ui->tabWidget->widget(2)->findChild<QTableWidget*>();
    qDebug() << "Number of items sold:" << members.getInventory().getNumberOfItems();
    qDebug().nospace() << "Total revenue: $" << members.getInventory().getTotalValue();

    table2->setRowCount(members.getInventory().getNumberOfItems());
    table2->setColumnCount(3);
    QStringList labels;
    labels << "Item Name" << "Item Price" << "Total Quantity Sold";
    table2->setHorizontalHeaderLabels(labels);
    table2->setColumnWidth(0, 300);
    table2->setColumnWidth(1, 100);
    table2->setColumnWidth(2, 50);
    table2->horizontalHeader()->setStretchLastSection(true);
    table2->setSelectionBehavior(QAbstractItemView::SelectRows);
    table2->setSelectionMode(QAbstractItemView::SingleSelection);


    this->setGeometry(rec.width()/2-400, rec.height()/2-300, 800, 500);
    connect(ui->tabWidget,SIGNAL(currentChanged(int)),this,SLOT(give()));
    connect(ui->pushButton, SIGNAL(clicked(bool)),this,SLOT(profile()));
    connect(ui->pushButton_3, SIGNAL(clicked(bool)),this,SLOT(remove()));
    connect(ui->actionDaily_Sales_Report, SIGNAL(triggered(bool)),this,SLOT(salesReport()));
    connect(ui->actionLookup_ID, SIGNAL(triggered(bool)),this,SLOT(memberIDSearch()));
    connect(ui->actionLookup_Name,SIGNAL(triggered(bool)),this,SLOT(memberNameSearch()));
    connect(ui->actionItem_Lookup,SIGNAL(triggered(bool)),this,SLOT(itemSearch()));
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
        table->setRowCount(members.size());
        int row = 0;
        while(cursor != NULL)
        {
            ui->pushButton->show();
            ui->pushButton_2->show();
            ui->pushButton_3->show();
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
    else if(ui->tabWidget->currentIndex() == 1){
        QString labelText = "Grand Total: $";
        labelText.append(QString::number(members.getGrandTotal()));
        ui->label->setText(labelText);
        node<memberPurchase>* memberPurchases = members.getAllPurchases().getTotalPurchases().begin();
        node<purchase>* cursor1 = memberPurchases->item.getPurchases().begin();
        int row1 = 0;
        while(memberPurchases != NULL){
            while(cursor1 != NULL)
            {
                table1->setItem(row1,0, new QTableWidgetItem(QString::fromStdString(cursor1->item.transactionDate)));
                table1->setItem(row1,1, new QTableWidgetItem(QString::fromStdString(memberPurchases->item.getMemberID())));
                table1->setItem(row1,2, new QTableWidgetItem(QString::fromStdString(cursor1->item.product.getName())));
                table1->setItem(row1,3, new QTableWidgetItem(QString::number(cursor1->item.product.getPrice(), 'f', 2)));
                table1->setItem(row1,4, new QTableWidgetItem(QString::number(cursor1->item.product.getQuantity())));
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

    else if(ui->tabWidget->currentIndex() == 2){
        node<Product>* item = members.getInventory().getInventory().begin();
        int row = 0;
        while(item != NULL){
            table2->setItem(row,0, new QTableWidgetItem(QString::fromStdString(item->item.getName())));
            table2->setItem(row,1, new QTableWidgetItem(QString::number(item->item.getPrice(), 'f', 2)));
            table2->setItem(row,2, new QTableWidgetItem(QString::number(item->item.getQuantity())));
            for(int i = 0; i < 3; ++i)
            {
                table2->item(row,i)->setFlags((table2->item(row,i)->flags() ^ Qt::ItemIsEditable));
                table2->item(row,i)->setTextAlignment(Qt::AlignCenter);
            }
            table2->item(row,0)->setTextAlignment(Qt::AlignLeft);

            item = item->next;
            ++row;
        }
    }
}

void MainWindow::showPurchases(node<member>* member)
{
    memberPurchase* allPurch = member->item.getMemberPurchase();
    if(allPurch->size() == 0)
        ui->textEdit->append("No purchases made by this member.");
    else
    {
        node<purchase>* singlePurch = allPurch->getPurchases().begin();
        while(singlePurch != NULL)
        {
            QString line = "Purchase Date: ";
            line.append(QString::fromStdString(singlePurch->item.transactionDate));
            ui->textEdit->append(line);

            line = "Item Name: ";
            line.append(QString::fromStdString(singlePurch->item.product.getName()).simplified());
            ui->textEdit->append(line);

            line = "Price: $";
            line.append(QString::number(singlePurch->item.product.getPrice(),'f',2));
            line.append("   Quantity: ");
            line.append(QString::number(singlePurch->item.product.getQuantity()));
            ui->textEdit->append(line);
            ui->textEdit->append("");

            singlePurch = singlePurch->next;
        }
    }
}

void MainWindow::profile()
{
    int page;
    page = ui->tabWidget->currentIndex();

    int selectedRow = table->currentRow();
    QString id = table->item(selectedRow, 1)->text();
    node<member>* mem = members.search(id.toStdString());

    ui->scrollArea->show();
    ui->textEdit->clear();
    ui->label_3->setText("Member Profile");
    QString line = "Name: ";
    line.append(QString::fromStdString(mem->item.getFullName()));
    ui->textEdit->append(line);
    line = "ID Number: ";
    line.append(QString::fromStdString(mem->item.getID()));
    ui->textEdit->append(line);
    line = "Membership Type: ";
    line.append(QString::fromStdString(mem->item.getMembershipType()));
    ui->textEdit->append(line);

    if(mem->item.getMembershipType() == "Preferred")
    {
        line = "Rebate amount: $";
        line.append(QString::number(mem->item.getRebateAmount(),'f',2));
        ui->textEdit->append(line);
        line = "Should downgrade: ";
        if(mem->item.shouldUpgradeOrDowngrade())
            line.append("Yes");
        else
            line.append("No");
        ui->textEdit->append(line);
    }
    else
    {
        line = "Potential rebate amount: $";
        double potential = mem->item.getAmountSpent() / 1.0875 * REBATE_RATE;
        line.append(QString::number(potential,'f',2));
        ui->textEdit->append(line);
        line = "Should upgrade: ";
        if(mem->item.shouldUpgradeOrDowngrade())
            line.append("Yes");
        else
            line.append("No");
        ui->textEdit->append(line);
    }
    ui->textEdit->append("\nPurchases\n-----------");
    showPurchases(mem);

    ui->textEdit->moveCursor(QTextCursor::Start);
}

void MainWindow::remove()
{
    int page;
    page = ui->tabWidget->currentIndex();
    if(page == 0)
    {
        int selectedRow = table->currentRow();
        QString id = table->item(selectedRow, 1)->text();
        members.deleteMember(id.toStdString());
        table->removeRow(selectedRow);
        table->setRowCount(table->rowCount());
        display();
    }
}

void MainWindow::give()
{
    int page;
    page = ui->tabWidget->currentIndex();

    if(page != 0)
    {
        ui->pushButton->hide();
        ui->pushButton_2->hide();
        ui->pushButton_3->hide();
    }
    else
    {
        ui->pushButton->hide();
        ui->pushButton_2->hide();
        ui->pushButton_3->hide();
    }

    if(page == 1)
        ui->label->show();
    else
        ui->label->hide();

    display();
}

void MainWindow::salesReport()
{
    ui->groupBox->setTitle("Daily Sales Report Search");
    ui->label_2->setText("Enter date for sales report");
    ui->lineEdit->clear();
    ui->groupBox->show();
}

void MainWindow::memberIDSearch()
{
    ui->groupBox->setTitle("Member's Purchases Search");
    ui->label_2->setText("Enter Member ID");
    ui->lineEdit->clear();
    ui->groupBox->show();
}

void MainWindow::memberNameSearch()
{
    ui->groupBox->setTitle("Member's Purchases Search");
    ui->label_2->setText("Enter Member Name");
    ui->lineEdit->clear();
    ui->groupBox->show();
}

void MainWindow::itemSearch()
{
    ui->groupBox->setTitle("Item Lookup");
    ui->label_2->setText("Enter Item Name");
    ui->lineEdit->clear();
    ui->groupBox->show();
}

void MainWindow::on_pushButton_2_clicked()
{
    Dialog win;
    string type;
    string id;
    string date;
    string tempFirst;
    string tempLast;
    win.setModal(true);
    win.exec();

   if(win.pref == true)
        type ="Preferred";
    else
        type ="Basic";

    srand(time(NULL));
    id = to_string(rand() % 90000 + 10000);

    date = "04/17/2013";
    tempFirst = win.firstName.toStdString();
    tempLast = win.lastName.toStdString();

   member newMember(tempFirst, tempLast,id,type,date);
   members.addMember(newMember);

   display();
}

void MainWindow::on_pushButton_5_clicked()
{
    ui->scrollArea->show();
    ui->textEdit->clear();

    if(ui->groupBox->title() == "Daily Sales Report Search")
    {
        QString title = "Daily Sales Report ";
        QString date = ui->lineEdit->text();
        title.append(date);
        ui->label_3->setText(title);

        class::dailyReport report(members, date.toStdString());
        if(report.getTotalRevenue() == 0)
            ui->textEdit->append("No sales data for that day.");
        else
        {
            ui->textEdit->append("Members who shopped: ");
            ui->textEdit->append(QString::fromStdString(report.getReport(members)));
            QString basic = "Basic members: ";
            basic.append(QString::number(report.getBasicMembers()));
            ui->textEdit->append(basic);
            QString preferred = "Preferred members: ";
            preferred.append(QString::number(report.getPreferredMembers()));
            ui->textEdit->append(preferred);
            ui->textEdit->append("");

            node<Product>* sold = report.getDailyInventory().getInventory().begin();
            while(sold != NULL)
            {
                QString line = "Item Name: ";
                line.append(QString::fromStdString(sold->item.getName()).simplified());
                ui->textEdit->append(line);

                line = "Quantity Sold: ";
                line.append(QString::number(sold->item.getQuantity()));
                ui->textEdit->append(line);
                ui->textEdit->append("");

                sold = sold->next;
            }
        }
        ui->textEdit->moveCursor(QTextCursor::Start);
    }

    else if(ui->groupBox->title() == "Member's Purchases Search")
    {
        QString title = "Member's Purchases ";
        node<member>* found = NULL;

        if(ui->label_2->text() == "Enter Member ID")
        {
            QString ID = ui->lineEdit->text();
            title.append(ID);
            ui->label_3->setText(title);
            found = members.search(ID.toStdString());
        }
        else
        {
            QString fullName = ui->lineEdit->text();
            title.append(fullName);
            ui->label_3->setText(title);
            QStringList name = fullName.split(" ");
            if(name.size() > 1)
            {
                QString first = name[0];
                QString last = name[1];
                found = members.search(first.toStdString(),last.toStdString());
            }
        }

        if(found == NULL)
            ui->textEdit->append("No member found.");
        else
            showPurchases(found);
        ui->textEdit->moveCursor(QTextCursor::Start);
    }

    else if(ui->groupBox->title() == "Item Lookup")
    {
        QString title = "Item Lookup ";
        QString name = ui->lineEdit->text();
        title.append(name);
        ui->label_3->setText(title);
        qDebug() << name;

        node<Product>* found = members.getInventory().search(name.toStdString());
        if(found == NULL)
            ui->textEdit->append("No item found.");
        else{
            ui->textEdit->append("Quantity: ");
            ui->textEdit->append(QString::number(found->item.getQuantity()));
            ui->textEdit->append("Total Sales Price: ");
            ui->textEdit->append(QString::number(found->item.getTotal(),'f',2));
        }
    }
}

