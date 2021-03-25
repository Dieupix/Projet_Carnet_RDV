#include "mainwindow.h"

MainWindow::MainWindow(QMainWindow *parent)
    : QMainWindow(parent), win(this)
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
    win->setCentralWidget(central);

    setupMenuBar();

    fixedLayout->addLayout(setupMainLayout());
    fixedLayout->addLayout(setupFooterLayout());

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
    addRDVAction->setShortcut(QKeySequence(Qt::CTRL | Qt::SHIFT | Qt::Key_P));
    addRDVAction->setShortcutVisibleInContextMenu(true);
    editMenu->addAction(addRDVAction);

    editMenu->addSeparator();

    auto removePersonneAction = new QAction("&Retirer une Personne");
    removePersonneAction->setToolTip("Ouvrir un fichier de personne ou de rendez-vous");
    removePersonneAction->setIcon(QIcon("../Carnet_RDV/icons/icon_macos_minimiser_black1_100"));
    removePersonneAction->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_O));
    removePersonneAction->setShortcutVisibleInContextMenu(true);
    editMenu->addAction(removePersonneAction);

    auto removeRDVAction = new QAction("&Retirer un RDV");
    removeRDVAction->setToolTip("Ouvrir un fichier de personne ou de rendez-vous");
    removeRDVAction->setShortcut(QKeySequence(Qt::CTRL | Qt::SHIFT | Qt::Key_O));
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

QBoxLayout* MainWindow::setupMainLayout(void){
    mainLayout = new QHBoxLayout();

    auto spinBox = new QSpinBox();
    spinBox->setRange(0, 200);
    spinBox->setValue(spinBox->minimum());
    loadingBar = new QProgressBar();
    loadingBar->setRange(spinBox->minimum(), spinBox->maximum());
    loadingBar->setValue(spinBox->value());
    mainLayout->addWidget(spinBox);
    mainLayout->addWidget(loadingBar);
    connect(spinBox, &QSpinBox::valueChanged, this, &MainWindow::onSpinBox);

    return mainLayout;
}

void MainWindow::setupMenuBar(void){
    setupFileMenu(menuBar()->addMenu("&Fichier"));
    setupEditMenu(menuBar()->addMenu("&Edit"));
}

void MainWindow::updateWindowTitle(void){
    setWindowTitle(windowTitle + (isSaved ? "" : "*"));
}

void MainWindow::updateLoadingBar(int i){
    loadingBar->setValue(i);
}



// ---------- Méthodes publiques ----------



// ---------- Slots privés ----------
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

void MainWindow::onSpinBox(int i){
    updateLoadingBar(i);
}
