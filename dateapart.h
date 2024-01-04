#ifndef DATEAPART_H
#define DATEAPART_H

#include <QWidget>
#include <QMouseEvent>

namespace Ui {
class DateApart;
}

class DateApart : public QWidget
{
    Q_OBJECT

public:
    explicit DateApart(QWidget *parent = nullptr);
    ~DateApart();

private slots:

    void on_calendarWidget_clicked(const QDate &date);

    void on_btnBegin_clicked();

    void on_btnEnd_clicked();

private:
    Ui::DateApart *ui;

    int currentCalender;

    bool eventFilter(QObject *obj, QEvent *event) override;
};

#endif // DATEAPART_H
