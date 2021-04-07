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

class Manager;
class LoadingDialog;

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
    Manager         manager;
    QBoxLayout*     mainLayout;
    QBoxLayout*     personneListLayout;
    QBoxLayout*     rdvListLayout;
    QBoxLayout*     rechRdvDate;
    QMainWindow*    window;

    // Méthodes privées
    void setup(void);
    QBoxLayout*     setupButtonLayout(void);
    void            setupEditMenu(QMenu* editMenu);
    void            setupFileMenu(QMenu* fileMenu);
    QBoxLayout*     setupFooterLayout(void);
    QBoxLayout*     setupListLayout(void);
    QBoxLayout*     setupMainLayout(void);
    void            setupMenuBar(void);
    void            setupRechRdvDate(void);
    void            setupViewMenu(QMenu* viewMenu);

    void showPersonneListLayout(bool);
    void showRDVListLayout(bool);
    void updatePersonneListLayout(void);
    void updateRDVListLayout(void);
    void updateWindowTitle(void);

public:
    MainWindow(QMainWindow *parent = nullptr);

    void loadFile(void);
    bool saveFile(void);

    // Getters
    Manager&    getManager(void);
    QString     getWindowTitle(void);

    // Setters
    void setSave(bool saved);

private slots:
    void onPersonneListCheckBox(bool);
    void onQuit(void);
    void onRDVListCheckBox(bool);
    void onRechRdvDate(void);
    void onSave(void);
    void onSaveAndQuit(void);
    void onSpinBox(int i);

};

#endif // MAINWINDOW_H
