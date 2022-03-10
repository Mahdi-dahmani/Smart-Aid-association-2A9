#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "membre.h"
#include <QMainWindow>

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

private:
    Ui::MainWindow *ui;
    Membre mem;
};
#endif // MAINWINDOW_H

