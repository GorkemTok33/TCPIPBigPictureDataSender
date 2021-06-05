/****************************************************************************************
Author: Görkem Tok
Language: C++
Platform: Qt Creator
Contact: ceng.gorkem.tok@gmail.com
License: MIT
****************************************************************************************/

#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QDataStream>
#include <QPushButton>
#include <QVector>
#include <QBuffer>
#include <QByteArray>
#include <QImageWriter>
#include "socket.h"

class server: public QObject
{
    Q_OBJECT
public:
    server();

signals:
    void sendData_();
    void newConnectionDetected(const QString, const QString);
    void startedServer_();
    void stoppedServer_();
    void updateProgressbar(const int);
    void showMessageBox(const QString, const QString, const bool);

public slots:
    void startServer(QString,int,QPushButton*,QPushButton*);
    void setData(QImage*);
    void newConnection();
    void acceptConnection();
    void declineConnection();
    void setReceiverClient(const int);

public:
    QList<int> *getClients();

private:
    QVector<socket*> *sockets;
    QList<int> *tempClients;
    QTcpServer *Server;
    QTcpSocket *tempSocket;
    QBuffer *buffer;
    QByteArray *bytearray;
    QDataStream *stream;
    QImageWriter *imwriter;
    QImage *image;
    socket *SOCKET;
    int idCounter;
    int receiverID;
    void sendData();
};

#endif // SERVER_H
