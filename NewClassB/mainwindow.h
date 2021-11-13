#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "tcpclient.h"
#include "countnumber.h"

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
    void SL_readData(QByteArray);//接收A发来的显示
    void SL_showCount(int);//显示计数值
    void SL_sendFinal(int);//上传最终数值给A
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    TcpClient *client;
    CountNumber * m_count;//计数器
    bool isStart=false;//计数开始

signals:
    void sg_startCount();
    void sg_pauseCount();
    void sg_resumeCount();
};

#endif // MAINWINDOW_H
