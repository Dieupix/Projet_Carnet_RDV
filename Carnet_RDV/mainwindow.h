#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QBoxLayout>
#include <QFileDialog>
#include <QFormLayout>
#include <QLabel>
#include <QLineEdit>
#include <QMainWindow>
#include <QMenuBar>
#include <QMessageBox>
#include <QPushButton>
#include <QScrollArea>
#include <QSpinBox>

#include "loadingdialog.h"
#include "manager.h"
#include "managingdialog.h"

class LoadingDialog;
class Manager;
class ManagingDialog;

// Fonctions annexes
void preHideOrShow(QBoxLayout* QBoxToHideOrShow, bool show);
void hideOrShow(QBoxLayout* QBoxToHideOrShow, bool show, QBoxLayout* parent, int ind = -1, int stretch = 0);

class MainWindow : public QMainWindow
{
    Q_OBJECT

    friend class LoadingDialog;
private:
    // Constantes
    const QString windowTitle = tr("Carnet de Rendez-vous", "Appointment Book");
    const QString uhaURL = "https://www.uha.fr";

    bool isSaved = true;

    QBoxLayout*     listLayout;
    QBoxLayout*     listPersonneRdvLayout;
    QLineEdit*      listPersonneRdvLayoutLineEdit;
    QLabel*         listPersonneRdvLayoutLabel;
    QScrollArea*    listPersonneRdvLayoutSA;
    QBoxLayout*     listRdvPersonneLayout;
    QLineEdit*      listRdvPersonneLayoutLineEditFirstName;
    QLineEdit*      listRdvPersonneLayoutLineEditLastName;
    QLabel*         listRdvPersonneLayoutLabel;
    QScrollArea*    listRdvPersonneLayoutSA;
    Manager         manager;
    QBoxLayout*     mainLayout;
    QBoxLayout*     modifyPersonneLayout;
    QLineEdit*      modifyPersonneLayoutLineEditEmail;
    QLineEdit*      modifyPersonneLayoutLineEditFirstName;
    QLineEdit*      modifyPersonneLayoutLineEditLastName;
    QLineEdit*      modifyPersonneLayoutLineEditPhone;
    QLabel*         modifyPersonneLayoutLabel;
    QScrollArea*    modifyPersonneLayoutSA;
    QBoxLayout*     modifyPersonneRdvLayout;
    QLineEdit*      modifyPersonneRdvLayoutLineEditFirstName;
    QLineEdit*      modifyPersonneRdvLayoutLineEditLastName;
    QLineEdit*      modifyPersonneRdvLayoutLineEditRdvName;
    QLabel*         modifyPersonneRdvLayoutLabel;
    QScrollArea*    modifyPersonneRdvLayoutSA;
    QBoxLayout*     modifyRdvLayout;
    QLineEdit*      modifyRdvLayoutLineEditName;
    QLineEdit*      modifyRdvLayoutLineEditDate;
    QLineEdit*      modifyRdvLayoutLineEditTimeStart;
    QLineEdit*      modifyRdvLayoutLineEditTimeEnd;
    QLabel*         modifyRdvLayoutLabel;
    QScrollArea*    modifyRdvLayoutSA;
    QBoxLayout*     personneListLayout;
    QBoxLayout*     rdvListLayout;
    QBoxLayout*     rechRdvDate;
    QLineEdit*      rechRdvDateLineEdit;
    QLabel*         rechRdvDateLabel;
    QScrollArea*    rechRdvDateSA;
    QMainWindow*    window;

    // Méthodes privées
    void            setup(void);
    QBoxLayout*     setupButtonLayout(void);
    void            setupEditMenu(QMenu* editMenu);
    void            setupFileMenu(QMenu* fileMenu);
    QBoxLayout*     setupFooterLayout(void);
    QBoxLayout*     setupListLayout(void);
    void            setupListPersonneRdvLayout(void);
    void            setupListRdvPersonneLayout(void);
    QBoxLayout*     setupMainLayout(void);
    void            setupMenuBar(void);
    void            setupModifyPersonneLayout(void);
    void            setupModifyPersonneRdvLayout(void);
    void            setupModifyRdvLayout(void);
    void            setupRechRdvDate(void);
    void            setupViewMenu(QMenu* viewMenu);

    void showPersonneListLayout(bool);
    void showRDVListLayout(bool);
    void updatePersonneListLayout(void);
    void updateRDVListLayout(void);
    void updateWindowTitle(void);

public:
    MainWindow(QMainWindow *parent = nullptr);

    // Méthodes
    void loadFile(void);
    bool saveFile(void);

    // Getters
    Manager&    getManager(void);
    QString     getWindowTitle(void);

    // Setters
    void setSave(bool saved);

private slots:
    void onAddPersonne(void);
    void onAddRdv(void);
    void onRemovePersonne(void);
    void onRemoveRdv(void);
    void onListPersonneRdv(void);
    void onListPersonneRdvButton(void);
    void onListRdvPersonne(void);
    void onListRdvPersonneButton(void);
    void onModifyPersonne(void);
    void onModifyPersonneButton(void);
    void onModifyPersonneRdv(void);
    void onModifyPersonneRdvAddButton(void);
    void onModifyPersonneRdvRemoveButton(void);
    void onModifyRdv(void);
    void onModifyRdvButton(void);
    void onPersonneListCheckBox(bool);
    void onQuit(void);
    void onRDVListCheckBox(bool);
    void onRechRdvDate(void);
    void onRechRdvDateButton(void);
    void onSave(void);
    void onSaveAndQuit(void);
    void onTextChangedlistPersonneRdvLineEdit(const QString& text);
    void onTextChangedlistRdvPersonneLineEditFirstName(const QString& text);
    void onTextChangedlistRdvPersonneLineEditLastName(const QString& text);
    void onTextChangedmodifyPersonneLineEditEmail(const QString& text);
    void onTextChangedmodifyPersonneLineEditFirstName(const QString& text);
    void onTextChangedmodifyPersonneLineEditLastName(const QString& text);
    void onTextChangedmodifyPersonneLineEditPhone(const QString& text);
    void onTextChangedmodifyPersonneRdvLineEditFirstName(const QString& text);
    void onTextChangedmodifyPersonneRdvLineEditLastName(const QString& text);
    void onTextChangedmodifyPersonneRdvLineEditRdvName(const QString& text);
    void onTextChangedmodifyRdvLineEditName(const QString& text);
    void onTextChangedmodifyRdvLineEditDate(const QString& text);
    void onTextChangedmodifyRdvLineEditTimeStart(const QString& text);
    void onTextChangedmodifyRdvLineEditTimeEnd(const QString& text);
    void onTextChangedrechRdvDateLineEdit(const QString& text);

};

#endif // MAINWINDOW_H
