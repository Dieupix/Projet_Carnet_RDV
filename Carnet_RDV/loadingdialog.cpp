#include "loadingdialog.h"

LoadingDialog::LoadingDialog(MainWindow* mainwindow, const QString& filePath, QWidget *parent) : QDialog(parent)
{
    this->mainwindow = mainwindow;
    this->filePath = filePath;
    setup();
}



// ---------- Méthodes privées ----------
void LoadingDialog::setup(void){
    setWindowTitle(mainwindow->getWindowTitle());
    auto mainLayoutDialog = new QVBoxLayout();
    setLayout(mainLayoutDialog);

    mainLayoutDialog->addWidget(new QLabel("Fichier : " + filePath), 0, Qt::AlignTop);

    auto label = new QLabel("Chargement en cours...");
    mainLayoutDialog->addWidget(label, 0, Qt::AlignHCenter);

    auto loadBar = new QProgressBar();
    mainLayoutDialog->addWidget(loadBar, 0, Qt::AlignTop);

    auto okButton = new QPushButton("OK");
    mainLayoutDialog->addWidget(okButton, 0, Qt::AlignBottom | Qt::AlignHCenter);
    okButton->setDisabled(true);

    show();
    setFixedSize(width(), 2 * height());
    bool loaded = mainwindow->manager.loadPersonne(filePath.toStdString(), loadBar);
    cout << endl;

    okButton->setEnabled(true);
    okButton->setDefault(true);

    if(loaded){

        if(filePath.endsWith(QFILENAMEPERSONNE)) mainwindow->updatePersonneListLayout();
        else if(filePath.endsWith(QFILENAMERDV)) mainwindow->updateRDVListLayout();

        label->setText("Chargement terminé");

        connect(okButton, &QPushButton::clicked, this, &LoadingDialog::onAccept);

    }else {
        label->setText("Erreur lors du chargement");

        connect(okButton, &QPushButton::clicked, this, &LoadingDialog::onReject);

    }

}



// ---------- Slots privés ----------
void LoadingDialog::onAccept(void){
    accept();
}

void LoadingDialog::onReject(void){
    reject();
}


