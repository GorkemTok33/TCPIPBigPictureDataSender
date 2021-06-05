/****************************************************************************************
Author: Görkem Tok
Language: C++
Platform: Qt Creator
Contact: ceng.gorkem.tok@gmail.com
License: MIT
****************************************************************************************/

#ifndef SOCKET_H
#define SOCKET_H

#include <QTcpSocket>
#include <QAbstractSocket>
#include <QObject>
#include <QByteArray>
#include <QDataStream>

class socket:public QObject
{
    Q_OBJECT

public:
    socket(QTcpSocket *socket, const int id);
    int getID();
    void writeData(QByteArray *arrayofdata);

private slots:
    void connected();
    void disconnected();

private:
    QTcpSocket *SOCKET;
    quint32 sizeOfData;
    int id;
};

#endif // SOCKET_H
