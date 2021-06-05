/****************************************************************************************
Author: Görkem Tok
Language: C++
Platform: Qt Creator
Contact: ceng.gorkem.tok@gmail.com
License: MIT
****************************************************************************************/

#include "clientwindow.h"
#include "ui_clientwindow.h"

clientWindow::clientWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::clientWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("TCP/IP Big Picture Data Sender - CLIENT");
    CLIENT = new client();
    connect(this, SIGNAL(connectToServer(const QString, const int, QPushButton*)), CLIENT, SLOT(connectToServer(const QString, const int, QPushButton*)));
    connect(this,SIGNAL(showData(QLabel *)),CLIENT,SLOT(showData(QLabel *)));
    connect(CLIENT,SIGNAL(showMessageBox(const QString, const QString, const bool)),this,SLOT(showMessageBox(const QString, const QString, const bool)));
    connect(CLIENT,SIGNAL(updateProgressbar(int&)), this, SLOT(updateProgressbar(int&)));
    connect(CLIENT,SIGNAL(updateMessageText(const QString)),this,SLOT(updateMessageText(const QString)));
    ui->lineEditPort->setValidator(new QIntValidator(0,9999));
}

clientWindow::~clientWindow()
{
    delete ui;
}

void clientWindow::on_btnConnect_clicked()
{
    emit connectToServer(ui->lineEditHostName->text(), ui->lineEditPort->text().toInt(),ui->btnConnect);
}

void clientWindow::updateProgressbar(int &value)
{
    ui->progbarData->setValue(value);
}

void clientWindow::showMessageBox(const QString title, const QString message, const bool positive)
{
    if(positive)
        QMessageBox::information(this,title,message);
    else
        QMessageBox::warning(this,title,message);

    return;
}

void clientWindow::updateMessageText(const QString message)
{
    ui->labelMessage->setText(message);
}

void clientWindow::on_btnShowdata_clicked()
{
    emit showData(ui->labelPicture);
}

void clientWindow::on_lineEditHostName_textEdited(const QString &arg1)
{
    if(arg1 == "" || ui->lineEditPort->text() == "")
        ui->btnConnect->setEnabled(false);
    else
        ui->btnConnect->setEnabled(true);
}

void clientWindow::on_lineEditPort_textEdited(const QString &arg1)
{
    if(arg1 == "" || ui->lineEditHostName->text() == "")
        ui->btnConnect->setEnabled(false);
    else
        ui->btnConnect->setEnabled(true);
}
