/****************************************************************************************
Author: Görkem Tok
Language: C++
Platform: Qt Creator
Contact: ceng.gorkem.tok@gmail.com
License: MIT
****************************************************************************************/

#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QAbstractSocket>
#include <QDataStream>
#include <QByteArray>
#include <QPushButton>
#include <QLabel>
#include <QImageReader>
#include <QBuffer>

class client:public QObject
{
    Q_OBJECT
public:
    client();

signals:
    void updateMessage(QString&);
    void updatePixmap(QPixmap&);
    void updateBtntext(QString&);
    void updateProgressbar(int&);
    void showMessageBox(const QString, const QString, const bool);
    void updateMessageText(const QString);

public slots:
    void connectToServer(const QString, const int, QPushButton* btn);
    void showData(QLabel *);

private slots:
    void readyReadData();
    void connected();
    void disconnected();

private:
    QTcpSocket *socket;
    QPushButton *btn;
    quint32 packetSize;
    QDataStream *stream;
    QByteArray *arrayofdata;
    int progbarcounter;
};

#endif // CLIENT_H
