#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QBoxLayout>
#include <QFileDialog>
#include <QLabel>
#include <QMainWindow>
#include <QMenuBar>
#include <QMessageBox>
#include <QPushButton>
#include <QScrollArea>
#include <QSpinBox>

#include "manager.h"

// Fonctions annexes
void preHideOrShow(QBoxLayout* QBoxToHideOrShow, bool show);
void hideOrShow(QBoxLayout* QBoxToHideOrShow, bool show, QBoxLayout* parent, int ind = -1, int stretch = 0);

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    // Constantes
    const QString windowTitle = "Carnet de Rendez-vous";
    const QString uhaURL = "https://www.uha.fr";

    bool isSaved = true;
    QBoxLayout* fixedLayout;
    QBoxLayout* listLayout;
    Manager manager;
    QBoxLayout* mainLayout;
    QBoxLayout* personneListLayout;
    QBoxLayout* rdvListLayout;
    QMainWindow* window;

    // Méthodes privées
    void setup(void);
    QBoxLayout* setupButtonLayout(void);
    void setupEditMenu(QMenu* editMenu);
    void setupFileMenu(QMenu* fileMenu);
    QBoxLayout* setupFooterLayout(void);
    QBoxLayout* setupListLayout(void);
    QBoxLayout* setupMainLayout(void);
    void setupMenuBar(void);
    void setupViewMenu(QMenu* viewMenu);

    void showPersonneListLayout(bool);
    void showRDVListLayout(bool);
    void updatePersonneListLayout(void);
    void updateRDVListLayout(void);
    void updateWindowTitle(void);

public:
    MainWindow(QMainWindow *parent = nullptr);

    void loadFile(void);

private slots:
    void onPersonneListCheckBox(bool);
    void onQuit(void);
    void onRDVListCheckBox(bool);
    void onSave(void);
    void onSaveAndQuit(void);
    void onSpinBox(int i);

};

#endif // MAINWINDOW_H
