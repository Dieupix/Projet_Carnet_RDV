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
    setupModifyPersonneLayout();
    setupModifyPersonneRdvLayout();

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
    auto changeRdvButton = new QPushButton(tr("Modifier un RDV", "Edit an appointment"));
    changeRdvButton->setMinimumHeight(30);
    auto changeMembersButton = new QPushButton(tr("Modifier les participants d'un RDV", "Edit participants of an appointment"));
    changeMembersButton->setMinimumHeight(30);

    buttonLayout->addWidget(rechRdvDateButton);
    buttonLayout->addWidget(listRdvPersonneButton);
    buttonLayout->addWidget(listPersonneRdvButton);
    buttonLayout->addWidget(changePersonneButton);
    buttonLayout->addWidget(changeRdvButton);
    buttonLayout->addWidget(changeMembersButton);

    connect(rechRdvDateButton, &QPushButton::clicked, this, &MainWindow::onRechRdvDate);
    connect(listPersonneRdvButton, &QPushButton::clicked, this, &MainWindow::onListPersonneRdv);
    connect(listRdvPersonneButton, &QPushButton::clicked, this, &MainWindow::onListRdvPersonne);
    connect(changeMembersButton, &QPushButton::clicked, this, &MainWindow::onModifyPersonneRdv);

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
    teamLabel->setTextInteractionFlags(Qt::TextBrowserInteraction);

    auto uhaLabel = new QLabel(tr(string("Université de Haute Alsace - (<a href='" + uhaURL.toStdString() + "'>UHA</a>)").c_str(),
                                  string("University of Hupper Alsace - (<a href='" + uhaURL.toStdString() + "'>UHA</a>)").c_str()));
    uhaLabel->setOpenExternalLinks(true);
    uhaLabel->setTextInteractionFlags(Qt::TextBrowserInteraction);
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
    rdvListLabel->setTextInteractionFlags(Qt::TextBrowserInteraction);
    rdvListLayout->addWidget(rdvListLabel, 0, Qt::AlignHCenter);

    auto saRDV = new QScrollArea();
    auto saRDVWidget = new QWidget();
    auto saRDVLayout = new QVBoxLayout();
    if(manager.getListRDV().size() == 0){
        auto label = new QLabel(tr("Aucun rendez-vous dans la base de données", "Any appointment in the data base"));
        label->setTextInteractionFlags(Qt::TextBrowserInteraction);
        saRDVLayout->addWidget(label);
    }
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
    personneListLabel->setTextInteractionFlags(Qt::TextBrowserInteraction);
    personneListLayout->addWidget(personneListLabel, 0, Qt::AlignHCenter);

    auto saPersonne = new QScrollArea();
    auto saPersonneWidget = new QWidget();
    auto saPersonneLayout = new QVBoxLayout();
    if(manager.getListPersonnes().size() == 0){
        auto label = new QLabel(tr("Aucune personne dans la base de données", "Any People in the data base"));
        label->setTextInteractionFlags(Qt::TextBrowserInteraction);
        saPersonneLayout->addWidget(label);
    }
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
    listPersonneRdvLayoutLabel->setTextInteractionFlags(Qt::TextBrowserInteraction);
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

    auto editLayout = new QHBoxLayout();

    auto formLayout = new QFormLayout();
    formLayout->addRow(new QLabel(tr("Saisir les informations de la Personne", "Insert the informations of the People")));
    this->listRdvPersonneLayoutLineEditLastName = new QLineEdit();
    listRdvPersonneLayoutLineEditLastName->setToolTip(tr("Saisir le nom de la Personne", "Put the lastname of the People"));
    listRdvPersonneLayoutLineEditLastName->setClearButtonEnabled(true);
    listRdvPersonneLayoutLineEditLastName->setDragEnabled(true);
    formLayout->addRow(tr("Nom", "Lastname"), listRdvPersonneLayoutLineEditLastName);
    this->listRdvPersonneLayoutLineEditFirstName = new QLineEdit();
    listRdvPersonneLayoutLineEditFirstName->setToolTip(tr("Saisir le prénom de la Personne", "Put the firstname of the People"));
    listRdvPersonneLayoutLineEditFirstName->setClearButtonEnabled(true);
    listRdvPersonneLayoutLineEditFirstName->setDragEnabled(true);
    formLayout->addRow(tr("Prénom", "Firstname"), listRdvPersonneLayoutLineEditFirstName);

    editLayout->addLayout(formLayout);
    editLayout->addSpacing(50);

    auto rechButton = new QPushButton(tr("Rechercher", "Find"));
    editLayout->addWidget(rechButton, 0, Qt::AlignVCenter);
    editLayout->addStretch(1);

    listRdvPersonneLayout->addLayout(editLayout);

    this->listRdvPersonneLayoutLabel = new QLabel();
    listRdvPersonneLayoutLabel->setFont(QFont(listRdvPersonneLayoutLabel->font().family(), 20));
    listRdvPersonneLayoutLabel->setTextInteractionFlags(Qt::TextBrowserInteraction);
    listRdvPersonneLayout->addWidget(listRdvPersonneLayoutLabel, 0, Qt::AlignHCenter);

    this->listRdvPersonneLayoutSA = new QScrollArea();
    auto saWidget = new QWidget();
    saWidget->setLayout(new QHBoxLayout());
    listRdvPersonneLayoutSA->setWidget(saWidget);
    listRdvPersonneLayoutSA->setWidgetResizable(true);
    listRdvPersonneLayout->addWidget(listRdvPersonneLayoutSA);

    connect(listRdvPersonneLayoutLineEditFirstName, &QLineEdit::textChanged, this, &MainWindow::onTextChangedlistRdvPersonneLineEditFirstName);
    connect(listRdvPersonneLayoutLineEditLastName, &QLineEdit::textChanged, this, &MainWindow::onTextChangedlistRdvPersonneLineEditLastName);
    connect(listRdvPersonneLayoutLineEditFirstName, &QLineEdit::returnPressed, this, &MainWindow::onListRdvPersonneButton);
    connect(rechButton, &QPushButton::clicked, this, &MainWindow::onListRdvPersonneButton);
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

