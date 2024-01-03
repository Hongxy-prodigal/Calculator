#include "scientificcalculator.h"
#include "ui_scientificcalculator.h"

#include <math.h>
#include <QtMath>
#include <QtCore/qmath.h>
#include <qdebug.h>
#include <QPushButton>

ScientificCalculator::ScientificCalculator(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ScientificCalculator)
{
    ui->setupUi(this);
//    operand = "0";
    ui->triangleGroupBox->setVisible(false);
    ui->functionGroupBox->setVisible(false);
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
    connect(ui->btnLog, SIGNAL(clicked()), this, SLOT(btnOperatorClicked()));

    //单操作符
    connect(ui->btnInverse, SIGNAL(clicked()), this, SLOT(btnUniOperatorClicked()));
    connect(ui->btnSqrt, SIGNAL(clicked()), this, SLOT(btnUniOperatorClicked()));
    connect(ui->btnSquare, SIGNAL(clicked()), this, SLOT(btnUniOperatorClicked()));
    connect(ui->btnTen, SIGNAL(clicked()), this, SLOT(btnUniOperatorClicked()));
    connect(ui->btnLn, SIGNAL(clicked()), this, SLOT(btnUniOperatorClicked()));
    connect(ui->btnAbs, SIGNAL(clicked()), this, SLOT(btnUniOperatorClicked()));
    connect(ui->btnFactorial, SIGNAL(clicked()), this, SLOT(btnUniOperatorClicked()));
    connect(ui->btnLog, SIGNAL(clicked()), this, SLOT(btnUniOperatorClicked()));
    //三角函数
    connect(ui->btnSin, SIGNAL(clicked()), this, SLOT(btnUniOperatorClicked()));
    connect(ui->btnCos, SIGNAL(clicked()), this, SLOT(btnUniOperatorClicked()));
    connect(ui->btnTan, SIGNAL(clicked()), this, SLOT(btnUniOperatorClicked()));
    connect(ui->btnSec, SIGNAL(clicked()), this, SLOT(btnUniOperatorClicked()));
    connect(ui->btnCsc, SIGNAL(clicked()), this, SLOT(btnUniOperatorClicked()));
    connect(ui->btnCot, SIGNAL(clicked()), this, SLOT(btnUniOperatorClicked()));
    //函数
    connect(ui->btnAbs_2, SIGNAL(clicked()), this, SLOT(btnUniOperatorClicked()));
    connect(ui->btnFloor, SIGNAL(clicked()), this, SLOT(btnUniOperatorClicked()));
    connect(ui->btnCeil, SIGNAL(clicked()), this, SLOT(btnUniOperatorClicked()));
    connect(ui->btnDeg, SIGNAL(clicked()), this, SLOT(btnUniOperatorClicked()));
    connect(ui->btnDms, SIGNAL(clicked()), this, SLOT(btnUniOperatorClicked()));
}

ScientificCalculator::~ScientificCalculator()
{
    delete ui;
}

//获取最后一次出现的操作符
int getLastOperator(const QString &str)
{
    QStringList operators = {"+", "-", "×", "÷", "mod", "^", "yroot", "log base"}; // 所有可能的运算符
    int index = -1;
    for (const QString &op : operators) {
        int temp = str.lastIndexOf(op);
        index = index >  temp ? index : temp;
    }
    return index;
}

int removeRightBracket(const QString &str)
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

//三角函数隐藏与显示
void ScientificCalculator::on_btnTriangle_clicked()
{
    ui->triangleGroupBox->setVisible(!ui->triangleGroupBox->isVisible());
    ui->functionGroupBox->setVisible(false);
}
//函数隐藏与显示
void ScientificCalculator::on_btnFuction_clicked()
{
    ui->triangleGroupBox->setVisible(false);
    ui->functionGroupBox->setVisible(!ui->functionGroupBox->isVisible());
}

