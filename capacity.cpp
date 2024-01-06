#include "capacity.h"
#include "ui_capacity.h"

Capacity::Capacity(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Capacity)
{
    ui->setupUi(this);
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
    capacityRate = {0.7645549 * 1000000, 0.7645549 * 1000000, 0.7645549 * 1000, 0.7645549, 201.974 * 768, 201.974 * 256,
                    201.974 * 128, 201.974 * 16, 201.974 * 8, 201.974 * 2, 201.974, 46656, 27, 1, 168.1786 * 768, 168.1786 * 256,
                    168.1786 * 128, 168.1786 * 8, 168.1786 * 4, 168.1786
                   };
    QList<QPushButton *> values = keyBtns.values();
    foreach (auto btn, values) {
        connect(btn, SIGNAL(clicked()), this, SLOT(btnNumClicked()));
    }
//初始化操作
    ui->displayUp->setStyleSheet("font-size:40pt ;text-align:left;font-weight: bold;");
}

Capacity::~Capacity()
{
    delete ui;
}

//数字键
void Capacity::btnNumClicked()
{
    QString digit = qobject_cast<QPushButton *>(sender())->text();
    if (digit == "0" && operand == "0") {
        digit = "";
    }
    if (digit != "0" && operand == "0") {
        operand = "";
    }
    operand += digit;
    setAllDisplay();
}

//清空
void Capacity::on_btnClearAll_clicked()
{
    ui->displayUp->setText("0");
    ui->displayDown->setText("0");
    operand = "0";
}

//删除
void Capacity::on_btnDel_clicked()
{
    if (operand != "") {
        operand = operand.left(operand.size() - 1);
    }
    if (operand == "")
        operand = "0";
    setAllDisplay();
}

//小数点
void Capacity::on_btnPeriod_clicked()
{
    if (!operand.contains('.')) {
        if (operand == "")
            operand = "0";
        operand += '.';
        setAllDisplay();
    }
}

//键盘事件
void Capacity::keyPressEvent(QKeyEvent *event)
{
    QList<int> values = keyBtns.keys();
    foreach (auto key, values) {
        if (event->key() == key)
            emit keyBtns[key]->clicked();
    }
}

void Capacity::setAllDisplay()
{
    QString displayFrom = operand;
    QString displayTo = QString::number(operand.toDouble() * rate);
    if (currentOperand == 0) {
        ui->displayUp->setText(displayFrom);
        ui->displayDown->setText(displayTo);
    } else {
        ui->displayDown->setText(displayFrom);
        ui->displayUp->setText(displayTo);
    }
}



void Capacity::on_displayUp_clicked()
{
    operand = "0";
    currentOperand = 0;
    ui->displayUp->setStyleSheet("font-size:40pt ;text-align:left;font-weight: bold;");
    ui->displayDown->setStyleSheet("font-size:40pt ;text-align:left;");
}


void Capacity::on_displayDown_clicked()
{
    operand = "0";
    currentOperand = 1;
    ui->displayDown->setStyleSheet("font-size:40pt ;text-align:left;font-weight: bold;");
    ui->displayUp->setStyleSheet("font-size:40pt ;text-align:left;");
}

void Capacity::on_comboBoxUp_currentIndexChanged(int index)
{
    int temp = ui->comboBoxDown->currentIndex();
    if (currentOperand == 0)
        rate = capacityRate[temp] / capacityRate[index];
    else
        rate = capacityRate[index] / capacityRate[temp];
    setAllDisplay();
}


void Capacity::on_comboBoxDown_currentIndexChanged(int index)
{
    int temp = ui->comboBoxUp->currentIndex();
    if (currentOperand == 0)
        rate = capacityRate[index] / capacityRate[temp];
    else
        rate = capacityRate[temp] / capacityRate[index];
    setAllDisplay();
}


