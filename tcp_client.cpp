#include "main.h"

#include "testrawdata.h"

TCP_Client::TCP_Client(QObject *parent) : QObject(parent)
{
    port = PORT_TCP;
    ip = IP_SERVER;

//    tcp_socket = new QTcpSocket(this);

    udp_socket = new QUdpSocket(this);
//    QHostAddress address;
//    address.setAddress(ip);
//    udp_socket->bind(QHostAddress(ip), 8881);
//    udp_socket->bind(QHostAddress::LocalHost, 10001);

    connect(udp_socket, SIGNAL(readyRead()), SLOT(slot_readyRead()));

//    connect(tcp_socket, SIGNAL(connected()), SLOT(slot_connected()) );
//    connect(tcp_socket, SIGNAL(readyRead()), SLOT(slot_readyRead()));
//    connect(tcp_socket, SIGNAL(error(QAbstractSocket::SocketError)),
//            SLOT(slot_error(QAbstractSocket::SocketError)));
//    connect(tcp_socket, SIGNAL(disconnected()), SLOT(slot_disconnected()));

//    test_data = 0;


//    t_send_to_server = new QTimer(this);
//    connect(t_send_to_server, SIGNAL(timeout()), SLOT(slot_t_send_to_server_timeout()));

//    t_connectedState = new QTimer(this);
//    connect(t_connectedState, SIGNAL(timeout()), SLOT(slot_t_connectedState_timeout()));

//    connect(this, SIGNAL(signal_sendToServer()), SLOT(slot_sendToServer()));

}



TCP_Client::~TCP_Client()
{
//    tcp_socket->disconnectFromHost();
//    tcp_socket->waitForDisconnected();
//    tcp_socket->deleteLater();

    qDebug() << "~TCP_Client()";
}



//void TCP_Client::slot_connectToHost()
//{
////    t_send_to_server->start(3000);
//}



//void TCP_Client::slot_disconnectFromHost()
//{
//    t_send_to_server->stop();
//}




void TCP_Client::slot_readyRead()
{
    QByteArray bd;

    while (udp_socket->hasPendingDatagrams())
    {
        bd.resize(udp_socket->pendingDatagramSize());
        QHostAddress sender;
        quint16 senderPort;

        udp_socket->readDatagram(bd.data(), bd.size(),
                                &sender, &senderPort);

//        emit signal_write_to_log(make_hex_log_data("receive\n\r"));
//        emit signal_write_to_log(make_hex_log_data(bd));
        make_hex_log_data(bd);
    }


}


void TCP_Client::slot_error(QAbstractSocket::SocketError err)
{
    QString strError =
    "Error: " + (err == QAbstractSocket::HostNotFoundError ?
    "The host was not found." :
    err == QAbstractSocket::RemoteHostClosedError ?
    "The remote host is closed." :
    err == QAbstractSocket::ConnectionRefusedError ?
    "The connection was refused." :
    QString(udp_socket->errorString())
    );
    emit signal_write_to_log(strError.toLocal8Bit());

}




void TCP_Client::slot_sendToServer()
{
    QByteArray bd;

    bd = testrawdata.fromHex(testrawdata);

    udp_socket->writeDatagram(bd.data(), bd.length(), QHostAddress(ip), port);

//    emit signal_write_to_log(make_hex_log_data(bd));

}






//-----------------------------------------------------------------------------------//
//ѕереводим данные в видимый hex формат

/*QByteArray*/
void TCP_Client::make_hex_log_data(QByteArray data)
{
    QByteArray ba, bd;
    quint8 l, lenw;
    QDateTime date;

    while ((data.length() / 13) > 0)
    {
        bd.clear();
        // аждый пакет составл€ет 13 байт / делим на блоки по 13 байт
        ba = data.left(13).toHex();
        data.remove(0,13);

    //    ba.append(data.toHex());

        l = (ba.left(2).toInt()) & 0x0F;
        lenw = ba.length();
        for (int i=0; i < lenw; i++)
        {
            ba.insert(i*3, 0x20);
        }

        ba.insert(3, " _");
        ba.insert(17, " _");
        if (l < 8)
            ba.remove(20+3*l, 3*(8-l));

        bd.append(date.currentDateTime().toString("dd.MM.yyyy hh:mm:ss.zzz"));
        bd.append("          ");
        bd.append(ba);
//        bd.append("\r");

        emit signal_write_to_log(bd);
    }

//    return ba;
}







void TCP_Client::slot_t_send_to_server_timeout()
{
    emit signal_sendToServer();
}


//void TCP_Client::slot_t_connectedState_timeout()
//{
//    tcp_socket->disconnectFromHost();
//    t_connectedState->stop();
//    t_send_to_server->stop();
//}


