/****************************************************************************************
Author: Görkem Tok
Language: C++
Platform: Qt Creator
Contact: ceng.gorkem.tok@gmail.com
License: MIT
****************************************************************************************/

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("TCP/IP Big Data Sender Demo");
    this->serverwindow = nullptr;
    this->clientwindow = nullptr;
    connect(this, SIGNAL(openserver()),SLOT(initserver()));
    connect(this, SIGNAL(openclient()),SLOT(initclient()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initserver()
{
    if(serverwindow == nullptr)
        serverwindow = new serverWindow(this);
    serverwindow->show();
}

void MainWindow::initclient()
{
    if(clientwindow == nullptr)
        clientwindow = new clientWindow(this);
    clientwindow->show();
}


void MainWindow::on_pushButton_clicked()
{
    emit openserver();
}

void MainWindow::on_pushButton_2_clicked()
{
    emit openclient();
}
