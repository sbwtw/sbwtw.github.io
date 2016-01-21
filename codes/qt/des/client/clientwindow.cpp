#include "clientwindow.h"

#include <QVBoxLayout>
#include <QDataStream>
#include <QFile>
#include <QBitArray>

#include <bitset>
#include <iostream>
#include <fstream>
#include <sstream>

ClientWindow::ClientWindow(QWidget *parent) :
    QFrame(parent)
{
    m_userName = new QLineEdit;
    m_password = new QLineEdit;
    m_password->setEchoMode(QLineEdit::Password);
    m_sendButton = new QPushButton;
    m_sendButton->setText("Send");
    m_socket = new QTcpSocket(this);
    m_socket->connectToHost("localhost", 5001);
    m_des = new Des;

    QVBoxLayout *vLayout = new QVBoxLayout;
    vLayout->addStretch();
    vLayout->addWidget(m_userName);
    vLayout->addWidget(m_password);
    vLayout->addStretch();

    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addStretch();
    mainLayout->addLayout(vLayout);
    mainLayout->addWidget(m_sendButton);
    mainLayout->addStretch();

    setLayout(mainLayout);
    setFixedSize(400, 300);

    connect(m_sendButton, &QPushButton::clicked, this, &ClientWindow::sendData);
    connect(m_socket, &QTcpSocket::readyRead, this, &ClientWindow::receiveData);

}

void ClientWindow::sendData()
{
//    qDebug() << getData().toLocal8Bit();

    QBitArray data = getData();
    QByteArray buf;
    QDataStream ds(&buf, QIODevice::WriteOnly);
    ds << data;

//    qDebug() << "data: " << data.toStdString().c_str();

    qDebug() << "write: " << m_socket->write(buf);
    m_socket->waitForBytesWritten();

}

void ClientWindow::receiveData()
{
    QTcpSocket *socket = qobject_cast<QTcpSocket *>(sender());
    if (!socket)
        return;

    qDebug() << socket->readAll();
}

const QBitArray ClientWindow::getData()
{

    Des des;

    des.key = des.charToBitset("12345678");
    des.generateKeys();
    bitset<64> data = des.charToBitset(m_password->text().toStdString().c_str());
    bitset<64> encode = des.encrypt(data);

    qDebug() << "encode: " << (char *)&encode;

//    bitset<64> decode = des.decrypt(encode);
//    qDebug() << "decode: " << (char *)&decode;


//    QByteArray buf;
//    QDataStream ds(&buf, QIODevice::WriteOnly);
//    ds.writeBytes(name.toStdString().c_str(), name.size());
//    ds.writeBytes(",", 1);
//    ds.writeBytes((char*)(&encode), sizeof(encode));

    QBitArray buf(64);

    for (int i = 0; i != 64; ++i)
    {
        buf[i] = (int)encode[i];
        qDebug() << (int)buf[i] << encode[i];
    }
    qDebug() << "========";
//    qDebug() << "encode: " << (char *)&encode;
//    qDebug() << "buf: " << buf;

//    Des dec;
//    dec.key = dec.charToBitset("12345678");
//    dec.generateKeys();

//    std::istringstream bits(buf.toStdString());
//    bitset<64> pla;
//    bits >> pla;
//    qDebug() << "pla: " << (char*)&pla;
//    pla << bits;
//    bitset<64> decode = dec.decrypt(pla);

//    qDebug() << "decode: " << (char*)&decode;

    return buf;
}

