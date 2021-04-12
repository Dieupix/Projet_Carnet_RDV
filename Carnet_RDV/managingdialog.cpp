#include "managingdialog.h"

ManagingDialog::ManagingDialog(MainWindow* mainwindow, ManagingDialogReason reason, QWidget* parent)
    : QDialog(parent)
{
    this->mainwindow = mainwindow;
    setModal(true);

    switch(reason){
    case AddPersonneToDataBase:
        setupAddPersonneToDataBase();
        break;
    case RemovePersonneFromDataBase:
        setupRemovePersonneFromDataBase();
        break;
    case AddRdvToDataBase:
        setupAddRdvToDataBase();
        break;
    case RemoveRdvFromDataBase:
        setupRemoveRdvFromDataBase();
        break;
    default:
        cerr << tr("Erreur : reason = ", "Error, reason = ").toStdString() << reason << endl << endl;
        break;
    }
    setFixedSize(width(), height());
    show();
}


// ---------- Méthodes privées ----------
void ManagingDialog::setupAddPersonneToDataBase(void){
    setWindowTitle(mainwindow->getWindowTitle());

    auto fixedLayout = new QVBoxLayout();
    setLayout(fixedLayout);

    auto label = new QLabel(tr("Ajouter des Personne à la base de données","Add People to the data base"));
    label->setFont(QFont(label->font().family(), 20));
    label->setTextInteractionFlags(Qt::TextBrowserInteraction);
    fixedLayout->addWidget(label);
    fixedLayout->addSpacing(10);
    auto line = new QFrame();
    line->setFrameStyle(QFrame::HLine);
    fixedLayout->addWidget(line);
    fixedLayout->addSpacing(10);

    auto mainLayout = new QHBoxLayout();
    auto addPersonneformLayout = new QVBoxLayout();
    auto formLayout = new QFormLayout();
    formLayout->addRow(new QLabel(tr("Saisir les informations de la Personne à ajouter","Enter the informations of the People to add")));
    this->lineEditLastName = new QLineEdit();
    formLayout->addRow(tr("Nom", "Last name"), lineEditLastName);
    this->lineEditFirstName = new QLineEdit();
    formLayout->addRow(tr("Prénom", "First name"), lineEditFirstName);
    this->lineEditPhone = new QLineEdit();
    formLayout->addRow(tr("N° de téléphone", "Phone number"), lineEditPhone);
    this->lineEditEmail = new QLineEdit();
    formLayout->addRow(tr("E-mail"), lineEditEmail);

    addPersonneformLayout->addLayout(formLayout);
    addPersonneformLayout->addSpacing(10);
    auto addButton = new QPushButton(tr("Ajouter", "Add"));
    addPersonneformLayout->addWidget(addButton, 0, Qt::AlignHCenter);
    addPersonneformLayout->addStretch(0);

    mainLayout->addLayout(addPersonneformLayout);
    mainLayout->addSpacing(50);

    auto listPersonneLayout = new QVBoxLayout();
    listPersonneLayout->addWidget(new QLabel(tr("Liste des Personnes à ajouter","List of the People to add")), 0, Qt::AlignHCenter);

    this->SA = new QScrollArea();
    auto saWidget = new QWidget();
    auto saLayout = new QVBoxLayout();
    saWidget->setLayout(saLayout);
    SA->setWidget(saWidget);
    SA->setWidgetResizable(true);

    listPersonneLayout->addWidget(SA);

    mainLayout->addLayout(listPersonneLayout);

    fixedLayout->addLayout(mainLayout);

    auto buttonLayout = new QHBoxLayout();
    auto finishButton = new QPushButton(tr("Terminer", "Finished"));
    auto cancelButton = new QPushButton(tr("Annuler", "Cancel"));

    buttonLayout->addStretch(0);
    buttonLayout->addWidget(finishButton);
    buttonLayout->addWidget(cancelButton);

    fixedLayout->addLayout(buttonLayout);

    connect(lineEditFirstName, &QLineEdit::textChanged, this, &ManagingDialog::onTextChangedLineEditFirstName);
    connect(lineEditLastName, &QLineEdit::textChanged, this, &ManagingDialog::onTextChangedLineEditLastName);
    connect(lineEditEmail, &QLineEdit::textChanged, this, &ManagingDialog::onTextChangedLineEditEmail);
    connect(lineEditPhone, &QLineEdit::textChanged, this, &ManagingDialog::onTextChangedLineEditPhone);
    connect(addButton, &QPushButton::clicked, this, &ManagingDialog::onAddPersonne);
    connect(finishButton, &QPushButton::clicked, this, &ManagingDialog::onAccept);
    connect(cancelButton, &QPushButton::clicked, this, &ManagingDialog::onReject);

}

