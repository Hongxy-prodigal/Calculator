#include "painting.h"
#include "ui_painting.h"

#include<QDebug>

Painting::Painting(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Painting)
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
        {Qt::Key_Return, ui->btnReturn},
    };
    //数字键入
    QList<QPushButton *> values = keyBtns.values();
    foreach (auto btn, values) {
        connect(btn, SIGNAL(clicked()), this, SLOT(btnDirectShowClicked()));
    }

    //普通
    connect(ui->btnE, SIGNAL(clicked()), this, SLOT(btnDirectShowClicked()));
    connect(ui->btnP, SIGNAL(clicked()), this, SLOT(btnDirectShowClicked()));
    connect(ui->btnX, SIGNAL(clicked()), this, SLOT(btnDirectShowClicked()));
    connect(ui->btnPlus, SIGNAL(clicked()), this, SLOT(btnDirectShowClicked()));
    connect(ui->btnSub, SIGNAL(clicked()), this, SLOT(btnDirectShowClicked()));
    connect(ui->btnMul, SIGNAL(clicked()), this, SLOT(btnDirectShowClicked()));
    connect(ui->btnDivide, SIGNAL(clicked()), this, SLOT(btnDirectShowClicked()));
    connect(ui->btnSign, SIGNAL(clicked()), this, SLOT(btnDirectShowClicked()));
    connect(ui->btnPeriod, SIGNAL(clicked()), this, SLOT(btnDirectShowClicked()));
    connect(ui->btnLeftBracket, SIGNAL(clicked()), this, SLOT(btnDirectShowClicked()));
    connect(ui->btnRightBracket, SIGNAL(clicked()), this, SLOT(btnDirectShowClicked()));

    connect(ui->btnInverse, SIGNAL(clicked()), this, SLOT(btnDirectShowClicked()));
    connect(ui->btnTen, SIGNAL(clicked()), this, SLOT(btnDirectShowClicked()));
    connect(ui->btnXy, SIGNAL(clicked()), this, SLOT(btnDirectShowClicked()));
    connect(ui->btnSquare, SIGNAL(clicked()), this, SLOT(btnDirectShowClicked()));
    connect(ui->btnLn, SIGNAL(clicked()), this, SLOT(btnDirectShowClicked()));

    //不普通
    connect(ui->btnAbs, SIGNAL(clicked()), this, SLOT(btnInDirectShowClicked()));
    connect(ui->btnSqrt, SIGNAL(clicked()), this, SLOT(btnInDirectShowClicked()));
    connect(ui->btnLog, SIGNAL(clicked()), this, SLOT(btnInDirectShowClicked()));
    connect(ui->btnLn, SIGNAL(clicked()), this, SLOT(btnInDirectShowClicked()));
    connect(ui->btnXy, SIGNAL(clicked()), this, SLOT(btnInDirectShowClicked()));
    connect(ui->btnSin, SIGNAL(clicked()), this, SLOT(btnInDirectShowClicked()));
    connect(ui->btnCos, SIGNAL(clicked()), this, SLOT(btnInDirectShowClicked()));
    connect(ui->btnTan, SIGNAL(clicked()), this, SLOT(btnInDirectShowClicked()));
    connect(ui->btnSec, SIGNAL(clicked()), this, SLOT(btnInDirectShowClicked()));
    connect(ui->btnCsc, SIGNAL(clicked()), this, SLOT(btnInDirectShowClicked()));
    connect(ui->btnCot, SIGNAL(clicked()), this, SLOT(btnInDirectShowClicked()));
    connect(ui->btnAbs_2, SIGNAL(clicked()), this, SLOT(btnInDirectShowClicked()));
    connect(ui->btnFloor, SIGNAL(clicked()), this, SLOT(btnInDirectShowClicked()));
    connect(ui->btnCeil, SIGNAL(clicked()), this, SLOT(btnInDirectShowClicked()));
}

Painting::~Painting()
{
    delete ui;
}

double cbrt(double x)
{
    return qPow(x, 1 / 3);
}
double root(double x, double y)
{
    return qPow(x, 1.0 / y);
}
double logBase(double y, double x)
{
    return qLn(x) / qLn(y);
}
double sec(double x)
{
    return 1 / cos(x);
}
double csc(double x)
{
    return 1 / sin(x);
}
double cot(double x)
{
    return 1 / tan(x);
}
double arcsec(double x)
{
    return acos(1 / x);
}
double arccsc(double x)
{
    return asin(1 / x);
}
double arccot(double x)
{
    return atan(1 / x);
}
double sech(double x)
{
    return 1 / cosh(x);
}
double csch(double x)
{
    return 1 / sinh(x);
}
double coth(double x)
{
    return 1 / tanh(x);
}
double arcsech(double x)
{
    return acosh(1 / x);
}
double arccsch(double x)
{
    return asinh(1 / x);
}
double arccoth(double x)
{
    return atanh(1 / x);
}

