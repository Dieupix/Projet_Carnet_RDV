#include "mainwindow.h"

// ---------- FONCTIONS ANNEXES ----------
void preHideOrShow(QBoxLayout* QBoxToHideOrShow, bool show){
    for(int i = 0; i < QBoxToHideOrShow->count(); i++){
        auto item = QBoxToHideOrShow->itemAt(i);
        auto w = item ? item->widget() : 0;
        if(w) w->setVisible(show);
        auto l = item ? (QBoxLayout*) item->layout() : 0;
        if(l) preHideOrShow(l, show);
    }
}

void hideOrShow(QBoxLayout* QBoxToHideOrShow, bool show, QBoxLayout* parent, int ind, int stretch){
    preHideOrShow(QBoxToHideOrShow, show);
    if(ind == -1 or ind > parent->count()) ind = parent->count();
    if(show) parent->insertLayout(ind, QBoxToHideOrShow, stretch);
    else parent->removeItem(QBoxToHideOrShow);
}
// ---------- FIN FONCTIONS ANNEXES ----------



MainWindow::MainWindow(QMainWindow *parent)
    : QMainWindow(parent), window(this)
{
    setup();
}



// ---------- Méthodes privées ----------
void MainWindow::setup(void){
    setWindowState(Qt::WindowMaximized);

    auto central = new QWidget();
    auto fixedLayout = new QVBoxLayout();
    central->setLayout(fixedLayout);
    window->setCentralWidget(central);

    setupMenuBar();

    fixedLayout->addLayout(setupButtonLayout());
    fixedLayout->addSpacing(5);
    fixedLayout->addLayout(setupMainLayout(), 10);
    fixedLayout->addLayout(setupListLayout(), 4);
    fixedLayout->addStretch(1);
    fixedLayout->addLayout(setupFooterLayout());

    setupRechRdvDate();

    updateWindowTitle();
}

QBoxLayout* MainWindow::setupButtonLayout(void) {
    auto buttonLayout = new QHBoxLayout();

    auto rechRdvDateButton = new QPushButton("Recherche de RDV par date");
    auto listRdvPersonneButton = new QPushButton("Liste de RDV d'une Personne");
    auto listPersonneRdvButton = new QPushButton("Liste de Personne d'un RDV");

    buttonLayout->addWidget(rechRdvDateButton, 0, Qt::AlignCenter);
    buttonLayout->addWidget(listRdvPersonneButton, 0, Qt::AlignCenter);
    buttonLayout->addWidget(listPersonneRdvButton, 0, Qt::AlignCenter);

    connect(rechRdvDateButton, &QPushButton::clicked, this, &MainWindow::onRechRdvDate);

    return buttonLayout;
}

void MainWindow::setupEditMenu(QMenu* editMenu){
    auto addPersonneAction = new QAction(tr("&Ajouter une Personne", "&Add a People"));
    addPersonneAction->setToolTip(tr("Ajouter une Personne à la base de données", "Add a People to the data base"));
    addPersonneAction->setIcon(QIcon("../Carnet_RDV/icons/icon_macos_maximiser_black1_100"));
    addPersonneAction->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_P));
    addPersonneAction->setShortcutVisibleInContextMenu(true);
    editMenu->addAction(addPersonneAction);

    auto addRDVAction = new QAction(tr("&Ajouter un RDV", "&Add an appointment"));
    addRDVAction->setToolTip(tr("Ajouter un RDV à la base de données", "Add an appointment to the data base"));
    addRDVAction->setShortcut(QKeySequence(Qt::CTRL| Qt::Key_R));
    addRDVAction->setShortcutVisibleInContextMenu(true);
    editMenu->addAction(addRDVAction);

    editMenu->addSeparator();

    auto removePersonneAction = new QAction(tr("&Retirer une Personne", "&Remove a People"));
    removePersonneAction->setToolTip(tr("Retirer une Personne de la base de données", "Remove a People from the data base"));
    removePersonneAction->setIcon(QIcon("../Carnet_RDV/icons/icon_macos_minimiser_black1_100"));
    removePersonneAction->setShortcut(QKeySequence(Qt::CTRL | Qt::ALT | Qt::Key_P));
    removePersonneAction->setShortcutVisibleInContextMenu(true);
    editMenu->addAction(removePersonneAction);

    auto removeRDVAction = new QAction(tr("&Retirer un RDV", "&Remove an appointment"));
    removeRDVAction->setToolTip(tr("Retirer un RDV de la base de données", "Remove an appointment from the data base"));
    removeRDVAction->setShortcut(QKeySequence(Qt::CTRL | Qt::ALT | Qt::Key_R));
    removeRDVAction->setShortcutVisibleInContextMenu(true);
    editMenu->addAction(removeRDVAction);
}

