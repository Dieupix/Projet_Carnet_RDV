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

Manager::Manager(void){

    loadPersonne();
    cout << endl;

    cout << listPersonnes << endl << endl;

    Date date {10, 4, 2021};
    Hour timeStart (8, 30), timeEnd (10, 0);

    listRDV.inserer(new RDV("Première réunion", date, timeStart, timeEnd));
    listRDV.inserer(new RDV("Deuxième réunion", date, {10, 5, 0}, {12, 0, 0}));
    auto rdv = listRDV[0];
    auto rdv2 = listRDV[1];

    rdv->addMember(listPersonnes[0]);
    rdv->addMember(listPersonnes[1]);
    rdv2->addMember(listPersonnes[0]);
    cout << *rdv << endl << rdv->participantsToString() << endl;

    cout << listPersonnes[0]->rdvToString() << endl;

    saveRDV();


}



// ---------- Surcharge des opérateurs ----------



// ---------- Méthodes ----------
bool Manager::addPersonne(Personne* p){
    return listPersonnes.inserer(p);
}

bool Manager::addRDV(RDV* rdv){
    return listRDV.inserer(rdv);
}

bool Manager::loadPersonne(const string& filePath, QProgressBar* loadingBar){
    cout << "Chargement du fichier " << (filePath == "" ? FILENAMEPERSONNE : filePath + FILENAMEPERSONNE) << endl;
    bool loaded = false;
    ifstream ifs(filePath == "" ? FILENAMEPERSONNE : filePath + FILENAMEPERSONNE);

    if(!ifs)
        cerr << "Impossible d'ouvrir le fichier en lecture" << endl;
    else{
        stringstream buffer;
        buffer << ifs.rdbuf();

        string lastName= "", firstName = "", phone = "", email = "";
        short int sequence = 0;
        unsigned long long i = 0, max = buffer.str().size();
        int line = 1;
        bool abort = true;
        double val = 0;
        char c = '0';
        for(i = 0;  i < buffer.str().size(); ++i){
            c = buffer.str()[i];
            if(loadingBar != nullptr){
                val = (i * 100) / max;
                loadingBar->setValue(val);
            }
            if(c == '&'){

                if(i+2 < max and buffer.str()[i+1] == 'l' and buffer.str()[i+2] == '='){
                    if(lastName != "" or  firstName != "" or phone != "" or email != ""){
                        cerr << "Erreur : ligne " << line - 1 << " : pas de fin de ligne" << endl;
                        lastName = firstName = phone = email = "";
                    }
                    sequence = 1;
                    i += 2;
                    abort = false;

                }else if(i+2 < max and buffer.str()[i+1] == 'f' and buffer.str()[i+2] == '='){
                    if(isStringEmpty(lastName)){
                        cerr << "Erreur : ligne " << line << " : lastName est vide" << endl;
                        abort = true;
                    }
                    sequence = 2;
                    i += 2;

                }else if(i+2 < max and buffer.str()[i+1] == 'p' and buffer.str()[i+2] == '='){
                    if(isStringEmpty(firstName)){
                        cerr << "Erreur : ligne " << line << " : firstName est vide" << endl;
                        abort = true;
                    }
                    sequence = 3;
                    i += 2;

                }else if(i+2 < max and buffer.str()[i+1] == 'e' and buffer.str()[i+2] == '='){
                    if(isStringEmpty(phone)){
                        cerr << "Erreur : ligne " << line << " : phone est vide" << endl;
                        abort = true;
                    }
                    sequence = 4;
                    i += 2;

                }else if(i+4 < max and buffer.str()[i+1] == 'e' and buffer.str()[i+2] == 'n' and buffer.str()[i+3] == 'd' and buffer.str()[i+4] == 'P'){
                    if(isStringEmpty(email)){
                        cerr << "Erreur : ligne " << line << " : email est vide" << endl;
                        abort = true;
                    }

                    if(!abort){
                        Personne* p = new Personne(firstName, lastName, phone, email);
                        if(!listPersonnes.inserer(p)){
                            cerr << *p << " : " << "Erreur : ligne " << line << " : La Personne est deja dans la base de donnees" << endl;
                            delete p;
                        }
                    }
                    sequence = 0;
                    i += 4;
                    lastName = firstName = phone = email = "";

                }else{
                    switch(sequence){
                    case 0:
                        break;
                    case 1:
                        lastName += c;
                        break;
                    case 2:
                        firstName += c;
                        break;
                    case 3:
                        phone += c;
                        break;
                    case 4:
                        email += c;
                        break;
                    default:
                        cerr << "Erreur : sequence = " << sequence << endl;
                        break;
                    }
                }
            }else{
                if(c == '\n') ++line;
                switch(sequence){
                case 0:
                    break;
                case 1:
                    lastName += c;
                    break;
                case 2:
                    firstName += c;
                    break;
                case 3:
                    phone += c;
                    break;
                case 4:
                    email += c;
                    break;
                default:
                    cerr << "Erreur : sequence = " << sequence << endl;
                    break;
                }
            }
        }

        if(loadingBar != nullptr){
            val = (i * 100) / max;
            loadingBar->setValue(val);
        }

        if(lastName != "" or firstName != "" or phone != "" or email != "")
            cerr << "Erreur : ligne " << line << " : pas de fin de ligne" << endl;

        loaded = true;
    }

    cout << "Fichier charge " << (loaded ? "avec" : "sans") << " succes" << endl;
    return loaded;

}
bool Manager::loadRDV(const string& filePath, QProgressBar* loadingBar){
    cout << "Chargement du fichier "  << (filePath == "" ? FILENAMERDV : filePath + FILENAMERDV) << endl;
    bool loaded = false;
    ifstream ifs(filePath == "" ? FILENAMERDV : filePath + FILENAMERDV);

    if(!ifs)
        cerr << "Impossible d'ouvrir le fichier en lecture" << endl;
    else{

        stringstream buffer;
        buffer << ifs.rdbuf();

        string name = "", date = "", timeStart = "", timeEnd = "", lastName= "", firstName = "";
        short int sequence = 0;
        unsigned long long i = 0, max = buffer.str().size();
        int line = 1;
        bool abortR = true, abortP = true;
        double val = 0;
        char c = '0';
        for(i = 0;  i < buffer.str().size(); ++i){
            c = buffer.str()[i];
            if(loadingBar != nullptr){
                val = (i * 100) / max;
                loadingBar->setValue(val);
            }
            if(c == '&'){

                if(i+2 < max and buffer.str()[i+1] == 'n' and buffer.str()[i+2] == '='){
                    if(name != "" or date != "" or timeStart != "" or timeEnd != ""){
                        cerr << "Erreur : ligne " << line - 1 << " : pas de fin de ligne" << endl;
                        name = date = timeStart = timeEnd = "";
                    }
                    sequence = 1;
                    i += 2;
                    abortR = false;
                }else if(i+2 < max and buffer.str()[i+1] == 'd' and buffer.str()[i+2] == '='){
                    if(isStringEmpty(name)){
                        cerr << "Erreur : ligne " << line << " : name est vide" << endl;
                        abortR = true;
                    }
                    sequence = 2;
                    i += 2;
                }else if(i+3 < max and buffer.str()[i+1] == 't' and buffer.str()[i+2] == 's' and buffer.str()[i+3] == '='){
                    if(isStringEmpty(date)){
                        cerr << "Erreur : ligne " << line << " : date est vide" << endl;
                        abortR = true;
                    }
                    sequence = 3;
                    i += 3;
                }else if(i+3 < max and buffer.str()[i+1] == 't' and buffer.str()[i+2] == 'e' and buffer.str()[i+3] == '='){
                    if(isStringEmpty(timeStart)){
                        cerr << "Erreur : ligne " << line << " : timeStart est vide" << endl;
                        abortR = true;
                    }
                    sequence = 4;
                    i += 3;
                }else if(i+4 < max and buffer.str()[i+1] == 'e' and buffer.str()[i+2] == 'n' and buffer.str()[i+3] == 'd' and buffer.str()[i+3] == 'R'){
                    if(isStringEmpty(timeEnd)){
                        cerr << "Erreur : ligne " << line << " : timeEnd est vide" << endl;
                        abortR = true;
                    }

                    if(!abortR){
                        Date d;
                        Hour tS, tE;
                        if(stoDate(date, d) and stoHour(timeStart, tS) and stoHour(timeEnd, tE)){
                            RDV* rdv = new RDV(name, d, tS, tE);
                            if(!listRDV.inserer(rdv)){
                                cerr << "Erreur : ligne " << line << " : le RDV est deja dans la base de donnees" << endl;
                                delete rdv;
                                abortP = true;
                            }

                        }else cerr << "Erreur : ligne " << line << " : format de date ou d'heure incorrect" << endl;
                    }

                    sequence = 5;
                    i += 4;
                }
                else if(i+2 < max and buffer.str()[i+1] == 'l' and buffer.str()[i+2] == '='){
                    if(lastName != "" or firstName != ""){
                        cerr << "Erreur : ligne " << line - 1 << " : pas de fin de ligne" << endl;
                        lastName = firstName = "";
                    }
                    sequence = 5;
                    i += 2;
                    if(!abortR) abortP = false;

                }else if(i+2 < max and buffer.str()[i+1] == 'f' and buffer.str()[i+2] == '='){
                    if(isStringEmpty(lastName)){
                        cerr << "Erreur : ligne " << line << " : lastName est vide" << endl;
                        abortP = true;
                    }
                    sequence = 6;
                    i += 2;

                }else if(i+4 < max and buffer.str()[i+1] == 'e' and buffer.str()[i+2] == 'n' and buffer.str()[i+3] == 'd' and buffer.str()[i+4] == 'P'){
                    if(isStringEmpty(firstName)){
                        cerr << "Erreur : ligne " << line << " : firstName est vide" << endl;
                        abortP = true;
                    }

                    if(!abortP){
                        Personne* p = new Personne(firstName, lastName, "", "");
                        Date d;
                        stoDate(date, d);
                        Hour tS, tE;
                        stoHour(timeStart, tS);
                        stoHour(timeEnd, tE);
                        RDV* rdv = new RDV(name, d, tS, tE);
                        int ind = listPersonnes.rechD(p);
                        if(ind != -1){
                            delete p;
                            p = listPersonnes[ind];
                            ind = listRDV.rechD(rdv);
                            delete rdv;
                            rdv = listRDV[ind];

                            if(!rdv->addMember(p)){
                                cerr << "Erreur : ligne " << line << " : La Personne est deja dans le RDV" << endl;
                                delete p;
                            }
                        }else{
                            listPersonnes.inserer(p);

                            if(!rdv->addMember(p)){
                                cerr << "Erreur : ligne " << line << " : La Personne est deja dans le RDV" << endl;
                                delete p;
                            }
                        }
                    }
                    sequence = 0;
                    i += 4;
                    name = date = timeStart = timeEnd = lastName = firstName = "";

                }else{
                    if(c == '\n') ++line;
                    switch(sequence){
                    case 0:
                        break;
                    case 1:
                        name += c;
                        break;
                    case 2:
                        date += c;
                        break;
                    case 3:
                        timeStart += c;
                        break;
                    case 4:
                        timeEnd += c;
                        break;
                    case 5:
                        lastName += c;
                        break;
                    case 6:
                        firstName += c;
                        break;
                    default:
                        cerr << "Erreur : sequence = " << sequence << endl;
                        break;
                    }
                }
            }else{
                if(c == '\n') ++line;
                switch(sequence){
                case 0:
                    break;
                case 1:
                    name += c;
                    break;
                case 2:
                    date += c;
                    break;
                case 3:
                    timeStart += c;
                    break;
                case 4:
                    timeEnd += c;
                    break;
                case 5:
                    lastName += c;
                    break;
                case 6:
                    firstName += c;
                    break;
                default:
                    cerr << "Erreur : sequence = " << sequence << endl;
                    break;
                }
            }
        }

        if(loadingBar != nullptr){
            val = (i * 100) / max;
            loadingBar->setValue(val);
        }

        if(lastName != "" or firstName != "")
            cerr << "Erreur : ligne " << line << " : pas de fin de ligne" << endl;


        loaded = true;
    }

    cout << "Fichier charge " << (loaded ? "avec" : "sans") << " succes" << endl;
    return loaded;

}

