#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <standardcalculator.h>
#include <scientificcalculator.h>
#include <programmercalculator.h>
#include <datecalculator.h>
#include <currency.h>

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

    void on_btnNavigator_clicked();


    void on_btnScientific_clicked();

    void on_btnProgram_clicked();

    void on_btnDate_clicked();

    void on_btnCurrency_clicked();

    void on_btnStandard_clicked();

private:
    Ui::MainWindow *ui;
    StandardCalculator *standard;
    ScientificCalculator *scient;
    ProgrammerCalculator *program;
    DateCalculator *date;
    Currency *currency;
    void pushWidgetToStackView(QWidget *widget);
};
#endif // MAINWINDOW_H
