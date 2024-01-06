#ifndef CURRENCY_H
#define CURRENCY_H

#include <QWidget>
#include <QMap>
#include <QPushButton>
#include <QKeyEvent>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonArray>

namespace Ui {
class Currency;
}

class Currency : public QWidget
{
    Q_OBJECT

public:
    explicit Currency(QWidget *parent = nullptr);
    ~Currency();
    void getCurrencyNumber();
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

    void processReply(QNetworkReply *reply);

    void on_btnUpdateRate_clicked();

private:
    Ui::Currency *ui;

    QString MY_APID = "kwsnqofcprok7kub";
    QString MY_APID_KEY = "tG0byAxmLkn1QHiNBOE9S2gBc7KLyrv8";
    QString baseUrl = "https://www.mxnzp.com/api/exchange_rate";

    QMap<int, QPushButton *> keyBtns;
    QJsonArray jArr;                            //获得可使用汇率转换的货币
    QNetworkAccessManager *manager;


    //汇率相关信息
    double price = 1.0;                           //当前汇率
    QString updateTime;                          //更新时间
    QString from = "CNY";
    QString to = "CNY";

    //operand
    int currentOperand = 0;
    QString operand = "0";

};

#endif // CURRENCY_H
