#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QString>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();
    QString firstName;
    QString lastName;
    bool basic;
    bool pref;

private slots:
    void on_buttonBox_accepted();
public slots:

    void chosen();
    void chosen2();


private:
    Ui::Dialog *ui;
    bool choice;



};

#endif // DIALOG_H
