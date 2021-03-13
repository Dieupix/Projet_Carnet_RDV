#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QBoxLayout>
#include <QPushButton>
#include <QProgressBar>
#include <QMessageBox>
#include <QLabel>

#include "manager.h"

class MainWindow : public QWidget
{
    Q_OBJECT

private:
    void setup(void);
    void mainLayoutSetup(void);

    void updateWindowTitle(void);

    bool isSaved = false;
    manager Manager;
    QHBoxLayout* mainLayout;
    string windowTitle = "Carnet de Rendez-vous";

public:
    MainWindow(QWidget *parent = nullptr);

private slots:
    void onSave(void);
    void onQuit(void);

};

#endif // MAINWINDOW_H