void ScientificCalculator::on_btnNd_clicked()
{
    if (nd == 0) {
        ui->btnSquare->setText("x³");
        ui->btnSqrt->setText("∛");
        ui->btnXy->setText("ʸ√");
        ui->btnTen->setText("2ˣ");
        ui->btnLog->setText("logᵥx");
        ui->btnLn->setText("eˣ");
        ui->btnNd->setStyleSheet("QPushButton:hover { " "background-color: rgb(25, 106, 167);"
                                 "font: 16pt Arial;" "} " "QPushButton { " "background-color: rgb(0, 90, 158); "
                                 "color: rgb(255, 255, 255); " "font: 12pt Arial;" "}");
        nd = 1;
    } else {
        ui->btnSquare->setText("x²");
        ui->btnSqrt->setText("√");
        ui->btnXy->setText("xʸ");
        ui->btnTen->setText("10ˣ");
        ui->btnLog->setText("log");
        ui->btnLn->setText("ln");
        ui->btnNd->setStyleSheet("QPushButton:hover {" "background-color: rgb(246, 246, 246);"
                                 "font: 16pt Arial;" "}" "QPushButton {" "background-color: rgb(249, 249, 249);" "font: 12pt Arial;"
                                 "}");
        nd = 0;
    }
}
//三角nd
void ScientificCalculator::on_btnTriangleNd_clicked()
{
    if (ndTriangle == 0) {
        for (auto &button : ui->triangleGroupBox->findChildren<QPushButton *>())
            if (button->text() != "2nd" && button->text() != "hyp")
                button->setText(button->text() + "⁻¹");
        ui->btnTriangleNd->setStyleSheet("QPushButton:hover { " "background-color: rgb(24, 105, 166);"
                                         "} " "QPushButton { " "background-color: rgb(0, 90, 158); "
                                         "color: rgb(255, 255, 255); " "font: 13pt Arial;" "}");
        ndTriangle = 1;
    } else {
        for (auto &button : ui->triangleGroupBox->findChildren<QPushButton *>())
            if (button->text() != "2nd" && button->text() != "hyp")
                button->setText(button->text().remove("⁻¹"));
        ui->btnTriangleNd->setStyleSheet("QPushButton:hover {" "background-color: rgb(241, 241, 241);"
                                         "}" "QPushButton {" "background-color: rgb(248, 248, 248);" "font: 13pt Arial;"
                                         "}");
        ndTriangle = 0;
    }
}

