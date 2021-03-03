#include "manager.h"

manager::manager()
{
    vector<Personne*> allPersons;
    string fN = "Alexandre", lN = "Janon";
    for(unsigned i = 0; i < lN.length(); ++i) lN[i] = toupper(lN[i]);

    allPersons.push_back(new Personne(fN, lN, "0695152925", "alexandre.janon@yahoo.fr"));

    vector<char> date {'1', '0', '0', '4', '2', '0', '2', '1'};
    vector<Personne*> membersList;
    membersList.push_back(allPersons[0]);

    RDV rdv {"Première réunion", date, "8h30", "10h", membersList};

    allPersons.push_back(new Personne(fN, lN, "666", "gmail"));
    rdv.getMembersList().push_back(allPersons[1]);

    cout << rdv << endl;
}
