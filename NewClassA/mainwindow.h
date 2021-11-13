#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "tcpserver.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_startButton_clicked();

    void SL_readData(QByteArray);//接收显示

    void on_exitButton_clicked();

private:
    Ui::MainWindow *ui;
    TcpServer *server;//服务端
};

#endif // MAINWINDOW_H
