#include "errorwindow.h"
#include "ui_errorwindow.h"

errorWindow::errorWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::errorWindow)
{
    ui->setupUi(this);
    ui->buttonBox->
}

errorWindow::errorWindow(std::string error)
{
    errors = error;
}

errorWindow::~errorWindow()
{
    delete ui;
}

bool errorWindow::displayError()
{
    switch(errors)
 {
    case "Error1" : ui->label->ui.setText("Error 1: One or more name spaces were empty. Please enter a valid name");
                    return true;
    case "Error2" : ui->label->setText("ERROR 2: A membership type was not chosen. Please make a selecion.");
                    return true;



 }

}


void errorWindow::on_buttonBox_rejected()
{
    relaunch = false;
}

void errorWindow::on_buttonBox_accepted()
{
    relaunch = true;
}
