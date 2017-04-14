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
    connect(ui->pushButton,SIGNAL(clicked(bool)),this,SLOT(profile()));
    connect(ui->pushButton_2,SIGNAL(clicked(bool)),this,SLOT(add()));
    connect(ui->pushButton_3,SIGNAL(clicked(bool)),this,SLOT(remove()));
    connect(ui->actionDaily_Sales_Report, SIGNAL(triggered(bool)),this,SLOT(salesReport()));
    connect(ui->actionMember_Rebates,SIGNAL(triggered(bool)),this,SLOT(rebateReport()));
    connect(ui->actionMembership_ues,SIGNAL(triggered(bool)),this,SLOT(duesReport()));
    connect(ui->actionLookup_ID,SIGNAL(triggered(bool)),this,SLOT(memberIDSearch()));
    connect(ui->actionLookup_Name,SIGNAL(triggered(bool)),this,SLOT(memberNameSearch()));
    connect(ui->actionSingle_Item_Report,SIGNAL(triggered(bool)),this,SLOT(itemNameSearch()));
    connect(ui->actionExpiration_Month,SIGNAL(triggered(bool)),this,SLOT(monthSearch()));
    connect(ui->pushButton_6,SIGNAL(clicked(bool)),this,SLOT(search()));
    connect(ui->pushButton_7,SIGNAL(clicked(bool)),this,SLOT(addPurchase()));
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
    int page;
    page = ui->tabWidget->currentIndex();
    if(page == 0){
        table->setRowCount(members.size());
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
            table->showRow(row);
            cursor = cursor->next;
            ++row;
        }
    }
    else if(page == 1){
        table1->setRowCount(members.getAllPurchases().size());
        QString labelText = "Grand Total: $";
        labelText.append(QString::number(members.getGrandTotal(),'f',2));
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
                table1->showRow(row1);
                cursor1 = cursor1->next;
                ++row1;
            }
            memberPurchases = memberPurchases->next;
            if((memberPurchases))
                cursor1 = memberPurchases->item.getPurchases().begin();
        }
    }

    else if(page == 2){
        table2->setRowCount(members.getInventory().getNumberOfItems());
        node<Product>* item = members.getInventory().getInventory().begin();
        int row = 0;
        while(item != NULL)
        {
            table2->setItem(row,0, new QTableWidgetItem(QString::fromStdString(item->item.getName()).simplified()));
            table2->setItem(row,1, new QTableWidgetItem(QString::number(item->item.getPrice(), 'f', 2)));
            table2->setItem(row,2, new QTableWidgetItem(QString::number(item->item.getQuantity())));
            for(int i = 0; i < 3; ++i)
            {
                table2->item(row,i)->setFlags((table2->item(row,i)->flags() ^ Qt::ItemIsEditable));
                table2->item(row,i)->setTextAlignment(Qt::AlignCenter);
            }
            table2->item(row,0)->setTextAlignment(Qt::AlignVCenter);
            table2->showRow(row);
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

void MainWindow::add()
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
   members.writeMemberFile("warehouse shoppers.txt");
}

void MainWindow::remove()
{
    int selectedRow = table->currentRow();
    QString id = table->item(selectedRow, 1)->text();
    members.deleteMember(id.toStdString());
    table->removeRow(selectedRow);
    display();
    members.writeMemberFile("warehouse shoppers.txt");
}

void MainWindow::search()
{
    int page;
    page = ui->tabWidget->currentIndex();
    if(ui->pushButton_6->text() == "Search")
    {
        if(page == 0)
            memberTabSearch();
        if(page == 1)
            purchaseTabSearch();
        if(page == 2)
            itemTabSearch();
        ui->pushButton_6->setText("Clear Search");
    }
    else if(ui->pushButton_6->text() == "Clear Search")
    {
        ui->pushButton_6->setText("Search");
        give();
    }
}

void MainWindow::addPurchase()
{
    int selectedRow = table->currentRow();
    QString id = table->item(selectedRow, 1)->text();
    node<member>* found = members.search(id.toStdString());
    Product example("Socks",4.99,2);
    members.addPurchases(found, "03/09/2013", example);
    members.appendSalesFile("day5.txt",id.toStdString(),found->item.getMemberPurchase()->search(example)->item);
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
        ui->pushButton_7->hide();
    }
    else
    {
        ui->pushButton->show();
        ui->pushButton_2->show();
        ui->pushButton_3->show();
        ui->pushButton_7->show();
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

void MainWindow::rebateReport()
{
    ui->scrollArea->show();
    ui->textEdit->clear();
    ui->label_3->setText("Preferred Member Rebates Report");
    node<member>* cursor = members.getMembers().begin();
    while(cursor)
    {
        if(cursor->item.getMembershipType() == "Preferred")
        {
            QString line = "Member's Name: ";
            line.append(QString::fromStdString(cursor->item.getFullName()));
            ui->textEdit->append(line);
            line = "Rebate amount: $";
            line.append(QString::number(cursor->item.getRebateAmount(),'f',2));
            ui->textEdit->append(line);
            ui->textEdit->append("");
        }
        cursor = cursor->next;
    }
    ui->textEdit->moveCursor(QTextCursor::Start);
}

void MainWindow::duesReport()
{
    ui->scrollArea->show();
    ui->textEdit->clear();
    ui->label_3->setText("Membership Dues Report");
    node<member>* cursor = members.getMembers().begin();
    while(cursor)
    {
        if(cursor->item.getMembershipType() == "Preferred")
        {
            QString line = "Member's Name: ";
            line.append(QString::fromStdString(cursor->item.getFullName()));
            ui->textEdit->append(line);
            line = "Membership dues: $";
            line.append(QString::number(PREFERRED_DUES));
            ui->textEdit->append(line);
            ui->textEdit->append("");
        }
        cursor = cursor->next;
    }

    cursor = members.getMembers().begin();
    while(cursor)
    {
        if(cursor->item.getMembershipType() == "Basic")
        {
            QString line = "Member's Name: ";
            line.append(QString::fromStdString(cursor->item.getFullName()));
            ui->textEdit->append(line);
            line = "Membership dues amount: $";
            line.append(QString::number(BASIC_DUES));
            ui->textEdit->append(line);
            ui->textEdit->append("");
        }
        cursor = cursor->next;
    }
    ui->textEdit->moveCursor(QTextCursor::Start);
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

void MainWindow::itemNameSearch()
{
    ui->groupBox->setTitle("Item Search");
    ui->label_2->setText("Enter Item Name");
    ui->lineEdit->clear();
    ui->groupBox->show();
}

void MainWindow::monthSearch()
{
    ui->groupBox->setTitle("Expiration Month Search");
    ui->label_2->setText("Enter 2 Digit Month");
    ui->lineEdit->clear();
    ui->groupBox->show();
}

void MainWindow::memberTabSearch()
{
    ui->groupBox->setTitle("Member Lookup");
    ui->label_2->setText("Enter Search Criteria");
    ui->lineEdit->clear();
    ui->groupBox->show();
}

void MainWindow::purchaseTabSearch()
{
    ui->groupBox->setTitle("Purchase Lookup");
    ui->label_2->setText("Enter Search Criteria");
    ui->lineEdit->clear();
    ui->groupBox->show();
}

void MainWindow::itemTabSearch()
{
    ui->groupBox->setTitle("Item Lookup");
    ui->label_2->setText("Enter Search Criteria");
    ui->lineEdit->clear();
    ui->groupBox->show();
}

void MainWindow::on_pushButton_5_clicked()
{

    if(ui->groupBox->title() == "Daily Sales Report Search")
    {
        ui->scrollArea->show();
        ui->textEdit->clear();
        QString title = "Daily Sales Report ";
        QString date = ui->lineEdit->text();
        title.append(date);
        ui->label_3->setText(title);

        class::dailyReport report(members, date.toStdString());
        if(report.getTotalRevenue() == 0)
            ui->textEdit->append("No sales data for that day.");
        else
        {
            QString line = "Total revenue: $";
            line.append(QString::number(report.getTotalRevenue()));
            ui->textEdit->append(line);
            ui->textEdit->append("\nMembers who shopped: ");
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
        ui->scrollArea->show();
        ui->textEdit->clear();
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

    else if(ui->groupBox->title() == "Item Search")
    {
        ui->scrollArea->show();
        ui->textEdit->clear();
        QString name = ui->lineEdit->text();
        QString line = "Single Item Report ";
        line.append(name);
        ui->label_3->setText(line);
        node<Product>* found = members.getInventory().search(name.toStdString());
        if(!found)
            ui->textEdit->append("Item not found.");
        else
        {
            line = "Item Name: ";
            line.append(QString::fromStdString(found->item.getName()));
            ui->textEdit->append(line);
            line = "Quantity Sold: ";
            line.append(QString::number(found->item.getQuantity()));
            ui->textEdit->append(line);
            line = "Total Sales Price (pre-tax): $";
            line.append(QString::number(found->item.getSubtotal(),'f',2));
            ui->textEdit->append(line);
            line = "Total Sales Price (w/ tax): $";
            line.append(QString::number(found->item.getTotal(),'f',2));
            ui->textEdit->append(line);
        }
    }

    else if(ui->groupBox->title() == "Expiration Month Search")
    {
        ui->scrollArea->show();
        ui->textEdit->clear();
        QString month = ui->lineEdit->text();
        node<member>* cursor = members.getMembers().begin();
        while(cursor)
        {
            if(cursor->item.getExpirationDate().find(month.toStdString()) == 0)
            {
                QString line = "Member Name: ";
                line.append(QString::fromStdString(cursor->item.getFullName()));
                ui->textEdit->append(line);
                line = "Expiration Date: ";
                line.append(QString::fromStdString(cursor->item.getExpirationDate()));
                ui->textEdit->append(line);
                line = "Membership dues: $";
                if(cursor->item.getMembershipType() == "Basic")
                    line.append(QString::number(BASIC_DUES));
                else if(cursor->item.getMembershipType() == "Preferred")
                    line.append(QString::number(PREFERRED_DUES));
                ui->textEdit->append(line);
                ui->textEdit->append("");
            }
            cursor = cursor->next;
        }
    }

    else if(ui->groupBox->title() == "Member Lookup")
    {
        QString toFind = ui->lineEdit->text();
        for(int i = 0; i < table->rowCount(); i++)
        {
            if(!table->item(i,0)->text().contains(toFind) &&
               !table->item(i,1)->text().contains(toFind) &&
               !table->item(i,2)->text().contains(toFind) &&
               !table->item(i,3)->text().contains(toFind))
                table->hideRow(i);
        }
    }
    else if(ui->groupBox->title() == "Purchase Lookup")
    {
        QString toFind = ui->lineEdit->text();
        for(int i = 0; i < table1->rowCount(); i++)
        {
            if(!table1->item(i,0)->text().contains(toFind) &&
               !table1->item(i,1)->text().contains(toFind) &&
               !table1->item(i,2)->text().contains(toFind) &&
               !table1->item(i,3)->text().contains(toFind) &&
               !table1->item(i,4)->text().contains(toFind))
                table1->hideRow(i);
        }
    }
    else if(ui->groupBox->title() == "Item Lookup")
    {
        QString toFind = ui->lineEdit->text();
        for(int i = 0; i < table2->rowCount(); i++)
        {
            if(!table2->item(i,0)->text().contains(toFind) &&
               !table2->item(i,1)->text().contains(toFind) &&
               !table2->item(i,2)->text().contains(toFind))
                table2->hideRow(i);
        }
    }


}

