#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    cout << "Launching program" << endl << endl;

    QApplication a(argc, argv);
    a.setWindowIcon(QIcon("../Carnet_RDV/icons/icon_carnet_rdv_black3_100"));
    MainWindow w;
    w.show();

    int rtrn = a.exec();

    cout << "Closing program" << endl;
    return rtrn;
}
