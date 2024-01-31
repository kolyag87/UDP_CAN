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
    void signal_sendToServer(QByteArray dt);

private slots:

    void slot_write_to_log(QByteArray data);
    void slot_write_to_log_2(QByteArray data);
//    void slot_disconnected();

//    void on_pB_connect_clicked();

//    void on_pB_disconnect_clicked();

    void on_pB_set_clicked();
    void on_pB_stop_clicked();
    void on_pB_set_2_clicked();
    void on_pB_stop_2_clicked();

//    void on_pB_Send_clicked();

    void on_pB_send_1_clicked();

    void on_pB_send_2_clicked();

    void on_pB_send_10_clicked();

    void on_pB_set_3_clicked();


    void on_pB_clear_clicked();
    void on_pB_clear_2_clicked();

private:
    TCP_Client *tcp_client;
    TCP_Client *tcp_client_2;

};

#endif // MAINWINDOW_H
