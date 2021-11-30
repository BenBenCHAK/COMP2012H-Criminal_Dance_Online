#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "render/render.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btn_back_in_desc_clicked();
    void on_btn_join_clicked();
    void on_btn_host_clicked();
    void on_btn_desc_clicked();
    void on_btn_exit_clicked();

    void on_btn_join_room_clicked();

private:
    Ui::MainWindow *ui;

    Render *canvas;
};
#endif // MAINWINDOW_H
