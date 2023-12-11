#ifndef DATECALCULATOR_H
#define DATECALCULATOR_H

#include <QWidget>
#include <dateapart.h>
#include <dateoperate.h>

namespace Ui {
class DateCalculator;
}

class DateCalculator : public QWidget
{
    Q_OBJECT

public:
    explicit DateCalculator(QWidget *parent = nullptr);
    ~DateCalculator();

private slots:
    void on_comboBox_activated(int index);

private:
    Ui::DateCalculator *ui;
    DateApart *apart;
    DateOperate *operate;
    void pushWidgetToStackView(QWidget *widget);
};

#endif // DATECALCULATOR_H
