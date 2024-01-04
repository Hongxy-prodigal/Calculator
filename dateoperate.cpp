#include "dateoperate.h"
#include "ui_dateoperate.h"

#include <QDebug>

DateOperate::DateOperate(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DateOperate)
{
    ui->setupUi(this);
    ui->calendarWidget->setVisible(false);
    installEventFilter(this);
    QDateTime begin_time = QDateTime::currentDateTime();
    QString begin = begin_time .toString("yyyy年MM月dd日");
    ui->btnBegin->setText(begin);
    ui->labelDate->setText(begin);

    //添加或减去
    connect(ui->radioAdd, SIGNAL(clicked()), this, SLOT(radioButtonClicked()));
    connect(ui->radioSub, SIGNAL(clicked()), this, SLOT(radioButtonClicked()));

    //年月日
    QStringList list;
    for (int i = 0; i < 1000; i++)
        list << QString::number(i);
    ui->comboBoxYear->addItems(list);
    ui->comboBoxMonth->addItems(list);
    ui->comboBoxDay->addItems(list);
    ui->comboBoxYear->setCurrentIndex(0);
    ui->comboBoxMonth->setCurrentIndex(0);
    ui->comboBoxDay->setCurrentIndex(0);
    connect(ui->comboBoxYear, SIGNAL(currentIndexChanged(int)), this, SLOT(calculation()));
    connect(ui->comboBoxMonth, SIGNAL(currentIndexChanged(int)), this, SLOT(calculation()));
    connect(ui->comboBoxDay, SIGNAL(currentIndexChanged(int)), this, SLOT(calculation()));

}

DateOperate::~DateOperate()
{
    delete ui;
}

void DateOperate::on_btnBegin_clicked()
{
    ui->calendarWidget->setVisible(true);
}

bool DateOperate::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::MouseButtonPress) {
        // 检查是否点击了除日历部件以外的地方
        QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
        if (obj != ui->calendarWidget && !ui->calendarWidget->geometry().contains(mouseEvent->pos())) {
            ui->calendarWidget->setVisible(false); // 隐藏日历部件
        }
    }
    return QWidget::eventFilter(obj, event);
}


void DateOperate::on_calendarWidget_clicked(const QDate &date)
{
    ui->btnBegin->setText(date.toString("yyyy年MM月dd日"));
    calculation();
    ui->calendarWidget->setVisible(false);
}

void DateOperate::radioButtonClicked()
{
    QString tempCode = qobject_cast<QRadioButton *>(sender())->text();
    if (tempCode == "添加")
        mode = 0;
    else
        mode = 1;
    calculation();
}

void DateOperate::calculation()
{
    QDate beginDate = QDate::fromString(ui->btnBegin->text(), "yyyy年MM月dd日");
    int years = ui->comboBoxYear->currentIndex();
    int months = ui->comboBoxMonth->currentIndex();
    int days = ui->comboBoxDay->currentIndex();
    if (mode == 1) {
        years = -years;
        months = -months;
        days = -days;
    }
    QDate endDate = beginDate.addYears(years).addMonths(months).addDays(days);
    ui->labelDate->setText(endDate.toString("yyyy年MM月dd日"));
}

