#ifndef PROGRAMMERCALCULATOR_H
#define PROGRAMMERCALCULATOR_H

#include <QWidget>
#include <QMap>
#include <QPushButton>
#include <QStack>
#include <QKeyEvent>

namespace Ui {
class ProgrammerCalculator;
}

class ProgrammerCalculator : public QWidget
{
    Q_OBJECT

public:
    explicit ProgrammerCalculator(QWidget *parent = nullptr);
    ~ProgrammerCalculator();

    QStack<QString> operands;   //存储操作数
    QStack<QString> codes;      //存储操作符
    QString operand;            //当前的操作数
    QString code;               //当前的操作符
    QMap<int, QPushButton *> keyBtns;
    QMap<int, QPushButton *> operatorBtns;

    //计算
    QString calculation();
    //入栈
    void pushCode(const QString &tempCode);
    //比较优先级
    int comparePriority(QString c);
    //显示所有进制
    void setAllDisplay(const QString &str);
    //清楚所有进制
    void clearAllDisplay();
    //转换进制设置addDisplay
    QString replaceNumbersWithBase(const QString &input, int fromBase, int ToBase);
    void removeOperand();


private:
    Ui::ProgrammerCalculator *ui;

    int Bracket = 0;            //括号
    int calculated = 0;         //已经将栈里面的内容计算
    int uniOperator = 0;        //当前的操作数是否已经被但操作数运算了
    int equal = 0;              //是否等号
    int Base = 10;              //当前的进制
    int bitShiftMode = 1;        //位移位的方式

private slots:
    void btnNumClicked();
    void btnBaseClicked();      //进制转换
//    void on_btnPeriod_clicked();
    void on_btnDel_clicked();
    void on_btnClearAll_clicked();
    void on_btnSign_clicked();
    void btnOperatorClicked();
    void btnUniOperatorClicked();
    void on_btnEqual_clicked();
    void keyPressEvent(QKeyEvent *event);
    void on_display_textChanged();   //变换C CE
//    void on_btnLeftBracket_clicked();
//    void on_btnRightBracket_clicked();
    void on_btnBitwise_clicked();
    void on_btnBitShift_clicked();
    void btnBitShiftModeClicked();
    void on_btnLeftBracket_clicked();
    void on_btnRightBracket_clicked();
};

#endif // PROGRAMMERCALCULATOR_H
