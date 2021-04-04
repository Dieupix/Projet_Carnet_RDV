#include "mainwindow.h"

#include <direct.h>

#include <QApplication>
#include <QLibraryInfo>
#include <QLocale>
#include <QTranslator>

int main(int argc, char *argv[])
{
    // Redirection des flux de sortie standard et d'erreurs vers un fichier .log
    Date ajd = today();
    Hour mtn = now();
    string dirName = "logs", extansion = ".log";
    string time =   to_string(ajd.getYear()) + "-" +
                    to_string(ajd.getMonth()) + "-" +
                    to_string(ajd.getDay()) + "_" +
                    to_string(mtn.getHour()) + "-" +
                    to_string(mtn.getMinute()) + "-" +
                    to_string(mtn.getSecond()) +
                    extansion;

    string fileName = dirName + "\\" + time;
    mkdir(dirName.c_str());

    ofstream stdStreamToFile(fileName);
    auto backCout = cout.rdbuf();
    auto backCerr = cerr.rdbuf();

    cout.rdbuf(stdStreamToFile.rdbuf());
    cerr.rdbuf(stdStreamToFile.rdbuf());

    // Lancement du programme
    cout << today() << " - " << now() << " : Démarrage du programme " << argv[0] << " ..." << endl << endl;

    // Création de l'application
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon("../Carnet_RDV/icons/icon_carnet_rdv_white2_100"));

    // Traduction de l'application dans la langue courante du système
    QString locale = QLocale::system().name().section('_', 0, 0);
    QTranslator translator;
    bool t = translator.load(QString("qt_") + locale, QLibraryInfo::path(QLibraryInfo::TranslationsPath));
    if(t) a.installTranslator(&translator);

    MainWindow w;
    w.show();

    // Éxécution de l'application
    int exe = a.exec();

    // Fermeture du programme
    cout << today() << " - " << now() << " : Fermeture du programme " << argv[0] << " avec le code " << exe << endl << endl;

    cout.rdbuf(backCout);
    cerr.rdbuf(backCerr);

    return exe;
}
