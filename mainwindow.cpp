#include "main.h"
#include <QValidator>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    setupUi(this);

    setWindowTitle("ECAN-E01S");

    QDir logDir(path_log_directory);
    if(logDir.exists())
        qDebug() << "log directory is exist yet...";
    else
        logDir.mkdir(path_log_directory);

    QString path_logDir = path_log_directory;
    QString log1Filename = log1_filename;
    QString log2Filename = log2_filename;
    log1_path->setText(path_logDir + log1Filename);
    log2_path->setText(path_logDir + log2Filename);
    allowLog1 = false;
    allowLog2 = false;

    txBr_log->document()->setMaximumBlockCount(2000);

    lE_Port->setValidator(new QIntValidator(1, 65535));
//    lE_time->setValidator(new QIntValidator());

    tcp_client = new TCP_Client(this);
    tcp_client_2 = new TCP_Client(this);

    connect(tcp_client, SIGNAL(signal_showData(QByteArray)),
            SLOT(slot_showData1(QByteArray)));
    connect(tcp_client_2, SIGNAL(signal_showData(QByteArray)),
            SLOT(slot_showData2(QByteArray)));

    connect(tcp_client, SIGNAL(signal_writeLog(QByteArray)),
            SLOT(slot_writeLog1(QByteArray)));
    connect(tcp_client_2, SIGNAL(signal_writeLog(QByteArray)),
            SLOT(slot_writeLog2(QByteArray)));

    connect(this, SIGNAL(signal_sendToServer(QByteArray)),
            tcp_client, SLOT(slot_sendToServer(QByteArray)));
    connect(this, SIGNAL(signal_sendToServer(QByteArray)),
            tcp_client_2, SLOT(slot_sendToServer(QByteArray)));

    //connect(tcp_client, SIGNAL(signal_disconnected()), SLOT(slot_disconnected()));
}


MainWindow::~MainWindow()
{
    tcp_client->~TCP_Client();
    tcp_client_2->~TCP_Client();
    qDebug() << "~MainWindow()";
}



void MainWindow::slot_showData1(QByteArray data)
{
    txBr_log->append(QString(data));
}

void MainWindow::slot_showData2(QByteArray data)
{
    txBr_log_2->append(QString(data));
}


void MainWindow::on_pB_clear_clicked()
{
    txBr_log->clear();
}

void MainWindow::on_log1_button_clicked()
{
    QString path = log1_path->text();

    logFile1.setFileName(path);
    if(logFile1.exists())
        logFile1.remove();

    if(logFile1.open(QFile::ReadWrite | QFile::Text) == false)
        qDebug() << "file " << path << " does not open...";
    else
        allowLog1  = true;
}

void MainWindow::slot_writeLog1(QByteArray data)
{
    if(allowLog1 == true)
    {
        logFile1.write(data + "\r\n");
    }
}


void MainWindow::on_stopLog1_button_clicked()
{
    allowLog1 = false;
    logFile1.close();
}

void MainWindow::on_log2_button_clicked()
{
    QString path = log2_path->text();

    logFile2.setFileName(path);
    if(logFile2.exists())
        logFile2.remove();

    if(logFile2.open(QFile::ReadWrite | QFile::Text) == false)
        qDebug() << "file " << path << " does not open...";
    else
        allowLog2 = true;
}

void MainWindow::slot_writeLog2(QByteArray data)
{
    if(allowLog2 == true)
    {
        logFile2.write(data + "\r\n");
    }
}

void MainWindow::on_stopLog2_button_clicked()
{
    allowLog2 = false;
    logFile2.close();
}

void MainWindow::on_pB_clear_2_clicked()
{
    txBr_log_2->clear();
}

void MainWindow::on_pB_set_clicked()
{
    tcp_client->port = lE_Port->text().toInt();
    tcp_client->ip = lE_IP->text();
    tcp_client->udp_socket->disconnectFromHost();
    tcp_client->udp_socket->bind(QHostAddress(tcp_client->ip), tcp_client->port);

    qDebug() << tcp_client->ip << tcp_client->port;
}

void MainWindow::on_pB_set_2_clicked()
{
    tcp_client_2->port = lE_Port_2->text().toInt();
    tcp_client_2->ip = lE_IP_2->text();
    tcp_client_2->udp_socket->disconnectFromHost();
    tcp_client_2->udp_socket->bind(QHostAddress(tcp_client_2->ip), tcp_client_2->port);

    qDebug() << tcp_client_2->ip << tcp_client_2->port;
}


void MainWindow::on_pB_stop_clicked()
{
    tcp_client->udp_socket->disconnectFromHost();

    qDebug() << "STOP" << tcp_client->ip << tcp_client->port;
}

void MainWindow::on_pB_stop_2_clicked()
{
    tcp_client_2->udp_socket->disconnectFromHost();

    qDebug() << "STOP" << tcp_client_2->ip << tcp_client_2->port;
}


void MainWindow::on_pB_set_3_clicked()
{
    tcp_client->portSend = lE_Port_3->text().toInt();
    tcp_client->ipSend = lE_IP_3->text();
}


