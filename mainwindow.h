#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include "donateurs.h"
#include <QTableView>
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

private:
    Ui::MainWindow *ui;
    donateurs dtmp;
    Dons dotmp;
};
#endif // MAINWINDOW_H
