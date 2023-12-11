#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QWidget>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->Frame->setVisible(false);
    standard = new StandardCalculator(this);
    pushWidgetToStackView(standard);
}

void MainWindow::pushWidgetToStackView(QWidget *widget)
{
    QWidget *temp = ui->stackCalculator->widget(0);
    ui->stackCalculator->removeWidget(temp);
    delete temp;
    ui->stackCalculator->addWidget(widget);
    int count = ui->stackCalculator->count();
    ui->stackCalculator->setCurrentIndex(count - 1);
    ui->labelTitle->setText(widget->windowTitle());
}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_btnNavigator_clicked()
{
    if (ui->Frame->isVisible()) {
        ui->Frame->setVisible(false);
    } else {
        ui->Frame->setVisible(true);
    }
}

void MainWindow::on_btnStandard_clicked()
{
    standard = new StandardCalculator(this);
    pushWidgetToStackView(standard);
}

void MainWindow::on_btnScientific_clicked()
{
    scient = new ScientificCalculator(this);
    pushWidgetToStackView(scient);
}


void MainWindow::on_btnProgram_clicked()
{
    program = new ProgrammerCalculator(this);
    pushWidgetToStackView(program);
}


void MainWindow::on_btnDate_clicked()
{
    date = new DateCalculator(this);
    pushWidgetToStackView(date);
}


void MainWindow::on_btnCurrency_clicked()
{
    currency = new Currency(this);
    pushWidgetToStackView(currency);
}




