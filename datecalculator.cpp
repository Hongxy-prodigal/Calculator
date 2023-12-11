#include "datecalculator.h"
#include "ui_datecalculator.h"

DateCalculator::DateCalculator(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DateCalculator)
{
    ui->setupUi(this);
    apart = new DateApart(this);
    pushWidgetToStackView(apart);
}

DateCalculator::~DateCalculator()
{
    delete ui;
}

void DateCalculator::on_comboBox_activated(int index)
{
    if (index == 0) {
        apart = new DateApart(this);
        pushWidgetToStackView(apart);
    } else {
        operate = new DateOperate(this);
        pushWidgetToStackView(operate);
    }
}

void DateCalculator::pushWidgetToStackView(QWidget *widget)
{
    QWidget *temp = ui->stackedDate->widget(0);
    ui->stackedDate->removeWidget(temp);
    delete temp;
    ui->stackedDate->addWidget(widget);
    int count = ui->stackedDate->count();
    ui->stackedDate->setCurrentIndex(count - 1);
}
