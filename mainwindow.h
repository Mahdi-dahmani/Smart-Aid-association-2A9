#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <sponsor1.h>
#include<QObject>
#include <QMainWindow>
#include "historique.h"
#include "arduino.h"
#include <QtDebug>
#include <QtBluetooth>
#include<QBluetoothDeviceDiscoveryAgent>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
QBluetoothDeviceDiscoveryAgent *agent=new QBluetoothDeviceDiscoveryAgent;
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
void deviceDiscovered(const QBluetoothDeviceInfo &device);

void on_kodem_pressed();

void on_kodem_released();

void on_imine_pressed();

void on_imine_released();

void on_isar_pressed();

void on_isar_released();

void on_lteli_pressed();

void on_lteli_released();
protected:

private:
    Ui::MainWindow *ui;
     Sponsor1 spon;
     historique h;
     Arduino A;
     QByteArray data;
};
#endif // MAINWINDOW_H
