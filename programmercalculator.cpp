#include "programmercalculator.h"
#include "ui_programmercalculator.h"

ProgrammerCalculator::ProgrammerCalculator(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ProgrammerCalculator)
{
    ui->setupUi(this);
}

ProgrammerCalculator::~ProgrammerCalculator()
{
    delete ui;
}