void MainWindow::setupFileMenu(QMenu *fileMenu){
    auto loadAction = new QAction(tr("&Ouvrir un fichier", "&Open a file") + "...");
    loadAction->setToolTip(tr("Ouvrir un fichier de personne ou de rendez-vous", "Open a file of People or appointments"));
    loadAction->setIcon(QIcon("../Carnet_RDV/icons/icon_dossier_ouvert_black1_100"));
    loadAction->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_O));
    loadAction->setShortcutVisibleInContextMenu(true);
    fileMenu->addAction(loadAction);

    fileMenu->addSeparator();

    auto saveAction = new QAction(tr("Enregi&strer", "&Save"));
    saveAction->setToolTip(tr("Enregistrer le carnet de rendez-vous", "Save the appointment book"));
    saveAction->setIcon(QIcon("../Carnet_RDV/icons/icon_sauvegarder_black1_100"));
    saveAction->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_S));
    saveAction->setShortcutVisibleInContextMenu(true);
    fileMenu->addAction(saveAction);

    auto saveAndQuitAction = new QAction(tr("Enregi&strer et quitter", "&Save and close"));
    saveAndQuitAction->setToolTip(tr("Enregistrer le carnet et quitter", "Save the appointment book and close"));
    saveAndQuitAction->setIcon(QIcon("../Carnet_RDV/icons/icon_enregistrer_et_fermer_black1_100"));
    saveAndQuitAction->setShortcut(QKeySequence(Qt::CTRL | Qt::SHIFT | Qt::Key_Q));
    saveAndQuitAction->setShortcutVisibleInContextMenu(true);
    fileMenu->addAction(saveAndQuitAction);

    fileMenu->addSeparator();

    auto quitAction = new QAction(tr("&Quitter", "&Exit"));
    quitAction->setToolTip(tr("Quitter l'application", "Exit the application"));
    quitAction->setIcon(QIcon("../Carnet_RDV/icons/icon_sortie_black1_100"));
    quitAction->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_Q));
    quitAction->setShortcutVisibleInContextMenu(true);
    fileMenu->addAction(quitAction);

    connect(loadAction, &QAction::triggered, this, &MainWindow::loadFile);
    connect(quitAction, &QAction::triggered, this, &MainWindow::onQuit);
    connect(saveAction, &QAction::triggered, this, &MainWindow::onSave);
    connect(saveAndQuitAction, &QAction::triggered, this, &MainWindow::onSaveAndQuit);
}

QBoxLayout* MainWindow::setupFooterLayout(void){
    auto preFooterLayout = new QVBoxLayout();

    auto line = new QFrame();
    line->setFrameStyle(QFrame::HLine);
    preFooterLayout->addStretch(0);
    preFooterLayout->addWidget(line, 0, Qt::AlignBottom);

    auto footerLayout = new QHBoxLayout();
    auto teamLabel = new QLabel("BARRÈRE Manuel - JANON Alexandre - POMMIER Logan");
    teamLabel->setToolTip(tr("L'équipe du projet", "Team of the project"));

    auto uhaLabel = new QLabel(tr(string("Université de Haute Alsace - (<a href='" + uhaURL.toStdString() + "'>UHA</a>)").c_str(), string("University of Hupper Alsace - (<a href='" + uhaURL.toStdString() + "'>UHA</a>)").c_str()));
    uhaLabel->setOpenExternalLinks(true);
    uhaLabel->setToolTip(tr("Accéder au site internet de l'UHA", "Website of the UHA"));

    footerLayout->addWidget(teamLabel, 0, Qt::AlignLeft);
    footerLayout->addStretch(0);
    footerLayout->addWidget(uhaLabel, 0, Qt::AlignRight);

    preFooterLayout->addLayout(footerLayout);
    preFooterLayout->setContentsMargins(0, 5, 0, 0);

    return preFooterLayout;
}

