/****************************************************************************************
Author: Görkem Tok
Language: C++
Platform: Qt Creator
Contact: ceng.gorkem.tok@gmail.com
License: MIT
****************************************************************************************/

#ifndef CLIENTWINDOW_H
#define CLIENTWINDOW_H

#include <QDialog>
#include "client.h"
#include <QMessageBox>

namespace Ui {
class clientWindow;
}

class clientWindow : public QDialog
{
    Q_OBJECT

public:
    explicit clientWindow(QWidget *parent = nullptr);
    ~clientWindow();

signals:
    void connectToServer(const QString, const int, QPushButton*);
    void showData(QLabel *);

private slots:
    void on_btnConnect_clicked();
    void updateProgressbar(int&);
    void showMessageBox(const QString, const QString, const bool);
    void updateMessageText(const QString);
    void on_btnShowdata_clicked();

    void on_lineEditHostName_textEdited(const QString &arg1);

    void on_lineEditPort_textEdited(const QString &arg1);

private:
    Ui::clientWindow *ui;
    client *CLIENT;
};

#endif // CLIENTWINDOW_H
