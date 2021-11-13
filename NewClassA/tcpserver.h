#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QObject>

#include <QTcpServer>
#include <QTcpSocket>
#include <QNetworkInterface>

class TcpServer:public QObject
{
    Q_OBJECT
public:
    TcpServer();
    void tcpServerInit(quint16);       //初始化监听(端口)
    QTcpServer *tcpServer;
    QTcpSocket *currentClient;
    QList<QTcpSocket*> tcpClient;

private slots:
    void SL_newConnection();    //有新的客户端连接
    void SL_disConnected();     //有客户端断开连接
    void SL_readData();         //从所有客户端读取数据

public slots:
    void SL_sendData(QByteArray);  //数据入口：给所有客户端发送数据
signals:
    void SG_recvData(QByteArray);  //数据出口：读取数据的数据传出
};

#endif // TCPSERVER_H
