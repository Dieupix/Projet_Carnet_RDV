#ifndef MANAGINGDIALOG_H
#define MANAGINGDIALOG_H

#include "mainwindow.h"

class MainWindow;

class ManagingDialog : public QDialog
{
    Q_OBJECT
public:
    enum ManagingDialogReason {AddPersonneToDataBase, RemovePersonneFromDataBase,
                              AddRdvToDataBase, RemoveRdvFromDataBase, };
private:
    LDCP                    listPersonne;
    LDCR                    listRDV;
    MainWindow*             mainwindow;
    ManagingDialogReason    reason;
    QFormLayout*            removePersonneFormLayout;
    QScrollArea*            SA;

public:
    ManagingDialog(MainWindow* mainwindow, ManagingDialogReason reason, QWidget* parent = nullptr);

    // Méthodes

    void setupAddPersonneToDataBase(void);
    void setupRemovePersonneFromDataBase(void);
    void setupAddRdvToDataBase(void);
    void setupRemoveRdvFromDataBase(void);

    // Getters
    const LDCP& getListPersonne(void);
    const LDCR& getListRDV(void);

private slots:
    void onAccept(void);
    void onAddPersonne(void);
    void onAddRdv(void);
    void onReject(void);
    void onRemovePersonne(void);
    void onRemoveRdv(void);
    void onTextChangedRemovePersonneFromDataBaseFirstName(const QString& text);
    void onTextChangedRemovePersonneFromDataBaseLastName(const QString& text);
};

#endif // MANAGINGDIALOG_H
