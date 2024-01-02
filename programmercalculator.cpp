#include "programmercalculator.h"
#include "ui_programmercalculator.h"

#include <qdebug.h>

ProgrammerCalculator::ProgrammerCalculator(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ProgrammerCalculator)
{
    ui->setupUi(this);
    ui->groupBoxShift->setVisible(false);
    ui->groupBoxBitwise->setVisible(false);
    ui->btnPeriod->setEnabled(false);
    keyBtns = {
        {Qt::Key_0, ui->btnNum0},
        {Qt::Key_1, ui->btnNum1},
        {Qt::Key_2, ui->btnNum2},
        {Qt::Key_3, ui->btnNum3},
        {Qt::Key_4, ui->btnNum4},
        {Qt::Key_5, ui->btnNum5},
        {Qt::Key_6, ui->btnNum6},
        {Qt::Key_7, ui->btnNum7},
        {Qt::Key_8, ui->btnNum8},
        {Qt::Key_9, ui->btnNum9},
        {Qt::Key_A, ui->btnNumA},
        {Qt::Key_B, ui->btnNumB},
        {Qt::Key_C, ui->btnNumC},
        {Qt::Key_D, ui->btnNumD},
        {Qt::Key_E, ui->btnNumE},
        {Qt::Key_F, ui->btnNumF},
    };
    operatorBtns = {
        {Qt::Key_Backspace, ui->btnDel},
        {Qt::Key_Slash, ui->btnDivide},
        {Qt::Key_Asterisk, ui->btnMul},
        {Qt::Key_Minus, ui->btnSub},
        {Qt::Key_Plus, ui->btnPlus},
        {Qt::Key_Equal, ui->btnEqual},
        {Qt::Key_Return, ui->btnEqual},
    };
    //数字键入
    QList<QPushButton *> values = keyBtns.values();
    foreach (auto btn, values) {
        connect(btn, SIGNAL(clicked()), this, SLOT(btnNumClicked()));
    }
    //操作符
    connect(ui->btnPlus, SIGNAL(clicked()), this, SLOT(btnOperatorClicked()));
    connect(ui->btnSub, SIGNAL(clicked()), this, SLOT(btnOperatorClicked()));
    connect(ui->btnMul, SIGNAL(clicked()), this, SLOT(btnOperatorClicked()));
    connect(ui->btnDivide, SIGNAL(clicked()), this, SLOT(btnOperatorClicked()));
    //进制转换
    connect(ui->btnHEX, SIGNAL(clicked()), this, SLOT(btnBaseClicked()));
    connect(ui->btnDEC, SIGNAL(clicked()), this, SLOT(btnBaseClicked()));
    connect(ui->btnOCT, SIGNAL(clicked()), this, SLOT(btnBaseClicked()));
    connect(ui->btnBIN, SIGNAL(clicked()), this, SLOT(btnBaseClicked()));
    ui->btnDEC->click();
}

ProgrammerCalculator::~ProgrammerCalculator()
{
    delete ui;
}

//进制转换
void ProgrammerCalculator::btnBaseClicked()
{
    QString base = qobject_cast<QPushButton *>(sender())->text();
    ui->btnHEX->setStyleSheet("border-left: none;""font: 9pt Arial;");
    ui->btnDEC->setStyleSheet("border-left: none;""font: 9pt Arial;");
    ui->btnOCT->setStyleSheet("border-left: none;""font: 9pt Arial;");
    ui->btnBIN->setStyleSheet("border-left: none;""font: 9pt Arial;");
    if (base == "HEX") {
        Base = 16;
        ui->btnHEX->setStyleSheet("border-left: 3px solid blue;""font: 9pt Arial;");
    } else if (base == "DEC") {
        Base = 10;
        ui->btnDEC->setStyleSheet("border-left: 3px solid blue;""font: 9pt Arial;");
    } else if (base == "OCT") {
        Base = 8;
        ui->btnOCT->setStyleSheet("border-left: 3px solid blue;""font: 9pt Arial;");
    } else {
        Base = 2;
        ui->btnBIN->setStyleSheet("border-left: 3px solid blue;""font: 9pt Arial;");
    }
    int i = 0;
    QList<QPushButton *> values = keyBtns.values();
    for (auto &key : values) {
        if (i < Base) {
            key->setEnabled(true);
            key->setStyleSheet("QPushButton:hover{""background-color: rgb(252, 252, 252);}"
                               "QPushButton:!hover{""background-color:rgb(255, 255, 255);}");
        } else {
            key->setEnabled(false);
            key->setStyleSheet("QPushButton { background-color: rgb(244, 244, 244); }");
        }
        i++;
    }
}