void MainWindow::on_pB_send_1_clicked()
{
    QByteArray bd;

    quint8 bt = 0;

    //Заполняем 0
//    bd.fill(0, 8);

    if (chB_extID_1->checkState() == Qt::Checked)
        bt |= (1<<7);               //Ext ID
    bt |= lE_DLC_1->text().toInt();
    bd.append(bt);

//    quint32 id = lE_ID_1->text().toUtf8();
    bd.append(QByteArray::fromHex(lE_ID_1->text().toUtf8()));

    bd.insert(5, 8, 0);

    quint8 dlc = lE_DLC_1->text().toInt();
    if (dlc > 0)
    {
        bd.replace(5, 1, QByteArray::fromHex(lE_D0_1->text().toUtf8()));
        dlc--;
    }
    if (dlc > 0)
    {
        bd.replace(6, 1, QByteArray::fromHex(lE_D1_1->text().toUtf8()));
        dlc--;
    }
    if (dlc > 0)
    {
        bd.replace(7, 1, QByteArray::fromHex(lE_D2_1->text().toUtf8()));
        dlc--;
    }
    if (dlc > 0)
    {
        bd.replace(8, 1, QByteArray::fromHex(lE_D3_1->text().toUtf8()));
        dlc--;
    }
    if (dlc > 0)
    {
        bd.replace(9, 1, QByteArray::fromHex(lE_D4_1->text().toUtf8()));
        dlc--;
    }
    if (dlc > 0)
    {
        bd.replace(10, 1, QByteArray::fromHex(lE_D5_1->text().toUtf8()));
        dlc--;
    }
    if (dlc > 0)
    {
        bd.replace(11, 1, QByteArray::fromHex(lE_D6_1->text().toUtf8()));
        dlc--;
    }
    if (dlc > 0)
    {
        bd.replace(12, 1, QByteArray::fromHex(lE_D7_1->text().toUtf8()));
        dlc--;
    }

    emit signal_sendToServer(bd);

    qDebug() << bt << dlc << bd;

}


void MainWindow::on_pB_send_2_clicked()
{
    QByteArray bd;

    quint8 bt = 0;

    //Заполняем 0
//    bd.fill(0, 8);

    if (chB_extID_2->checkState() == Qt::Checked)
        bt |= (1<<7);               //Ext ID
    bt |= lE_DLC_2->text().toInt();
    bd.append(bt);

//    quint32 id = lE_ID_1->text().toUtf8();
    bd.append(QByteArray::fromHex(lE_ID_2->text().toUtf8()));

    bd.insert(5, 8, 0);

    quint8 dlc = lE_DLC_2->text().toInt();
    if (dlc > 0)
    {
        bd.replace(5, 1, QByteArray::fromHex(lE_D0_2->text().toUtf8()));
        dlc--;
    }
    if (dlc > 0)
    {
        bd.replace(6, 1, QByteArray::fromHex(lE_D1_2->text().toUtf8()));
        dlc--;
    }
    if (dlc > 0)
    {
        bd.replace(7, 1, QByteArray::fromHex(lE_D2_2->text().toUtf8()));
        dlc--;
    }
    if (dlc > 0)
    {
        bd.replace(8, 1, QByteArray::fromHex(lE_D3_2->text().toUtf8()));
        dlc--;
    }
    if (dlc > 0)
    {
        bd.replace(9, 1, QByteArray::fromHex(lE_D4_2->text().toUtf8()));
        dlc--;
    }
    if (dlc > 0)
    {
        bd.replace(10, 1, QByteArray::fromHex(lE_D5_2->text().toUtf8()));
        dlc--;
    }
    if (dlc > 0)
    {
        bd.replace(11, 1, QByteArray::fromHex(lE_D6_2->text().toUtf8()));
        dlc--;
    }
    if (dlc > 0)
    {
        bd.replace(12, 1, QByteArray::fromHex(lE_D7_2->text().toUtf8()));
        dlc--;
    }

    emit signal_sendToServer(bd);

    qDebug() << bt << dlc << bd;

}


void MainWindow::on_pB_send_10_clicked()
{
    QByteArray bd;

    quint8 bt = 0;

    //Заполняем 0
//    bd.fill(0, 8);

    if (chB_extID_10->checkState() == Qt::Checked)
        bt |= (1<<7);               //Ext ID
    bt |= lE_DLC_10->text().toInt();
    bd.append(bt);

//    quint32 id = lE_ID_1->text().toUtf8();
    bd.append(QByteArray::fromHex(lE_ID_10->text().toUtf8()));

    bd.insert(5, 8, 0);

    quint8 dlc = lE_DLC_10->text().toInt();
    if (dlc > 0)
    {
        bd.replace(5, 1, QByteArray::fromHex(lE_D0_10->text().toUtf8()));
        dlc--;
    }
    if (dlc > 0)
    {
        bd.replace(6, 1, QByteArray::fromHex(lE_D1_10->text().toUtf8()));
        dlc--;
    }
    if (dlc > 0)
    {
        bd.replace(7, 1, QByteArray::fromHex(lE_D2_10->text().toUtf8()));
        dlc--;
    }
    if (dlc > 0)
    {
        bd.replace(8, 1, QByteArray::fromHex(lE_D3_10->text().toUtf8()));
        dlc--;
    }
    if (dlc > 0)
    {
        bd.replace(9, 1, QByteArray::fromHex(lE_D4_10->text().toUtf8()));
        dlc--;
    }
    if (dlc > 0)
    {
        bd.replace(10, 1, QByteArray::fromHex(lE_D5_10->text().toUtf8()));
        dlc--;
    }
    if (dlc > 0)
    {
        bd.replace(11, 1, QByteArray::fromHex(lE_D6_10->text().toUtf8()));
        dlc--;
    }
    if (dlc > 0)
    {
        bd.replace(12, 1, QByteArray::fromHex(lE_D7_10->text().toUtf8()));
        dlc--;
    }

    emit signal_sendToServer(bd);

    qDebug() << bt << dlc << bd;

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


