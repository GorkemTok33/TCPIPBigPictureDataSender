/****************************************************************************************
Author: Görkem Tok
Language: C++
Platform: Qt Creator
Contact: ceng.gorkem.tok@gmail.com
License: MIT
****************************************************************************************/

#include "client.h"

client::client()
{
    socket = new QTcpSocket();
    connect(socket, SIGNAL(connected()), this, SLOT(connected()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()));
    connect(socket, SIGNAL(bytesWritten(qint64)), this, SLOT(bytesReaded(qint64)));
    connect(socket, SIGNAL(readyRead()), this, SLOT(readyReadData()));
    btn = nullptr;
    packetSize = 0;
}

void client::connectToServer(const QString hostAddress, const int port, QPushButton* btn)
{
    this->btn = btn;
    if(btn->text() == "Connect To Server")
        socket->connectToHost(hostAddress,port);
    else if(btn->text() == "Disconnect From Server")
        socket->close();
}

void client::readyReadData()
{
    if(packetSize == 0)
    {
        stream = new QDataStream(socket);
        stream->setVersion(QDataStream::Qt_5_9);
        progbarcounter += 5;
        emit updateProgressbar(progbarcounter);
        if((quint64)socket->bytesAvailable() < sizeof(quint32))
            return;

        *stream>>packetSize;
        emit updateMessageText(QString("Reading data... uint32: %1").arg(QString::number(packetSize)));
        free(stream);
    }

    if(packetSize > socket->bytesAvailable())
        return;

    arrayofdata = new QByteArray();
    *arrayofdata = socket->read(packetSize);
    progbarcounter = 100;
    emit updateProgressbar(progbarcounter);
    emit updateMessageText("Data successfully readed !");
    packetSize = 0;
}

void client::connected()
{
    btn->setText("Disconnect From Server");
    emit showMessageBox("Connected", "Connected to the server !", true);
}

void client::disconnected()
{
    btn->setText("Connect To Server");
    emit showMessageBox("Disconnected", "Disconnected from the server !", false);
}

void client::showData(QLabel *lbl)
{
    QImage image;
    QBuffer buffer(arrayofdata);
    buffer.open(QIODevice::ReadOnly);
    QImageReader imreader(&buffer, "PNG");
    image = imreader.read();
    if(!image.isNull())
        lbl->setPixmap(QPixmap::fromImage(image).scaled(lbl->size(),Qt::KeepAspectRatio));
    else
    {
        emit showMessageBox("Couldn't show image data", "Image data is corrupted !", false);
        emit updateMessageText("Data is corrupted !");
    }

    return;
}