QBoxLayout* MainWindow::setupListLayout(void) {
    listLayout = new QHBoxLayout();

    rdvListLayout = new QVBoxLayout();
    auto rdvListLabel = new QLabel(tr("Liste de tous les rendez-vous", "List of all appointments"));
    rdvListLabel->setFont(QFont(rdvListLabel->font().family(), 20));
    rdvListLayout->addWidget(rdvListLabel, 0, Qt::AlignHCenter);

    auto saRDV = new QScrollArea();
    auto saRDVWidget = new QWidget();
    auto saRDVLayout = new QVBoxLayout();
    if(manager.getListRDV().size() == 0) saRDVLayout->addWidget(new QLabel(tr("Aucune personne dans la base de données", "Any People in the data base")));
    else for(unsigned i = 0; i < manager.getListRDV().size(); ++i)
            saRDVLayout->addWidget(new QPushButton(manager.getListRDV()[i]->toQString()));

    saRDVLayout->addStretch();
    saRDVWidget->setLayout(saRDVLayout);
    saRDV->setWidget(saRDVWidget);
    saRDV->setWidgetResizable(true);
    rdvListLayout->addWidget(saRDV);

    personneListLayout = new QVBoxLayout();
    auto personneListLabel = new QLabel(tr("Liste de toutes les personnes", "List of all People"));
    personneListLabel->setFont(QFont(personneListLabel->font().family(), 20));
    personneListLayout->addWidget(personneListLabel, 0, Qt::AlignHCenter);

    auto saPersonne = new QScrollArea();
    auto saPersonneWidget = new QWidget();
    auto saPersonneLayout = new QVBoxLayout();
    if(manager.getListPersonnes().size() == 0) saPersonneLayout->addWidget(new QLabel(tr("Aucun rendez-vous dans la base de données", "Any appointment in the data base")));
    else for(unsigned i = 0; i < manager.getListPersonnes().size(); ++i)
            saPersonneLayout->addWidget(new QPushButton(manager.getListPersonnes()[i]->toQString()));

    saPersonneLayout->addStretch();
    saPersonneWidget->setLayout(saPersonneLayout);
    saPersonne->setWidget(saPersonneWidget);
    saPersonne->setWidgetResizable(true);
    personneListLayout->addWidget(saPersonne);

    listLayout->addLayout(rdvListLayout);
    listLayout->addLayout(personneListLayout);

    return listLayout;

}

QBoxLayout* MainWindow::setupMainLayout(void){
    mainLayout = new QHBoxLayout();

    auto sa = new QScrollArea();
    auto saWidget = new QWidget();
    auto saLayout = new QHBoxLayout();
    saWidget->setLayout(saLayout);
    sa->setWidget(saWidget);
    sa->setWidgetResizable(true);

    mainLayout->addWidget(sa);

    return mainLayout;
}

void MainWindow::setupMenuBar(void){
    setupFileMenu(menuBar()->addMenu(tr("&Fichier", "&File")));
    setupEditMenu(menuBar()->addMenu(tr("&Éditer", "&Edit")));
    setupViewMenu(menuBar()->addMenu(tr("&Affichage", "&View")));
}

void MainWindow::setupRechRdvDate(void){
    this->rechRdvDate = new QHBoxLayout();
    rechRdvDate->setObjectName("rechRdvDateLayout");

    auto date = new QLineEdit();
    auto formLayout = new QFormLayout();
    rechRdvDate->addLayout(formLayout);
    formLayout->addRow("Date", date);

}

