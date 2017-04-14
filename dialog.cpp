#include "dialog.h"
#include "ui_dialog.h"
#include <QInputDialog>
#include <QString>
Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    pref = false;

    connect(ui->checkBox,SIGNAL(clicked(bool)),this,SLOT(checkedPref()));
    connect(ui->checkBox_2,SIGNAL(clicked(bool)),this,SLOT(checkedBasic()));
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_buttonBox_accepted()
{
    firstName= ui->lineEdit->text();
    lastName = ui->lineEdit_2->text();
}

void Dialog::checkedPref()
{
    ui->checkBox_2->setChecked(false);
    pref = true;
}

void Dialog::checkedBasic()
{
    ui->checkBox->setChecked(false);
    pref = false;
}
