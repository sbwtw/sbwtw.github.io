#ifndef SERVERWINDOW_H
#define SERVERWINDOW_H

#include "../common/des.h"

#include <QFrame>
#include <QTextEdit>
#include <QTcpServer>

class ServerWindow : public QFrame
{
public:
    explicit ServerWindow(QWidget *parent = nullptr);

private:
    void clientAccepted();
    void reayReadData();

private:
    QTextEdit *m_textArea;
    QTcpServer *m_tcpServer;
};

#endif // SERVERWINDOW_H