void Painting::on_btnChangePage_clicked()
{
    if (ui->stackedWidget->currentIndex() == 0) {
        ui->stackedWidget->setCurrentIndex(1);
        ui->btnChangePage->setIcon(QIcon(":/image/painting.png"));
    } else if (ui->stackedWidget->currentIndex() == 1) {
        ui->stackedWidget->setCurrentIndex(0);
        ui->btnChangePage->setIcon(QIcon(":/image/function.png"));
    }
}

//三角函数隐藏与显示
void Painting::on_btnTriangle_clicked()
{
    ui->triangleGroupBox->setVisible(!ui->triangleGroupBox->isVisible());
    ui->functionGroupBox->setVisible(false);
}
//函数隐藏与显示
void Painting::on_btnFuction_clicked()
{
    ui->triangleGroupBox->setVisible(false);
    ui->functionGroupBox->setVisible(!ui->functionGroupBox->isVisible());
}

void Painting::on_btnNd_clicked()
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
void Painting::on_btnTriangleNd_clicked()
{
    if (ndTriangle == 0) {
        for (QPushButton *button : ui->triangleGroupBox->findChildren<QPushButton *>())
            if (button->text() != "2nd" && button->text() != "hyp")
                button->setText(button->text() + "⁻¹");
        ui->btnTriangleNd->setStyleSheet("QPushButton:hover { " "background-color: rgb(24, 105, 166);"
                                         "} " "QPushButton { " "background-color: rgb(0, 90, 158); "
                                         "color: rgb(255, 255, 255); " "font: 13pt Arial;" "}");
        ndTriangle = 1;
    } else {
        for (QPushButton *button : ui->triangleGroupBox->findChildren<QPushButton *>())
            if (button->text() != "2nd" && button->text() != "hyp")
                button->setText(button->text().remove("⁻¹"));
        ui->btnTriangleNd->setStyleSheet("QPushButton:hover {" "background-color: rgb(241, 241, 241);"
                                         "}" "QPushButton {" "background-color: rgb(248, 248, 248);" "font: 13pt Arial;"
                                         "}");
        ndTriangle = 0;
    }
}

//hyp
void Painting::on_btnHyp_clicked()
{
    if (hyp == 0) {
        for (QPushButton *button : ui->triangleGroupBox->findChildren<QPushButton *>())
            if (button->text() != "2nd" && button->text() != "hyp")
                button->setText(button->text().insert(3, 'h'));
        ui->btnHyp->setStyleSheet("QPushButton:hover { " "background-color: rgb(24, 105, 166);"
                                  "} " "QPushButton { " "background-color: rgb(0, 90, 158); "
                                  "color: rgb(255, 255, 255); " "font: 13pt Arial;" "}");
        hyp = 1;
    } else {
        for (QPushButton *button : ui->triangleGroupBox->findChildren<QPushButton *>())
            if (button->text() != "2nd" && button->text() != "hyp")
                button->setText(button->text().remove("h"));
        ui->btnHyp->setStyleSheet("QPushButton:hover {" "background-color: rgb(241, 241, 241);"
                                  "}" "QPushButton {" "background-color: rgb(248, 248, 248);" "font: 13pt Arial;"
                                  "}");
        hyp = 0;
    }
}

//键盘事件
void Painting::keyPressEvent(QKeyEvent *event)
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

void Painting::on_btnDel_clicked()
{
    ui->display->setText(ui->display->text().remove(ui->display->cursorPosition() - 1, 1));
}

void Painting::on_btnClearAll_clicked()
{
    ui->display->clear();
}

void Painting::btnDirectShowClicked()
{
    QString temp = qobject_cast<QPushButton *>(sender())->text();
    if (temp == "π")
        temp = "pi";
    else if (temp == "(-)")
        temp = "-";
    else if (temp == "1/x")
        temp = "1/";
    else if (temp == "10ˣ")
        temp = "10^";
    else if (temp == "xʸ")
        temp = "^";
    else if (temp == "x²")
        temp = "^2";
    else if (temp == "x³")
        temp = "^3";
    else if (temp == "2ˣ")
        temp = "2^";
    else if (temp == "eˣ")
        temp = "e^";
    else if (temp == "×")
        temp = "*";
    else if (temp == "÷")
        temp = "/";
    else if (temp == "ln" || temp == "ʸ√")
        return;
    int position = ui->display->cursorPosition();
    ui->display->setText(ui->display->text().insert(position, temp));
    ui->display->setFocus();
    ui->display->setCursorPosition(position + temp.size());
}

