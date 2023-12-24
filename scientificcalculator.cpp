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
    connect(ui->btnMod, SIGNAL(clicked()), this, SLOT(btnOperatorClicked()));
    connect(ui->btnXy, SIGNAL(clicked()), this, SLOT(btnOperatorClicked()));

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
    //单操作符操作了
    if (uniOperator == 1) {
        uniOperator = 0;
        removeOperand();
        operand = "";
        ui->display->setText(operand);
    }
    if (ui->addDisplay->text().right(1) == ")") {
        removeOperand();
        operand = "";
        ui->display->setText(operand);
    }
    QString digit = qobject_cast<QPushButton *>(sender())->text();
    if (digit == "e") {
        operand = QString::number(M_E);
    } else if (digit == "π")
        operand = QString::number(M_PI);
    //根据点击的数字和当前操作数，判断操作数
    else {
        if (digit == "0" && operand == "0") {
            digit = "";
        }
        if (digit != "0" && operand == "0") {
            operand = "";
        }
        operand += digit;
    }
    QString str = ui->display->text();
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
        ui->display->setText("");
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
    if (equal == 1) {
        equal = 0;
        ui->addDisplay->setText("");
    }
    QString tempCode = qobject_cast<QPushButton *>(sender())->text();
    if (tempCode == "xʸ")
        tempCode = "^";
    else if (tempCode == "ʸ√")
        tempCode = "yroot";
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
        operands.push(operand);
        pushCode(tempCode);
        if (uniOperator == 1)
            ui->addDisplay->setText(ui->addDisplay->text() + tempCode);
        else
            ui->addDisplay->setText(ui->addDisplay->text() + operand + tempCode);
        code = tempCode;
    }

}

void ScientificCalculator::pushCode(const QString &tempCode)
{
    QString result;
    if (tempCode == "×" || tempCode == "÷" || tempCode == "+" || tempCode == "-"
            || tempCode == "mod" || tempCode == "^" || tempCode == "yroot") {
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
}

int ScientificCalculator::comparePriority(QString c)
{
    if (c == "+" || c == "-" || c == "yroot")
        return 1;
    else if (c == "×" || c == "÷" || c == "mod" || c == "^")
        return 2;
    else
        return 0;
}

void ScientificCalculator::on_btnEqual_clicked()
{
    if (equal == 1)
        return;
    QString result = "";
    //如果为空,就将display给operand
    if (operand == "")
        operand = ui->display->text();
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

//单操作符
//单操作数叠加问题
void ScientificCalculator::btnUniOperatorClicked()
{
    if (equal == 1) {
        equal = 0;
        ui->addDisplay->setText("");
    }
    QString op = qobject_cast<QPushButton *>(sender())->text();
    QString str = ui->addDisplay->text();
    QString temp;
    double result = ui->display->text().toDouble();
    QString resultString = ui->display->text();
    if (resultString == "") {
        resultString = "0";
        result = 0;
    }
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
    uniOperator = 1;
}

//对应去除
void ScientificCalculator::removeOperand()
{
    QStringList operators = {"+", "-", "×", "÷", "mod"}; // 所有可能的运算符
    int index = -1;
    QString str = ui->addDisplay->text();
    for (const QString &op : operators) {
        int temp = str.lastIndexOf(op);
        index = index >  temp ? index : temp;
    }
    str = str.left(index + 1);
    ui->addDisplay->setText(str);
}

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

QString ScientificCalculator::calculation()
{
    double result;
    QString tempCode = codes.pop();
    double operand1 = operands.pop().toDouble();
    double operand2 = operands.pop().toDouble();
    if (tempCode == "+") {
        result = operand1 + operand2;
    } else if (tempCode == "-") {
        result = operand1 - operand2;
    } else if (tempCode == "×") {
        result = operand1 * operand2;
    } else if (tempCode == "mod") {
        double quotient = std::floor(operand1 / operand2);
        result = operand1 - (operand2 * quotient);
    } else if (tempCode == "^") {
        result = qPow(operand2, operand1);
    }  else if (tempCode == "yroot") {
        result = qPow(operand2, 1.0 / operand1);
    }  else if (tempCode == "÷") {
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

//左括号
void ScientificCalculator::on_btnLeftBracket_clicked()
{
    if (code == "") {        //数字跟括号 直接相乘
        ui->btnMul->click();
    }
    ui->addDisplay->setText(ui->addDisplay->text() + "(");
    ui->display->setText("0");
    pushCode("(");
    Bracket++;
}

//右括号
void ScientificCalculator::on_btnRightBracket_clicked()
{
    //如果没有左括号 就不加右括号
    if (Bracket == 0) {
        return;
    } else {
        if (code != "") {
            operand = ui->display->text();
            operands.push(operand);
            pushCode(")");
            ui->addDisplay->setText(ui->addDisplay->text() + operand + ")");
        } else {
            operands.push(operand);
            pushCode(")");
            ui->addDisplay->setText(ui->addDisplay->text() + operand + ")");
        }
        Bracket--;
    }
}


void ScientificCalculator::on_btnLog_clicked()
{
    if (Change == 1) {

    }
}

