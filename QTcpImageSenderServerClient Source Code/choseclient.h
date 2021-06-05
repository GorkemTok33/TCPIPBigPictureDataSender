/****************************************************************************************
Author: Görkem Tok
Language: C++
Platform: Qt Creator
Contact: ceng.gorkem.tok@gmail.com
License: MIT
****************************************************************************************/

#ifndef CHOSECLIENT_H
#define CHOSECLIENT_H

#include <QDialog>
#include <QList>
#include <QListWidgetItem>

namespace Ui {
class choseClient;
}

class choseClient : public QDialog
{
    Q_OBJECT

public:
    explicit choseClient(QWidget *parent = nullptr);
    void updateClients(QList<int> *clients);
    ~choseClient();

signals:
    void setReceiverClient(const int);

private slots:
    void on_listWidgetClients_itemClicked(QListWidgetItem *item);
    void on_btnSelect_clicked();

private:
    Ui::choseClient *ui;
    QList<int> *clients;
    void initListwidget();
};

#endif // CHOSECLIENT_H
