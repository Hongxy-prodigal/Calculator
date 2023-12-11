#ifndef DATEOPERATE_H
#define DATEOPERATE_H

#include <QWidget>

namespace Ui {
class DateOperate;
}

class DateOperate : public QWidget
{
    Q_OBJECT

public:
    explicit DateOperate(QWidget *parent = nullptr);
    ~DateOperate();

private:
    Ui::DateOperate *ui;
};

#endif // DATEOPERATE_H
