#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QApplication>
#include <QDesktopWidget>
#include <QMainWindow>
#include <QTableWidget>
#include <QRect>
#include <QString>

#include "member.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void getMemberInfo(std::string filename);
    void getSalesInfo(std::string filename);
    void display();
    void showPurchases(node<member> *member);

public slots:
    void profile();
    void add();
    void remove();
    void search();
    void addPurchase();
    void give();
    void salesReport();
    void rebateReport();
    void duesReport();
    void memberIDSearch();
    void memberNameSearch();
    void itemNameSearch();
    void memberTabSearch();
    void purchaseTabSearch();
    void itemTabSearch();

private slots:
    void on_pushButton_5_clicked();


private:
    Ui::MainWindow *ui;
    memberList members;
    QTableWidget* table;
    QTableWidget* table1;
    QTableWidget* table2;
    QTableWidget* table3;

};

#endif // MAINWINDOW_H