//删除右括号接数字的括号
int removeRightBracket1(const QString &str)
{
    int rightBracketCount = 0;
    int index = str.length() - 1;
    int count = 0;

    // 从右往左找，找到第一个左括号之前
    while (index >= 0 && str[index] != '(') {
        if (str[index] == ')') {
            ++rightBracketCount;
        }
        --index;
    }
    while (index >= 0) {
        if (str[index] == "(") {
            ++count;
            if (count == rightBracketCount) {
                return index; // 返回第 nth 个字符的索引位置
            }
        }
        --index;
    }
    return index;
}

void ProgrammerCalculator::on_btnBitwise_clicked()
{
    ui->groupBoxBitwise->setVisible(!ui->groupBoxBitwise->isVisible());
    ui->groupBoxShift->setVisible(false);
}


void ProgrammerCalculator::on_btnBitShift_clicked()
{
    ui->groupBoxShift->setVisible(!ui->groupBoxShift->isVisible());
    ui->groupBoxBitwise->setVisible(false);
}

//数字键
void ProgrammerCalculator::btnNumClicked()
{
    //等号
    if (equal == 1) {
        ui->addDisplay->setText("");
        ui->display->setText("");
        equal = 0;
    }
    //出栈计算了
    if (calculated == 1)
        calculated = 0;
    //刚添加操作符
    if (code != "") {
        code = "";
        ui->display->setText("");
        operand = "";
    }
    //右括号加数字
    if (ui->addDisplay->text().right(1) == ")") {
        operand = "";
        ui->display->setText(operand);

        QString str = ui->addDisplay->text();
        int index = removeRightBracket1(str);
        str = str.left(index);
        ui->addDisplay->setText(str);
        qDebug() << operands.pop();
    }
    QString digit = qobject_cast<QPushButton *>(sender())->text();
    if (digit == "0" && operand == "0") {
        digit = "";
    }
    if (digit != "0" && operand == "0") {
        operand = "";
    }
    operand += digit;
    ui->display->setText(operand);
}

//删除键 把符号也删了
void ProgrammerCalculator::on_btnDel_clicked()
{
    if (operand != "" && calculated == 0) {
        operand = operand.left(operand.size() - 1);
        if (operand == "-")
            operand = "";
        ui->display->setText(operand);
    }
}

void ProgrammerCalculator::on_display_textChanged()
{
    if (ui->display->text() != "") {
        ui->btnClearAll->setText("CE");
    } else
        ui->btnClearAll->setText("C");
}

void ProgrammerCalculator::on_btnClearAll_clicked()
{
    //清楚所有
    if (ui->display->text() == "") {
        code = "";
        operands.clear();
        codes.clear();
        ui->display->setText("");
        ui->addDisplay->setText("");
    }
    //清楚当前操作数
    else {
        operand = "";
        ui->display->setText("");
    }
}

//正负号
void ProgrammerCalculator::on_btnSign_clicked()
{

    if (operand != "") {
        if (!operand.contains('-')) {
            operand = '-' + operand;
        } else {
            operand = operand.right(operand.size() - 1);
        }
        ui->display->setText(operand);
        //如果是对以及被单操作符操作过的操作数，则要用negate()
//        if (uniOperator == 1) {
//            QString str = ui->addDisplay->text();
//            int index = getLastOperator(str);
//            QString resultString = str.right(str.size() - index - 1);
//            str = str.left(index + 1);
//            resultString = "negate(" + resultString + ")";

//            if (operand == "" && ui->addDisplay->text().right(1) == "=") {
//                ui->addDisplay->setText(resultString);
//            } else {
//                ui->addDisplay->setText(str + resultString);
//            }
//        }
    }
}

