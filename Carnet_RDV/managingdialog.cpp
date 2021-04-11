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
        cerr << "Error : reason = " << reason << endl << endl;
        break;
    }
    setFixedSize(width(), height());
    show();
}


// ---------- Méthodes ----------
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
    auto lastName = new QLineEdit();
    formLayout->addRow(tr("Nom", "Last name"), lastName);
    auto firstName = new QLineEdit();
    formLayout->addRow(tr("Prénom", "First name"), firstName);
    auto phone = new QLineEdit();
    formLayout->addRow(tr("N° de téléphone", "Phone number"), phone);
    auto email = new QLineEdit();
    formLayout->addRow(tr("E-mail"), email);

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
    this->removePersonneFormLayout = new QFormLayout();
    removePersonneFormLayout->addRow(new QLabel(tr("Saisir les informations de la Personne à supprimer","Enter the informations of the People to remove")));
    auto lastName = new QLineEdit();
    removePersonneFormLayout->addRow(tr("Nom", "Last name"), lastName);
    auto firstName = new QLineEdit();
    removePersonneFormLayout->addRow(tr("Prénom", "First name"), firstName);

    addPersonneformLayout->addLayout(removePersonneFormLayout);
    addPersonneformLayout->addSpacing(10);
    auto removeButton = new QPushButton(tr("Supprimer", "Remove"));
    addPersonneformLayout->addWidget(removeButton, 0, Qt::AlignHCenter);
    addPersonneformLayout->addStretch(0);

    mainLayout->addLayout(addPersonneformLayout);
    mainLayout->addSpacing(50);

    auto listPersonneLayout = new QVBoxLayout();
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

    connect(firstName, &QLineEdit::textChanged, this, &ManagingDialog::onTextChangedRemovePersonneFromDataBaseFirstName);
    connect(lastName, &QLineEdit::textChanged, this, &ManagingDialog::onTextChangedRemovePersonneFromDataBaseLastName);
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
    auto name = new QLineEdit();
    formLayout->addRow(tr("Nom", "Name"), name);
    auto date = new QLineEdit();
    date->setInputMask("99/99/9999");
    date->setToolTip(tr("Format : jj/mm/aaaa", "Format : dd/mm/yyyy"));
    date->setMaxLength(10);
    formLayout->addRow(tr("Date", "Date"), date);
    auto timeStart = new QLineEdit();
    timeStart->setInputMask("99\\h99m99s");
    timeStart->setToolTip(tr("Format : hh mm ss", "Format : hh mm ss"));
    timeStart->setMaxLength(9);
    formLayout->addRow(tr("Heure de début", "Starting time"), timeStart);
    auto timeEnd = new QLineEdit();
    timeEnd->setInputMask("99\\h99m99s");
    timeEnd->setToolTip(tr("Format : hh mm ss", "Format : hh mm ss"));
    timeEnd->setMaxLength(9);
    formLayout->addRow(tr("Heure de fin", "Ending time"), timeEnd);

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
    formLayout->addRow(new QLabel(tr("Saisir les informations du Rendez-vous à supprimer","Enter the informations of the appointment to remove")));
    auto name = new QLineEdit();
    formLayout->addRow(tr("Nom", "Name"), name);

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

    connect(removeButton, &QPushButton::clicked, this, &ManagingDialog::onRemoveRdv);
    connect(finishButton, &QPushButton::clicked, this, &ManagingDialog::onAccept);
    connect(cancelButton, &QPushButton::clicked, this, &ManagingDialog::onReject);
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

}

void ManagingDialog::onAddRdv(void){

}

void ManagingDialog::onReject(void){
    QDialog::reject();
}

void ManagingDialog::onRemovePersonne(void){
    if(removePersonneFormLayout){
        auto lastName = (QLineEdit*) removePersonneFormLayout->itemAt(1, QFormLayout::FieldRole);
        auto firstName = (QLineEdit*) removePersonneFormLayout->itemAt(2, QFormLayout::FieldRole);
        QMessageBox(QMessageBox::Information, "", lastName->text() + firstName->text(), QMessageBox::Ok).exec();
    }
}

void ManagingDialog::onRemoveRdv(void){

}

void ManagingDialog::onTextChangedRemovePersonneFromDataBaseFirstName(const QString& text){
    auto firstName = removePersonneFormLayout ? (QLineEdit*) removePersonneFormLayout->itemAt(2, QFormLayout::FieldRole) : 0;
    if(firstName){
        QSignalBlocker blocker(firstName);
        firstName->setText(text);
        blocker.unblock();
    }
}

void ManagingDialog::onTextChangedRemovePersonneFromDataBaseLastName(const QString& text){
    auto lastName = removePersonneFormLayout and removePersonneFormLayout->itemAt(1, QFormLayout::FieldRole) ? (QLineEdit*) removePersonneFormLayout->itemAt(1, QFormLayout::FieldRole) : 0;
    if(lastName){
        QSignalBlocker blocker(lastName);
        lastName->setText(text);
        blocker.unblock();
    }
}


