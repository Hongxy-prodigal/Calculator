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

    QStack<QString> operands;   //存储操作数
    QStack<QString> codes;      //存储操作符
    QString operand;            //当前的操作数
    QString code;               //当前的操作符
//    QString operands;
//    QString codes;
    QMap<int, QPushButton *> keyBtns;
    QMap<int, QPushButton *> operatorBtns;
    QString calculation();
    //入栈
    void pushCode(const QString &tempCode);
    int comparePriority(QString c);
    //出栈
    void popCode(const QString &code);
    //去除到操作数
    void removeOperand();

private:
    Ui::ScientificCalculator *ui;
    int Change = 0;         //变换按键
    int Bracket = 0;    //括号
    int have = 0;        //当前的操作数是否已经被但操作数运算了
    int calculated = 0;   //已经将栈里面的内容计算

private slots:
    void on_btnNd_clicked();
    void btnNumClicked();
    void on_btnPeriod_clicked();
    void on_btnDel_clicked();
    void on_btnClearAll_clicked();
    void on_btnSign_clicked();
    void btnOperatorClicked();
//    void on_btnEqual_clicked();
    void btnUniOperatorClicked();
    void keyPressEvent(QKeyEvent *event);
    void on_display_textChanged(const QString &arg1);   //变换C CE
    void on_btnLeftBracket_clicked();
    void on_btnRightBracket_clicked();
};

#endif // SCIENTIFICCALCULATOR_H
