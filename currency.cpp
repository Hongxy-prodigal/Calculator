#include "currency.h"
#include "ui_currency.h"

Currency::Currency(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Currency)
{
    ui->setupUi(this);
    manager = new QNetworkAccessManager();
    keyBtns = {
        {Qt::Key_0, ui->btnNum0},
        {Qt::Key_1, ui->btnNum1},
        {Qt::Key_2, ui->btnNum2},
        {Qt::Key_3, ui->btnNum3},
        {Qt::Key_4, ui->btnNum4},
        {Qt::Key_5, ui->btnNum5},
        {Qt::Key_6, ui->btnNum6},
        {Qt::Key_7, ui->btnNum7},
        {Qt::Key_8, ui->btnNum8},
        {Qt::Key_9, ui->btnNum9},
    };
    QList<QPushButton *> values = keyBtns.values();
    foreach (auto btn, values) {
        connect(btn, SIGNAL(clicked()), this, SLOT(btnNumClicked()));
    }
    //初始化操作
    ui->displayUp->setStyleSheet("font-size:40pt ;text-align:left;font-weight: bold;");
    getCurrencyNumber();
}

Currency::~Currency()
{
    delete manager;
    delete ui;
}

//数字键
void Currency::btnNumClicked()
{
    QString digit = qobject_cast<QPushButton *>(sender())->text();
    if (digit == "0" && operand == "0") {
        digit = "";
    }
    if (digit != "0" && operand == "0") {
        operand = "";
    }
    if (operand.contains('.')) {
        if (operand.rightRef(operand.size() - operand.lastIndexOf('.') - 1).size() < 2)
            operand += digit;
    } else
        operand += digit;
    setAllDisplay();
}

//清空
void Currency::on_btnClearAll_clicked()
{
    ui->displayUp->setText("0");
    ui->displayDown->setText("0");
    operand = "0";
}

//删除
void Currency::on_btnDel_clicked()
{
    if (operand != "") {
        operand = operand.left(operand.size() - 1);
    }
    if (operand == "")
        operand = "0";
    setAllDisplay();
}

//小数点
void Currency::on_btnPeriod_clicked()
{
    if (!operand.contains('.')) {
        if (operand == "")
            operand = "0";
        operand += '.';
        setAllDisplay();
    }
}

//键盘事件
void Currency::keyPressEvent(QKeyEvent *event)
{
    QList<int> values = keyBtns.keys();
    foreach (auto key, values) {
        if (event->key() == key)
            emit keyBtns[key]->clicked();
    }
}

//获取货币编号列表
void Currency::getCurrencyNumber()
{
    QString sUrl = QString("%1/configs?app_id=%2&app_secret=%3").arg(baseUrl, MY_APID, MY_APID_KEY);
    QUrl url(sUrl);

    QNetworkRequest request(url);
    QNetworkReply *reply = manager->get(request);

    QObject::connect(reply, &QNetworkReply::readyRead, this, [ = ]() {
        if (reply->error() == QNetworkReply::NoError) {
            QByteArray data = reply->readAll();
            QJsonObject jObj;
            QJsonParseError parseError;
            const QJsonDocument jsonDoc = QJsonDocument::fromJson(data, &parseError);
            if (parseError.error == QJsonParseError::NoError && jsonDoc.isObject()) {
                jObj = jsonDoc.object();
            }

            jArr = jObj["data"].toArray();
            QStringList list;
            for (int i = 0; i < jArr.size(); i++) {
                QJsonObject obj = jArr[i].toObject();
                list << obj["desc"].toString();
                qDebug() << obj["desc"].toString();
            }
            ui->comboBoxUp->addItems(list);
            ui->comboBoxDown->addItems(list);

            ui->comboBoxDown->setCurrentText("人民币");
            ui->comboBoxUp->setCurrentText("人民币");
            ui->labelDown->setText("CNY");
            ui->labelUp->setText("CNY");


        } else {
            qDebug() << "请求失败：" << reply->errorString();
            // 处理错误情况
        }
        reply->deleteLater();
    });
}

void Currency::setAllDisplay()
{
    QString displayFrom = operand;
    QString displayTo = QString::number(operand.toDouble() * price);
    if (displayFrom.contains('.')) {
        int count = displayFrom.rightRef(displayFrom.size() - displayFrom.lastIndexOf('.') - 1).size();
        if ( count == 0)
            displayFrom = displayFrom + "00";
        else if (count == 1)
            displayFrom = displayFrom + "0";
    }
    //显示的时候设置一下有小数点加0
    if (currentOperand == 0) {
        ui->displayUp->setText(displayFrom);
        ui->displayDown->setText(displayTo);
    } else {
        ui->displayDown->setText(displayFrom);
        ui->displayUp->setText(displayTo);
    }
}



