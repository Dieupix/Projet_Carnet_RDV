#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>

#include "manager.h"

class MainWindow : public QWidget
{
    Q_OBJECT

private:

    void setup(void);

private slots:

public:
    MainWindow(QWidget *parent = nullptr);

};

#endif // MAINWINDOW_H