void ManagingDialog::setupRemovePersonneFromDataBase(void){
    setWindowTitle(mainwindow->getWindowTitle());

    auto fixedLayout = new QVBoxLayout();
    setLayout(fixedLayout);

    auto label = new QLabel(tr("Supprimer des Personne de la base de données","Remove People from the data base"));
    label->setFont(QFont(label->font().family(), 20));
    label->setTextInteractionFlags(Qt::TextBrowserInteraction);
    fixedLayout->addWidget(label);
    fixedLayout->addSpacing(10);
    auto line = new QFrame();
    line->setFrameStyle(QFrame::HLine);
    fixedLayout->addWidget(line);
    fixedLayout->addSpacing(10);

    auto mainLayout = new QHBoxLayout();
    auto addPersonneformLayout = new QVBoxLayout();
    auto formLayout = new QFormLayout();
    formLayout->addRow(new QLabel(tr("Saisir les informations de la Personne à supprimer","Enter the informations of the People to remove")));
    this->lineEditLastName = new QLineEdit();
    lineEditLastName->setToolTip(tr("Saisir le nom de la Personne", "Put the lastname of the People"));
    lineEditLastName->setClearButtonEnabled(true);
    lineEditLastName->setDragEnabled(true);
    formLayout->addRow(tr("Nom", "Last name"), lineEditLastName);
    this->lineEditFirstName = new QLineEdit();
    lineEditFirstName->setToolTip(tr("Saisir le prénom de la Personne", "Put the firstname of the People"));
    lineEditFirstName->setClearButtonEnabled(true);
    lineEditFirstName->setDragEnabled(true);
    formLayout->addRow(tr("Prénom", "First name"), lineEditFirstName);

    addPersonneformLayout->addLayout(formLayout);
    addPersonneformLayout->addSpacing(10);
    auto removeButton = new QPushButton(tr("Supprimer", "Remove"));
    addPersonneformLayout->addWidget(removeButton, 0, Qt::AlignHCenter);
    addPersonneformLayout->addStretch(0);

    mainLayout->addLayout(addPersonneformLayout);
    mainLayout->addSpacing(50);

    this->listPersonneLayout = new QVBoxLayout();
    listPersonneLayout->addWidget(new QLabel(tr("Liste des Personnes à supprimer","List of the People to remove")), 0, Qt::AlignHCenter);

    this->SA = new QScrollArea();
    auto saWidget = new QWidget();
    auto saLayout = new QVBoxLayout();
    saWidget->setLayout(saLayout);
    SA->setWidget(saWidget);
    SA->setWidgetResizable(true);

    listPersonneLayout->addWidget(SA);

    mainLayout->addLayout(listPersonneLayout);

    fixedLayout->addLayout(mainLayout);

    auto buttonLayout = new QHBoxLayout();
    auto finishButton = new QPushButton(tr("Terminer", "Finished"));
    auto cancelButton = new QPushButton(tr("Annuler", "Cancel"));

    buttonLayout->addStretch(0);
    buttonLayout->addWidget(finishButton);
    buttonLayout->addWidget(cancelButton);

    fixedLayout->addLayout(buttonLayout);

    connect(lineEditFirstName, &QLineEdit::textChanged, this, &ManagingDialog::onTextChangedLineEditFirstName);
    connect(lineEditLastName, &QLineEdit::textChanged, this, &ManagingDialog::onTextChangedLineEditLastName);
    connect(removeButton, &QPushButton::clicked, this, &ManagingDialog::onRemovePersonne);
    connect(finishButton, &QPushButton::clicked, this, &ManagingDialog::onAccept);
    connect(cancelButton, &QPushButton::clicked, this, &ManagingDialog::onReject);
}

