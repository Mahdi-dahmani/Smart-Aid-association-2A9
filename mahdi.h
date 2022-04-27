#ifndef MAHDI_H
#define MAHDI_H

#include <QMainWindow>
#include <sponsor1.h>
#include<QObject>
#include <QMainWindow>
#include "historique.h"
#include "arduino.h"
#include <QtDebug>
#include<QTimer>
#include "avis.h"
#include <QtWidgets>
namespace Ui {
class mahdi;
}

class mahdi : public QMainWindow
{
    Q_OBJECT

public:
    explicit mahdi(QWidget *parent = nullptr);
    ~mahdi();
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

    void on_adresse_3_textChanged(const QString &arg1);

    void on_pushButton_5_clicked();

    void on_pushButton_4_clicked();
void  update_label();


void on_pushButton_pressed();

void on_kodem_clicked();

void on_isar_clicked();

void on_imine_clicked();

void on_lteli_clicked();

void on_stop_clicked();


void on_kodem_pressed();

void on_kodem_released();

void on_imine_pressed();

void on_imine_released();

void on_isar_pressed();

void on_isar_released();

void on_lteli_pressed();

void on_lteli_released();
void on_id_c_clicked();

void on_nom_c_clicked();

void on_prenom_c_clicked();

void on_email_c_clicked();

void on_num_c_clicked();

void on_adresse_c_clicked();

void on_Dtate_c_clicked();

void on_montant_c_clicked();

void on_sponsor_2_clicked();

void on_gif_linkActivated(const QString &link);

void on_temps_linkActivated(const QString &link);
void myfunction();
void Add();
void Remove();
void Multy();
void Div();
void on_pushButton_7_clicked();
void on_forward_clicked();

void on_forward_released();

void on_left_clicked();

void on_left_released();

void on_back_clicked();

void on_back_released();

void on_right_clicked();

void on_right_released();

void on_art_clicked();

private:
    Ui::mahdi *ui;
    Sponsor1 spon;
    historique h;
    avis ar;
    Arduino A;
    QByteArray data;
    QTimer *timer;
QDateTime *sDate;
};

#endif // MAHDI_H
