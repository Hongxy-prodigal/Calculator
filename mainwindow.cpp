#include "mainwindow.h"
#include "ui_mainwindow.h"

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
    ui->stackCaculator->addWidget(widget);
    int count = ui->stackCaculator->count();
    ui->stackCaculator->setCurrentIndex(count - 1);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_10_clicked()
{
    ui->Frame->setVisible(true);

}