void ManagingDialog::setupAddRdvToDataBase(void){
    setWindowTitle(mainwindow->getWindowTitle());

    auto fixedLayout = new QVBoxLayout();
    setLayout(fixedLayout);

    auto label = new QLabel(tr("Ajouter des Rendez-vous à la base de données","Add appointment to the data base"));
    label->setFont(QFont(label->font().family(), 20));
    label->setTextInteractionFlags(Qt::TextBrowserInteraction);
    fixedLayout->addWidget(label);
    fixedLayout->addSpacing(10);
    auto line = new QFrame();
    line->setFrameStyle(QFrame::HLine);
    fixedLayout->addWidget(line);
    fixedLayout->addSpacing(10);

    auto mainLayout = new QHBoxLayout();
    auto addPersonneformLayout = new QVBoxLayout();
    auto formLayout = new QFormLayout();
    formLayout->addRow(new QLabel(tr("Saisir les informations du Rendez-vous à ajouter","Enter the informations of the appointment to add")));
    this->lineEditName = new QLineEdit();
    formLayout->addRow(tr("Nom", "Name"), lineEditName);
    this->lineEditDate = new QLineEdit();
    lineEditDate->setInputMask("99/99/9999");
    lineEditDate->setToolTip(tr("Format : jj/mm/aaaa", "Format : dd/mm/yyyy"));
    lineEditDate->setMaxLength(10);
    formLayout->addRow(tr("Date", "Date"), lineEditDate);
    this->lineEditTimeStart = new QLineEdit();
    lineEditTimeStart->setInputMask("99\\h99m99s");
    lineEditTimeStart->setToolTip(tr("Format : hh mm ss", "Format : hh mm ss"));
    lineEditTimeStart->setMaxLength(9);
    formLayout->addRow(tr("Heure de début", "Starting time"), lineEditTimeStart);
    this->lineEditTimeEnd = new QLineEdit();
    lineEditTimeEnd->setInputMask("99\\h99m99s");
    lineEditTimeEnd->setToolTip(tr("Format : hh mm ss", "Format : hh mm ss"));
    lineEditTimeEnd->setMaxLength(9);
    formLayout->addRow(tr("Heure de fin", "Ending time"), lineEditTimeEnd);

    addPersonneformLayout->addLayout(formLayout);
    addPersonneformLayout->addSpacing(10);
    auto addButton = new QPushButton(tr("Ajouter", "Add"));
    addPersonneformLayout->addWidget(addButton, 0, Qt::AlignHCenter);
    addPersonneformLayout->addStretch(0);

    mainLayout->addLayout(addPersonneformLayout);
    mainLayout->addSpacing(50);

    auto listPersonneLayout = new QVBoxLayout();
    listPersonneLayout->addWidget(new QLabel(tr("Liste des Rendez-vous à ajouter","List of the appointment to add")), 0, Qt::AlignHCenter);

    this->SA = new QScrollArea();
    auto saWidget = new QWidget();
    auto saLayout = new QVBoxLayout();
    saWidget->setLayout(saLayout);
    SA->setWidget(saWidget);
    SA->setWidgetResizable(true);

    listPersonneLayout->addWidget(SA);

    mainLayout->addLayout(listPersonneLayout);

    fixedLayout->addLayout(mainLayout);

    auto buttonLayout = new QHBoxLayout();
    auto finishButton = new QPushButton(tr("Terminer", "Finished"));
    auto cancelButton = new QPushButton(tr("Annuler", "Cancel"));

    buttonLayout->addStretch(0);
    buttonLayout->addWidget(finishButton);
    buttonLayout->addWidget(cancelButton);

    fixedLayout->addLayout(buttonLayout);

    connect(lineEditName, &QLineEdit::textChanged, this, &ManagingDialog::onTextChangedLineEditName);
    connect(lineEditDate, &QLineEdit::textChanged, this, &ManagingDialog::onTextChangedLineEditDate);
    connect(lineEditTimeStart, &QLineEdit::textChanged, this, &ManagingDialog::onTextChangedLineEditTimeStart);
    connect(lineEditTimeEnd, &QLineEdit::textChanged, this, &ManagingDialog::onTextChangedLineEditTimeEnd);
    connect(addButton, &QPushButton::clicked, this, &ManagingDialog::onAddRdv);
    connect(finishButton, &QPushButton::clicked, this, &ManagingDialog::onAccept);
    connect(cancelButton, &QPushButton::clicked, this, &ManagingDialog::onReject);
}