bool Manager::removePersonne(Personne* p){
}

bool Manager::removeRDV(RDV* rdv){
}

bool Manager::savePersonne(const string& filePath, QProgressBar* loadingBar){
    cout << "Enregistrement du fichier " << (filePath == "" ? FILENAMEPERSONNE : filePath + FILENAMEPERSONNE) << endl;
    bool saved = false;
    ofstream ofs(filePath == "" ? FILENAMEPERSONNE : filePath + FILENAMEPERSONNE);

    if(!ofs)
        cerr << "Erreur, impossible d'ouvrir le fichier en ecriture" << endl;
    else{
        int i = 0;
        loadingBar->setRange(0, listPersonnes.size());
        loadingBar->setValue(0);
        string buf = "";
        for(i = 0; i < listPersonnes.size(); ++i){
            auto p = listPersonnes[i];
            buf += (string) "&l=" + p->getLastName()
                    + "&f=" + p->getFirstName()
                    + "&p=" + p->getPhone()
                    + "&e=" + p->getEmail()
                    + "&endP\n";
            if(loadingBar != nullptr)
                loadingBar->setValue(i);
        }
        if(loadingBar != nullptr)
            loadingBar->setValue(i);

        i = 0;
        loadingBar->setMaximum(buf.length());
        loadingBar->setValue(i);
        stringstream buffer;
        for(char c : buf){
            buffer.put(c);
            if(loadingBar != nullptr){
                loadingBar->setValue(i++);
            }
            cout << c;
        }
        if(loadingBar != nullptr)
            loadingBar->setValue(i);

        ofs << buffer.rdbuf();

        saved = true;

    }

    cout << "Fichier enregistre " << (saved ? "avec" : "sans") << " succes" << endl;
    return saved;

}