void MainWindow::setupModifyPersonneLayout(void){
    this->modifyPersonneRdvLayout = new QVBoxLayout();
    modifyPersonneLayout->setObjectName("modifyPersonneLayout");

    auto editLayout = new QHBoxLayout();

    auto formLayout = new QFormLayout();
    formLayout->addRow(new QLabel(tr("Saisir les informations de la Personne (vide pour inchanger)", "Insert the informations of the People (blank to not change)")));
    this->modifyPersonneLayoutLineEditLastName = new QLineEdit();
    modifyPersonneLayoutLineEditLastName->setToolTip(tr("Saisir le nom de la Personne", "Put the lastname of the People"));
    modifyPersonneLayoutLineEditLastName->setClearButtonEnabled(true);
    modifyPersonneLayoutLineEditLastName->setDragEnabled(true);
    formLayout->addRow(tr("Nom", "Lastname"), modifyPersonneLayoutLineEditLastName);
    this->modifyPersonneLayoutLineEditFirstName = new QLineEdit();
    modifyPersonneLayoutLineEditFirstName->setToolTip(tr("Saisir le prénom de la Personne", "Put the firstname of the People"));
    modifyPersonneLayoutLineEditFirstName->setClearButtonEnabled(true);
    modifyPersonneLayoutLineEditFirstName->setDragEnabled(true);
    formLayout->addRow(tr("Prénom", "Firstname"), modifyPersonneLayoutLineEditFirstName);
    this->modifyPersonneLayoutLineEditEmail = new QLineEdit();
    modifyPersonneLayoutLineEditEmail->setToolTip(tr("Saisir la nouvelle adresse email", "Put the new email of the People"));
    modifyPersonneLayoutLineEditEmail->setClearButtonEnabled(true);
    modifyPersonneLayoutLineEditEmail->setDragEnabled(true);
    formLayout->addRow(tr("Adresse mail", "Email"), modifyPersonneLayoutLineEditEmail);
    this->modifyPersonneLayoutLineEditPhone = new QLineEdit();
    modifyPersonneLayoutLineEditPhone->setToolTip(tr("Saisir le nouveau numéro de téléphone", "Put the new phone number of the People"));
    modifyPersonneLayoutLineEditPhone->setClearButtonEnabled(true);
    modifyPersonneLayoutLineEditPhone->setDragEnabled(true);
    formLayout->addRow(tr("Téléphone", "Phone number"), modifyPersonneLayoutLineEditPhone);

    editLayout->addLayout(formLayout);
    editLayout->addSpacing(50);

    auto changeButton = new QPushButton(tr("Modifier", "Change"));
    editLayout->addWidget(changeButton, 0, Qt::AlignVCenter);
    editLayout->addStretch(1);

    modifyPersonneLayout->addLayout(editLayout);

    this->modifyPersonneLayoutLabel = new QLabel();
    modifyPersonneLayoutLabel->setFont(QFont(listRdvPersonneLayoutLabel->font().family(), 20));
    modifyPersonneLayoutLabel->setTextInteractionFlags(Qt::TextBrowserInteraction);
    modifyPersonneLayout->addWidget(modifyPersonneLayoutLabel, 0, Qt::AlignHCenter);

    this->modifyPersonneLayoutSA = new QScrollArea();
    auto saWidget = new QWidget();
    saWidget->setLayout(new QHBoxLayout());
    modifyPersonneLayoutSA->setWidget(saWidget);
    modifyPersonneLayoutSA->setWidgetResizable(true);
    modifyPersonneLayout->addWidget(modifyPersonneLayoutSA);

    connect(modifyPersonneLayoutLineEditEmail, &QLineEdit::textChanged, this, &MainWindow::onTextChangedmodifyPersonneLineEditEmail);
    connect(modifyPersonneLayoutLineEditFirstName, &QLineEdit::textChanged, this, &MainWindow::onTextChangedmodifyPersonneLineEditFirstName);
    connect(modifyPersonneLayoutLineEditLastName, &QLineEdit::textChanged, this, &MainWindow::onTextChangedmodifyPersonneLineEditLastName);
    connect(changeButton, &QPushButton::clicked, this, &MainWindow::onModifyPersonneRdvAddButton);
}

