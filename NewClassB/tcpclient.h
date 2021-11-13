#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <QObject>
#include <QWidget>

#include <QTcpSocket>
#include <QHostAddress>
#include <QMessageBox>

class TcpClient : public QObject
{
    Q_OBJECT
public:
    TcpClient();
    void tcpClientInit(QString,quint16); //初始化连接(ip,端口)
    QTcpSocket *tcpClient;
    void SL_sendData(QByteArray);  //给服务端发送数据

private slots:
    void ReadError(QAbstractSocket::SocketError);
    void SL_readData();            //从服务端读取数据

signals:
    void SG_recvData(QByteArray);  //接收的数据传到主界面
};

#endif // TCPCLIENT_H
