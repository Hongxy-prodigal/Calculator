#include "dateoperate.h"
#include "ui_dateoperate.h"

DateOperate::DateOperate(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DateOperate)
{
    ui->setupUi(this);
}

DateOperate::~DateOperate()
{
    delete ui;
}
