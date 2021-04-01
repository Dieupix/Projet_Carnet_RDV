#include "mainwindow.h"

// ---------- FONCTIONS ANNEXES ----------
void hideOrShow(QBoxLayout* QBoxToHideOrShow, bool show){
    for(int i = 0; i < QBoxToHideOrShow->count(); i++){
        auto item = QBoxToHideOrShow->itemAt(i);
        auto w = item ? item->widget() : 0;
        if(w) w->setVisible(show);
        QLayout* l = item ? item->layout() : 0;
        if(l) hideOrShow((QBoxLayout*) l, show);
    }
}

void preHideOrShow(QBoxLayout* QBoxToHideOrShow, bool show, QBoxLayout* parent, int ind){
    hideOrShow(QBoxToHideOrShow, show);
    if(ind == -1 or ind > parent->count()) ind = parent->count();
    if(show) parent->insertLayout(ind, QBoxToHideOrShow);
    else parent->removeItem(QBoxToHideOrShow);
}
// ---------- FIN FONCTIONS ANNEXES ----------


MainWindow::MainWindow(QMainWindow *parent)
    : QMainWindow(parent), window(this)
{
    setup();
    updateWindowTitle();
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
    fixedLayout->addStretch(1);
    fixedLayout->addLayout(setupMainLayout(), 10);
    fixedLayout->addLayout(setupListLayout(), 4);
    fixedLayout->addStretch(1);
    fixedLayout->addLayout(setupFooterLayout());

}

QBoxLayout* MainWindow::setupButtonLayout(void) {
    auto buttonLayout = new QHBoxLayout();

    buttonLayout->addWidget(new QPushButton("test"), 0, Qt::AlignCenter);

    return buttonLayout;
}

void MainWindow::setupEditMenu(QMenu* editMenu){
    auto addPersonneAction = new QAction("&Ajouter une Personne");
    addPersonneAction->setToolTip("Ouvrir un fichier de personne ou de rendez-vous");
    addPersonneAction->setIcon(QIcon("../Carnet_RDV/icons/icon_macos_maximiser_black1_100"));
    addPersonneAction->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_P));
    addPersonneAction->setShortcutVisibleInContextMenu(true);
    editMenu->addAction(addPersonneAction);

    auto addRDVAction = new QAction("&Ajouter un RDV");
    addRDVAction->setToolTip("Ouvrir un fichier de personne ou de rendez-vous");
    addRDVAction->setShortcut(QKeySequence(Qt::CTRL| Qt::Key_R));
    addRDVAction->setShortcutVisibleInContextMenu(true);
    editMenu->addAction(addRDVAction);

    editMenu->addSeparator();

    auto removePersonneAction = new QAction("&Retirer une Personne");
    removePersonneAction->setToolTip("Ouvrir un fichier de personne ou de rendez-vous");
    removePersonneAction->setIcon(QIcon("../Carnet_RDV/icons/icon_macos_minimiser_black1_100"));
    removePersonneAction->setShortcut(QKeySequence(Qt::CTRL | Qt::ALT | Qt::Key_P));
    removePersonneAction->setShortcutVisibleInContextMenu(true);
    editMenu->addAction(removePersonneAction);

    auto removeRDVAction = new QAction("&Retirer un RDV");
    removeRDVAction->setToolTip("Ouvrir un fichier de personne ou de rendez-vous");
    removeRDVAction->setShortcut(QKeySequence(Qt::CTRL | Qt::ALT | Qt::Key_R));
    removeRDVAction->setShortcutVisibleInContextMenu(true);
    editMenu->addAction(removeRDVAction);
}