void ManagingDialog::setupRemoveRdvFromDataBase(void){
    setWindowTitle(mainwindow->getWindowTitle());

    auto fixedLayout = new QVBoxLayout();
    setLayout(fixedLayout);

    auto label = new QLabel(tr("Supprimer des Rendez-vous de la base de données","Remove appointment from the data base"));
    label->setFont(QFont(label->font().family(), 20));
    label->setTextInteractionFlags(Qt::TextBrowserInteraction);
    fixedLayout->addWidget(label);
    fixedLayout->addSpacing(10);
    auto line = new QFrame();
    line->setFrameStyle(QFrame::HLine);
    fixedLayout->addWidget(line);
    fixedLayout->addSpacing(10);

    auto mainLayout = new QHBoxLayout();
    auto addPersonneformLayout = new QVBoxLayout();
    auto formLayout = new QFormLayout();
    formLayout->addRow(new QLabel(tr("Saisir le nom du Rendez-vous à supprimer","Enter the name of the appointment to remove")));
    this->lineEditName = new QLineEdit();
    lineEditName->setToolTip(tr("Saisir le nom du Rendez-vous", "Put the name of the appointment"));
    lineEditName->setClearButtonEnabled(true);
    lineEditName->setDragEnabled(true);
    formLayout->addRow(tr("Nom", "Name"), lineEditName);

    addPersonneformLayout->addLayout(formLayout);
    addPersonneformLayout->addSpacing(10);
    auto removeButton = new QPushButton(tr("Supprimer", "Remove"));
    addPersonneformLayout->addWidget(removeButton, 0, Qt::AlignHCenter);
    addPersonneformLayout->addStretch(0);

    mainLayout->addLayout(addPersonneformLayout);
    mainLayout->addSpacing(50);

    auto listPersonneLayout = new QVBoxLayout();
    listPersonneLayout->addWidget(new QLabel(tr("Liste des Rendez-vous à supprimer","List of the appointment to remove")), 0, Qt::AlignHCenter);

    this->SA = new QScrollArea();
    auto saWidget = new QWidget();
    auto saLayout = new QVBoxLayout();
    saWidget->setLayout(saLayout);
    SA->setWidget(saWidget);
    SA->setWidgetResizable(true);

    listPersonneLayout->addWidget(SA);

    mainLayout->addLayout(listPersonneLayout);

    fixedLayout->addLayout(mainLayout);

    auto buttonLayout = new QHBoxLayout();
    auto finishButton = new QPushButton(tr("Terminer", "Finished"));
    auto cancelButton = new QPushButton(tr("Annuler", "Cancel"));

    buttonLayout->addStretch(0);
    buttonLayout->addWidget(finishButton);
    buttonLayout->addWidget(cancelButton);

    fixedLayout->addLayout(buttonLayout);

    connect(lineEditName, &QLineEdit::textChanged, this, &ManagingDialog::onTextChangedLineEditName);
    connect(removeButton, &QPushButton::clicked, this, &ManagingDialog::onRemoveRdv);
    connect(finishButton, &QPushButton::clicked, this, &ManagingDialog::onAccept);
    connect(cancelButton, &QPushButton::clicked, this, &ManagingDialog::onReject);
}

