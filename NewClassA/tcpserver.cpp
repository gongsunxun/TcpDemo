#include "tcpserver.h"

TcpServer::TcpServer()
{

}

void TcpServer::tcpServerInit(quint16 port)
{
    tcpServer = new QTcpServer();
    tcpServer->listen(QHostAddress::Any, port);           //开始监听客户端连接请求
    connect(tcpServer, SIGNAL(newConnection()), this, SLOT(SL_newConnection()));
}

/****************************有新的客户端连接***********************************/
void TcpServer::SL_newConnection()
{
    currentClient = tcpServer->nextPendingConnection();
    tcpClient.append(currentClient);
    connect(currentClient, SIGNAL(readyRead()), this, SLOT(SL_readData()));//接收数据
    connect(currentClient, SIGNAL(disconnected()), this, SLOT(SL_disConnected()));
}

/****************************有客户端断开连接***********************************/
void TcpServer::SL_disConnected()
{
    //由于disconnected信号并未提供SocketDescriptor，所以需要遍历寻找
    for(int i=0; i<tcpClient.length(); i++)
    {
        if(tcpClient[i]->state() == QAbstractSocket::UnconnectedState)
        {
            // 删除存储在tcpClient列表中的客户端信息
             tcpClient[i]->destroyed();
             tcpClient.removeAt(i);
        }
    }
}

/**********************读取数据***********************************/
void TcpServer::SL_readData()
{
    // 由于readyRead信号并未提供SocketDecriptor，所以需要遍历所有客户端
    for(int i=0; i<tcpClient.length(); i++)
    {
        QByteArray buffer = tcpClient[i]->readAll();
        if(!buffer.isEmpty())
        {
            emit SG_recvData(buffer);//接收的数据传到主界面
        }
    }
}

/*************************发送数据********************************/
void TcpServer::SL_sendData(QByteArray data)
{
    if(data == "")  //为空时
    {
        return;
    }
    for(int i=0; i<tcpClient.length(); i++)//发给所有客户端
    {
        tcpClient[i]->write(data); //发送数据
    }
}