void MainWindow::setupFileMenu(QMenu *fileMenu){
    auto loadAction = new QAction("&Ouvrir un fichier...");
    loadAction->setToolTip("Ouvrir un fichier de personne ou de rendez-vous");
    loadAction->setIcon(QIcon("../Carnet_RDV/icons/icon_dossier_ouvert_black1_100"));
    loadAction->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_O));
    loadAction->setShortcutVisibleInContextMenu(true);
    fileMenu->addAction(loadAction);

    fileMenu->addSeparator();

    auto saveAction = new QAction("Enregi&strer");
    saveAction->setToolTip("Enregistrer le carnet de rendez-vous");
    saveAction->setIcon(QIcon("../Carnet_RDV/icons/icon_sauvegarder_black1_100"));
    saveAction->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_S));
    saveAction->setShortcutVisibleInContextMenu(true);
    fileMenu->addAction(saveAction);

    auto saveAndQuitAction = new QAction("Enregi&strer et quitter");
    saveAndQuitAction->setToolTip("Enregistrer le carnet et quitter");
    saveAndQuitAction->setIcon(QIcon("../Carnet_RDV/icons/icon_enregistrer_et_fermer_black1_100"));
    saveAndQuitAction->setShortcut(QKeySequence(Qt::CTRL | Qt::SHIFT | Qt::Key_Q));
    saveAndQuitAction->setShortcutVisibleInContextMenu(true);
    fileMenu->addAction(saveAndQuitAction);

    fileMenu->addSeparator();

    auto quitAction = new QAction("&Quitter");
    quitAction->setToolTip("Quitter l'application");
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
    auto teamLabel = new QLabel("BARRERE Manuel - JANON Alexandre - POMMIER Logan");
    teamLabel->setToolTip("L'équipe du projet");

    auto uhaLabel = new QLabel("Université de Haute Alsace - (<a href='" + uhaURL + "'>UHA</a>)");
    uhaLabel->setOpenExternalLinks(true);
    uhaLabel->setToolTip("Accéder au site internet de l'UHA");

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
    auto rdvListLabel = new QLabel("Liste de tous les rendez-vous");
    rdvListLabel->setFont(QFont(rdvListLabel->font().family(), 20));
    rdvListLayout->addWidget(rdvListLabel, 0, Qt::AlignHCenter);

    auto saRDV = new QScrollArea();
    auto saRDVWidget = new QWidget();
    auto saRDVLayout = new QVBoxLayout();
    if(manager.getListRDV().size() == 0) saRDVLayout->addWidget(new QLabel("Aucun rendez-vous dans la base de données"));
    else for(unsigned i = 0; i < manager.getListRDV().size(); ++i)
            saRDVLayout->addWidget(new QPushButton(QIcon("../Carnet_RDV/icons/icon_carnet_d'adresses_black1_100"), manager.getListRDV()[i]->toQString()));

    saRDVLayout->addStretch();
    saRDVWidget->setLayout(saRDVLayout);
    saRDV->setWidget(saRDVWidget);
    saRDV->setWidgetResizable(true);
    rdvListLayout->addWidget(saRDV);

    personneListLayout = new QVBoxLayout();
    auto personneListLabel = new QLabel("Liste de toutes les personnes");
    personneListLabel->setFont(QFont(personneListLabel->font().family(), 20));
    personneListLayout->addWidget(personneListLabel, 0, Qt::AlignHCenter);

    auto saPersonne = new QScrollArea();
    auto saPersonneWidget = new QWidget();
    auto saPersonneLayout = new QVBoxLayout();
    if(manager.getListPersonnes().size() == 0) saPersonneLayout->addWidget(new QLabel("Aucune personne dans la base de données"));
    else for(unsigned i = 0; i < manager.getListPersonnes().size(); ++i)
            saPersonneLayout->addWidget(new QPushButton(QIcon("../Carnet_RDV/icons/icon_carnet_rdv_black1_100"), manager.getListPersonnes()[i]->toQString()));

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

    return mainLayout;
}

void MainWindow::setupMenuBar(void){
    setupFileMenu(menuBar()->addMenu("&Fichier"));
    setupEditMenu(menuBar()->addMenu("&Edit"));
    setupViewMenu(menuBar()->addMenu("&Afficher"));
}

