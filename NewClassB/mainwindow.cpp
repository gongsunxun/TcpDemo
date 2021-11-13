#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("B");

    client = new TcpClient();
    QString ip="127.0.0.1";
    quint16 port=8000;
    client->tcpClientInit(ip,port);
    connect(client,SIGNAL(SG_recvData(QByteArray)),this,SLOT(SL_readData(QByteArray)));

    m_count = new CountNumber;

    connect(this,SIGNAL(sg_startCount()),m_count,SLOT(SL_startCount()));//开始线程-计数
    connect(this,SIGNAL(sg_pauseCount()),m_count,SLOT(SL_pauseCount()));//暂停计数
    connect(this,SIGNAL(sg_resumeCount()),m_count,SLOT(SL_resumeCount()));//恢复计数

    connect(m_count,SIGNAL(SG_sendResult(int)),this,SLOT(SL_showCount(int)));//主界面数值变动
    connect(m_count,SIGNAL(SG_sendFinal(int)),this,SLOT(SL_sendFinal(int)));//最终数值传到A


}

MainWindow::~MainWindow()
{
    m_count->quit();
    m_count->wait();
    delete ui;
}

void MainWindow::SL_readData(QByteArray data)
{
    if(data=="Start"){
        if(isStart==false){
            emit sg_startCount();
        }else {
            emit sg_resumeCount();
        }
        isStart=true;
    }else if(data=="Stop"){
        emit sg_pauseCount();
    }else if(data=="Exit"){
        this->close();
    }
}

void MainWindow::SL_showCount(int data)
{
    ui->label->setText("Current number:"+QString::number(data));
}

void MainWindow::SL_sendFinal(int data)
{
    client->SL_sendData(QByteArray::number(data));//告知A自己的最终计数值
}

void MainWindow::on_pushButton_clicked()
{
    client->SL_sendData("Exit");//告知A终止程序
    this->close();
}
