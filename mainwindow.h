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
    void give();
    void profile();
    void remove();
    void salesReport();
    void memberIDSearch();
    void memberNameSearch();
    void itemSearch();

private slots:
    void on_pushButton_2_clicked();
    void on_pushButton_5_clicked();


private:
    Ui::MainWindow *ui;
    memberList members;
    QTableWidget* table;
    QTableWidget* table1;
    QTableWidget* table2;

};

#endif // MAINWINDOW_H
