#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    cout << "Launching program" << endl << endl;

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    int rtrn = a.exec();

    vector<Personne> allPersons;
    string fN = "Alexandre", lN = "Janon";
    for(int i = 0; i < (int) lN.length(); i++) lN[i] = toupper(lN[i]);

    allPersons.push_back(Personne(fN, lN, "0695152925", "alexandre.janon@yahoo.fr"));


    vector<char> date {'1', '0', '0', '4', '2', '0', '2', '1'};
    vector<Personne*> membersList;
    membersList.push_back(&allPersons[0]);

    RDV rdv {"Première réunion", date, "8h30", "10h", membersList};

    cout << rdv << endl;

    cout << "Closing program" << endl;
    return rtrn;
}
