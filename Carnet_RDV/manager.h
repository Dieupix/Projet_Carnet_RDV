#ifndef MANAGER_H
#define MANAGER_H

#include "ldcp.h"
#include "ldcr.h"

#include <QProgressBar>

#include <fstream>
#include <sstream>

const string FILENAMEPERSONNE = "Personne.carnetRDV";
const string FILENAMERDV = "RDV.carnetRDV";

class manager
{
private:
    LDCP listPersonnes;
    LDCR listRDV;

public:
    manager(void);

    // Surcharge des opérateurs

    // Méthodes
    bool loadPersonne(const string& filePath = "", QProgressBar* loadingBar = nullptr);
    bool loadRDV(const string& filePath = "", QProgressBar* loadingBar = nullptr);

    bool savePersonne(const string& filePath = "", QProgressBar* loadingBar = nullptr);
    bool saveRDV(const string& filePath = "", QProgressBar* loadingBar = nullptr);

    // Getteurs

    // Setteurs

};

// Fonctions globales

#endif // MANAGER_H
