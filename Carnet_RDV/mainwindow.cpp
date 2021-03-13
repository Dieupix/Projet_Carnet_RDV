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
    auto saveButton = new QPushButton("Enregistrer");
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
    string s = "Carnet de Rendez-vous";
    setWindowTitle(QString::fromStdString(s += (isSaved ? "" : "*")));
}



// ---------- Méthodes publiques ----------



// ---------- Slots privés ----------
void MainWindow::onQuit(void){
    if(isSaved) close();
    else{
        QString title = "Carnet de Rendez-vous non enregistré";
        QString msg = "Votre Carnet de Rendez-vous n'est pas enregistré\n\nVoulez-vous vraiment quitter sans enregistrer ?";

        int exit = QMessageBox(QMessageBox::Information, title, msg, QMessageBox::Save | QMessageBox::Yes | QMessageBox::No).exec();

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
