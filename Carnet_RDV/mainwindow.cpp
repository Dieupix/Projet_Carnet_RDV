#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    setup();
    updateWindowTitle();
}



// ---------- Méthodes privées ----------
void MainWindow::setup(void){

    auto fixedLayout = new QVBoxLayout();
    setLayout(fixedLayout);
    mainLayout = new QHBoxLayout();
    mainLayoutSetup();
    fixedLayout->addLayout(mainLayout);

    auto buttonLayout = new QVBoxLayout();
    auto line = new QFrame();
    line->setFrameStyle(QFrame::HLine);
    buttonLayout->addStretch(0);
    buttonLayout->addWidget(line, 0, Qt::AlignBottom);

    auto preButtonLayout = new QHBoxLayout();
    auto teamLabel = new QLabel("BARRERE Manuel - JANON Alexandre - POMMIER Logan");

    auto quitButton = new QPushButton("Quitter");
    quitButton->setToolTip("Quitter l'application");
    quitButton->setShortcut(QKeySequence(QKeyCombination(Qt::ControlModifier, Qt::Key_Q)));

    auto saveButton = new QPushButton("Enregistrer");
    saveButton->setToolTip("Enregistrer le carnet de rendez-vous");
    saveButton->setShortcut(QKeySequence(QKeySequence::Save));

    preButtonLayout->addWidget(teamLabel, 0, Qt::AlignLeft);
    preButtonLayout->addStretch(0);
    preButtonLayout->addWidget(saveButton, 0, Qt::AlignBottom);
    preButtonLayout->addWidget(quitButton, 0, Qt::AlignBottom);
    preButtonLayout->setContentsMargins(0, 5, 0, 0);

    buttonLayout->addLayout(preButtonLayout);
    buttonLayout->setContentsMargins(0, 5, 0, 0);

    fixedLayout->addLayout(buttonLayout);

    connect(quitButton, &QPushButton::clicked, this, &MainWindow::onQuit);
    connect(saveButton, &QPushButton::clicked, this, &MainWindow::onSave);

}

void MainWindow::mainLayoutSetup(void){

}

void MainWindow::updateWindowTitle(void){
    setWindowTitle(QString::fromStdString(windowTitle + (isSaved ? "" : "*")));
}



// ---------- Méthodes publiques ----------
void MainWindow::updateLoadingBar(int i){
    loadingBar->setValue(i);
}



// ---------- Slots privés ----------
void MainWindow::onQuit(void){
    if(isSaved) close();
    else{
        QString msg = (QString) "Votre Carnet de Rendez-vous n'est pas enregistré" + "\n\n" +
                "Voulez-vous vraiment quitter sans enregistrer ?";

        int exit = QMessageBox(QMessageBox::Information, QString::fromStdString(windowTitle), msg, QMessageBox::Save | QMessageBox::Yes | QMessageBox::No).exec();

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
