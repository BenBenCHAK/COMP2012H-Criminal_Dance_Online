#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_button_exit_clicked()
{
    close();
}

void MainWindow::on_btn_desc_clicked()
{
    ui->stackedwidget->setCurrentIndex(1);
}


void MainWindow::on_button_back_clicked()
{
    ui->stackedwidget->setCurrentIndex(0);
}

