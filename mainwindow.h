#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "membre.h"
#include <QMainWindow>
#include "donateurs.h"
#include "dons.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

void on_pushButton_ajouter_clicked();
private slots:
void on_pushButton_clicked();

void on_pushButton_2_clicked();

void on_pushButton_4_clicked();

void on_pushButton_6_clicked();

void on_lineEdit_user_selectionChanged();

void on_lineEdit_nom_editingFinished();

void on_lineEdit_prenom_editingFinished();

void on_lineEdit_branche_editingFinished();

void on_lineEdit_mdp_editingFinished();

void on_lineEdit_user_editingFinished();

void on_p_nom_clicked();

void on_p_id_clicked();
void on_pushButton_7_clicked();


void on_p_prenom_clicked();

void on_p_user_clicked();

void on_excel_clicked();

void on_pushButton_7_clicked(bool checked);

void on_mdm_clicked();

void on_pushButton_8_clicked();

private:
donateurs dtmp;
Dons dotmp;
    Ui::MainWindow *ui;
    Membre mem;
};
#endif // MAINWINDOW_H

