#include "currency.h"
#include "ui_currency.h"

Currency::Currency(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Currency)
{
    ui->setupUi(this);
}

Currency::~Currency()
{
    delete ui;
}
