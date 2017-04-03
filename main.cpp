#include "mainwindow.h"
#include "member.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    memberList AzusaBranch;
    member one, two;
    Item bacon("Bacon", 3.89);
    Item eggs("Eggs", 0.99);
    one.setName("Harry", "Potter");
    one.setMembershipNumber("174862");
    one.setMembershipType("Preferred");
    one.setExpirationDate("12/31/2017");
    one.insertPurchase("04/02/2017", bacon);
    AzusaBranch.addMember(one);
    one.insertPurchase("04/02/2017", eggs);
    one.setName("Hermione", "Grainger");
//    two.setName("Hermione", "Grainger");
//    two.setMembershipNumber("593147");
//    two.setMembershipType("Basic");
//    two.setExpirationDate("03/30/2018");
//    AzusaBranch.addMember(two);
    cout<<AzusaBranch;
    cout<<AzusaBranch.getAllPurchases().size() << endl;

    return a.exec();
}
