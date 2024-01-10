#include "main.h"
#include <QValidator>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    setupUi(this);

    setWindowTitle("ECAN-E01S");

    txBr_log->document()->setMaximumBlockCount(2000);

    lE_Port->setValidator(new QIntValidator(1, 65535));
//    lE_time->setValidator(new QIntValidator());

    tcp_client = new TCP_Client(this);

    connect(tcp_client, SIGNAL(signal_write_to_log(QByteArray)),
            SLOT(slot_write_to_log(QByteArray)));
//    connect(this, SIGNAL(signal_connectToHost()),
//            tcp_client, SLOT(slot_connectToHost()));
//    connect(this, SIGNAL(signal_disconnectFromHost()),
//            tcp_client, SLOT(slot_disconnectFromHost()));

    connect(this, SIGNAL(signal_sendToServer()),
            tcp_client, SLOT(slot_sendToServer()));

    //connect(tcp_client, SIGNAL(signal_disconnected()), SLOT(slot_disconnected()));
}


MainWindow::~MainWindow()
{
    tcp_client->~TCP_Client();

    qDebug() << "~MainWindow()";
}



void MainWindow::slot_write_to_log(QByteArray data)
{
    txBr_log->append(QString(data));
}


//void MainWindow::on_pB_connect_clicked()
//{
//    lE_IP->setEnabled(false);
//    lE_Port->setEnabled(false);
//    lE_time->setEnabled(false);

//    emit signal_connectToHost();
//}


//void MainWindow::on_pB_disconnect_clicked()
//{
//    lE_IP->setEnabled(true);
//    lE_Port->setEnabled(true);
//    lE_time->setEnabled(true);

//    emit signal_disconnectFromHost();

//}



void MainWindow::on_pB_set_clicked()
{
    tcp_client->port = lE_Port->text().toInt();
    tcp_client->ip = lE_IP->text();

//    tcp_client->udp_socket->bind(tcp_client->port);
    tcp_client->udp_socket->disconnectFromHost();
    tcp_client->udp_socket->bind(QHostAddress(tcp_client->ip), tcp_client->port);

    qDebug() << tcp_client->ip << tcp_client->port;
}


void MainWindow::on_pB_stop_clicked()
{
    tcp_client->udp_socket->disconnectFromHost();

    qDebug() << "STOP" << tcp_client->ip << tcp_client->port;
}



//void MainWindow::on_pB_Send_clicked()
//{
//    emit signal_sendToServer();
//}


//void MainWindow::slot_disconnected()
//{
//    lE_IP->setEnabled(true);
//    lE_Port->setEnabled(true);
//    lE_time->setEnabled(true);
//}