void ManagingDialog::updateSA(void){

    this->listPersonneLayout->itemAt(1)->widget()->hide();
    this->listPersonneLayout->removeWidget(SA);
    this->SA = new QScrollArea();
    auto saWidget = new QWidget();
    auto saLayout = new QVBoxLayout();

    switch(reason){
    case AddPersonneToDataBase:
    case RemovePersonneFromDataBase:
        for(unsigned i = 0; i < listPersonne.size(); ++i)
            saLayout->addWidget(new QPushButton(listPersonne[i]->toQString()));
        break;
    case AddRdvToDataBase:
    case RemoveRdvFromDataBase:
        for(unsigned i = 0; i < listRDV.size(); ++i)
            saLayout->addWidget(new QPushButton(listRDV[i]->toQString()));
        break;
    default:
        cerr << tr("Erreur : reason = ", "Error, reason = ").toStdString() << reason << endl << endl;
        break;
    }

    saLayout->addStretch(0);
    saWidget->setLayout(saLayout);
    this->SA->setWidget(saWidget);
    this->listPersonneLayout->addWidget(SA);
}



// ---------- Getters ----------
const LDCP& ManagingDialog::getListPersonne(void){
    return this->listPersonne;
}

const LDCR& ManagingDialog::getListRDV(void){
    return this->listRDV;
}


// ---------- Slots privés ----------
void ManagingDialog::onAccept(void){
    QDialog::accept();
}

void ManagingDialog::onAddPersonne(void){
    auto lastName = lineEditLastName->text().toStdString(), firstName = lineEditFirstName->text().toStdString(),
            email = lineEditEmail->text().toStdString(), phone = lineEditPhone->text().toStdString();

    if(lastName == "" or firstName == "" or email == "" or phone == ""){
        QString msg = tr("Les champs sont incorrectes", "Fields are incorrects") + "\t\n";
        QMessageBox(QMessageBox::Warning, mainwindow->getWindowTitle(), msg, QMessageBox::Ok).exec();
        return;
    }

    auto p = new Personne(firstName, lastName, email, phone);
    int ind = mainwindow->getManager().getListPersonnes().rechD(p);

    if(ind != -1){
        QString msg = tr("La Personne est déjà dans la base de données", "The People is already inside the data base") + "\t\n";
        QMessageBox(QMessageBox::Warning, mainwindow->getWindowTitle(), msg, QMessageBox::Ok).exec();
        delete p;
    }else{
        listPersonne.inserer(p);
        updateSA();
    }
}

void ManagingDialog::onAddRdv(void){
    auto name = lineEditName->text().toStdString(), date = lineEditDate->text().toStdString(),
            timeStart = lineEditTimeStart->text().toStdString(), timeEnd = lineEditTimeEnd->text().toStdString();

    if(name == "" or date == "//" or timeStart == "hms" or timeEnd == "hms"){
        QString msg = tr("Les champs sont incorrectes", "Fields are incorrects") + "\t\n";
        QMessageBox(QMessageBox::Warning, mainwindow->getWindowTitle(), msg, QMessageBox::Ok).exec();
        return;
    }

    Date d;
    Hour ts, te;

    int db = date == "//" ? 2 : stoDate(date, d),
            tsb = timeStart == "hms" ? 2 : stoHour(timeStart, ts),
            teb = timeEnd == "hms" ? 2 : stoHour(timeEnd, te);
    if(db != 2 or tsb != 2 or teb != 2 ) cout << endl;

    if(!db or !tsb or !teb){
        QString msg = "";

        if(!db) msg += tr("La date est invalide", "The date is incorrect") + " : " + date.c_str() + "\t\n";
        if(!tsb) msg += tr("L'heure de début est incorrecte", "The starting time is incorrect") + " : " + timeStart.c_str() + "\t\n";
        if(!teb) msg += tr("L'heure de fin est incorrecte", "The ending time is incorrect") + " : " + timeEnd.c_str() + "\t\n";

        QMessageBox(QMessageBox::Warning, mainwindow->getWindowTitle(), msg, QMessageBox::Ok).exec();

    }else if(ts > te){
        QString msg = tr("L'heure de début est supérieure à l'heure de fin", "Starting time is greater than the ending time") + "\t\n";
        QMessageBox(QMessageBox::Warning, mainwindow->getWindowTitle(), msg, QMessageBox::Ok).exec();

    }else if(db and tsb and teb){
        auto rdv = new RDV(name, d, ts, te);
        int ind = mainwindow->getManager().getListRDV().rechD(rdv);

        if(ind != -1){
            QString msg = tr("Le Rendez-vous est déjà dans la base de données", "The appointment is already inside the data base") + "\t\n";
            QMessageBox(QMessageBox::Warning, mainwindow->getWindowTitle(), msg, QMessageBox::Ok).exec();
            delete rdv;
        }else{
            delete rdv;
            rdv = mainwindow->getManager().getListRDV()[ind];

            listRDV.inserer(rdv);
            updateSA();
        }
    }
}