void Currency::on_displayUp_clicked()
{
    operand = "0";
    QString temp = from;
    from = to;
    to = temp;
    price = 1 / price;
    ui->labelExchangeRate->setText("1 " + from + " = " + QString::number(price) + " " + to);
    currentOperand = 0;
    ui->displayUp->setStyleSheet("font-size:40pt ;text-align:left;font-weight: bold;");
    ui->displayDown->setStyleSheet("font-size:40pt ;text-align:left;");
}


void Currency::on_displayDown_clicked()
{
    operand = "0";
    QString temp = from;
    from = to;
    to = temp;
    price = 1 / price;
    ui->labelExchangeRate->setText("1 " + from + " = " + QString::number(price) + " " + to);
    currentOperand = 1;
    ui->displayDown->setStyleSheet("font-size:40pt ;text-align:left;font-weight: bold;");
    ui->displayUp->setStyleSheet("font-size:40pt ;text-align:left;");
}

void Currency::processReply(QNetworkReply *reply)
{
    QObject::connect(reply, &QNetworkReply::readyRead, this, [ = ]() {
        if (reply->error() == QNetworkReply::NoError) {
            QByteArray data = reply->readAll();
            qDebug() << data;
            QJsonObject jObj;
            QJsonParseError parseError;
            const QJsonDocument jsonDoc = QJsonDocument::fromJson(data, &parseError);
            if (parseError.error == QJsonParseError::NoError && jsonDoc.isObject()) {
                jObj = jsonDoc.object();
            }
            //获取更新时间和汇率
            if (jObj["msg"].toString().contains("数据返回成功")) {
                jObj = jObj["data"].toObject();
                updateTime = jObj["updateTime"].toString();
                QString temp = jObj["price"].toString();
                if (!temp.contains('.'))
                    temp = temp + ".0";
                price = temp.toDouble();
                ui->labelUpdateTime->setText("已更新 " + updateTime);
                qDebug() << "updateTime" << updateTime << endl << "price" << QString::number(
                             price);
            }

        } else {
            qDebug() << "请求失败：" << reply->errorString();
        }
    });
}

void Currency::on_comboBoxUp_currentIndexChanged(int index)
{
    if (currentOperand == 0) {
        from = jArr.at(index)["name"].toString();
        ui->labelUp->setText(from);
    } else {
        to = jArr.at(index)["name"].toString();
        ui->labelUp->setText(to);
    }
    QString sUrl = QString("%1/aim?from=%2&to=%3&app_id=%4&app_secret=%5").arg(baseUrl, from, to,
                                                                               MY_APID, MY_APID_KEY);
    QUrl url(sUrl);
    QNetworkRequest request(url);
    QNetworkReply *reply = manager->get(request);

    processReply(reply);
    QObject::connect(reply, &QNetworkReply::finished, this, [ = ]() {
        if (reply->error() == QNetworkReply::NoError) {
            setAllDisplay();
            ui->labelExchangeRate->setText("1 " + from + " = " + QString::number(price) + " " + to);
        } else {
            qDebug() << "请求失败：" << reply->errorString();
        }
        reply->deleteLater();
    });
}


void Currency::on_comboBoxDown_currentIndexChanged(int index)
{
    if (currentOperand == 1) {
        from = jArr.at(index)["name"].toString();
        ui->labelDown->setText(from);
    } else {
        to = jArr.at(index)["name"].toString();
        ui->labelDown->setText(to);
    }

    QString sUrl = QString("%1/aim?from=%2&to=%3&app_id=%4&app_secret=%5").arg(baseUrl, from, to,
                                                                               MY_APID, MY_APID_KEY);
    QUrl url(sUrl);
    QNetworkRequest request(url);
    QNetworkReply *reply = manager->get(request);

    processReply(reply);

    QObject::connect(reply, &QNetworkReply::finished, this, [ = ]() {
        if (reply->error() == QNetworkReply::NoError) {
            setAllDisplay();
            ui->labelExchangeRate->setText("1 " + from + " = " + QString::number(price) + " " + to);
        } else {
            qDebug() << "请求失败：" << reply->errorString();
        }
        reply->deleteLater();
    });
}


void Currency::on_btnUpdateRate_clicked()
{
    QString sUrl = QString("%1/aim?from=%2&to=%3&app_id=%4&app_secret=%5").arg(baseUrl, from, to,
                                                                               MY_APID, MY_APID_KEY);
    QUrl url(sUrl);
    QNetworkRequest request(url);
    QNetworkReply *reply = manager->get(request);

    processReply(reply);

    QObject::connect(reply, &QNetworkReply::finished, this, [ = ]() {
        if (reply->error() == QNetworkReply::NoError) {
            setAllDisplay();
            ui->labelExchangeRate->setText("1 " + from + " = " + QString::number(price) + " " + to);
        } else {
            qDebug() << "请求失败：" << reply->errorString();
        }
        reply->deleteLater();
    });
}

