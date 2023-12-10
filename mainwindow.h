#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <standardcalculator.h>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_10_clicked();

private:
    Ui::MainWindow *ui;
    StandardCalculator *standard;
    void pushWidgetToStackView(QWidget *widget);
};
#endif // MAINWINDOW_H
