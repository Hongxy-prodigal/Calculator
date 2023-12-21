#include "scientificcalculator.h"
#include "ui_scientificcalculator.h"

#include <math.h>
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
    QList<QPushButton *> values = keyBtns.values();
    foreach (auto btn, values) {
        connect(btn, SIGNAL(clicked()), this, SLOT(btnNumClicked()));
    }

//    connect(ui->btnPlus, SIGNAL(clicked()), this, SLOT(btnOperatorClicked()));
//    connect(ui->btnSub, SIGNAL(clicked()), this, SLOT(btnOperatorClicked()));
//    connect(ui->btnMul, SIGNAL(clicked()), this, SLOT(btnOperatorClicked()));
//    connect(ui->btnDivide, SIGNAL(clicked()), this, SLOT(btnOperatorClicked()));

//    connect(ui->btnInverse, SIGNAL(clicked()), this, SLOT(btnUniOperatorClicked()));
//    connect(ui->btnSqrt, SIGNAL(clicked()), this, SLOT(btnUniOperatorClicked()));
//    connect(ui->btnSquare, SIGNAL(clicked()), this, SLOT(btnUniOperatorClicked()));

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



//QString ScientificCalculator::calculation()
//{
//    double result;
//    if (codes == "+") {
//        if (operand == "")
//            result = operands.toDouble() * 2;
//        else
//            result = operands.toDouble() + operand.toDouble();
//    } else if (codes == "-") {
//        if (operand == "")
//            result = 0;
//        else
//            result = operands.toDouble() - operand.toDouble();
//    } else if (codes == "×") {
//        if (operand == "")
//            result = operands.toDouble() * operands.toDouble();
//        else
//            result = operands.toDouble() * operand.toDouble();
//    } else {
//        if (operand == "")
//            result = 1;
//        else if (operand == "0") {
//            operand = "";
//            code = "";
//            codes = "";
//            return "除数不能为零";
//        }
//        result = operands.toDouble() / operand.toDouble();
//    }
//    return QString::number(result);
//}

//数字键
void ScientificCalculator::btnNumClicked()
{
    QString digit = qobject_cast<QPushButton *>(sender())->text();
    //根据点击的数字和当前操作数，判断操作数
    if (digit == "0" && operand == "0") {
        digit = "";
    }
    if (digit != "0" && operand == "0") {
        operand = "";
    }
    operand += digit;

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
        QString result;
        if (!operand.contains('-')) {
            result = '-' + operand;

        } else {
            result = operand.right(operand.size() - 1);
        }
        str.replace(operand, result);
        operand = result;
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

//这是清楚所有
void ScientificCalculator::on_btnClearAll_clicked()
{
    //判断操作数来进行分辨时C CE
    if (operand == "") {
        code = "";
        operands.clear();
        codes.clear();
        ui->display->setText("");
    } else {
        operand = "";
        QString str = ui->display->text();
        str.replace(operand, "");
        ui->display->setText(str);
    }
}


//操作符
//void ScientificCalculator::btnOperatorClicked()
//{
//    code = qobject_cast<QPushButton *>(sender())->text();
//    if (operand == "") {        //避免多次使用操作数
//        codes = code;
//        ui->display->setText(operands + codes);
//        return;
//    }
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
//}

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

////单操作符
//void ScientificCalculator::btnUniOperatorClicked()
//{
//    QString op = qobject_cast<QPushButton *>(sender())->text();
////    QString digit = ui->display->text();
//    double result = ui->display->text().toDouble();
//    if (op == "%")
//        result /= 100.0;
//    else if (op == "1/x") {
//        if (result == 0) {
//            operands = "除数不能为零";
//            operand = "";
//            code = "";
//            codes = "";
//            ui->display->setText(operands);
//            return;
//        }
//        result = 1 / result;
//    } else if (op == "x^2")
//        result = result * result;
//    else if (op == "√")
//        result = sqrt(result);
////    if (digit == operands) {
////        operands = QString::number(result);
////        ui->display->setText(operands);
////    } else {
////        operand = QString::number(result);
////        ui->display->setText(operand);
////    }
//    //判断当前数字是结果还是操作数
//    if (operand == "") {
//        operands = QString::number(result);
//        ui->display->setText(operands);
//    } else {
//        operand = QString::number(result);
//        ui->display->setText(operand);
//    }
//}

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
