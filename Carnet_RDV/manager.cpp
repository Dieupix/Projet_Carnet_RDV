#include "manager.h"

manager::manager()
{
    LDCP allPersons;

    string fN = "Alexandre", lN = "Janon";
    for(unsigned i = 0; i < lN.length(); ++i) lN[i] = toupper(lN[i]);

    auto p1 = new Personne(fN, lN, "0695152925", "alexandre.janon@yahoo.fr"), p2 = new Personne("Alexandre", "JANON", "0666", "gmail");

    allPersons.inserer(p1);

    vector<char> date {'1', '0', '0', '4', '2', '0', '2', '1'};

    RDV rdv ("Première réunion", date, "8h30", "10h");

    allPersons.inserer(p2);
    cout << allPersons << endl << endl;
    rdv.getMembersList().push_back(p1);
    rdv.getMembersList().push_back(p2);

    cout << rdv;
}
