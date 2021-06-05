/****************************************************************************************
Author: Görkem Tok
Language: C++
Platform: Qt Creator
Contact: ceng.gorkem.tok@gmail.com
License: MIT
****************************************************************************************/

#include "serverwindow.h"
#include "ui_serverwindow.h"

serverWindow::serverWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::serverWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("TCP/IP Big Picture Data Sender - SERVER");
    SERVER = new server();
    CHOOSECLT = nullptr;
    img = nullptr;
    connect(this, SIGNAL(startServer(QString,int,QPushButton*,QPushButton*)), SERVER, SLOT(startServer(QString,int,QPushButton*,QPushButton*)));
    connect(this,SIGNAL(acceptConnection()),SERVER,SLOT(acceptConnection()));
    connect(this,SIGNAL(declineConnection()),SERVER,SLOT(declineConnection()));
    connect(this,SIGNAL(setData(QImage*)),SERVER,SLOT(setData(QImage*)));
    connect(SERVER,SIGNAL(newConnectionDetected(const QString, const QString)),this,SLOT(newConnectionDetected(const QString, const QString)));
    connect(SERVER,SIGNAL(showMessageBox(const QString, const QString, const bool)),this,SLOT(showMessageBox(const QString, const QString, const bool)));
    connect(SERVER,SIGNAL(updateProgressbar(const int)),this,SLOT(updateProgressbar(const int)));
    ui->lineEditFileLocation->setEnabled(false);
    ui->btnSend->setEnabled(false);
    ui->lineEditPortName->setValidator(new QIntValidator(0,9999));
    this->dataPath = nullptr;
    this->filter = new QString();
    *filter = "Picture Files *.jpg *.jpeg *.png *.bmp";
}

serverWindow::~serverWindow()
{
    delete ui;
}

void serverWindow::on_btnSelectFile_clicked()
{
    if(dataPath == nullptr)
        dataPath = new QString();

    *dataPath = QFileDialog::getOpenFileName(this, "Select picture you want to send to the client app !",
                                 "Pictures",*filter);
    if(*dataPath != "")
    {
        img = new QImage(*dataPath);

        if(!img->isNull())
        {
            emit setData(img);
            ui->lineEditFileLocation->setText(*dataPath);
            ui->lblPictureData->setPixmap(QPixmap::fromImage(*img).scaled(ui->lblPictureData->size(), Qt::KeepAspectRatio));
            ui->btnSend->setEnabled(true);
        }

        else
        {
            QMessageBox::warning(this,"Image Read Error", "Couldn't read image data from file");
            free(img);
        }
    }
}



void serverWindow::on_btnSend_clicked()
{
    updateProgressbar(0);
    if(img == nullptr)
    {
        QMessageBox::warning(this,"Couldn't found picture data","Your current picture data is empty, please select picture file !");
        return;
    }

    if(CHOOSECLT == nullptr)
    {
        CHOOSECLT = new choseClient(this);
        connect(CHOOSECLT,SIGNAL(setReceiverClient(const int)),SERVER,SLOT(setReceiverClient(const int)));
    }
    CHOOSECLT->updateClients(SERVER->getClients());
    CHOOSECLT->show();
}

void serverWindow::on_btnStartServer_clicked()
{
    emit startServer(ui->lineEditHostName->text(), ui->lineEditPortName->text().toInt(), ui->btnStartServer, ui->btnSend);
}

void serverWindow::showMessageBox(const QString title, const QString message, const bool positive)
{
    if(positive)
        QMessageBox::information(this,title,message);
    else
        QMessageBox::warning(this,title,message);

    return;
}

void serverWindow::newConnectionDetected(const QString title, const QString message)
{
    QMessageBox msgBox;
    msgBox.setWindowTitle(title);
    msgBox.setText(message);
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    int result = msgBox.exec();
    switch(result)
    {
    case QMessageBox::Yes:
        qDebug()<<"Accept conn";
        emit acceptConnection();
        break;

    case QMessageBox::No:
        qDebug()<<"Decline conn";
        emit declineConnection();
        break;
    }
}

void serverWindow::updateProgressbar(const int value)
{
    ui->progbarSending->setValue(value);
}

void serverWindow::on_lineEditHostName_textEdited(const QString &arg1)
{
    if(arg1 == "" || ui->lineEditPortName->text() == "")
        ui->btnStartServer->setEnabled(false);
    else
        ui->btnStartServer->setEnabled(true);
}

void serverWindow::on_lineEditPortName_textEdited(const QString &arg1)
{
    if(arg1 == "" || ui->lineEditHostName->text() == "")
        ui->btnStartServer->setEnabled(false);
    else
        ui->btnStartServer->setEnabled(true);
}
