#include "mainwindow.h"

#include <direct.h>

#include <QApplication>
#include <QLibraryInfo>
#include <QLocale>
#include <QTranslator>

int main(int argc, char *argv[])
{
    // Création de l'application
    QApplication a(argc, argv);

    // Redirection des flux de sortie standard et d'erreurs vers un fichier .log
    Date ajd = today();
    Hour mtn = now();
    string dirName = a.applicationDirPath().toStdString() + "\\" + "logs", extansion = ".log";
    string time =   to_string(ajd.getYear()) + "-" +
                    (ajd.getMonth() < 10 ? "0" : "") + to_string(ajd.getMonth()) + "-" +
                    (ajd.getDay() < 10 ? "0" : "") + to_string(ajd.getDay()) + "_" +
                    (mtn.getHour() < 10 ? "0" : "") + to_string(mtn.getHour()) + "-" +
                    (mtn.getMinute() < 10 ? "0" : "") + to_string(mtn.getMinute()) + "-" +
                    (mtn.getSecond() < 10 ? "0" : "") + to_string(mtn.getSecond()) +
                    extansion;

    string fileName = dirName + "\\" + time;
    mkdir(dirName.c_str());

    ofstream stdStreamToFile(fileName);
    auto backCout = cout.rdbuf();
    auto backCerr = cerr.rdbuf();

    cout.rdbuf(stdStreamToFile.rdbuf());
    cerr.rdbuf(stdStreamToFile.rdbuf());

    // Lancement du programme
    cout << today() << " - " << now() << " : " << QString(QObject::tr("Démarrage du programme", "Starting program")).toStdString() << " " << argv[0] << " ..." << endl << endl;

    a.setWindowIcon(QIcon("../Carnet_RDV/icons/icon_carnet_rdv_white2_100"));

    /* Traduction de l'application dans la langue courante du système
     * Remarque :   seuls les objets pré-faits par Qt seront traduits,
     *              les nôtres ne pourront être traduits actuellement par manque de temps pour la traduction
    */
    QString locale = QLocale::system().name().section('_', 0, 0);
    QTranslator* translator = new QTranslator();
    if(translator->load(QString("qt_") + locale, QString("../Carnet_RDV/translations"))) a.installTranslator(translator);
    delete translator;

    MainWindow w;
    w.show();

    // Éxécution de l'application
    int exe = a.exec();

    // Fermeture du programme
    cout << today() << " - " << now() << " : " << QString(QObject::tr("Fermeture du programme", "Closing program")).toStdString() << " " << argv[0] << " "
                                                << QString(QObject::tr("avec le code", "with code")).toStdString() << " " << exe << endl << endl;

    cout.rdbuf(backCout);
    cerr.rdbuf(backCerr);

    return exe;
}
