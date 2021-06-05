/****************************************************************************************
Author: Görkem Tok
Language: C++
Platform: Qt Creator
Contact: ceng.gorkem.tok@gmail.com
License: MIT
****************************************************************************************/

#include "choseclient.h"
#include "ui_choseclient.h"

choseClient::choseClient(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::choseClient)
{
    ui->setupUi(this);
    this->setWindowTitle("Choose Receiver Client");
}

void choseClient::updateClients(QList<int> *clients)
{
    this->clients = clients;
    initListwidget();
}

choseClient::~choseClient()
{
    delete ui;
}

void choseClient::initListwidget()
{
    ui->listWidgetClients->clear();

    foreach(const int id, *clients)
    {
        ui->listWidgetClients->addItem("client "+QString::number(id));
    }
}

void choseClient::on_listWidgetClients_itemClicked(QListWidgetItem *item)
{
    ui->lblSelected->setText(QString("Selected client: %1").arg(item->text()));
}

void choseClient::on_btnSelect_clicked()
{
    emit setReceiverClient(ui->listWidgetClients->selectionModel()->currentIndex().row());
    this->close();
}
