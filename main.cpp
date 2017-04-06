#include "mainwindow.h"
#include "member.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    w.show();
    w.display();

    return a.exec();
}