bool Manager::saveRDV(const string& filePath, QProgressBar* loadingBar){
    cout << "Enregistrement du fichier " << (filePath == "" ? FILENAMERDV : filePath + FILENAMERDV) << endl;
    bool saved = false;
    ofstream ofs(filePath == "" ? FILENAMERDV : filePath + FILENAMERDV);

    if(!ofs)
        cerr << "Erreur, impossible d'ouvrir le fichier en ecriture" << endl;
    else{
        int ind = 0, max = listRDV.size();
        for(int ind = 0; ind < listRDV.size(); ++ind) max += listRDV[ind]->getMembersList().size();
        double val = 0;
        string buf = "";
        for(int i = 0; i < listRDV.size(); ++i){
            auto rdv = listRDV[i];
            buf += (string) "&n=" + rdv->getName()
                    + "&d=" + rdv->getDate().toString()
                    + "&ts=" + rdv->getTimeStart().toString(true)
                    + "&te=" + rdv->getTimeEnd().toString(true)
                    + "&endR\n";
            if(loadingBar != nullptr){
                val = (ind * 100) / max;
                loadingBar->setValue(val);
                ++ind;
            }
            for(auto p : rdv->getMembersList()){
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

    cout << "Fichier enregistre " << (saved ? "avec" : "sans") << " succes" << endl;
    return saved;

}



// ---------- Getteurs ----------



// ---------- Setteurs ----------



// ---------- Fonctions globales ----------