void MainWindow::setupModifyPersonneRdvLayout(void){
    this->modifyPersonneRdvLayout = new QVBoxLayout();
    modifyPersonneRdvLayout->setObjectName("modifyPersonneRdvLayout");

    auto editLayout = new QHBoxLayout();

    auto formLayout = new QFormLayout();
    formLayout->addRow(new QLabel(tr("Saisir le nom du Rendez-vous et les informations de la Personne", "Insert the name of the appoitnement and the informations of the People")));
    this->modifyPersonneRdvLayoutLineEditRdvName = new QLineEdit();
    modifyPersonneRdvLayoutLineEditRdvName->setToolTip(tr("Saisir le nom du Rendez-vous", "Put the name of the appointment"));
    modifyPersonneRdvLayoutLineEditRdvName->setClearButtonEnabled(true);
    modifyPersonneRdvLayoutLineEditRdvName->setDragEnabled(true);
    formLayout->addRow(tr("Rendez-vous", "Appointment (name)"), modifyPersonneRdvLayoutLineEditRdvName);
    this->modifyPersonneRdvLayoutLineEditLastName = new QLineEdit();
    modifyPersonneRdvLayoutLineEditLastName->setToolTip(tr("Saisir le nom de la Personne", "Put the lastname of the People"));
    modifyPersonneRdvLayoutLineEditLastName->setClearButtonEnabled(true);
    modifyPersonneRdvLayoutLineEditLastName->setDragEnabled(true);
    formLayout->addRow(tr("Nom", "Lastname"), modifyPersonneRdvLayoutLineEditLastName);
    this->modifyPersonneRdvLayoutLineEditFirstName = new QLineEdit();
    modifyPersonneRdvLayoutLineEditFirstName->setToolTip(tr("Saisir le prénom de la Personne", "Put the firstname of the People"));
    modifyPersonneRdvLayoutLineEditFirstName->setClearButtonEnabled(true);
    modifyPersonneRdvLayoutLineEditFirstName->setDragEnabled(true);
    formLayout->addRow(tr("Prénom", "Firstname"), modifyPersonneRdvLayoutLineEditFirstName);

    editLayout->addLayout(formLayout);
    editLayout->addSpacing(50);

    auto addButton = new QPushButton(tr("Ajouter", "Add"));
    editLayout->addWidget(addButton, 0, Qt::AlignVCenter);
    auto removeButton = new QPushButton(tr("Supprimer", "Remove"));
    editLayout->addWidget(removeButton, 0, Qt::AlignVCenter);
    editLayout->addStretch(1);

    modifyPersonneRdvLayout->addLayout(editLayout);

    this->modifyPersonneRdvLayoutLabel = new QLabel();
    modifyPersonneRdvLayoutLabel->setFont(QFont(listRdvPersonneLayoutLabel->font().family(), 20));
    modifyPersonneRdvLayoutLabel->setTextInteractionFlags(Qt::TextBrowserInteraction);
    modifyPersonneRdvLayout->addWidget(modifyPersonneRdvLayoutLabel, 0, Qt::AlignHCenter);

    this->modifyPersonneRdvLayoutSA = new QScrollArea();
    auto saWidget = new QWidget();
    saWidget->setLayout(new QHBoxLayout());
    modifyPersonneRdvLayoutSA->setWidget(saWidget);
    modifyPersonneRdvLayoutSA->setWidgetResizable(true);
    modifyPersonneRdvLayout->addWidget(modifyPersonneRdvLayoutSA);

    connect(modifyPersonneRdvLayoutLineEditRdvName, &QLineEdit::textChanged, this, &MainWindow::onTextChangedmodifyPersonneRdvLineEditRdvName);
    connect(modifyPersonneRdvLayoutLineEditFirstName, &QLineEdit::textChanged, this, &MainWindow::onTextChangedmodifyPersonneRdvLineEditFirstName);
    connect(modifyPersonneRdvLayoutLineEditLastName, &QLineEdit::textChanged, this, &MainWindow::onTextChangedmodifyPersonneRdvLineEditLastName);
    connect(addButton, &QPushButton::clicked, this, &MainWindow::onModifyPersonneRdvAddButton);
    connect(removeButton, &QPushButton::clicked, this, &MainWindow::onModifyPersonneRdvRemoveButton);
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
    rechRdvDateLabel->setTextInteractionFlags(Qt::TextBrowserInteraction);
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
    if(manager.getListPersonnes().size() == 0){
        auto label = new QLabel(tr("Aucune personne dans la base de données", "Any People in the data base"));
        label->setTextInteractionFlags(Qt::TextBrowserInteraction);
        saPersonneLayout->addWidget(label);
    }
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
    if(manager.getListRDV().size() == 0){
        auto label = new QLabel(tr("Aucun rendez-vous dans la base de données", "Any appointment in the data base"));
        label->setTextInteractionFlags(Qt::TextBrowserInteraction);
        saRDVLayout->addWidget(label);
    }
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

            LoadingDialog(this, filePath).exec();

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
            rdv = *manager.getListRDV()[ind];
            QString msg = tr("Liste des participants au rendez-vous", "List of all participants of the appointment named");
            listPersonneRdvLayoutLabel->setText(msg + " " + QString::fromStdString(rdv.getName()));
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

void MainWindow::onListRdvPersonne(void){
    auto item = mainLayout->itemAt(0);
    auto SA = item ? (QScrollArea*) item->widget() : 0;
    auto saWidget = SA ? SA->widget() : 0;
    if(!listRdvPersonneLayout) setupListRdvPersonneLayout();
    if(saWidget){
        auto layout = (QBoxLayout*) saWidget->layout();
        auto newWidget = new QWidget();
        if(!layout or layout->objectName() != listRdvPersonneLayout->objectName())
            newWidget->setLayout(listRdvPersonneLayout);
        else newWidget->setLayout(new QVBoxLayout());

        SA->setWidget(newWidget);
        if(SA->widget()->objectName() != listRdvPersonneLayout->objectName()) setupListRdvPersonneLayout();
    }
}

void MainWindow::onListRdvPersonneButton(void){
    if(listRdvPersonneLayoutLineEditFirstName and listRdvPersonneLayoutLineEditLastName and listRdvPersonneLayoutLabel){

        auto p = new Personne(listRdvPersonneLayoutLineEditFirstName->text().toStdString(),
                          listRdvPersonneLayoutLineEditLastName->text().toStdString(),
                          "", "");

        int ind = manager.getListPersonnes().rechD(p);
        if(ind == -1){
            QString msg =   tr("Erreur, la Personne n'existe pas", "Error, the People does not exists") + "\t\n" + QString::fromStdString(p->getFirstName() + " " + p->getLastName());
            QMessageBox(QMessageBox::Warning, windowTitle, msg, QMessageBox::Ok).exec();
            delete p;
        }else{
            delete p;
            p = manager.getListPersonnes()[ind];
            listRdvPersonneLayoutLabel->setText(tr("Liste de tous les Rendez-vous de", "List of all appointments for")
                                                + " " + QString::fromStdString(p->getLastName() + " " + p->getFirstName()));

            auto newWidget = new QWidget();
            auto saLayout = new QVBoxLayout();

            if(p->getRDVList().size() == 0) saLayout->addWidget(new QLabel(tr("Cette personne n'a aucun Rendez-vous", "This People has any appointment")));
            else for(auto rdv : p->getRDVList()) saLayout->addWidget(new QPushButton(rdv->toQString()));
            saLayout->addStretch(0);

            newWidget->setLayout(saLayout);
            listRdvPersonneLayoutSA->setWidget(newWidget);
            onListPersonneRdv();
            onListRdvPersonne();
        }
    }
}

void MainWindow::onModifyPersonneRdv(void){
    auto item = mainLayout->itemAt(0);
    auto SA = item ? (QScrollArea*) item->widget() : 0;
    auto saWidget = SA ? SA->widget() : 0;
    if(!modifyPersonneRdvLayout) setupModifyPersonneRdvLayout();
    if(saWidget){
        auto layout = (QBoxLayout*) saWidget->layout();
        auto newWidget = new QWidget();
        if(!layout or layout->objectName() != modifyPersonneRdvLayout->objectName())
            newWidget->setLayout(modifyPersonneRdvLayout);
        else newWidget->setLayout(new QVBoxLayout());

        SA->setWidget(newWidget);
        if(SA->widget()->objectName() != modifyPersonneRdvLayout->objectName()) setupModifyPersonneRdvLayout();
    }
}

void MainWindow::onModifyPersonneRdvAddButton(void){
    auto rdv = new RDV(modifyPersonneRdvLayoutLineEditRdvName->text().toStdString(), {}, {}, {});
    auto p = new Personne(modifyPersonneRdvLayoutLineEditFirstName->text().toStdString(), modifyPersonneRdvLayoutLineEditLastName->text().toStdString(), "", "");
    int ind = manager.getListRDV().rechD(rdv);
    if(ind == -1){
        QString msg = tr("Le Rendez-vous n'existe pas", "The appointment does not exists") + "\t\n" + QString::fromStdString(rdv->getName());
        QMessageBox(QMessageBox::Warning, windowTitle, msg, QMessageBox::Ok).exec();
        delete rdv;
        delete p;
    }else{
        rdv = manager.getListRDV()[ind];

        modifyPersonneRdvLayoutLabel->setText(tr("Liste des participants au Rendez-vous", "List of the participants at tha appointment") + " " + QString::fromStdString(rdv->getName()));

        auto newWidget = new QWidget();
        auto saLayout = new QVBoxLayout();

        if(rdv->getMembersList().size() == 0) saLayout->addWidget(new QLabel(tr("Ce Rendez-vous n'a aucun participant", "This appointment as any participant")));
        else for(auto pt : rdv->getMembersList()) saLayout->addWidget(new QPushButton(pt->toQString()));
        saLayout->addStretch(0);

        newWidget->setLayout(saLayout);
        modifyPersonneRdvLayoutSA->setWidget(newWidget);
        onListPersonneRdv();
        onModifyPersonneRdv();

        ind = manager.getListPersonnes().rechD(p);
        if(ind == -1){
            QString msg = tr("La Personne n'existe pas", "The People does not exists") + "\t\n" + QString::fromStdString(p->getLastName() + " " + p->getLastName());
            QMessageBox(QMessageBox::Warning, windowTitle, msg, QMessageBox::Ok).exec();
            delete p;
        }else{
            p = manager.getListPersonnes()[ind];
            int exe = rdv->addMember(p);

            if(exe == RDV::PersonneIsAlreadyInsideRdv){
                QString msg = QString::fromStdString(p->getLastName() + " " + p->getFirstName()) + " " + tr("est déjà dans le Rendez-vous", "is already inside the appointment") + "\t";
                QMessageBox(QMessageBox::Warning, windowTitle, msg, QMessageBox::Ok).exec();

            }else if(exe == Personne::PersonneHasAnRdv){
                QString msg = QString::fromStdString(p->getLastName() + " " + p->getFirstName()) + " " + tr("est déjà dans un autre Rendez-vous au même moment",
                                                                                                            "is already inside another appointment at the same time") + "\t";
                QMessageBox(QMessageBox::Warning, windowTitle, msg, QMessageBox::Ok).exec();

            }else if(exe == RDV::PersonneAdded){
                QString msg = tr("La Personne a été ajoutée au Rendez-vous", "The People has been added to the appointment") + "\t";
                QMessageBox(QMessageBox::Information, windowTitle, msg, QMessageBox::Ok).exec();
                setSave(false);

                modifyPersonneRdvLayoutLabel->setText(tr("Liste des participants au Rendez-vous", "List of the participants at tha appointment") + " " + QString::fromStdString(rdv->getName()));

                auto newWidget = new QWidget();
                auto saLayout = new QVBoxLayout();

                if(rdv->getMembersList().size() == 0) saLayout->addWidget(new QLabel(tr("Ce Rendez-vous n'a aucun participant", "This appointment as any participant")));
                else for(auto pt : rdv->getMembersList()) saLayout->addWidget(new QPushButton(pt->toQString()));
                saLayout->addStretch(0);

                newWidget->setLayout(saLayout);
                modifyPersonneRdvLayoutSA->setWidget(newWidget);
                onListPersonneRdv();
                onModifyPersonneRdv();

            }else{
                QString msg = tr("Erreur", "Error") + " : code Personne::AddPersonneToOrRemovePersonneFromRdv{" + QString::number(exe) + "}\t";
                QMessageBox(QMessageBox::Critical, windowTitle, msg, QMessageBox::Ok).exec();
            }
        }
    }
}

void MainWindow::onModifyPersonneRdvRemoveButton(void){
    auto rdv = new RDV(modifyPersonneRdvLayoutLineEditRdvName->text().toStdString(), {}, {}, {});
    auto p = new Personne(modifyPersonneRdvLayoutLineEditFirstName->text().toStdString(), modifyPersonneRdvLayoutLineEditLastName->text().toStdString(), "", "");
    int ind = manager.getListRDV().rechD(rdv);
    if(ind == -1){
        QString msg = tr("Le Rendez-vous n'existe pas", "The appointment does not exists") + "\t\n" + QString::fromStdString(rdv->getName());
        QMessageBox(QMessageBox::Warning, windowTitle, msg, QMessageBox::Ok).exec();
        delete rdv;
        delete p;
    }else{
        rdv = manager.getListRDV()[ind];

        modifyPersonneRdvLayoutLabel->setText(tr("Liste des participants au Rendez-vous", "List of the participants at tha appointment") + " " + QString::fromStdString(rdv->getName()));

        auto newWidget = new QWidget();
        auto saLayout = new QVBoxLayout();

        if(rdv->getMembersList().size() == 0) saLayout->addWidget(new QLabel(tr("Ce Rendez-vous n'a aucun participant", "This appointment as any participant")));
        else for(auto pt : rdv->getMembersList()) saLayout->addWidget(new QPushButton(pt->toQString()));
        saLayout->addStretch(0);

        newWidget->setLayout(saLayout);
        modifyPersonneRdvLayoutSA->setWidget(newWidget);
        onListPersonneRdv();
        onModifyPersonneRdv();

        ind = manager.getListPersonnes().rechD(p);
        if(ind == -1){
            QString msg = tr("La Personne n'existe pas", "The People does not exists") + "\t\n" + QString::fromStdString(p->getLastName() + " " + p->getLastName());
            QMessageBox(QMessageBox::Warning, windowTitle, msg, QMessageBox::Ok).exec();
            delete p;
        }else{
            p = manager.getListPersonnes()[ind];
            int exe = rdv->removeMember(p);

            if(exe == RDV::MembersListIsEmpty){
                QString msg = tr("Le Rendez-vous ne contient aucun participant", "The appointment as any participant") + "\t";
                QMessageBox(QMessageBox::Warning, windowTitle, msg, QMessageBox::Ok).exec();
            }else if(exe == Personne::RdvListIsEmpty or exe == Personne::RdvHasNotBeenRemoved){
                QString msg = tr("La Personne n'est pas présente au Rendez-vous", "The People is not in the appointment") + "\t";
                QMessageBox(QMessageBox::Warning, windowTitle, msg, QMessageBox::Ok).exec();
            }else if(exe == RDV::PersonneRemoved){
                QString msg = tr("La Personne a été retirée du Rendez-vous", "The People has been removed from the appointment") + "\t";
                QMessageBox(QMessageBox::Information, windowTitle, msg, QMessageBox::Ok).exec();
                setSave(false);

                modifyPersonneRdvLayoutLabel->setText(tr("Liste des participants au Rendez-vous", "List of the participants at tha appointment") + " " + QString::fromStdString(rdv->getName()));

                auto newWidget = new QWidget();
                auto saLayout = new QVBoxLayout();

                if(rdv->getMembersList().size() == 0) saLayout->addWidget(new QLabel(tr("Ce Rendez-vous n'a aucun participant", "This appointment as any participant")));
                else for(auto pt : rdv->getMembersList()) saLayout->addWidget(new QPushButton(pt->toQString()));
                saLayout->addStretch(0);

                newWidget->setLayout(saLayout);
                modifyPersonneRdvLayoutSA->setWidget(newWidget);
                onListPersonneRdv();
                onModifyPersonneRdv();

            }else{
                QString msg = tr("Erreur", "Error") + " : code Personne::AddPersonneToOrRemovePersonneFromRdv{" + QString::number(exe) + "}\t";
                QMessageBox(QMessageBox::Critical, windowTitle, msg, QMessageBox::Ok).exec();
            }
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

void MainWindow::onTextChangedlistPersonneRdvLineEdit(const QString& text){
    QSignalBlocker blocker(listPersonneRdvLayoutLineEdit);
    listPersonneRdvLayoutLineEdit->setText(text);
    blocker.unblock();
}

void MainWindow::onTextChangedlistRdvPersonneLineEditFirstName(const QString& text){
    QSignalBlocker blocker(listRdvPersonneLayoutLineEditFirstName);
    listRdvPersonneLayoutLineEditFirstName->setText(text);
    blocker.unblock();
}

void MainWindow::onTextChangedlistRdvPersonneLineEditLastName(const QString& text){
    QSignalBlocker blocker(listRdvPersonneLayoutLineEditLastName);
    listRdvPersonneLayoutLineEditLastName->setText(text);
    blocker.unblock();
}

void MainWindow::onTextChangedmodifyPersonneLineEditEmail(const QString& text){
    QSignalBlocker blocker(modifyPersonneLayoutLineEditEmail);
    modifyPersonneLayoutLineEditEmail->setText(text);
    blocker.unblock();
}

void MainWindow::onTextChangedmodifyPersonneLineEditFirstName(const QString& text){
    QSignalBlocker blocker(modifyPersonneLayoutLineEditFirstName);
    modifyPersonneLayoutLineEditFirstName->setText(text);
    blocker.unblock();
}

void MainWindow::onTextChangedmodifyPersonneLineEditLastName(const QString& text){
    QSignalBlocker blocker(modifyPersonneLayoutLineEditLastName);
    modifyPersonneLayoutLineEditLastName->setText(text);
    blocker.unblock();
}

void MainWindow::onTextChangedmodifyPersonneLineEditPhone(const QString& text){
    QSignalBlocker blocker(modifyPersonneLayoutLineEditPhone);
    modifyPersonneLayoutLineEditPhone->setText(text);
    blocker.unblock();
}

void MainWindow::onTextChangedmodifyPersonneRdvLineEditFirstName(const QString& text){
    QSignalBlocker blocker(modifyPersonneRdvLayoutLineEditFirstName);
    modifyPersonneRdvLayoutLineEditFirstName->setText(text);
    blocker.unblock();
}

void MainWindow::onTextChangedmodifyPersonneRdvLineEditLastName(const QString& text){
    QSignalBlocker blocker(modifyPersonneRdvLayoutLineEditLastName);
    modifyPersonneRdvLayoutLineEditLastName->setText(text);
    blocker.unblock();
}

void MainWindow::onTextChangedmodifyPersonneRdvLineEditRdvName(const QString& text){
    QSignalBlocker blocker(modifyPersonneRdvLayoutLineEditRdvName);
    modifyPersonneRdvLayoutLineEditRdvName->setText(text);
    blocker.unblock();
}

void MainWindow::onTextChangedrechRdvDateLineEdit(const QString& text){
    QSignalBlocker blocker(rechRdvDateLineEdit);
    rechRdvDateLineEdit->setText(text);
    blocker.unblock();
}
