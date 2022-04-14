#ifndef AVIS1_H
#define AVIS1_H

#include <QWidget>

namespace Ui {
class avis1;
}

class avis1 : public QWidget
{
    Q_OBJECT

public:
    explicit avis1(QWidget *parent = nullptr);
    ~avis1();

private:
    Ui::avis1 *ui;
};

#endif // AVIS1_H
