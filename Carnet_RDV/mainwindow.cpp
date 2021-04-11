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
    setupListPersonneRdvLayout();
    setupListRdvPersonneLayout();

    updateWindowTitle();
}

QBoxLayout* MainWindow::setupButtonLayout(void) {
    auto buttonLayout = new QHBoxLayout();

    auto rechRdvDateButton = new QPushButton(tr("Recherche de RDV par date", "Find appointment with a date"));
    rechRdvDateButton->setMinimumHeight(30);
    auto listRdvPersonneButton = new QPushButton(tr("Liste de RDV d'une Personne", "List of all appointment of a People"));
    listRdvPersonneButton->setMinimumHeight(30);
    auto listPersonneRdvButton = new QPushButton(tr("Liste de Personne d'un RDV", "List of all People of an appointment"));
    listPersonneRdvButton->setMinimumHeight(30);
    auto changePersonneButton = new QPushButton(tr("Modifier une Personne", "Edit a People"));
    changePersonneButton->setMinimumHeight(30);
    auto changeRdvButton = new QPushButton(tr("Modifier un Rendez-vous", "Edit an appointment"));
    changeRdvButton->setMinimumHeight(30);
    auto changeMembersButton = new QPushButton(tr("Modifier les participants d'un Rendez-vous", "Edit participants of an appointment"));
    changeMembersButton->setMinimumHeight(30);

    buttonLayout->addWidget(rechRdvDateButton);
    buttonLayout->addWidget(listRdvPersonneButton);
    buttonLayout->addWidget(listPersonneRdvButton);
    buttonLayout->addWidget(changePersonneButton);
    buttonLayout->addWidget(changeRdvButton);
    buttonLayout->addWidget(changeMembersButton);

    connect(rechRdvDateButton, &QPushButton::clicked, this, &MainWindow::onRechRdvDate);
    connect(listPersonneRdvButton, &QPushButton::clicked, this, &MainWindow::onListPersonneRdv);

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

    connect(addPersonneAction, &QAction::triggered, this, &MainWindow::onAddPersonne);
    connect(addRDVAction, &QAction::triggered, this, &MainWindow::onAddRdv);
    connect(removePersonneAction, &QAction::triggered, this, &MainWindow::onRemovePersonne);
    connect(removeRDVAction, &QAction::triggered, this, &MainWindow::onRemoveRdv);
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

void MainWindow::setupListPersonneRdvLayout(void){
    this->listPersonneRdvLayout = new QVBoxLayout();
    listPersonneRdvLayout->setObjectName("listPersonneRdvLayout");

    auto editLayout = new QHBoxLayout();

    auto formLayout = new QFormLayout();
    formLayout->addRow(new QLabel(tr("Entrez le nom du rendez-vous", "Insert the name of the appointment")));
    this->listPersonneRdvLayoutLineEdit = new QLineEdit();
    listPersonneRdvLayoutLineEdit->setToolTip(tr("Saisir le nom du rendez-vous", "Put the name of the appointment"));
    listPersonneRdvLayoutLineEdit->setClearButtonEnabled(true);
    listPersonneRdvLayoutLineEdit->setDragEnabled(true);
    formLayout->addRow(tr("Nom", "Name"), listPersonneRdvLayoutLineEdit);

    editLayout->addLayout(formLayout);
    editLayout->addSpacing(50);

    auto rechButton = new QPushButton(tr("Rechercher", "Find"));
    editLayout->addWidget(rechButton, 0, Qt::AlignBottom);
    editLayout->addStretch(1);

    listPersonneRdvLayout->addLayout(editLayout);

    this->listPersonneRdvLayoutLabel = new QLabel();
    listPersonneRdvLayoutLabel->setFont(QFont(listPersonneRdvLayoutLabel->font().family(), 20));
    listPersonneRdvLayout->addWidget(listPersonneRdvLayoutLabel, 0, Qt::AlignHCenter);

    this->listPersonneRdvLayoutSA = new QScrollArea();
    auto saWidget = new QWidget();
    saWidget->setLayout(new QHBoxLayout());
    listPersonneRdvLayoutSA->setWidget(saWidget);
    listPersonneRdvLayoutSA->setWidgetResizable(true);
    listPersonneRdvLayout->addWidget(listPersonneRdvLayoutSA);

    connect(listPersonneRdvLayoutLineEdit, &QLineEdit::textChanged, this, &MainWindow::onTextChangedlistPersonneRdvLineEdit);
    connect(listPersonneRdvLayoutLineEdit, &QLineEdit::returnPressed, this, &MainWindow::onListPersonneRdvButton);
    connect(rechButton, &QPushButton::clicked, this, &MainWindow::onListPersonneRdvButton);

}

void MainWindow::setupListRdvPersonneLayout(void){
    this->listRdvPersonneLayout = new QVBoxLayout();
    listRdvPersonneLayout->setObjectName("listRdvPersonneLayout");
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
    this->rechRdvDate = new QVBoxLayout();
    rechRdvDate->setObjectName("rechRdvDateLayout");

    auto editLayout = new QHBoxLayout();

    auto formLayout = new QFormLayout();
    formLayout->addRow(new QLabel(tr("Entrez une date au format jj/mm/aaaa", "Insert a date as dd/mm/yyyy")));
    this->rechRdvDateLineEdit = new QLineEdit();
    rechRdvDateLineEdit->setToolTip(tr("Format : jj/mm/aaaa", "Format : dd/mm/yyyy"));
    rechRdvDateLineEdit->setClearButtonEnabled(true);
    rechRdvDateLineEdit->setInputMask("99/99/9999");
    rechRdvDateLineEdit->setMaxLength(10);
    rechRdvDateLineEdit->setDragEnabled(true);
    formLayout->addRow(tr("Date", "Date"), rechRdvDateLineEdit);

    editLayout->addLayout(formLayout);
    editLayout->addSpacing(50);

    auto rechButton = new QPushButton(tr("Rechercher", "Find"));
    editLayout->addWidget(rechButton, 0, Qt::AlignBottom);
    editLayout->addStretch(1);

    rechRdvDate->addLayout(editLayout);

    rechRdvDateLabel = new QLabel();
    rechRdvDateLabel->setFont(QFont(rechRdvDateLabel->font().family(), 20));
    rechRdvDate->addWidget(rechRdvDateLabel, 0, Qt::AlignHCenter);

    rechRdvDateSA = new QScrollArea();
    auto saWidget = new QWidget();
    saWidget->setLayout(new QHBoxLayout());
    rechRdvDateSA->setWidget(saWidget);
    rechRdvDateSA->setWidgetResizable(true);
    rechRdvDate->addWidget(rechRdvDateSA);

    connect(rechRdvDateLineEdit, &QLineEdit::textChanged, this, &MainWindow::onTextChangedrechRdvDateLineEdit);
    connect(rechRdvDateLineEdit, &QLineEdit::returnPressed, this, &MainWindow::onRechRdvDateButton);
    connect(rechButton, &QPushButton::clicked, this, &MainWindow::onRechRdvDateButton);

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
void MainWindow::onAddPersonne(void){
    auto md = ManagingDialog(this, ManagingDialog::AddPersonneToDataBase);
    auto exe = md.exec();
    if(exe == QDialog::Accepted){
        bool added = true;
        for(unsigned i = 0; i < md.getListPersonne().size(); ++i)
            if(!manager.addPersonne(md.getListPersonne()[i])) added = false;

        if(!added){
            QString msg = tr("Erreur lors de l'ajout d'une Personne", "Error while adding a People");
            QMessageBox(QMessageBox::Warning, windowTitle, msg, QMessageBox::Ok).exec();

        }else{
            QString msg = tr("Les Personne ont été ajoutées", "All People have been added");
            QMessageBox(QMessageBox::Information, windowTitle, msg, QMessageBox::Ok).exec();
        }
    }
}

void MainWindow::onAddRdv(void){
    auto exe = ManagingDialog(this, ManagingDialog::AddRdvToDataBase).exec();
    if(exe == QDialog::Accepted){

    }
}

void MainWindow::onRemovePersonne(void){
    auto exe = ManagingDialog(this, ManagingDialog::RemovePersonneFromDataBase).exec();
    if(exe == QDialog::Accepted){

    }
}

void MainWindow::onRemoveRdv(void){
    auto exe = ManagingDialog(this, ManagingDialog::RemoveRdvFromDataBase).exec();
    if(exe == QDialog::Accepted){

    }
}

void MainWindow::onListPersonneRdv(void){
    auto item = mainLayout->itemAt(0);
    auto SA = item ? (QScrollArea*) item->widget() : 0;
    auto saWidget = SA ? SA->widget() : 0;
    if(!listPersonneRdvLayout) setupListPersonneRdvLayout();
    if(saWidget){
        auto layout = (QBoxLayout*) saWidget->layout();
        auto newWidget = new QWidget();
        if(!layout or layout->objectName() != listPersonneRdvLayout->objectName())
            newWidget->setLayout(listPersonneRdvLayout);
        else newWidget->setLayout(new QVBoxLayout());

        SA->setWidget(newWidget);
        if(SA->widget()->objectName() != listPersonneRdvLayout->objectName()) setupListPersonneRdvLayout();
    }
}

void MainWindow::onListPersonneRdvButton(void){
    if(listPersonneRdvLayoutLineEdit and listPersonneRdvLayoutLabel){
        if(listPersonneRdvLayoutLineEdit->text() == ""){
            QString msg = tr("Erreur, le nom saisie est vide", "Error, the name is empty") + "\t";
            QMessageBox(QMessageBox::Warning, windowTitle, msg, QMessageBox::Ok).exec();
            return;
        }
        auto rdv = RDV(listPersonneRdvLayoutLineEdit->text().toStdString(), {}, {}, {});
        int ind = manager.getListRDV().rechD(&rdv);
        if(ind == -1){
            QString msg = tr("Aucun rendez-vous trouvé à ce nom", "Any appointment found for this name") + "\t\n\n" + listPersonneRdvLayoutLineEdit->text();
            QMessageBox(QMessageBox::Warning, windowTitle, msg, QMessageBox::Ok).exec();
        }else{
            QString msg = "Liste des participants au rendez-vous \"" + listPersonneRdvLayoutLineEdit->text() + "\"";
            QString trad = "List of all participants of the appointment named \"" + listPersonneRdvLayoutLineEdit->text() + "\"";
            listPersonneRdvLayoutLabel->setText(tr(msg.toStdString().c_str(), trad.toStdString().c_str()));
            rdv = *manager.getListRDV()[ind];
            auto newWidget = new QWidget();
            auto saLayout = new QVBoxLayout();

            if(rdv.getMembersList().size() == 0) saLayout->addWidget(new QLabel(tr("Aucun participant à ce rendez-vous", "Any participant at this appointment")));
            else for(auto p : rdv.getMembersList()) saLayout->addWidget(new QPushButton(p->toQString()));
            saLayout->addStretch(0);

            newWidget->setLayout(saLayout);
            listPersonneRdvLayoutSA->setWidget(newWidget);

            onRechRdvDate();
            onListPersonneRdv();

        }
    }
}

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
    if(!rechRdvDate) setupRechRdvDate();
    if(saWidget){
        auto layout = (QBoxLayout*) saWidget->layout();
        auto newWidget = new QWidget();
        if(!layout or layout->objectName() != rechRdvDate->objectName())
            newWidget->setLayout(rechRdvDate);
        else newWidget->setLayout(new QVBoxLayout());

        SA->setWidget(newWidget);
        if(SA->widget()->objectName() != rechRdvDate->objectName()) setupRechRdvDate();
    }
}

void MainWindow::onRechRdvDateButton(void){
    if(rechRdvDateLineEdit and rechRdvDateLabel){
        Date d = Date();
        if(rechRdvDateLineEdit->text() == "//"){
            QString msg =   tr("Erreur, la date est vide.", "Error, the date is empty.") + "\t";
            QMessageBox(QMessageBox::Warning, windowTitle, msg, QMessageBox::Ok).exec();
        }else if(!stoDate(rechRdvDateLineEdit->text().toStdString(), d)){
            cout << endl;
            QString msg =   tr("Erreur, la date est incorrecte.", "Error, the date is incorrect.") + "\t\n\n" + rechRdvDateLineEdit->text();
            QMessageBox(QMessageBox::Warning, windowTitle, msg, QMessageBox::Ok).exec();
        }else{
            rechRdvDateLabel->setText(tr("Liste de tous les Rendez-vous du", "List of all appointments for the date") + " " + d);

            auto newWidget = new QWidget();
            auto saLayout = new QVBoxLayout();

            auto rdvList = manager.rechRdvDate(d);
            if(rdvList.size() == 0) saLayout->addWidget(new QLabel(tr("Aucun rendez-vous pour cette date", "Any appointment for this date")));
            else for(auto rdv : rdvList) saLayout->addWidget(new QPushButton(rdv->toQString()));
            saLayout->addStretch(0);

            newWidget->setLayout(saLayout);
            rechRdvDateSA->setWidget(newWidget);
            onListPersonneRdv();
            onRechRdvDate();
        }
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

void MainWindow::onTextChangedlistPersonneRdvLineEdit(const QString& text){
    QSignalBlocker blocker(listPersonneRdvLayoutLineEdit);
    listPersonneRdvLayoutLineEdit->setText(text);
    blocker.unblock();
}

void MainWindow::onTextChangedrechRdvDateLineEdit(const QString& text){
    QSignalBlocker blocker(rechRdvDateLineEdit);
    rechRdvDateLineEdit->setText(text);
    blocker.unblock();
}