void MainWindow::setupViewMenu(QMenu* viewMenu){
    auto personneListCheckBox = new QAction("Afficher la liste des &Personnes");
    personneListCheckBox->setToolTip("Affiche la liste de toutes les Personnes");
    personneListCheckBox->setIcon(QIcon("../Carnet_RDV/icons/icon_carnet_rdv_black1_100"));
    personneListCheckBox->setShortcut(QKeySequence(Qt::ALT | Qt::Key_P));
    personneListCheckBox->setShortcutVisibleInContextMenu(true);
    personneListCheckBox->setCheckable(true);
    personneListCheckBox->setChecked(true);
    viewMenu->addAction(personneListCheckBox);

    auto rdvListCheckBox = new QAction("Afficher la liste des &RDV");
    rdvListCheckBox->setToolTip("Affiche la liste de tous les Rendez-vous");
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
    preHideOrShow(personneListLayout, b, listLayout, 1);
}

void MainWindow::showRDVListLayout(bool b) {
    preHideOrShow(rdvListLayout, b, listLayout, 0);
}

void MainWindow::updatePersonneListLayout(void){
}

void MainWindow::updateRDVListLayout(void){

}

void MainWindow::updateWindowTitle(void){
    setWindowTitle(windowTitle + (isSaved ? "" : "*"));
}



// ---------- Méthodes publiques ----------
void MainWindow::loadFile(void){

    auto filePath = QFileDialog::getOpenFileName(this, windowTitle, windowFilePath(), "Fichiers de Personne ou de RDV (*.carnetRDV);; Tous les fichiers (*)");

    if(filePath != ""){
        if(filePath.endsWith(QFILENAMEPERSONNE)){

            auto loadingDialog = new QDialog();
            loadingDialog->setWindowTitle(windowTitle);
            loadingDialog->setModal(true);
            auto mainLayoutDialog = new QVBoxLayout();
            auto okButton = new QPushButton("OK");
            okButton->setDisabled(true);

            mainLayoutDialog->addWidget(new QLabel("Fichier : " + filePath), 0, Qt::AlignTop);
            auto label = new QLabel("Chargement en cours...");
            mainLayoutDialog->addWidget(label, 0, Qt::AlignHCenter);
            auto loadBar = new QProgressBar();
            mainLayoutDialog->addWidget(loadBar, 0, Qt::AlignTop);
            loadingDialog->setLayout(mainLayoutDialog);

            mainLayoutDialog->addWidget(okButton, 0, Qt::AlignBottom | Qt::AlignHCenter);

            loadingDialog->show();
            loadingDialog->setFixedSize(loadingDialog->width(), 2 * loadingDialog->height());
            manager.loadPersonne(filePath.toStdString(), loadBar);
            label->setText("Chargement terminé");
            okButton->setEnabled(true);


        }else if(filePath.endsWith(QFILENAMERDV)){

        }else{
            QString msg = "Fichier invalide.\n\nVeuillez sélectionner un fichier de Personne ou de Rendez-vous.\t\n";
            int exe = QMessageBox(QMessageBox::Critical, "Erreur de fichier", msg, QMessageBox::Retry | QMessageBox::Cancel).exec();

            if(exe == QMessageBox::Retry) loadFile();
        }
    }
}


// ---------- Slots privés ----------
void MainWindow::onPersonneListCheckBox(bool b){
    showPersonneListLayout(b);
}

void MainWindow::onQuit(void){
    if(isSaved) close();
    else{
        QString msg = (QString) "Votre Carnet de Rendez-vous n'est pas enregistré" + "\n\n" +
                "Voulez-vous vraiment quitter sans enregistrer ?";

        int exit = QMessageBox(QMessageBox::Information, windowTitle, msg, QMessageBox::Save | QMessageBox::Yes | QMessageBox::No).exec();

        if(exit == QMessageBox::Save){
            onSave();
            close();
        }else if(exit == QMessageBox::Yes) close();
    }
}

void MainWindow::onRDVListCheckBox(bool b){
    showRDVListLayout(b);
}

void MainWindow::onSaveAndQuit(void){
    onSave();
    onQuit();
}

void MainWindow::onSave(void){
    if(!isSaved){
        isSaved = true;
        updateWindowTitle();
    }
}

void MainWindow::onSpinBox(int) {
}
