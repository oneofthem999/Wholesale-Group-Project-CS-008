#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>
#include <QString>
#include <fstream>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    getInfo(std::string fileName);
    display();

public slots:
    void give();

private slots:
    void on_pushButton_3_clicked();

private:
    Ui::MainWindow *ui;

    std::vector<QString> member;
    std::vector<QString> memberID;
    std::vector<QString> date;
    std::vector<QString> price;
    std::vector<QString> item;
    std::vector<QString> quantity;
    int column = 0;
    int row = 11;

};

#endif // MAINWINDOW_H
