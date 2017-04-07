#include "dialog.h"
#include "ui_dialog.h"
#include <QInputDialog>
#include <QString>
Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    connect(ui->checkBox,SIGNAL(clicked(bool)),this,SLOT(chosen()));
    connect(ui->checkBox_2,SIGNAL(clicked(bool)),this,SLOT(chosen2()));
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_buttonBox_accepted()
{

    firstName= ui->lineEdit->text();
    lastName = ui->lineEdit_2->text();

   // firstName = QInputDialog::getText(this,tr("Enter Name"),tr("User Name"), QLineEdit::Normal,
      //                                QDir::home().dirName(), &ok
         //                             );
    //ui->lineEdit->getText;



}

Dialog::chosen()
{
    if(choice == true)
    {
        ui->checkBox_2->setEnabled(false);
        choice = false;
        pref = true;
    }
    else
    {
        ui->checkBox_2->setEnabled(true);
        choice = true;
        pref = false;
    }
}

Dialog::chosen2()
{
    if(choice == true)
    {
        ui->checkBox->setEnabled(false);
        choice = false;
        basic = true;
    }
    else
    {
        ui->checkBox->setEnabled(true);
        choice = true;
        basic = false;
    }
}
