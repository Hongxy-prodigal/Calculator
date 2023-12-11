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

private:
    Ui::ProgrammerCalculator *ui;
};

#endif // PROGRAMMERCALCULATOR_H
