#include "dateapart.h"
#include "ui_dateapart.h"

#include <QtDebug>

DateApart::DateApart(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DateApart)
{
    ui->setupUi(this);
    ui->calendarWidget->setVisible(false);
    installEventFilter(this);
    QDateTime begin_time = QDateTime::currentDateTime();
    QString begin = begin_time .toString("yyyy年MM月dd日");
    ui->btnBegin->setText(begin);
    ui->btnEnd->setText(begin);
    ui->labelMany->setText("相同日期");
}

DateApart::~DateApart()
{
    delete ui;
}

bool DateApart::eventFilter(QObject *obj, QEvent *event)
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


void DateApart::on_calendarWidget_clicked(const QDate &date)
{
    QDate beginDate, endDate;
    if (currentCalender == 0)
        ui->btnBegin->setText(date.toString("yyyy年MM月dd日"));
    else
        ui->btnEnd->setText(date.toString("yyyy年MM月dd日"));
    beginDate = QDate::fromString(ui->btnBegin->text(), "yyyy年MM月dd日");
    endDate = QDate::fromString(ui->btnEnd->text(), "yyyy年MM月dd日");
    int diffTime = abs(beginDate.daysTo(endDate));
    if (diffTime == 0)
        ui->labelConcrete->setText("");
    else
        ui->labelConcrete->setText(QString::number(diffTime) + "天");
    //相差的年份
    QString total = "";
    int years = abs(beginDate.year() - endDate.year());
    if (years == 0)
        total += "";
    else
        total += QString::number(years) + "年 ";
    //相差的月份
    int months = abs(beginDate.month() - endDate.month());
    if (months == 0)
        total += "";
    else
        total += QString::number(months) + "月 ";
    //相差的周
    int days = abs(beginDate.day() - endDate.day());
    int weeks = days / 7;
    if (weeks == 0)
        total += "";
    else
        total += QString::number(weeks) + "周 ";
    //相差的天数
    days %= 7;
    if (days == 0)
        total += "";
    else
        total += QString::number(days) + "天 ";
    ui->labelMany->setText(total);
    ui->calendarWidget->setVisible(false);
}


void DateApart::on_btnBegin_clicked()
{
    ui->calendarWidget->setVisible(true);
    currentCalender = 0;
}


void DateApart::on_btnEnd_clicked()
{
    ui->calendarWidget->setVisible(true);
    currentCalender = 1;
}

