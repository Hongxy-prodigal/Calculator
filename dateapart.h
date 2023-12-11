#ifndef DATEAPART_H
#define DATEAPART_H

#include <QWidget>

namespace Ui {
class DateApart;
}

class DateApart : public QWidget
{
    Q_OBJECT

public:
    explicit DateApart(QWidget *parent = nullptr);
    ~DateApart();

private:
    Ui::DateApart *ui;
};

#endif // DATEAPART_H
