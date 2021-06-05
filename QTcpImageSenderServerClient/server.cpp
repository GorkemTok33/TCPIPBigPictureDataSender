/****************************************************************************************
Author: Görkem Tok
Language: C++
Platform: Qt Creator
Contact: ceng.gorkem.tok@gmail.com
License: MIT
****************************************************************************************/


#include "server.h"

server::server()
{
    Server = new QTcpServer();
    tempClients = new QList<int>();
    connect(Server, SIGNAL(newConnection()),this,SLOT(newConnection()));
    sockets = new QVector<socket*>();
    idCounter = 0;
    receiverID = 0;
    image = nullptr;
}

void server::startServer(QString hostAddress, int port, QPushButton *btn,QPushButton* btnsend)
{
    btn->setEnabled(false);

    if(btn->text() == "Start Server")
    {
        Server->listen(QHostAddress(hostAddress),port);
        if(!Server->isListening())
        {
            emit showMessageBox("Couldn't start server !","Couldn't start server on \nhost: "+hostAddress+", Port: "+QString::number(port), false);
            btn->setText("Start Server");
            btn->setEnabled(true);
            btnsend->setEnabled(false);
            return;
        }

        emit showMessageBox("Server Started !","Server is listening on \nhost: "+hostAddress+", Port: "+QString::number(port), true);
        btn->setText("Stop Server");
        btn->setEnabled(true);
        btnsend->setEnabled(true);
    }

    else
    {
        Server->close();
        emit showMessageBox("Server Closed !","Server stopped listening !", true);
        btn->setText("Start Server");
        btnsend->setEnabled(true);
    }
}

void server::setData(QImage *image)
{
    this->image = image;
}

void server::sendData()
{
    emit updateProgressbar(15);
    socket *tempSocket = nullptr;

    for(int i = 0; i <sockets->size(); i++)
    {
        if(sockets->at(i)->getID() == receiverID)
        {
            emit(updateProgressbar(30));
            tempSocket = sockets->at(i);
            break;
        }
    }
    emit updateProgressbar(45);
    if(tempSocket != nullptr)
    {
        buffer = new QBuffer(this);
        bytearray = new QByteArray();
        emit updateProgressbar(60);
        imwriter = new QImageWriter(buffer, "PNG");
        imwriter->write(*image);
        stream = new QDataStream(bytearray,QIODevice::WriteOnly);
        stream->setVersion(QDataStream::Qt_5_9);
        emit updateProgressbar(80);
        *stream<<(quint32)buffer->data().size();
        bytearray->append(buffer->data());
        tempSocket->writeData(bytearray);
        free(buffer);
        free(bytearray);
        free(imwriter);
        free(stream);
        emit updateProgressbar(100);
        emit showMessageBox("Action Successfully Completed!","Data sucessfully writed to receiver client", true);
        return;
    }

    emit updateProgressbar(0);
    emit showMessageBox("Couldn't send data !","Couldn't found receiver client from id !", false);
    return;
}

void server::newConnection()
{
    tempSocket = Server->nextPendingConnection();
    emit newConnectionDetected("New connection detected !","Do you want to accept connection ?");
}

void server::acceptConnection()
{
    SOCKET = new socket(tempSocket,idCounter);
    sockets->push_back(SOCKET);
    tempClients->push_back(idCounter);
    idCounter++;
}

void server::declineConnection()
{
    tempSocket->write("Server declined request !");
    tempSocket->waitForBytesWritten(2000);
    tempSocket->close();
    free(tempSocket);
}

void server::setReceiverClient(const int id)
{
    receiverID = id;
    sendData();
}

QList<int>* server::getClients()
{
    return tempClients;
}
