#ifndef PAINTING_H
#define PAINTING_H

#include <QWidget>
#include <qcustomplot.h>
#include <tinyexpr.h>
#include <QWidget>
#include <QMap>
#include <QPushButton>
#include <QStack>
#include <QKeyEvent>

namespace Ui {
class Painting;
}

class Painting : public QWidget
{
    Q_OBJECT

public:
    explicit Painting(QWidget *parent = nullptr);
    ~Painting();

    QMap<int, QPushButton *> keyBtns;
    QMap<int, QPushButton *> operatorBtns;

private slots:
    void on_btnChangePage_clicked();
    void on_btnNd_clicked();
    void keyPressEvent(QKeyEvent *event);
    void on_btnTriangle_clicked();
    void on_btnFuction_clicked();
    void on_btnTriangleNd_clicked();
    void on_btnHyp_clicked();

    //功能性
    void on_btnDel_clicked();
    void on_btnClearAll_clicked();

    //显示性
    void btnDirectShowClicked();
    void btnInDirectShowClicked();

    void on_btnReturn_clicked();

private:
    Ui::Painting *ui;
    int ndTriangle = 0;     //三角函数的nd转换
    int hyp = 0;
    int nd = 0;           //变换按键
};

#endif // PAINTING_H

