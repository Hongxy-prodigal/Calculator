#include "dateapart.h"
#include "ui_dateapart.h"

DateApart::DateApart(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DateApart)
{
    ui->setupUi(this);
}

DateApart::~DateApart()
{
    delete ui;
}
