#ifndef SCIENTIFICCALCULATOR_H
#define SCIENTIFICCALCULATOR_H

#include <QWidget>

namespace Ui {
class ScientificCalculator;
}

class ScientificCalculator : public QWidget
{
    Q_OBJECT

public:
    explicit ScientificCalculator(QWidget *parent = nullptr);
    ~ScientificCalculator();

private slots:
    void on_btnNd_clicked();

private:
    Ui::ScientificCalculator *ui;
    int Change = 0;
};

#endif // SCIENTIFICCALCULATOR_H
