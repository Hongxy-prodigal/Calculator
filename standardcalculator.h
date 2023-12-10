#ifndef STANDARDCALCULATOR_H
#define STANDARDCALCULATOR_H

#include <QWidget>
#include<QStack>
#include<QMap>
#include<QPushButton>
#include<QKeyEvent>

namespace Ui {
class StandardCalculator;
}

class StandardCalculator : public QWidget
{
    Q_OBJECT

public:
    explicit StandardCalculator(QWidget *parent = nullptr);
    ~StandardCalculator();
    QString operand;
    QString code;
    QString operands;
    QString codes;
    QMap<int, QPushButton *> keyBtns;
    QMap<int, QPushButton *> operatorBtns;
    QString calculation();

private:
    Ui::StandardCalculator *ui;

private slots:
    void btnNumClicked();
    void on_btnPeriod_clicked();
    void on_btnDel_clicked();
    void on_btnClearAll_clicked();
    void on_btnSign_clicked();
    void on_btnClear_clicked();
    void btnOperatorClicked();
    void on_btnEqual_clicked();
    void btnUniOperatorClicked();
    void keyPressEvent(QKeyEvent *event);
};

#endif // STANDARDCALCULATOR_H









