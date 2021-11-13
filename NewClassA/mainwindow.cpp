#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("A");
    server = new TcpServer();
    server->tcpServerInit(8000);    //初始化（端口8000）
    connect(server,SIGNAL(SG_recvData(QByteArray)),this,SLOT(SL_readData(QByteArray)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_startButton_clicked()
{
    if(ui->startButton->text()=="Start"){
        ui->startButton->setText("Stop");
        ui->label->setText("Running...");
        server->SL_sendData("Start");//告知B开始计算
    }else {
        ui->startButton->setText("Start");
        server->SL_sendData("Stop");//告知B停止计算
    }

}

void MainWindow::SL_readData(QByteArray data)
{
    if(data=="Exit"){//接收到B发来的程序终止指令
        this->close();
    }else {
        ui->label->setText("Result:"+data);
    }
}

void MainWindow::on_exitButton_clicked()
{
    server->SL_sendData("Exit");//告知B终止程序
    this->close();
}
