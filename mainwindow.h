#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QDir>
#include <QString>
#include <QDebug>
#include <QTimer>
#include "ui_mainwindow.h"
#include "tcp_client.h"

#define path_log_directory "../logs/"
#define log1_filename "can1.txt"
#define log2_filename "can2.txt"

#define PERIOD_CYCLE_SEND   1000        //msec

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

    void slot_showData1(QByteArray data);
    void slot_showData2(QByteArray data);
    void slot_writeLog1(QByteArray data);
    void slot_writeLog2(QByteArray data);

    void slot_timerCycle_timeout();
//    void slot_disconnected();

//    void on_pB_connect_clicked();

//    void on_pB_disconnect_clicked();

    void on_pB_set_clicked();
    void on_pB_stop_clicked();
    void on_pB_set_2_clicked();
    void on_pB_stop_2_clicked();

//    void on_pB_Send_clicked();

    void on_pB_send_1_clicked();
    void on_pB_send_3_clicked();

    void on_pB_send_2_clicked();
    void on_pB_send_5_clicked();


    void on_pB_send_10_clicked();
    void on_pB_send_14_clicked();


    void on_pB_set_3_clicked();
    void on_pB_set_4_clicked();

    void on_pB_clear_clicked();
    void on_pB_clear_2_clicked();

    void on_log1_button_clicked();
    void on_log2_button_clicked();

    void on_stopLog1_button_clicked();
    void on_stopLog2_button_clicked();

    void on_pB_stop_3_clicked();
    
private:
    TCP_Client *tcp_client;
    TCP_Client *tcp_client_2;
    bool allowLog1, allowLog2;
    QFile logFile1, logFile2;
    QTimer *timerCycle;

};

#endif // MAINWINDOW_H
