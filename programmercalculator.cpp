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
    connect(ui->btnMod, SIGNAL(clicked()), this, SLOT(btnOperatorClicked()));
    connect(ui->btnAND, SIGNAL(clicked()), this, SLOT(btnOperatorClicked()));
    connect(ui->btnOR, SIGNAL(clicked()), this, SLOT(btnOperatorClicked()));
    connect(ui->btnNOT, SIGNAL(clicked()), this, SLOT(btnOperatorClicked()));
    connect(ui->btnNAND, SIGNAL(clicked()), this, SLOT(btnOperatorClicked()));
    connect(ui->btnNOR, SIGNAL(clicked()), this, SLOT(btnOperatorClicked()));
    connect(ui->btnXOR, SIGNAL(clicked()), this, SLOT(btnOperatorClicked()));
    connect(ui->btnLeftShift, SIGNAL(clicked()), this, SLOT(btnOperatorClicked()));
    connect(ui->btnRightShift, SIGNAL(clicked()), this, SLOT(btnOperatorClicked()));

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
    int tempBase = Base;
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
    ui->display->setText(QString::number(ui->display->text().toInt(nullptr, tempBase), Base));
    operand = QString::number(operand.toInt(nullptr, tempBase), Base);
    ui->addDisplay->setText(replaceNumbersWithBase(ui->addDisplay->text(), tempBase, Base));
}

//在所有进制中都要显示
void ProgrammerCalculator::setAllDisplay(const QString &str)
{
    ui->display->setText(str);
    int dec = str.toInt(nullptr, Base);
    ui->lineEditBIN->setText(QString::number(dec, 2));
    ui->lineEditOCT->setText(QString::number(dec, 8));
    ui->lineEditDEC->setText(QString::number(dec, 10));
    ui->lineEditHEX->setText(QString::number(dec, 16).toUpper());
}

void ProgrammerCalculator::clearAllDisplay()
{
    ui->display->setText("");
    ui->lineEditBIN->setText("");
    ui->lineEditOCT->setText("");
    ui->lineEditDEC->setText("");
    ui->lineEditHEX->setText("");
}

QString ProgrammerCalculator::replaceNumbersWithBase(const QString &input, int fromBase, int ToBase)
{
    QString result = input;
    int pos = 0;
    QString regexPattern = "\\b[0-9A-Fa-f]+\\b"; // 匹配十进制、十六进制数

    while ((pos = result.indexOf(QRegExp(regexPattern), pos)) != -1) {
        bool ok;
        QString numberString = result.mid(pos, result.indexOf(QRegExp("[^0-9A-Fa-f]"),
                                                              pos) - pos); // 提取数字字符串
        int decimalValue = numberString.toInt(&ok, fromBase); // 将字符串转换为整数

        if (ok) {
            QString convertedString = QString::number(decimalValue,
                                                      ToBase).toUpper(); // 将整数转换为指定进制的字符串
            result.replace(pos, numberString.length(), convertedString); // 替换原字符串中的数字
            pos += convertedString.length(); // 更新位置
        } else {
            pos += numberString.length(); // 若无法转换，则移动到下一个位置
        }
    }
    qDebug() << result;
    return result;
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

//按位按键
void ProgrammerCalculator::on_btnBitwise_clicked()
{
    ui->groupBoxBitwise->setVisible(!ui->groupBoxBitwise->isVisible());
    ui->groupBoxShift->setVisible(false);
}

//位移位按键
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
    setAllDisplay(operand);
}

//删除键 把符号也删了
void ProgrammerCalculator::on_btnDel_clicked()
{
    if (operand != "" && calculated == 0) {
        operand = operand.left(operand.size() - 1);
        if (operand == "-")
            operand = "";
        setAllDisplay(operand);
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
        ui->addDisplay->setText("");
    }
    //清楚当前操作数
    else {
        operand = "";
        ui->display->setText("");
        clearAllDisplay();
    }
}

