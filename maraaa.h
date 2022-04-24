#ifndef MARAAA_H
#define MARAAA_H

#include <QMainWindow>
#include "donateurs.h"
#include <QTableView>
#include "dons.h"
#include "arduino.h"

namespace Ui {
class Maraaa;
}

class Maraaa : public QMainWindow
{
    Q_OBJECT

public:
    explicit Maraaa(QWidget *parent = nullptr);
    ~Maraaa();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_12_clicked();

    void on_pushButton_13_clicked();

    void on_pushButton_3_clicked();

    void on_trie_clicked();

    void on_lineEdit_editingFinished();

    void on_excel_clicked();

    void on_pushButton_7_clicked();

    void on_boutonajoutdon_clicked();

    void on_supprimerdon_clicked();

    void on_pushButton_4_clicked();
    void update_label();   // slot permettant la mise à jour du label état de la lampe 1,
    // ce slot est lancé à chaque réception d'un message de Arduino



    void on_pushButton_2_clicked(); // bouton OFF




    void on_art_clicked();
    void on_pushButton_released();
private:
    Ui::Maraaa *ui;
    donateurs dtmp;
    Dons dotmp;
    QByteArray data; // variable contenant les données reçues

    Arduino A;
};

#endif // MARAAA_H
