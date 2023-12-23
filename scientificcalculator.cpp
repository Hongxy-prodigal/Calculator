#include "scientificcalculator.h"
#include "ui_scientificcalculator.h"

#include <math.h>
#include <QtMath>
#include <QtCore/qmath.h>
#include <qdebug.h>

ScientificCalculator::ScientificCalculator(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ScientificCalculator)
{
    ui->setupUi(this);
//    operand = "0";
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
    connect(ui->btnE, SIGNAL(clicked()), this, SLOT(btnNumClicked()));
    connect(ui->btnP, SIGNAL(clicked()), this, SLOT(btnNumClicked()));
    //操作符
    connect(ui->btnPlus, SIGNAL(clicked()), this, SLOT(btnOperatorClicked()));
    connect(ui->btnSub, SIGNAL(clicked()), this, SLOT(btnOperatorClicked()));
    connect(ui->btnMul, SIGNAL(clicked()), this, SLOT(btnOperatorClicked()));
    connect(ui->btnDivide, SIGNAL(clicked()), this, SLOT(btnOperatorClicked()));
    connect(ui->btnXy, SIGNAL(clicked()), this, SLOT(btnOperatorClicked()));
    connect(ui->btnLog, SIGNAL(clicked()), this, SLOT(btnOperatorClicked()));
    connect(ui->btnMod, SIGNAL(clicked()), this, SLOT(btnOperatorClicked()));
    //单操作符
    connect(ui->btnInverse, SIGNAL(clicked()), this, SLOT(btnUniOperatorClicked()));
    connect(ui->btnSqrt, SIGNAL(clicked()), this, SLOT(btnUniOperatorClicked()));
    connect(ui->btnSquare, SIGNAL(clicked()), this, SLOT(btnUniOperatorClicked()));
    connect(ui->btnTen, SIGNAL(clicked()), this, SLOT(btnUniOperatorClicked()));
    connect(ui->btnLn, SIGNAL(clicked()), this, SLOT(btnUniOperatorClicked()));
    connect(ui->btnAbs, SIGNAL(clicked()), this, SLOT(btnUniOperatorClicked()));
    connect(ui->btnFactorial, SIGNAL(clicked()), this, SLOT(btnUniOperatorClicked()));

}

ScientificCalculator::~ScientificCalculator()
{
    delete ui;
}

void ScientificCalculator::on_btnNd_clicked()
{
    if (Change == 0) {
        ui->btnSquare->setText("x³");
        ui->btnSqrt->setText("∛");
        ui->btnXy->setText("ʸ√");
        ui->btnTen->setText("2ˣ");
        ui->btnLog->setText("logᵥx");
        ui->btnLn->setText("eˣ");
        Change = 1;
    } else {
        ui->btnSquare->setText("x²");
        ui->btnSqrt->setText("√");
        ui->btnXy->setText("xʸ");
        ui->btnTen->setText("10ˣ");
        ui->btnLog->setText("log");
        ui->btnLn->setText("ln");
        Change = 0;
    }

}


//数字键
void ScientificCalculator::btnNumClicked()
{
    if (have == 1) {
        have = 0;
        removeOperand();
        operand = "";
        ui->display->setText(operand);
    }
    QString digit = qobject_cast<QPushButton *>(sender())->text();
    if (digit == "e")
        digit = QString::number(M_E);
    if (digit == "π")
        digit = QString::number(M_PI);
    //根据点击的数字和当前操作数，判断操作数
    if (digit == "0" && operand == "0") {
        digit = "";
    }
    if (digit != "0" && operand == "0") {
        operand = "";
    }
    operand += digit;

    QString str = ui->display->text();
    if (ui->addDisplay->text().right(1) == ")") {

    }
    ui->display->setText(str + digit);
    qDebug() << (digit + " btn click");

}

//小数点
void ScientificCalculator::on_btnPeriod_clicked()
{
    //判断是否存在小数点
    if (!operand.contains('.')) {
        QString str = ui->display->text();
        //判断操作数是否存在
        if (operand == "") {
            operand = "0.";
            ui->display->setText(str + "0.");
        } else {
            operand += '.';
            ui->display->setText(str + '.');
        }
    }
}

//正负号
void ScientificCalculator::on_btnSign_clicked()
{
    if (operand != "") {
        QString str = ui->display->text();
        QString latter;
        if (!operand.contains('-')) {
            latter = '-' + operand;

        } else {
            latter = operand.right(operand.size() - 1);
        }
        str.replace(operand, latter);
        operand = latter;
        ui->display->setText(str);
    }
}

//删除键 把符号也删了
void ScientificCalculator::on_btnDel_clicked()
{
    QString str = ui->display->text();
    if (operand != "") {
        QString former = operand;
        operand = operand.left(operand.size() - 1);
        if (operand == "-")
            operand = "";
        str.replace(former, operand);
        ui->display->setText(str);
    }
}

//关于清空
void ScientificCalculator::on_display_textChanged(const QString &arg1)
{
    if (operand != "") {
        ui->btnClearAll->setText("CE");
    } else
        ui->btnClearAll->setText("C");
}

void ScientificCalculator::on_btnClearAll_clicked()
{
    //清楚所有
    if (operand == "") {
        code = "";
        operands.clear();
        codes.clear();
        ui->addDisplay->setText("");
    }
    //清楚当前操作数
    else {
        operand = "";
        ui->display->setText("");
    }
}


