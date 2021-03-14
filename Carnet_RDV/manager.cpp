#include "manager.h"

/*
 * FONCTION ANNEXE
*/
bool isStringEmpty(const string& s){
    for(char c : s)
        if(c < 0 or (c > 32 and c != 127))
            return false;
    return true;
}

manager::manager(void){

    string fN = "Alexandre", lN = "JANON";
    for(unsigned i = 0; i < lN.length(); ++i) lN[i] = toupper(lN[i]);

    auto p1 = new Personne(fN, lN, "0695152925", "alexandre.janon@yahoo.fr"), p2 = new Personne("Franck", "JANON", "0666", "gmail");

    loadPersonne("Personne.carnetRDV");
    cout << endl;

    cout << listPersonnes << endl << endl;

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
    cout << "Chargement du fichier " << filePath << endl;
    bool loaded = false;
    ifstream ifs(filePath);

    if(!ifs)
        cerr << "Impossible d'ouvrir le fichier en lecture" << endl;
    else{
        stringstream buffer;
        buffer << ifs.rdbuf();

        string s = "", lastName= "", firstName = "", phone = "", email = "";
        bool stringIsEmpty = false;
        unsigned long long max = buffer.str().size(), line = 1;
        double val = 0;
        char c = '0';
        for(unsigned long long i = 0;  i < buffer.str().size(); ++i){
            c = buffer.str()[i];
            if(c == '&'){

                if(i+2 < max and buffer.str()[i+1] == 'l' and buffer.str()[i+2] == '='){
                        s = "";
                        i += 2;

                }else if(i+2 < max and buffer.str()[i+1] == 'f' and buffer.str()[i+2] == '='){
                    if(!isStringEmpty(s)){
                        lastName = s;
                        s = "";
                        i += 2;
                    }else{
                        cerr << "Erreur : ligne " << line << " : lastName est vide" << endl;
                        ++line;
                        stringIsEmpty = true;
                    }

                }else if(i+2 < max and buffer.str()[i+1] == 'p' and buffer.str()[i+2] == '='){
                    if(!isStringEmpty(s)){
                        firstName = s;
                        s = "";
                        i += 2;
                    }else{
                        cerr << "Erreur : ligne " << line << " : firstName est vide" << endl;
                        ++line;
                        stringIsEmpty = true;
                    }

                }else if(i+2 < max and buffer.str()[i+1] == 'e' and buffer.str()[i+2] == '='){
                    if(!isStringEmpty(s)){
                        phone = s;
                        s = "";
                        i += 2;
                    }

                }else if(i+4 < max and buffer.str()[i+1] == 'e' and buffer.str()[i+2] == 'n' and buffer.str()[i+3] == 'd' and buffer.str()[i+4] == 'P'){
                    if(!isStringEmpty(s)){
                        email = s;
                        s = "";
                        i += 4;

                        auto p = new Personne(firstName, lastName, phone, email);
                        if(!listPersonnes.inserer(p)) cerr << "Erreur : ligne " << line << " : personne deja ajoutee" << endl;
                    }

                }else s += c;

                if(stringIsEmpty){

                    bool isOk = false;
                    if(i+1 < max) ++i;
                    else isOk = true;

                    while(!isOk){
                        if(buffer.str()[i] == '&'){
                            if(i+2 < max and buffer.str()[i+1] == 'l' and buffer.str()[i+2] == '='){
                                s = "";
                                i += 2;
                                isOk = true;
                            }
                        }else if(i+1 < max) ++i;
                        else isOk = true;
                    }
                    stringIsEmpty = false;

                }else{
                    if(loadingBar != nullptr){
                        val = (i * 100) / max;
                        loadingBar->setValue(val);
                    }
                }

            }else s += c;

        }

        loaded = true;
    }

    cout << "Fichier charge " << (loaded ? "avec" : "sans") << " succes" << endl;
    return loaded;

}
bool manager::laodRDV(const string& filePath, QProgressBar* loadingBar){
    cout << "Chargement du fichier "  << filePath<< endl;
    bool loaded = false;
    ifstream ifs(filePath);

    if(!ifs)
        cerr << "Impossible d'ouvrir le fichier en lecture" << endl;
    else{


        loaded = true;
    }

    cout << "Fichier charge " << (loaded ? "avec" : "sans") << " succes" << endl;
    return loaded;

}
bool manager::savePersonne(const string& filePath, QProgressBar* loadingBar) const{
    cout << "Enregistrement du fichier " << filePath << endl;
    bool saved = false;
    ofstream ofs(filePath);

    if(!ofs)
        cerr << "Erreur, impossible d'ouvrir le fichier en ecriture" << endl;
    else{
        int i = 0, max = listPersonnes.size();
        double val = 0;
        string buf = "";
        for(i = 0; i < listPersonnes.size(); ++i){
            auto p = listPersonnes[i];
            buf += (string) "&l=" + p->getLastName()
                    + "&f=" + p->getFirstName()
                    + "&p=" + p->getPhone()
                    + "&e=" + p->getEmail()
                    + "&endP\n";
            if(loadingBar != nullptr){
                val = (i * 100) / max;
                loadingBar->setValue(val);
            }
        }
        if(loadingBar != nullptr){
            val = (i * 100) / max;
            loadingBar->setValue(val);
        }

        i = 0, max = buf.length();
        stringstream buffer;
        for(char c : buf){
            buffer.put(c);
            if(loadingBar != nullptr){
                val = (i * 100) / max;
                loadingBar->setValue(val);
                ++i;
            }
        }
        if(loadingBar != nullptr){
            val = (i * 100) / max;
            loadingBar->setValue(val);
        }

        ofs << buffer.rdbuf();

        saved = true;

    }

    cout << "Enregistrement du fichier " << (saved ? "avec" : "sans") << " succes" << endl;
    return saved;

}
bool manager::saveRDV(const string& filePath, QProgressBar* loadingBar) const{
    cout << "Enregistrement du fichier " << filePath << endl;
    bool saved = false;
    ofstream ofs(filePath);

    if(!ofs)
        cerr << "Erreur, impossible d'ouvrir le fichier en ecriture" << endl;
    else{
        int ind = 0, max = listRDV.size();
        for(int ind = 0; ind < listRDV.size(); ++ind) max += listRDV[ind].getMembersList().size();
        double val = 0;
        string buf = "";
        for(int i = 0; i < listRDV.size(); ++i){
            auto rdv = listRDV[i];
            buf += (string) "&n=" + rdv.getName()
                    + "&d=" + rdv.getDate().toString()
                    + "&ts=" + rdv.getTimeStart().toString()
                    + "&te=" + rdv.getTimeEnd().toString()
                    + "&endR\n";
            if(loadingBar != nullptr){
                val = (ind * 100) / max;
                loadingBar->setValue(val);
                ++ind;
            }
            for(auto p : rdv.getMembersList()){
                buf += (string) "&l=" + p->getLastName()
                        + "&f=" + p->getFirstName()
                        + "&endP\n";

                if(loadingBar != nullptr){
                    val = (ind * 100) / max;
                    loadingBar->setValue(val);
                    ++ind;
                }
            }
        }
        if(loadingBar != nullptr){
            val = (ind * 100) / max;
            loadingBar->setValue(val);
        }

        ind = 0, max = buf.length();
        stringstream buffer;
        for(char c : buf){
            buffer.put(c);
            if(loadingBar != nullptr){
                val = (ind * 100) / max;
                loadingBar->setValue(val);
                ++ind;
            }
        }
        if(loadingBar != nullptr){
            val = (ind * 100) / max;
            loadingBar->setValue(val);
        }

        ofs << buffer.rdbuf();

        saved = true;

    }

    cout << "Enregistrement du fichier " << (saved ? "avec" : "sans") << " succes" << endl;
    return saved;

}



// Getteurs



// Setteurs



// Fonctions globales


