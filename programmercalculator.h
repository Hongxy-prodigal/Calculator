#ifndef PROGRAMMERCALCULATOR_H
#define PROGRAMMERCALCULATOR_H

#include <QWidget>

namespace Ui {
class ProgrammerCalculator;
}

class ProgrammerCalculator : public QWidget
{
    Q_OBJECT

public:
    explicit ProgrammerCalculator(QWidget *parent = nullptr);
    ~ProgrammerCalculator();

private slots:
    void on_btnBitwise_clicked();

    void on_btnBitShift_clicked();

private:
    Ui::ProgrammerCalculator *ui;
};

#endif // PROGRAMMERCALCULATOR_H
