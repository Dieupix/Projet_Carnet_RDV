#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    setup();
}



// ---------- Méthodes privées ----------
void MainWindow::setup(void){
    Manager = manager();

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



// ---------- Méthodes publiques ----------



// ---------- Slots privés ----------
void MainWindow::onQuit(void){
    close();
}
void MainWindow::onSave(void){

}