//正负号
void ProgrammerCalculator::on_btnSign_clicked()
{

    if (Base == 10) {
        if (operand != "") {
            if (!operand.contains('-')) {
                operand = '-' + operand;
            } else {
                operand = operand.right(operand.size() - 1);
            }
            setAllDisplay(operand);

        }
    }
    //如果是除十进制以外的，则要用negate()
    else {
//        QString str = ui->addDisplay->text();
//        int index = getLastOperator(str);
//        QString resultString = str.right(str.size() - index - 1);
//        str = str.left(index + 1);
//        resultString = "negate(" + resultString + ")";

//        if (operand == "" && ui->addDisplay->text().right(1) == "=") {
//            ui->addDisplay->setText(resultString);
//        } else {
//            ui->addDisplay->setText(str + resultString);
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
        operands.push(QString::number(operand.toInt(nullptr, Base)));

        while (!codes.isEmpty()) {     //有操作符时
            result = calculation();
            operands.push(result);
        }

        //划等号
        ui->addDisplay->setText(ui->addDisplay->text() + operand + "=");
        setAllDisplay(result);
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
        setAllDisplay("");
    }
    if (tempCode == "<<")
        tempCode = "Lsh";
    else if (tempCode == ">>")
        tempCode = "Rsh";
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
        operands.push(QString::number(operand.toInt(nullptr, Base)));
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
    if (tempCode == "×" || tempCode == "÷" || tempCode == "+" || tempCode == "-" || tempCode == "%"
            || tempCode == "Lsh" || tempCode == "Rsh" || tempCode == "AND" || tempCode == "OR"
            || tempCode == "NAND" || tempCode == "NOR" || tempCode == "XOR") {
        if (codes.empty() || codes.top() == '(') {
            codes.push(tempCode);
        } else {
            if (!codes.empty() && comparePriority(codes.top()) >= comparePriority(tempCode)) {
                while (!codes.empty() && comparePriority(codes.top()) >= comparePriority(tempCode)) {
                    //需要计算
                    result = calculation();
                    operands.push(result);
                }
                setAllDisplay(result);
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
        setAllDisplay(result);
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
    else if (c == "×" || c == "÷" || c == "%" || c == "Lsh" || c == "Rsh")
        return 2;
    else
        return 0;
}

//计算
QString ProgrammerCalculator::calculation()
{
    int result = 0;
    QString tempCode = codes.pop();
    int operand1 = operands.pop().toInt();
    int operand2 = operands.pop().toInt();
    if (tempCode == "+") {
        result = operand1 + operand2;
    } else if (tempCode == "-") {
        result = operand2 - operand1;
    } else if (tempCode == "×") {
        result = operand1 * operand2;
    } else if (tempCode == "%") {
        result = operand2 % operand1;
    } else if (tempCode == "AND") {
        result = operand2 & operand1;
    }  else if (tempCode == "OR") {
        result = operand2 | operand1;
    } else if (tempCode == "NAND") {
        result = ~(operand2 & operand1);
    } else if (tempCode == "NOR") {
        result = ~(operand2 | operand1);
    } else if (tempCode == "XOR") {
        result = operand2 ^ operand1;
    } else if (tempCode == "Lsh") {
        result = operand2 << operand1;
    }  else if (tempCode == "Rsh") {
        result = operand2 >> operand1;
    } else if (tempCode == "÷") {
        if (operand2 == 0) {
            operand = "";
            code = "";
            operands.clear();
            codes.clear();
            return "除数不能为零";
        } else
            result = operand2 / operand1;
    }
    return QString::number(result);
}
//// 算术左移
//unsigned int arithmeticLeftShift(unsigned int value, unsigned int shift)
//{
//    return value << shift;
//}

//// 逻辑左移
//unsigned int logicalLeftShift(unsigned int value, unsigned int shift)
//{
//    return value << shift;
//}

//// 循环左移
//unsigned int rotateLeft(unsigned int value, unsigned int shift)
//{
//    return (value << shift) | (value >> (sizeof(value) * CHAR_BIT - shift));
//}

//// 带进位循环左移
//unsigned int rotateLeftWithCarry(unsigned int value, unsigned int shift)
//{
//    const unsigned int mask = (1u << (sizeof(value) * CHAR_BIT - 1));
//    return ((value << shift) | (value >> (sizeof(value) * CHAR_BIT - shift))) & (~mask | ((value >>
//                                                                                           (sizeof(value) * CHAR_BIT - shift)) << 1));
//}

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



