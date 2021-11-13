#include "tcpclient.h"

TcpClient::TcpClient()
{

}

void TcpClient::tcpClientInit(QString ip,quint16 port)
{
    //初始化TCP客户端
    tcpClient = new QTcpSocket(this);   //实例化tcpClient
    tcpClient->abort();                 //取消原有连接
    connect(tcpClient, SIGNAL(readyRead()), this, SLOT(SL_readData()));
    connect(tcpClient, SIGNAL(error(QAbstractSocket::SocketError)),
                this, SLOT(ReadError(QAbstractSocket::SocketError)));
    tcpClient->connectToHost(ip,port);
    tcpClient->waitForConnected(1000);  //等待连接成功
}

void TcpClient::ReadError(QAbstractSocket::SocketError)
{
    tcpClient->disconnectFromHost();
    QMessageBox msgBox;
    msgBox.setText(tr("failed to connect server because %1").arg(tcpClient->errorString()));
    msgBox.exec();
}

void TcpClient::SL_readData()
{
    QByteArray buffer = tcpClient->readAll();
    if(!buffer.isEmpty())
    {
        emit SG_recvData(buffer);//接收的数据传到主界面
    }
}

void TcpClient::SL_sendData(QByteArray data)
{
    if(data != "")
    {
        tcpClient->write(data); //发送数据到服务端
    }
}