void MainWindow::setupViewMenu(QMenu* viewMenu){
    auto personneListCheckBox = new QAction(tr("Afficher la liste des &Personnes", "Show the list of &People"));
    personneListCheckBox->setToolTip(tr("Affiche la liste de toutes les Personnes", "Show the list of all People"));
    personneListCheckBox->setIcon(QIcon("../Carnet_RDV/icons/icon_carnet_rdv_black1_100"));
    personneListCheckBox->setShortcut(QKeySequence(Qt::ALT | Qt::Key_P));
    personneListCheckBox->setShortcutVisibleInContextMenu(true);
    personneListCheckBox->setCheckable(true);
    personneListCheckBox->setChecked(true);
    viewMenu->addAction(personneListCheckBox);

    auto rdvListCheckBox = new QAction(tr("Afficher la liste des &RDV", "Show the list of &appointments"));
    rdvListCheckBox->setToolTip(tr("Affiche la liste de tous les Rendez-vous", "Show the list of all appointments"));
    rdvListCheckBox->setIcon(QIcon("../Carnet_RDV/icons/icon_carnet_d'adresses_black1_100"));
    rdvListCheckBox->setShortcut(QKeySequence(Qt::ALT | Qt::Key_R));
    rdvListCheckBox->setShortcutVisibleInContextMenu(true);
    rdvListCheckBox->setCheckable(true);
    rdvListCheckBox->setChecked(true);
    viewMenu->addAction(rdvListCheckBox);

    connect(personneListCheckBox, &QAction::toggled, this, &MainWindow::onPersonneListCheckBox);
    connect(rdvListCheckBox, &QAction::toggled, this, &MainWindow::onRDVListCheckBox);
}

void MainWindow::showPersonneListLayout(bool b) {
    hideOrShow(personneListLayout, b, listLayout, 1);
    auto central = window->centralWidget();
    auto item = central ? central->layout() : 0;
    auto fixedLayout = item ? (QVBoxLayout*) item : 0;
    if(fixedLayout){
        if(listLayout->count() == 0 and !b) hideOrShow(listLayout, false, fixedLayout, 3, 4);
        else if(listLayout->count() == 1 and b) hideOrShow(listLayout, true, fixedLayout, 3, 4);
    }
}

void MainWindow::showRDVListLayout(bool b) {
    hideOrShow(rdvListLayout, b, listLayout, 0);
    auto central = window->centralWidget();
    auto item = central ? central->layout() : 0;
    auto fixedLayout = item ? (QVBoxLayout*) item : 0;
    if(fixedLayout){
        if(listLayout->count() == 0 and !b) hideOrShow(listLayout, false, fixedLayout, 3, 4);
        else if(listLayout->count() == 1 and b) hideOrShow(listLayout, true, fixedLayout, 3, 4);
    }
}

void MainWindow::updatePersonneListLayout(void){
    auto saPersonneWidget = new QWidget();
    auto saPersonneLayout = new QVBoxLayout();
    if(manager.getListPersonnes().size() == 0) saPersonneLayout->addWidget(new QLabel(tr("Aucune personne dans la base de données", "Any People in the data base")));
    else for(unsigned i = 0; i < manager.getListPersonnes().size(); ++i)
            saPersonneLayout->addWidget(new QPushButton(manager.getListPersonnes()[i]->toQString()));

    saPersonneLayout->addStretch();
    saPersonneWidget->setLayout(saPersonneLayout);

    auto item = personneListLayout->itemAt(1);
    auto SA = item ? item->widget() : 0;
    if(SA){
        auto* qsa = (QScrollArea*) SA;
        qsa->setWidget(saPersonneWidget);
    }
}

void MainWindow::updateRDVListLayout(void){
    auto saRDVWidget = new QWidget();
    auto saRDVLayout = new QVBoxLayout();
    if(manager.getListRDV().size() == 0) saRDVLayout->addWidget(new QLabel(tr("Aucun rendez-vous dans la base de données", "Any appointment in the data base")));
    else for(unsigned i = 0; i < manager.getListRDV().size(); ++i)
            saRDVLayout->addWidget(new QPushButton(manager.getListRDV()[i]->toQString()));

    saRDVLayout->addStretch();
    saRDVWidget->setLayout(saRDVLayout);

    auto item = rdvListLayout->itemAt(1);
    auto SA = item ? item->widget() : 0;
    if(SA){
        auto qsa = (QScrollArea*) SA;
        qsa->setWidget(saRDVWidget);
    }
}

