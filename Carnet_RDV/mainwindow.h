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
    QIcon carnetIcon = QIcon("‪E:/Téléchargements/icons8-carnet-d-adresses-2-100.bmp");

    bool isSaved = false;
    manager Manager;
    QHBoxLayout* mainLayout;

public:
    MainWindow(QWidget *parent = nullptr);

private slots:
    void onSave(void);
    void onQuit(void);

};

#endif // MAINWINDOW_H
