#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <sponsor1.h>
#include <QMainWindow>
#include "historique.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_ajouter_clicked();

    void on_dial_2_valueChanged(int value);

    void on_Supprimer_clicked();

    void on_afficher_clicked();

    void on_Modifier_clicked();



    void on_recherche_clicked();



    void on_identifiant_editingFinished();

    void on_identifiant2_editingFinished();

    void on_historique_clicked();

    void on_option_currentIndexChanged(const QString &arg1);

    void on_option_activated(const QString &arg1);

    void on_trie_clicked();

    void on_afficher_2_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_export_2_clicked();

    void on_pushButton_3_clicked();

    void on_tableView_clicked(const QModelIndex &index);

    void on_tableView_activated(const QModelIndex &index);

private:
    Ui::MainWindow *ui;
     Sponsor1 spon;
     historique h;
};
#endif // MAINWINDOW_H
