#include "avis1.h"
#include "ui_avis1.h"

avis1::avis1(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::avis1)
{
    ui->setupUi(this);
}

avis1::~avis1()
{
    delete ui;
}
