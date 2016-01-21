#include "serverwindow.h"

#include <QHBoxLayout>
#include <QTcpSocket>
#include <QDataStream>
#include <QBitArray>

#include <bitset>

using namespace std;

ServerWindow::ServerWindow(QWidget *parent) :
    QFrame(parent)
{
    m_textArea = new QTextEdit;
    m_textArea->setReadOnly(true);

    m_tcpServer = new QTcpServer(this);
    m_tcpServer->listen(QHostAddress::Any, 5001);

    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addWidget(m_textArea);

    setLayout(mainLayout);
    setFixedSize(400, 300);

    connect(m_tcpServer, &QTcpServer::newConnection, this, &ServerWindow::clientAccepted);
}

void ServerWindow::clientAccepted()
{
    qDebug() << "new connection";

    QTcpSocket *socket = m_tcpServer->nextPendingConnection();

    connect(socket, &QTcpSocket::disconnected, socket, &QTcpSocket::deleteLater);
    connect(socket, &QTcpSocket::readyRead, this, &ServerWindow::reayReadData);
}

void ServerWindow::reayReadData()
{
    QTcpSocket *socket = qobject_cast<QTcpSocket *>(sender());
    if (!socket)
        return;

    QByteArray data = socket->readAll();
    QDataStream ds(&data, QIODevice::ReadOnly);
    QBitArray bits;
    ds >> bits;

//    QDataStream ds(&data, QIODevice::ReadOnly);

//    qDebug() << data;


    Des des;
    des.key = des.charToBitset("12345678");
    des.generateKeys();

//    const char *s = data.toStdString().c_str();

//    bitset<64> bits;
//    for(int i=0; i<8; ++i)
//        for(int j=0; j<8; ++j)
//            bits[i*8+j] = (((s[i] & 0xff)>>j) & 0x1);

//    qDebug() << "datas: " << (char*)&bits;

    bitset<64> decode;
    for (int i = 0; i != 64; ++i)
    {
        decode[i] = bits[i];
        qDebug() << decode[i];
    }
    QString raw;
    for (int i = 0; i != 8; ++i)
    {
        raw += ((char*)&decode)[i];
    }

    qDebug() << "decode: " << (char*)&decode;
    decode = des.decrypt(decode);
    qDebug() << "decode: " << (char*)&decode;

    QString res;
    for (int i = 0; i != 8; ++i)
    {
        res += ((char*)&decode)[i];
    }


    m_textArea->append("recv: " + raw);
    m_textArea->append("decode: " + res);
}