//操作符
void ScientificCalculator::btnOperatorClicked()
{
    code = qobject_cast<QPushButton *>(sender())->text();
    //如果没有左括号 就不加右括号
    if (code == ")" && Bracket == 0) {
        return;
    }
    if (operand == "") {        //避免多次使用操作数
        //自定义一个push 需要处理括号 需要处理入栈优先级变高的
        codes.pop();
        pushCode(code);

//        ui->display->setText(operands + codes);
        return;
    }
    pushCode(code);
//    if (codes != "") {
//        //计算
//        operands = calculation();
//        operand = "";
//        codes = code;
//        ui->display->setText(operands + codes);
//    } else {
//        //不计算
//        if (operand != "") {
//            operands = operand;
//            operand = "";
//        } else {
//            operands = "0";
//        }
//        codes = code;
//        ui->display->setText(operands + codes);
//    }
}

//void ScientificCalculator::on_btnEqual_clicked()
//{

//    if (codes != "") {      //有操作符时
//        //计算
//        if (operand == "") {                    //操作数为空让它自己乘自己
//            operands = calculation();
//            codes = "";
//            ui->display->setText(operands);
//        } else {                                //就算前面的数和操作数相乘
//            operands = calculation();
//            operand = "";
//            codes = "";
//            ui->display->setText(operands);
//        }
//    }
//}

//单操作符
void ScientificCalculator::btnUniOperatorClicked()
{
    QString op = qobject_cast<QPushButton *>(sender())->text();
    QString str = ui->addDisplay->text();
    QString temp;
    double result = ui->display->text().toDouble();
    QString resultString = ui->display->text();
    if (op == "x²") {
        temp = "sqr(" + resultString + ")";
        result = result * result;
    } else if (op == "√") {
        if (result < 0) {
            operands.clear();
            codes.clear();
            operand = "";
            code = "";
            ui->display->setText("无效输入");
            return;
        }
        temp = "√(" + resultString + ")";
        result = sqrt(result);
    } else if (op == "10ˣ") {
        temp = "10^(" + resultString + ")";
        result = qPow(10, result);
    } else if (op == "ln") {
        temp = "ln(" + resultString + ")";
        result = qLn(result);
    } else if (op == "1/x") {
        if (result == 0) {
            operands.clear();
            codes.clear();
            operand = "";
            code = "";
            ui->display->setText("除数不能为零");
            return;
        }
        temp = "1/(" + resultString + ")";
        result = 1 / result;
    } else if (op == "|x|") {
        temp = "abs(" + resultString + ")";
        result = qFabs(result);
    } else if (op == "n!") {
        temp = "fact(" + resultString + ")";
        if (result < 0) {
            operands.clear();
            codes.clear();
            operand = "";
            code = "";
            ui->display->setText("无效输入");
            return;
        } else if (result == 0 || result == 1) {
            result = 1;
        } else {
            for (int i = 2; i <= result; i++)
                result *= i;
        }
    }
    //判断当前数字是结果还是操作数
    if (operand == "" && ui->addDisplay->text().right(1) == "=") {
        ui->addDisplay->setText(temp);
    } else {
        ui->addDisplay->setText(str + temp);
    }
    operand = QString::number(result);
    ui->display->setText(operand);
    have = 1;
}

//对应去除


//键盘事件
void ScientificCalculator::keyPressEvent(QKeyEvent *event)
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

void ScientificCalculator::pushCode(const QString &code)
{
    char sign = code[0].toLatin1();
    switch (sign) {
    case '+':
    case '-':
    case '*':
    case '/': {
        if (codes.empty() || codes.top() == '(') {
            codes.push(code);
        } else {
            if (!codes.empty() && comparePriority(codes.top()) >= comparePriority(code)) {
                //需要计算
                calculation();
            } else
                codes.push(code);
        }
        break;
    }
    case '(': {
        codes.push(code);
        break;
    }
    case ')': {
        while (codes.top() != "(") {
            //计算 出栈
            calculation();
        }
        //出栈"("
        codes.pop();
        break;
    }
    default:
        break;
    }
}

int ScientificCalculator::comparePriority(QString c)
{
    if (c == "+" || c == "-")
        return 1;
    else if (c == "*" || c == "/" || c == "mod")
        return 2;
    else
        return 0;
}

void ScientificCalculator::removeOperand()
{
    QStringList operators = {"+", "-", "*", "/", "mod"}; // 所有可能的运算符
    int index = -1;
    QString str = ui->addDisplay->text();
    for (const QString &op : operators) {
        int temp = str.lastIndexOf(op);
        index = index >  temp ? index : temp;
    }
    str = str.left(index + 1);
    ui->addDisplay->setText(str);
}

QString ScientificCalculator::calculation()
{
    double result;
    QString tempCode = codes.pop();
    QString tempOperand = operands.pop();
    if (tempCode == "+") {
        if (operand == "")
            result = tempOperand.toDouble() * 2;
        else
            result = tempOperand.toDouble() + operand.toDouble();
    } else if (tempCode == "-") {
        if (operand == "")
            result = 0;
        else
            result = tempOperand.toDouble() - operand.toDouble();
    } else if (tempCode == "×") {
        if (operand == "")
            result = tempOperand.toDouble() * tempOperand.toDouble();
        else
            result = tempOperand.toDouble() * operand.toDouble();
    } else {
        if (operand == "")
            result = 1;
        else if (operand == "0") {
            operand = "";
            code = "";
            return "除数不能为零";
        }
        result = tempOperand.toDouble() / operand.toDouble();
    }
    return QString::number(result);
}
