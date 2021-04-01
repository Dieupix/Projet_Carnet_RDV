#ifndef MANAGER_H
#define MANAGER_H

#include "date.h"
#include "hour.h"
#include "ldcp.h"
#include "ldcr.h"

#include <QProgressBar>

#include <fstream>
#include <sstream>

// Fonctions annexes
bool isStringEmpty(const string& s);

const static string FILENAMEPERSONNE = "Personne.carnetRDV";
const static QString QFILENAMEPERSONNE = "Personne.carnetRDV";
const static string FILENAMERDV = "RDV.carnetRDV";
const static QString QFILENAMERDV = "RDV.carnetRDV";

class Manager
{
private:
    LDCP listPersonnes;
    LDCR listRDV;

public:
    Manager(void);

    // Surcharge des opérateurs

    // Méthodes
    bool addPersonne(Personne* p);
    bool addRDV(RDV* rdv);
    bool loadPersonne(const string& filePath = FILENAMEPERSONNE, QProgressBar* loadingBar = nullptr);
    bool loadRDV(const string& filePath = FILENAMERDV, QProgressBar* loadingBar = nullptr);
    bool removePersonne(Personne* p);
    bool removeRDV(RDV* rdv);
    bool savePersonne(const string& filePath = FILENAMEPERSONNE, QProgressBar* loadingBar = nullptr);
    bool saveRDV(const string& filePath = FILENAMERDV, QProgressBar* loadingBar = nullptr);

    // Getteurs
    const LDCP& getListPersonnes(void) const;
    const LDCR& getListRDV(void) const;

    // Setteurs

};

// Fonctions globales

#endif // MANAGER_H
