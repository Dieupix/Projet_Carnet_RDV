#include "manager.h"

manager::manager(void){

    string fN = "Alexandre", lN = "JANON";
    for(unsigned i = 0; i < lN.length(); ++i) lN[i] = toupper(lN[i]);

    auto p1 = new Personne(fN, lN, "0695152925", "alexandre.janon@yahoo.fr"), p2 = new Personne("Franck", "JANON", "0666", "gmail");

    listPersonnes.inserer(p1);

    cout << listPersonnes << endl;

    Date date {10, 4, 2021};
    Hour timeStart (8, 30, 0), timeEnd (10, 0, 0);

    RDV rdv ("Première réunion", date, timeStart, timeEnd);

    rdv.addMember(p1);
    rdv.addMember(p2);

    cout << rdv << endl;

}



// Surcharge des opérateurs



// Méthodes
bool manager::loadPersonne(const string& filePath, QProgressBar* loadingBar){
    bool loaded = false;
    ifstream ifs(filePath);

    if(!ifs)
        cerr << "Impossible d'ouvrir le fichier " << filePath << " en lecture" << endl;
    else{
        stringstream buffer;
        buffer << ifs.rdbuf();

        string s = "";
        unsigned max = buffer.str().size(), line = 1;
        double val = 0;
        char c = '0';
        for(unsigned i = 0;  i < buffer.str().size(); ++i){
            c = buffer.str()[i];
            if(c == '&'){
                if(i+2 < max){
                    if(buffer.str()[i+1] == 'l' and buffer.str()[i+2] == '='){
                    }else if(buffer.str()[i+1] == 'f' and buffer.str()[i+2] == '='){

                        if()

                    }

                }

            }

            s += c;

        }

        loaded = true;
    }
    return loaded;

}
bool manager::laodRDV(const string& filePath, QProgressBar* loadingBar){
    bool loaded = false;
    ifstream ifs(filePath);

    if(!ifs)
        cerr << "Impossible d'ouvrir le fichier " << filePath << " en lecture" << endl;
    else{


        loaded = true;
    }
    return loaded;

}
bool manager::savePersonne(const string& filePath, QProgressBar* loadingBar) const{
    bool saved = false;
    ofstream ofs(filePath);

    if(!ofs)
        cerr << "Erreur, impossible d'ouvrir le fichier " << filePath << " en ecriture" << endl;
    else{
        unsigned i = 0, max = listPersonnes.size();
        double val = 0;
        string buf = "";
        for(i = 0; listPersonnes.size(); ++i){
            auto p = listPersonnes[i];
            buf += (string) "&l=" + p->getLastName()
                    + "&f=" + p->getFirstName()
                    + "&p=" + p->getPhone()
                    + "&e=" + p->getEmail()
                    + "&endP\n";
            if(loadingBar != nullptr){
                val = (i / max) / 2;
                loadingBar->setValue(val);
            }
        }
        if(loadingBar != nullptr){
            val = (i / max) / 2;
            loadingBar->setValue(val);
            ++i;
        }

        stringstream buffer;
        for(char c : buf){
            buffer.put(c);
            if(loadingBar != nullptr){
                val = (i / max) / 2;
                loadingBar->setValue(val);
                ++i;
            }
        }
        if(loadingBar != nullptr){
            val = (i / max) / 2;
            loadingBar->setValue(val);
        }

        ofs << buffer.rdbuf();

        saved = true;

    }
    return saved;

}
bool manager::saveRDV(const string& filePath, QProgressBar* loadingBar) const{
    bool saved = false;
    ofstream ofs(filePath);

    if(!ofs)
        cerr << "Erreur, impossible d'ouvrir le fichier " << filePath << " en ecriture" << endl;
    else{
        int ind = 0, max = listRDV.size();
        double val = 0;
        string buf = "";
        for(int i = 0; listRDV.size(); ++i){
            auto rdv = listRDV[i];
            buf += (string) "&n=" + rdv.getName()
                    + "&d=" + rdv.getDate().toString()
                    + "&ts=" + rdv.getTimeStart().toString()
                    + "&te=" + rdv.getTimeEnd().toString()
                    + "&endR\n";
            if(loadingBar != nullptr){
                val = (ind / max) / 2;
                loadingBar->setValue(val);
            }
            for(auto p : rdv.getMembersList()){
                buf += (string) "&l=" + p->getLastName()
                        + "&f=" + p->getFirstName()
                        + "&endP\n";

                if(loadingBar != nullptr){
                    val = (ind / max) / 2;
                    loadingBar->setValue(val);
                }
            }
        }
        if(loadingBar != nullptr){
            val = (ind / max) / 2;
            loadingBar->setValue(val);
            ++ind;
        }

        stringstream buffer;
        for(char c : buf){
            buffer.put(c);
            if(loadingBar != nullptr){
                val = (ind / max) / 2;
                loadingBar->setValue(val);
                ++ind;
            }
        }
        if(loadingBar != nullptr){
            val = (ind / max) / 2;
            loadingBar->setValue(val);
        }

        ofs << buffer.rdbuf();

        saved = true;

    }
    return saved;

}



// Getteurs



// Setteurs



// Fonctions globales


