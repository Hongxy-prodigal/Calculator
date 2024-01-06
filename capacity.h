#ifndef CAPACITY_H
#define CAPACITY_H

#include <QWidget>
#include <QPushButton>
#include <QKeyEvent>

namespace Ui {
class Capacity;
}

class Capacity : public QWidget
{
    Q_OBJECT

public:
    explicit Capacity(QWidget *parent = nullptr);
    ~Capacity();

    void setAllDisplay();

private slots:
    void on_btnClearAll_clicked();

    void btnNumClicked();

    void on_btnDel_clicked();

    void on_btnPeriod_clicked();

    void keyPressEvent(QKeyEvent *event) override;

    void on_displayUp_clicked();

    void on_displayDown_clicked();

    void on_comboBoxUp_currentIndexChanged(int index);

    void on_comboBoxDown_currentIndexChanged(int index);

private:
    Ui::Capacity *ui;

    QMap<int, QPushButton *> keyBtns;

    QList<double> capacityRate;

    //operand
    int currentOperand = 0;
    QString operand = "0";

    double rate = 1;

};

#endif // CAPACITY_H
