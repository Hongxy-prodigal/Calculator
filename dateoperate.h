#ifndef DATEOPERATE_H
#define DATEOPERATE_H

#include <QWidget>
#include <QMouseEvent>

namespace Ui {
class DateOperate;
}

class DateOperate : public QWidget
{
    Q_OBJECT

public:
    explicit DateOperate(QWidget *parent = nullptr);
    ~DateOperate();

private slots:
    void on_btnBegin_clicked();

    void on_calendarWidget_clicked(const QDate &date);

    void radioButtonClicked();

    void calculation();

private:
    Ui::DateOperate *ui;

    int mode = 0;

    bool eventFilter(QObject *obj, QEvent *event) override;
};

#endif // DATEOPERATE_H
