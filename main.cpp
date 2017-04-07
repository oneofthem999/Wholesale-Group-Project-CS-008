#include "mainwindow.h"
#include "inputwindow.h"
#include <QApplication>
#include <fstream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    w.show();
    w.getInfo("shoppers.txt");
    w.display();

    return a.exec();
}
