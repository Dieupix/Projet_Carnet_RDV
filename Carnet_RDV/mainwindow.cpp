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

    mainLayout = new QHBoxLayout();
    setupMainLayout();
    fixedLayout->addLayout(mainLayout);

    fixedLayout->addLayout(setupFooterLayout());

}

QVBoxLayout* MainWindow::setupFooterLayout(void){
    auto footerLayout = new QVBoxLayout();
    auto line = new QFrame();
    line->setFrameStyle(QFrame::HLine);
    footerLayout->addStretch(0);
    footerLayout->addWidget(line, 0, Qt::AlignBottom);

    auto preFooterLayout = new QHBoxLayout();
    auto teamLabel = new QLabel("BARRERE Manuel - JANON Alexandre - POMMIER Logan");

    auto uhaLabel = new QLabel("Université de Haute Alsace - (<a href='" + uhaURL + "'>UHA</a>)");
    uhaLabel->setOpenExternalLinks(true);
    uhaLabel->setToolTip("Accéder au site internet de l'UHA");

    preFooterLayout->addWidget(teamLabel, 0, Qt::AlignLeft);
    preFooterLayout->addStretch(0);
    preFooterLayout->addWidget(uhaLabel, 0, Qt::AlignRight);

    footerLayout->addLayout(preFooterLayout);
    footerLayout->setContentsMargins(0, 5, 0, 0);

    return footerLayout;
}

void MainWindow::setupFileMenu(QMenu *fileMenu){
    auto loadAction = new QAction("&Ouvrir un fichier...");
    loadAction->setToolTip("Ouvrir un fichier de personne ou de rendez-vous");
    loadAction->setIcon(QIcon("../Carnet_RDV/icons/icon_dossier_ouvert_black1_100"));
    loadAction->setShortcut(QKeySequence(QKeyCombination(Qt::ControlModifier, Qt::Key_O)));
    loadAction->setShortcutVisibleInContextMenu(true);
    fileMenu->addAction(loadAction);

    fileMenu->addSeparator();

    auto saveAction = new QAction("Enregi&strer");
    saveAction->setToolTip("Enregistrer le carnet de rendez-vous");
    saveAction->setIcon(QIcon("../Carnet_RDV/icons/icon_sauvegarder_black1_100"));
    saveAction->setShortcut(QKeySequence(QKeyCombination(Qt::ControlModifier, Qt::Key_S)));
    saveAction->setShortcutVisibleInContextMenu(true);
    fileMenu->addAction(saveAction);

    fileMenu->addSeparator();

    auto quitAction = new QAction("&Quitter");
    quitAction->setToolTip("Quitter l'application");
    quitAction->setIcon(QIcon("../Carnet_RDV/icons/icon_sortie_black1_100"));
    quitAction->setShortcut(QKeySequence(QKeyCombination(Qt::ControlModifier, Qt::Key_Q)));
    quitAction->setShortcutVisibleInContextMenu(true);
    fileMenu->addAction(quitAction);

    connect(saveAction, &QAction::triggered, this, &MainWindow::onSave);
    connect(quitAction, &QAction::triggered, this, &MainWindow::onQuit);
}

void MainWindow::setupMainLayout(void){
    auto spinBox = new QSpinBox();
    spinBox->setRange(0, 200);
    loadingBar = new QProgressBar();
    loadingBar->setRange(0, 200);
    loadingBar->setValue(0);
    mainLayout->addWidget(spinBox);
    mainLayout->addWidget(loadingBar);
    connect(spinBox, &QSpinBox::valueChanged, this, &MainWindow::onSpinBox);
}

void MainWindow::setupMenuBar(void){
    auto fileMenu = menuBar()->addMenu("&Fichier");
    setupFileMenu(fileMenu);
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

void MainWindow::onSave(void){
    isSaved = true;
    updateWindowTitle();
}

void MainWindow::onSpinBox(int i){
    updateLoadingBar(i);
}
