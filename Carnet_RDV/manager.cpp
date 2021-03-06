#include "manager.h"

manager::manager()
{
    LDCP allPersons;

    string fN = "Alexandre", lN = "JANON";
    for(unsigned i = 0; i < lN.length(); ++i) lN[i] = toupper(lN[i]);

    auto p1 = new Personne(fN, lN, "0695152925", "alexandre.janon@yahoo.fr"), p2 = new Personne("Franck", "JANON", "0666", "gmail");

    allPersons.inserer(p1);

    Date date {10, 04, 2021};
    Hour timeStart (8, 30, 0), timeEnd (10, 0, 0);

    RDV rdv ("Première réunion", date, timeStart, timeEnd);

    cout << allPersons << endl << endl;
    rdv.getMembersList().push_back(p1);
    rdv.getMembersList().push_back(p2);

    cout << rdv;
}