void Painting::btnInDirectShowClicked()
{
    QString temp = qobject_cast<QPushButton *>(sender())->text();
    if (temp == "|x|")
        temp = "abs()";
    else if (temp == "√")
        temp = "sqrt()";
    else if (temp == "∛")
        temp = "cbrt()";        //不支持
    else if (temp == "ʸ√")
        temp = "root(x,)";      //不支持
    else if (temp == "logᵥx")
        temp = "logBase(,x)";           //看情况修改 //不支持

    else if (temp == "sin⁻¹")
        temp = "arcsin()";
    else if (temp == "cos⁻¹")
        temp = "arccos()";
    else if (temp == "tan⁻¹")
        temp = "arctan()";
    else if (temp == "sec⁻¹")
        temp = "arcsec()";
    else if (temp == "csc⁻¹")
        temp = "arccsc()";
    else if (temp == "cot⁻¹")
        temp = "arccot()";

    else if (temp == "sinh⁻¹")
        temp = "arcsinh()";
    else if (temp == "cosh⁻¹")
        temp = "arccosh()";
    else if (temp == "tanh⁻¹")
        temp = "arctanh()";
    else if (temp == "sech⁻¹")
        temp = "arcsech()";
    else if (temp == "csch⁻¹")
        temp = "arccsch()";
    else if (temp == "coth⁻¹")
        temp = "arccoth()";

    else if (temp == "⌈x⌉")
        temp = "ceil()";
    else if (temp == "⌊x⌋")
        temp = "floor()";

    else if (temp == "eˣ" || temp == "xʸ")
        return;
    else
        temp = temp + "()";
    int position = ui->display->cursorPosition();
    ui->display->setText(ui->display->text().insert(position, temp));
    ui->display->setFocus();
    ui->display->setCursorPosition(position + temp.size() - 1);
}


void Painting::on_btnReturn_clicked()
{
    QString str = ui->display->text();
    QByteArray byte  = str.toLocal8Bit();
    const char *expression = byte.data();   // QString to const char

    int err;
    double a = -10;
    double b = 10;
    qDebug() << "a=" << a << "b=" << b << endl;

    int LEN = 1000;
    QVector<double> x_vec(LEN), y_vec(LEN); // initialize with entries 0..100

    double h = (double) (b - a) / (double)LEN;
    /* the variables x is bound at eval-time. */
    double x;
    te_variable vars[] = {
        {"x", &x, TE_VARIABLE, 0},
        {"cbrt", (const void *)cbrt, TE_FUNCTION1, 0},
        {"root", (const void *)root, TE_FUNCTION2, 0},
        {"logBase", (const void *)logBase, TE_FUNCTION2, 0},
        {"sec", (const void *)sec, TE_FUNCTION1, 0},
        {"csc", (const void *)csc, TE_FUNCTION1, 0},
        {"cot", (const void *)cot, TE_FUNCTION1, 0},
        {"arcsin", (const void *)asin, TE_FUNCTION1, 0},
        {"arccos", (const void *)acos, TE_FUNCTION1, 0},
        {"arctan", (const void *)atan, TE_FUNCTION1, 0},
        {"arcsec", (const void *)arcsec, TE_FUNCTION1, 0},
        {"arccsc", (const void *)arccsc, TE_FUNCTION1, 0},
        {"arccot", (const void *)arccot, TE_FUNCTION1, 0},
        {"sech", (const void *)sech, TE_FUNCTION1, 0},
        {"csch", (const void *)csch, TE_FUNCTION1, 0},
        {"coth", (const void *)coth, TE_FUNCTION1, 0},
        {"archsinh", (const void *)asinh, TE_FUNCTION1, 0},
        {"arccosh", (const void *)acosh, TE_FUNCTION1, 0},
        {"arctanh", (const void *)atanh, TE_FUNCTION1, 0},
        {"arcsech", (const void *)arcsech, TE_FUNCTION1, 0},
        {"arccsch", (const void *)arccsch, TE_FUNCTION1, 0},
        {"arccoth", (const void *)arccoth, TE_FUNCTION1, 0},

    };
    /* This will compile the expression and check for errors. */
    te_expr *n = te_compile(expression, vars, 22, &err);

    // evaluating the function results
    for (int i = 0; i < LEN; ++i) {
        x_vec[i] = a + i * h; // x goes from -1 to 1
        if (n) {
            x = x_vec[i];
            y_vec[i] = (double)te_eval(n);
        }
    }

    // create graph and assign data to it:
    ui->widget->addGraph();
    ui->widget->graph(0)->setData(x_vec, y_vec);
    // give the axes some labels:
    ui->widget->xAxis->setLabel("x");
    ui->widget->yAxis->setLabel("y");
    // set axes ranges, so we see all data:
    ui->widget->rescaleAxes(true);
    ui->widget->replot();
}

