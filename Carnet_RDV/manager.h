#ifndef MANAGER_H
#define MANAGER_H

#include "date.h"
#include "hour.h"
#include "ldcp.h"
#include "ldcr.h"

#include <QProgressBar>

#include <fstream>
#include <sstream>

// Fonction annexe
bool isStringEmpty(const string& s);

class Manager
{
private:
    const string FILENAMEPERSONNE = "Personne.carnetRDV";
    const string FILENAMERDV = "RDV.carnetRDV";

    LDCP listPersonnes;
    LDCR listRDV;

public:
    Manager(void);

    // Surcharge des opérateurs

    // Méthodes
    bool addPersonne(Personne* p);
    bool addRDV(RDV* rdv);
    bool loadPersonne(const string& filePath = "", QProgressBar* loadingBar = nullptr);
    bool loadRDV(const string& filePath = "", QProgressBar* loadingBar = nullptr);
    bool removePersonne(Personne* p);
    bool removeRDV(RDV* rdv);
    bool savePersonne(const string& filePath = "", QProgressBar* loadingBar = nullptr);
    bool saveRDV(const string& filePath = "", QProgressBar* loadingBar = nullptr);

    // Getteurs

    // Setteurs

};

// Fonctions globales

#endif // MANAGER_H