//等于号
void ProgrammerCalculator::on_btnEqual_clicked()
{
    if (equal != 1) {
        QString result = "";
        //如果操作符不为空且操作数为空,认定display的数字为操作数
        if (code != "" && operand == "")
            operand = ui->display->text();
        if (operand == "")
            operand = "0";
        operands.push(operand);

        while (!codes.isEmpty()) {     //有操作符时
            result = calculation();
            operands.push(result);
        }

        //划等号
        ui->addDisplay->setText(ui->addDisplay->text() + operand + "=");
        ui->display->setText(result);
        operands.clear();
        codes.clear();
        code = "";
        operand = result;
        equal = 1;
    }
}

//操作符
void ProgrammerCalculator::btnOperatorClicked()
{
    QString tempCode = qobject_cast<QPushButton *>(sender())->text();
    if (equal == 1) {
        equal = 0;
        ui->addDisplay->setText("");
    }
    if (code != "") {        //避免多次使用操作符
        QString previousCode = codes.pop();
        pushCode(tempCode);
        code = tempCode;
        QString str = ui->addDisplay->text();
        //        叠加问题在这处理
        if (calculated == 1 && comparePriority(code) > comparePriority(previousCode)) {
            ui->addDisplay->setText("(" + str.left(str.size() - 1) + ")" + tempCode);
            calculated = 0;
        } else
            ui->addDisplay->setText(str.left(str.size() - 1) + tempCode);
    } else {
        //当操作数为空时，不需要将操作数放入栈里
        if (operand == "")
            operand = "0";
        operands.push(operand);
        pushCode(tempCode);

        ui->addDisplay->setText(ui->addDisplay->text() + operand + tempCode);
        code = tempCode;
    }
    operand = "";
}

//操作符入栈
void ProgrammerCalculator::pushCode(const QString &tempCode)
{
    qDebug() << codes;
    qDebug() << operands;
    QString result;
    if (tempCode == "×" || tempCode == "÷" || tempCode == "+" || tempCode == "-") {
        if (codes.empty() || codes.top() == '(') {
            codes.push(tempCode);
        } else {
            if (!codes.empty() && comparePriority(codes.top()) >= comparePriority(tempCode)) {
                while (!codes.empty() && comparePriority(codes.top()) >= comparePriority(tempCode)) {
                    //需要计算
                    result = calculation();
                    operands.push(result);
                }
                ui->display->setText(result);
                calculated = 1;
            }
            codes.push(tempCode);
        }
    } else if (tempCode == "(") {
        codes.push(tempCode);
    } else if (tempCode == ")") {
        while (codes.top() != "(") {
            //计算 出栈
            result = calculation();
            operands.push(result);
        }
        ui->display->setText(result);
        //出栈"("
        codes.pop();
    }
    qDebug() << codes;
    qDebug() << operands;
}

//判断优先级
int ProgrammerCalculator::comparePriority(QString c)
{
    if (c == "+" || c == "-")
        return 1;
    else if (c == "×" || c == "÷")
        return 2;
    else
        return 0;
}

//计算
QString ProgrammerCalculator::calculation()
{
    double result = 0;
    QString tempCode = codes.pop();
    double operand1 = operands.pop().toDouble();
    double operand2 = operands.pop().toDouble();
    if (tempCode == "+") {
        result = operand1 + operand2;
    } else if (tempCode == "-") {
        result = operand2 - operand1;
    } else if (tempCode == "×") {
        result = operand1 * operand2;
    } else if (tempCode == "÷") {
        if (operand2 == 0) {
            operand = "";
            code = "";
            operands.clear();
            codes.clear();
            return "除数不能为零";
        } else
            result = operand1 / operand2;
    }
    return QString::number(result);
}

//键盘事件
void ProgrammerCalculator::keyPressEvent(QKeyEvent *event)
{
    QList<int> values = keyBtns.keys();
    foreach (auto key, values) {
        if (event->key() == key)
            emit keyBtns[key]->clicked();
    }
    QList<int> values1 = operatorBtns.keys();
    foreach (auto op, values1) {
        if (event->key() == op)
            emit operatorBtns[op]->clicked();
    }
}



