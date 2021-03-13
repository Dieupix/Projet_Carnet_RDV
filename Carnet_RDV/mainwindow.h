#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QBoxLayout>
#include <QPushButton>
#include <QMessageBox>
#include <QLabel>

#include "manager.h"

class MainWindow : public QWidget
{
    Q_OBJECT

    friend class manager;
private:
    void setup(void);
    void mainLayoutSetup(void);

    void updateWindowTitle(void);

    bool isSaved = false;
    manager Manager;
    QProgressBar* loadingBar;
    QHBoxLayout* mainLayout;
    string windowTitle = "Carnet de Rendez-vous";

public:
    MainWindow(QWidget *parent = nullptr);

    void updateLoadingBar(int i);

private slots:
    void onSave(void);
    void onQuit(void);

};

#endif // MAINWINDOW_H
