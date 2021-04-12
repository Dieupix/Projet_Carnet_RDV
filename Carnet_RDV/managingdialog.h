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
    QLineEdit*              lineEditDate;
    QLineEdit*              lineEditEmail;
    QLineEdit*              lineEditFirstName;
    QLineEdit*              lineEditLastName;
    QLineEdit*              lineEditPhone;
    QLineEdit*              lineEditName;
    QLineEdit*              lineEditTimeEnd;
    QLineEdit*              lineEditTimeStart;
    LDCP                    listPersonne;
    QBoxLayout*             listPersonneLayout;
    LDCR                    listRDV;
    MainWindow*             mainwindow;
    ManagingDialogReason    reason;
    QScrollArea*            SA;

    // Méthodes
    void setupAddPersonneToDataBase(void);
    void setupRemovePersonneFromDataBase(void);
    void setupAddRdvToDataBase(void);
    void setupRemoveRdvFromDataBase(void);
    void updateSA(void);

public:
    ManagingDialog(MainWindow* mainwindow, ManagingDialogReason reason, QWidget* parent = nullptr);

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
    void onTextChangedLineEditDate(const QString& text);
    void onTextChangedLineEditEmail(const QString& text);
    void onTextChangedLineEditFirstName(const QString& text);
    void onTextChangedLineEditLastName(const QString& text);
    void onTextChangedLineEditPhone(const QString& text);
    void onTextChangedLineEditName(const QString& text);
    void onTextChangedLineEditTimeEnd(const QString& text);
    void onTextChangedLineEditTimeStart(const QString& text);
};

#endif // MANAGINGDIALOG_H