void MainWindow::updateWindowTitle(void){
    setWindowTitle(windowTitle + (isSaved ? "" : "*"));
}



// ---------- Méthodes publiques ----------
void MainWindow::loadFile(void){

    QString filters =   tr("Fichiers de Personne ou de RDV (*.carnetRDV);;"
                        "Tous les fichiers (*)",
                        "Files of People or appointment (*.carnetRDV);;"
                        "All files (*)");

    auto filePath = QFileDialog::getOpenFileName(nullptr, windowTitle, windowFilePath(), filters);

    if(filePath != ""){
        if(filePath.endsWith(QFILENAMEPERSONNE) or filePath.endsWith(QFILENAMERDV)){

            int exe = LoadingDialog(this, filePath).exec();
            if(exe == QDialog::Accepted) setSave(false);

        }else{
            QString msg =   tr("Fichier invalide."
                            "\n\n"
                            "Veuillez sélectionner un fichier de Personne ou de Rendez-vous."
                            "\t\n",
                            "Invalid File."
                            "\n\n"
                            "Please select a file of People or appointment"
                            "\t\n");

            int exe = QMessageBox(QMessageBox::Critical, tr("Erreur de fichier", "File error"), msg, QMessageBox::Retry | QMessageBox::Cancel).exec();
            if(exe == QMessageBox::Retry) loadFile();
        }
    }
}

bool MainWindow::saveFile(void){
    QString msg = "", title = tr("Sauvegarde", "Save");

    bool saved = manager.savePersonne() and manager.saveRDV();
    cout << endl;

    if(saved){
        msg =   tr("Fichiers sauvegardés"
                "\t\n",
                "Files saved"
                "\t\n",
                2);
    }else{
        msg =   tr("Erreur lors de la sauvegarde"
                "\t\n",
                "Error while saving"
                "\t\n");
    }

    QMessageBox((saved ? QMessageBox::Information : QMessageBox::Warning), title, msg).exec();

    return saved;

}



// ---------- Getters ----------
Manager& MainWindow::getManager(void){
    return this->manager;
}

QString MainWindow::getWindowTitle(void){
    return this->windowTitle;
}



// ---------- Setters ----------
void MainWindow::setSave(bool saved){
    this->isSaved = saved;
    updateWindowTitle();
}



// ---------- Slots privés ----------
void MainWindow::onPersonneListCheckBox(bool b){
    showPersonneListLayout(b);
}

void MainWindow::onQuit(void){
    if(isSaved) close();
    else{
        QString msg =   tr("Votre Carnet de Rendez-vous n'est pas enregistré"
                        "\n\n"
                        "Voulez-vous vraiment quitter sans enregistrer ?"
                        "\t\n",
                        "Your appointment book is not saved"
                        "\n\n"
                        "Would you like to quit without saving?"
                        "\t\n");

        int exit = QMessageBox(QMessageBox::Information, windowTitle, msg, QMessageBox::Yes | QMessageBox::Save | QMessageBox::No).exec();

        if(exit == QMessageBox::Save){
            onSave();
            close();
        }else if(exit == QMessageBox::Yes) close();
    }
}

void MainWindow::onRDVListCheckBox(bool b){
    showRDVListLayout(b);
}

void MainWindow::onRechRdvDate(void){
    auto item = mainLayout->itemAt(0);
    auto SA = item ? (QScrollArea*) item->widget() : 0;
    auto saWidget = SA ? SA->widget() : 0;
    if(saWidget){
        auto layout = (QBoxLayout*) saWidget->layout();
        auto newWidget = new QWidget();
        if(!layout or layout->objectName() != rechRdvDate->objectName())
            newWidget->setLayout(rechRdvDate);
        else newWidget->setLayout(new QHBoxLayout());

        SA->setWidget(newWidget);
        if(SA->widget()->objectName() != rechRdvDate->objectName()) setupRechRdvDate();
    }
}

void MainWindow::onSaveAndQuit(void){
    onSave();
    onQuit();
}

void MainWindow::onSave(void){
    if(saveFile()){
        setSave(true);
    }
}

void MainWindow::onSpinBox(int) {
}
