#ifndef CLIENTWINDOW_H
#define CLIENTWINDOW_H

#include "../common/des.h"

#include <QFrame>
#include <QLineEdit>
#include <QPushButton>
#include <QTcpSocket>

class ClientWindow : public QFrame
{
    Q_OBJECT

public:
    explicit ClientWindow(QWidget *parent = nullptr);

private:
    void sendData();
    void receiveData();
    const QBitArray getData();

private:
    QLineEdit *m_userName;
    QLineEdit *m_password;
    QPushButton *m_sendButton;
    QTcpSocket *m_socket;

    Des *m_des;
};

#endif // CLIENTWINDOW_H
