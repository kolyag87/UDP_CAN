#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ui_mainwindow.h"

#include "tcp_client.h"



class MainWindow : public QMainWindow, Ui::MainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


signals:
//    void signal_connectToHost();
//    void signal_disconnectFromHost();
    void signal_sendToServer();

private slots:

    void slot_write_to_log(QByteArray data);

//    void slot_disconnected();

//    void on_pB_connect_clicked();

//    void on_pB_disconnect_clicked();

    void on_pB_set_clicked();
    void on_pB_stop_clicked();

//    void on_pB_Send_clicked();

private:
    TCP_Client *tcp_client;
    TCP_Client *tcp_client_2;

};

#endif // MAINWINDOW_H
