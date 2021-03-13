#include "mainwindow.h"

#include <QApplication>
#include <QTranslator>
#include <QLocale>
#include <QLibraryInfo>

int main(int argc, char *argv[])
{
    cout << "Launching program" << endl << endl;

    QApplication a(argc, argv);
    a.setWindowIcon(QIcon("../Carnet_RDV/icons/icon_carnet_rdv_black3_100"));

    QString locale = QLocale::system().name().section('_', 0, 0);
    QTranslator translator;
    auto t = translator.load(QString("qt_") + locale, QLibraryInfo::path(QLibraryInfo::TranslationsPath));
    if(t) a.installTranslator(&translator);

    MainWindow w;
    w.show();

    int rtrn = a.exec();

    cout << "Closing program" << endl;
    return rtrn;
}