//hyp
void ScientificCalculator::on_btnHyp_clicked()
{
    if (hyp == 0) {
        for (auto &button : ui->triangleGroupBox->findChildren<QPushButton *>())
            if (button->text() != "2nd" && button->text() != "hyp")
                button->setText(button->text().insert(3, 'h'));
        ui->btnHyp->setStyleSheet("QPushButton:hover { " "background-color: rgb(24, 105, 166);"
                                  "} " "QPushButton { " "background-color: rgb(0, 90, 158); "
                                  "color: rgb(255, 255, 255); " "font: 13pt Arial;" "}");
        hyp = 1;
    } else {
        for (auto &button : ui->triangleGroupBox->findChildren<QPushButton *>())
            if (button->text() != "2nd" && button->text() != "hyp")
                button->setText(button->text().remove("h"));
        ui->btnHyp->setStyleSheet("QPushButton:hover {" "background-color: rgb(241, 241, 241);"
                                  "}" "QPushButton {" "background-color: rgb(248, 248, 248);" "font: 13pt Arial;"
                                  "}");
        hyp = 0;
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
    //右括号加数字
    if (ui->addDisplay->text().right(1) == ")") {
        operand = "";
        ui->display->setText(operand);

        QString str = ui->addDisplay->text();
        int index = removeRightBracket(str);
        str = str.left(index);
        ui->addDisplay->setText(str);
        qDebug() << operands.pop();
    }
    QString digit = qobject_cast<QPushButton *>(sender())->text();
    if (digit == "e") {
        ePi = 1;
        operand = QString::number(M_E);
        digit = QString::number(M_E);
        ui->display->setText(digit);
    } else if (digit == "π") {
        ePi = 1;
        operand = QString::number(M_PI);
        digit = QString::number(M_PI);
        ui->display->setText(digit);
    }
    //根据点击的数字和当前操作数，判断操作数
    //根据exp操作
    else {
        if (ePi == 1) {
            ui->display->setText("");
            operand = "";
        }
        if (digit == "0" && operand == "0") {
            digit = "";
        }
        if (digit != "0" && operand == "0") {
            operand = "";
        }
        int index = operand.lastIndexOf('e');
        //判断是否有exp操作并且为0
        if (operand.contains('e') && operand.right(operand.size() - index - 2) == "0")
            operand = operand.left(index + 2) + digit;
        else
            operand += digit;
        ui->display->setText(operand);
    }
}

//小数点
void ScientificCalculator::on_btnPeriod_clicked()
{
    //exp不能有小数点. 判断是否存在小数点
    if (!operand.contains('.') && !operand.contains('e') && uniOperator == 0) {
        QString str = ui->display->text();
        //判断操作数是否存在
        if (operand == "") {
            operand = "0.";
            ui->display->setText("0.");
        } else {
            operand += '.';
            ui->display->setText(str + '.');
        }
        code = "";
    }

}

//正负号
void ScientificCalculator::on_btnSign_clicked()
{
    if (!operand.contains('e') && calculated == 0) {
        if (operand != "") {
            if (!operand.contains('-')) {
                operand = '-' + operand;
            } else {
                operand = operand.right(operand.size() - 1);
            }
            ui->display->setText(operand);
            //如果是对以及被单操作符操作过的操作数，则要用negate()
            if (uniOperator == 1) {
                QString str = ui->addDisplay->text();
                int index = getLastOperator(str);
                QString resultString = str.right(str.size() - index - 1);
                str = str.left(index + 1);
                resultString = "negate(" + resultString + ")";

                if (operand == "" && ui->addDisplay->text().right(1) == "=") {
                    ui->addDisplay->setText(resultString);
                } else {
                    ui->addDisplay->setText(str + resultString);
                }
            }
        }
    } else {
        if (operand.contains("e-"))
            operand.replace("e-", "e+");
        else
            operand.replace("e+", "e-");
        ui->display->setText(operand);
    }
}


//删除键 把符号也删了
void ScientificCalculator::on_btnDel_clicked()
{
    //单操作符操作后的数，不能删除
    if (uniOperator != 1) {
        if (!operand.contains('e')) {
            if (operand != "") {
                operand = operand.left(operand.size() - 1);
                if (operand == "-")
                    operand = "";
                ui->display->setText(operand);
            }
        } else {
            int index = operand.lastIndexOf('e');
            QString exp = operand.right(operand.size() - index - 2);
            if (exp == "0")
                operand = operand.left(index);
            else {
                operand = operand.left(operand.size() - 1);
                exp = operand.right(operand.size() - index - 1);
                if (exp == "-" || exp == "+")
                    operand = operand.left(index + 1) + "+0";
            }
            ui->display->setText(operand);
        }
    }
}

//关于清空
void ScientificCalculator::on_display_textChanged()
{
    if (ui->display->text() != "") {
        ui->btnClearAll->setText("CE");
    } else
        ui->btnClearAll->setText("C");
}

void ScientificCalculator::on_btnClearAll_clicked()
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


//操作符
void ScientificCalculator::btnOperatorClicked()
{
    QString tempCode = qobject_cast<QPushButton *>(sender())->text();
    //这是单操作符
    if (tempCode == "log")
        return;
    if (equal == 1) {
        equal = 0;
        ui->addDisplay->setText("");
    }
    if (tempCode == "xʸ")
        tempCode = "^";
    else if (tempCode == "ʸ√")
        tempCode = "yroot";
    else if (tempCode == "logᵥx")
        tempCode = "log base";
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
        //当操作数为空时，置0
        if (operand == "")
            operand = "0";
        //当exp操作时，需要先计算
        if (operand.contains('e')) {
            operand = QString::number(operand.toDouble());
            ui->display->setText(operand);
        }
        operands.push(operand);
        pushCode(tempCode);
        if (uniOperator == 1)
            ui->addDisplay->setText(ui->addDisplay->text() + tempCode);
        else
            ui->addDisplay->setText(ui->addDisplay->text() + operand + tempCode);
        code = tempCode;
    }
    operand = "";
}

