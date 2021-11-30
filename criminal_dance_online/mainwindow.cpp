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

void MainWindow::on_btn_back_in_desc_clicked() {ui->stackedwidget->setCurrentIndex(0);}
void MainWindow::on_btn_join_clicked() {ui->stackedwidget->setCurrentIndex(2);}
void MainWindow::on_btn_host_clicked() {ui->stackedwidget->setCurrentIndex(3);}
void MainWindow::on_btn_desc_clicked() {ui->stackedwidget->setCurrentIndex(1);}
void MainWindow::on_btn_exit_clicked() {close();}
void MainWindow::on_btn_join_room_clicked()
{
    canvas = new Render(ui->textEdit->toPlainText().split(QRegExp("[\n]"),QString::SkipEmptyParts));

    canvas->showView();
}

