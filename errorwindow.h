#ifndef ERRORWINDOW_H
#define ERRORWINDOW_H

#include <QDialog>

namespace Ui {
class errorWindow;
}

class errorWindow : public QDialog
{
    Q_OBJECT

public:
    explicit errorWindow(QWidget *parent = 0);
    ~errorWindow();

    bool displayError();
    bool relaunch;

private slots:
    void on_buttonBox_rejected();

    void on_buttonBox_accepted();

private:
    Ui::errorWindow *ui;
    string errors;

};

#endif // ERRORWINDOW_H
