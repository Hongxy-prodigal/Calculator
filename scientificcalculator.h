#ifndef SCIENTIFICCALCULATOR_H
#define SCIENTIFICCALCULATOR_H

#include <QWidget>
#include <QMap>
#include <QPushButton>
#include <QStack>
#include <QKeyEvent>

namespace Ui {
class ScientificCalculator;
}

class ScientificCalculator : public QWidget
{
    Q_OBJECT

public:
    explicit ScientificCalculator(QWidget *parent = nullptr);
    ~ScientificCalculator();

    QStack<QString> operands;
    QStack<QString> codes;
    QString operand;
    QString code;
//    QString operands;
//    QString codes;
    QMap<int, QPushButton *> keyBtns;
    QMap<int, QPushButton *> operatorBtns;
    QString calculation();

private:
    Ui::ScientificCalculator *ui;
    int Change = 0;
    int Clear = 0;

private slots:
    void on_btnNd_clicked();
    void btnNumClicked();
    void on_btnPeriod_clicked();
    void on_btnDel_clicked();
    void on_btnClearAll_clicked();
    void on_btnSign_clicked();
    void btnOperatorClicked();
//    void on_btnEqual_clicked();
//    void btnUniOperatorClicked();
    void keyPressEvent(QKeyEvent *event);
};

#endif // SCIENTIFICCALCULATOR_H
