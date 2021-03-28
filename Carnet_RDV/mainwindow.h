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

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    // Constantes
    const QString windowTitle = "Carnet de Rendez-vous";
    const QString uhaURL = "https://www.uha.fr";

    bool isSaved = true;
    Manager manager;
    QBoxLayout* mainLayout;
    QMainWindow* window;
    QProgressBar* loadingBar = new QProgressBar();

    // Méthodes privées
    void setup(void);
    void setupEditMenu(QMenu* editMenu);
    void setupFileMenu(QMenu* fileMenu);
    QBoxLayout* setupFooterLayout(void);
    QBoxLayout* setupMainLayout(void);
    void setupMenuBar(void);

    void updateLoadingBar(int i);
    void updateWindowTitle(void);

public:
    MainWindow(QMainWindow *parent = nullptr);

    void loadFile(void);

private slots:
    void onQuit(void);
    void onSave(void);
    void onSaveAndQuit(void);
    void onSpinBox(int i);

};

#endif // MAINWINDOW_H
