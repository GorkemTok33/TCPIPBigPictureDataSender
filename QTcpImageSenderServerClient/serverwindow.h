/****************************************************************************************
Author: Görkem Tok
Language: C++
Platform: Qt Creator
Contact: ceng.gorkem.tok@gmail.com
License: MIT
****************************************************************************************/

#ifndef SERVERWINDOW_H
#define SERVERWINDOW_H

#include <QDialog>
#include <QFile>
#include <QFileDialog>
#include <QImage>
#include <QMessageBox>
#include "server.h"
#include "choseclient.h"

namespace Ui {
class serverWindow;
}

class serverWindow : public QDialog
{
    Q_OBJECT

public:
    explicit serverWindow(QWidget *parent = nullptr);
    ~serverWindow();

signals:
     void startServer(QString,int,QPushButton*,QPushButton*);
     void acceptConnection();
     void declineConnection();
     void setData(QImage*);

private slots:
    void on_btnSelectFile_clicked();
    void on_btnSend_clicked();
    void on_btnStartServer_clicked();
    void showMessageBox(const QString,const QString, const bool);
    void newConnectionDetected(const QString, const QString);
    void updateProgressbar(const int value);
    void on_lineEditHostName_textEdited(const QString &arg1);
    void on_lineEditPortName_textEdited(const QString &arg1);

private:
    Ui::serverWindow *ui;
    server *SERVER;
    choseClient *CHOOSECLT;
    QImage *img;
    QPixmap *pixmap;
    QString *dataPath;
    QString *filter;

};

#endif // SERVERWINDOW_H