//操作符入栈
void ScientificCalculator::pushCode(const QString &tempCode)
{
    qDebug() << codes;
    qDebug() << operands;
    QString result;
    if (tempCode == "×" || tempCode == "÷" || tempCode == "+" || tempCode == "-"
            || tempCode == "mod" || tempCode == "^" || tempCode == "yroot" || tempCode == "log base") {
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
int ScientificCalculator::comparePriority(QString c)
{
    if (c == "+" || c == "-" || c == "yroot" || c == "log base")
        return 1;
    else if (c == "×" || c == "÷" || c == "mod" || c == "^")
        return 2;
    else
        return 0;
}

//等于号
void ScientificCalculator::on_btnEqual_clicked()
{
    if (equal != 1) {
        QString result = "";
        //如果操作符不为空且操作数为空,认定display的数字为操作数
        if (code != "" && operand == "")
            operand = ui->display->text();
        if (operand != "") {
            //如果有exp运算，要先运算
            if (operand.contains('e'))
                operand = QString::number(operand.toDouble());
        } else
            operand = "0";
        operands.push(operand);


        while (!codes.isEmpty()) {     //有操作符时
            result = calculation();
            operands.push(result);
        }
        //划等号
        //如果是单操作符运算了，不需要加操作数
        if (uniOperator == 1)
            ui->addDisplay->setText(ui->addDisplay->text() + "=");
        else
            ui->addDisplay->setText(ui->addDisplay->text() + operand + "=");
        ui->display->setText(result);
        operands.clear();
        codes.clear();
        code = "";
        operand = result;
        equal = 1;
    }
}

//单操作符
//单操作数叠加问题
void ScientificCalculator::btnUniOperatorClicked()
{
    QString op = qobject_cast<QPushButton *>(sender())->text();
    //这是双操作符
    if (op == "logᵥx")
        return;
    if (equal == 1) {
        equal = 0;
        ui->addDisplay->setText("");
    }
    QString str = ui->addDisplay->text();
    QString temp;
    double result = ui->display->text().toDouble();
    QString resultString;
    //单操作符叠加处理
    if (uniOperator == 1) {
        int index = getLastOperator(str);
        resultString = str.right(str.size() - index - 1);
        str = str.left(index + 1);
    } else
        resultString = QString::number(result);
    if (resultString == "") {
        resultString = "0";
        result = 0;
    }
    standardCalculate(result, op, temp, resultString);
    triangleCalculate(result, op, temp, resultString);
    functionCalculate(result, op, temp, resultString);
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
    QString str = ui->addDisplay->text();
    int index = getLastOperator(str);
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
    } else if (tempCode == "mod") {
        double quotient = std::floor(operand2 / operand1);
        result = operand2 - (operand1 * quotient);
    } else if (tempCode == "^") {
        result = qPow(operand2, operand1);
    }  else if (tempCode == "yroot") {
        result = qPow(operand2, 1.0 / operand1);
    } else if (tempCode == "log base") {
        result = qLn(operand2) / qLn(operand1);
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

//左括号
void ScientificCalculator::on_btnLeftBracket_clicked()
{
    if (code == "") {        //数字跟括号 直接相乘
        ui->btnMul->click();
    }
    ui->addDisplay->setText(ui->addDisplay->text() + "(");
    pushCode("(");
    ui->display->setText("0");
    operand = "0";
    Bracket++;
}

//右括号
void ScientificCalculator::on_btnRightBracket_clicked()
{
    //如果没有左括号 就不加右括号
    if (Bracket == 0) {
        return;
    } else {
        //操作符后面接括号，将显示的当作操作数
        if (code != "") {
            qDebug() << "code is not null";
            operand = ui->display->text();
            operands.push(operand);
            pushCode(")");
            ui->addDisplay->setText(ui->addDisplay->text() + operand + ")");
        } else {
            qDebug() << "code is null";
            operands.push(operand);
            pushCode(")");
            ui->addDisplay->setText(ui->addDisplay->text() + operand + ")");
        }
        Bracket--;
        operand = "";
    }
}


void ScientificCalculator::on_btnExp_clicked()
{
    if (uniOperator != 1 && code == "" && !operand.contains('e')) {
        if (operand == "")
            operand = "0";
        if (operand.contains('.'))
            operand = operand + "e+0";
        else
            operand = operand + ".e+0";
        ui->display->setText(operand);
    }
}

void ScientificCalculator::on_btnRand_clicked()
{
    srand(time(nullptr));
    // 生成随机数
    double randomNumber = static_cast<double>(rand()) / RAND_MAX;
    operand  = QString::number(randomNumber);
    ui->display->setText(operand);
}

void ScientificCalculator::triangleCalculate(double &result, QString &op, QString &temp,
                                             QString &resultString)
{
    //正常的三角函数
    if (op == "sin") {
        temp = "sin(" + resultString + ")";
        result = sin(result);
    }  else if (op == "cos") {
        temp = "cos(" + resultString + ")";
        result = cos(result);
    } else if (op == "tan") {
        temp = "tan(" + resultString + ")";
        result = tan(result);
    } else if (op == "sec") {
        temp = "sec(" + resultString + ")";
        result = 1 / cos(result);
    } else if (op == "csc") {
        temp = "csc(" + resultString + ")";
        result = 1 / sin(result);
    } else if (op == "cot") {
        temp = "cot(" + resultString + ")";
        result = 1 / tan(result);
    }

    //双曲三角函数
    else if (op == "sinh") {
        temp = "sinh(" + resultString + ")";
        result = sinh(result);
    }  else if (op == "cosh") {
        temp = "cosh(" + resultString + ")";
        result = cosh(result);
    } else if (op == "tanh") {
        temp = "tanh(" + resultString + ")";
        result = tanh(result);
    } else if (op == "sech") {
        temp = "sech(" + resultString + ")";
        result = 1 / cosh(result);
    } else if (op == "csch") {
        temp = "csch(" + resultString + ")";
        result = 1 / sinh(result);
    } else if (op == "coth") {
        temp = "coth(" + resultString + ")";
        result = 1 / tanh(result);
    }

    //反函数
    else if (op == "sin⁻¹") {
        temp = "sin⁻¹(" + resultString + ")";
        result = asin(result);
    }  else if (op == "cos⁻¹") {
        temp = "cos⁻¹(" + resultString + ")";
        result = acos(result);
    } else if (op == "tan⁻¹") {
        temp = "tan⁻¹(" + resultString + ")";
        result = atan(result);
    } else if (op == "sec⁻¹") {
        temp = "sec⁻¹(" + resultString + ")";
        result = acos(1 / result);
    } else if (op == "csc⁻¹") {
        temp = "csc⁻¹(" + resultString + ")";
        result = asin(1 / result);
    } else if (op == "cot⁻¹") {
        temp = "cot⁻¹(" + resultString + ")";
        result = atan(1 / result);
    }

    //反双曲函数
    else if (op == "sinh⁻¹") {
        temp = "sinh⁻¹(" + resultString + ")";
        result = asinh(result);
    }  else if (op == "cosh⁻¹") {
        temp = "cosh⁻¹(" + resultString + ")";
        result = acosh(result);
    } else if (op == "tanh⁻¹") {
        temp = "tanh⁻¹(" + resultString + ")";
        result = atanh(result);
    } else if (op == "sech⁻¹") {
        temp = "sech⁻¹(" + resultString + ")";
        result = acosh(1 / result);
    } else if (op == "csch⁻¹") {
        temp = "csch⁻¹(" + resultString + ")";
        result = asinh(1 / result);
    } else if (op == "coth⁻¹") {
        temp = "coth⁻¹(" + resultString + ")";
        result = atanh(1 / result);
    }
    //用完就关闭
    ui->triangleGroupBox->setVisible(false);
}

void ScientificCalculator::functionCalculate(double &result, QString &op, QString &temp,
                                             QString &resultString)
{
    if (op == "⌊x⌋") {
        temp = "floor(" + resultString + ")";
        result = floor(result);
    }  else if (op == "⌈x⌉") {
        temp = "ceil(" + resultString + ")";
        result = ceil(result);
    } else if (op == "→dms") {
        temp = "dms(" + resultString + ")";
        result = result * (M_PI / 180.0);  ;
    } else if (op == "→deg") {
        temp = "deg(" + resultString + ")";
        result = result * (180.0 / M_PI);
    }
    //用完就关闭
    ui->functionGroupBox->setVisible(false);
}

void ScientificCalculator::standardCalculate(double &result, QString &op, QString &temp,
                                             QString &resultString)
{
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
    } else if (op == "log") {
        temp = "log(" + resultString + ")";
        result = qLn(result) / qLn(10);
    } else if (op == "x³") {
        temp = "cube(" + resultString + ")";
        result = result * result * result;
    } else if (op == "∛") {
        temp = "cuberoot(" + resultString + ")";
        result = qPow(result, 1 / 3);
    } else if (op == "2ˣ") {
        temp = "2^(" + resultString + ")";
        result = qPow(2, result);
    } else if (op == "eˣ") {
        temp = "e^(" + resultString + ")";
        result = qPow(M_E, result);
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
}

