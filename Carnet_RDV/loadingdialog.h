#ifndef LOADINGDIALOG_H
#define LOADINGDIALOG_H

#include "mainwindow.h"

class MainWindow;

class LoadingDialog : public QDialog
{
    Q_OBJECT
private:
    void setup(void);

    MainWindow* mainwindow;
    QString     filePath;

public:
    LoadingDialog(MainWindow* mainwindow, const QString& filePath, QWidget *parent = nullptr);

private slots:
    void onAccept(void);
    void onReject(void);

};

#endif // LOADINGDIALOG_H