void ManagingDialog::onReject(void){
    QDialog::reject();
}

void ManagingDialog::onRemovePersonne(void){
    auto lastName = lineEditLastName->text().toStdString(), firstName = lineEditFirstName->text().toStdString();

    auto p = new Personne(firstName, lastName, "", "");
    int ind = mainwindow->getManager().getListPersonnes().rechD(p);
    if(ind == -1){
        QString msg = tr("La Personne n'existe pas", "The People does not exists") + "\t\n" + QString::fromStdString(p->getLastName() + " " + p->getFirstName());
        QMessageBox(QMessageBox::Warning, mainwindow->getWindowTitle(), msg, QMessageBox::Ok).exec();
        delete p;
    }else{
        delete p;
        p = mainwindow->getManager().getListPersonnes()[ind];

        if(p->getRDVList().size() != 0){
            QString msg = tr("La Personne a des Rendez-vous", "The People has appointments") + "\t\n";
            QMessageBox(QMessageBox::Warning, mainwindow->getWindowTitle(), msg, QMessageBox::Ok).exec();
        }else{
            listPersonne.inserer(p);
            updateSA();
        }
    }
}

void ManagingDialog::onRemoveRdv(void){
    auto name = lineEditName->text().toStdString();

    auto rdv = new RDV(name, {}, {}, {});
    int ind = mainwindow->getManager().getListRDV().rechD(rdv);

    if(ind == -1){
        QString msg = tr("Le Rendez-vous n'existe pas", "The appointment does not exists") + "\t\n" + QString::fromStdString(rdv->getName());
        QMessageBox(QMessageBox::Warning, mainwindow->getWindowTitle(), msg, QMessageBox::Ok).exec();
        delete rdv;

    }else{
        delete rdv;
        rdv = mainwindow->getManager().getListRDV()[ind];
        listRDV.inserer(rdv);
        updateSA();
    }
}

void ManagingDialog::onTextChangedLineEditDate(const QString& text){
    QSignalBlocker blocker(lineEditDate);
    lineEditDate->setText(text);
    blocker.unblock();
}

void ManagingDialog::onTextChangedLineEditEmail(const QString& text){
    QSignalBlocker blocker(lineEditEmail);
    lineEditEmail->setText(text);
    blocker.unblock();
}

void ManagingDialog::onTextChangedLineEditFirstName(const QString& text){
    QSignalBlocker blocker(lineEditFirstName);
    lineEditFirstName->setText(text);
    blocker.unblock();
}

void ManagingDialog::onTextChangedLineEditLastName(const QString& text){
    QSignalBlocker blocker(lineEditLastName);
    lineEditLastName->setText(text);
    blocker.unblock();
}

void ManagingDialog::onTextChangedLineEditPhone(const QString& text){
    QSignalBlocker blocker(lineEditPhone);
    lineEditPhone->setText(text);
    blocker.unblock();
}

void ManagingDialog::onTextChangedLineEditName(const QString& text){
    QSignalBlocker blocker(lineEditName);
    lineEditName->setText(text);
    blocker.unblock();
}

void ManagingDialog::onTextChangedLineEditTimeEnd(const QString& text){
    QSignalBlocker blocker(lineEditTimeEnd);
    lineEditTimeEnd->setText(text);
    blocker.unblock();
}

void ManagingDialog::onTextChangedLineEditTimeStart(const QString& text){
    QSignalBlocker blocker(lineEditTimeStart);
    lineEditTimeStart->setText(text);
    blocker.unblock();
}


