#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    cout << "Launching program" << endl << endl;

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    int rtrn = a.exec();

    cout << "Closing program" << endl;
    return rtrn;
}
