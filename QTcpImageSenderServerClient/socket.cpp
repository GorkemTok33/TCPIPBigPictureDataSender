/****************************************************************************************
Author: Görkem Tok
Language: C++
Platform: Qt Creator
Contact: ceng.gorkem.tok@gmail.com
License: MIT
****************************************************************************************/

#include "socket.h"

socket::socket(QTcpSocket *socket, const int id)
{
    SOCKET = socket;
    this->id = id;
    sizeOfData = 0;
    connect(SOCKET, SIGNAL(connected()), this, SLOT(connected()));
    connect(SOCKET, SIGNAL(disconnected()), this, SLOT(disconnected()));
}

int socket::getID()
{
    return id;
}

void socket::writeData(QByteArray *arrayofdata)
{
    SOCKET->write(*arrayofdata);
    SOCKET->waitForBytesWritten(3000);
}

void socket::connected()
{

}

void socket::disconnected()
{

}


