#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "globals.h"
#include "checkclient.h"
#include <iostream>

using namespace std;

Server *serverx;
Client *clientx;
checkClient *checkClientX;


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow){

    ui->setupUi(this);

    settings = new QSettings(INIFILENAME, QSettings::IniFormat);
    readSettings();

    serverx = new Server();
    clientx = new Client();
    checkClientX = new checkClient();

    for (int i = 0; i < dInpSize; i++) dInpArr[i] = '0';
    dInpArr[dInpSize] = '\0';

    for (int i = 0; i < dOutSize; i++) dOutArr[i] = '1';
    dOutArr[dInpSize] = '\0';

    for (int i = 0; i < dOutSize; i++) dOutReadArr[i] = '0';
    dOutReadArr[dInpSize] = '\0';

    for (int i = 0; i < aInpSize; i++) aInpArr[i] = 0;
    for (int i = 0; i < aInpSize; i++) aInpArrVal[i] = 0.0;

    for (int i = 0; i < aOutSize; i++) aOutArr[i] = 0;

    // 1sec timer
    QTimer *timerSec = new QTimer();
    QObject::connect(timerSec, SIGNAL(timeout()), checkClientX, SLOT(connect()));
    timerSec->start(1000);

    connect(serverx, SIGNAL(readFinished()),this, SLOT(displayInputs()));
    connect(checkClientX, SIGNAL(Connected()),this, SLOT(ConnectedToServer()));
    connect(checkClientX, SIGNAL(notConnected()),this, SLOT(NotConnectedToServer()));
    connect(this, SIGNAL(sendData()),this, SLOT(transferData()));

}

MainWindow::~MainWindow(){

    delete ui;
}

void MainWindow::ConnectedToServer(){

    ui->connStatusLabel->setText(MSG_CONN_YES);
    ui->connStatusLabel->setStyleSheet("color: green");
}

void MainWindow::NotConnectedToServer(){

    //cout << MSG_CONN_NO.toUtf8().constData() << endl;

    ui->connStatusLabel->setText(MSG_CONN_NO);
    ui->connStatusLabel->setStyleSheet("color: red");

    ui->dINP1->setStyleSheet("background-color: light gray");
    ui->dINP2->setStyleSheet("background-color: light gray");
    ui->dINP3->setStyleSheet("background-color: light gray");
    ui->dINP4->setStyleSheet("background-color: light gray");
    ui->dINP5->setStyleSheet("background-color: light gray");
    ui->dINP6->setStyleSheet("background-color: light gray");
    ui->dINP7->setStyleSheet("background-color: light gray");
    ui->dINP8->setStyleSheet("background-color: light gray");

    ui->dOUT1->setStyleSheet("background-color: light gray");
    ui->dOUT2->setStyleSheet("background-color: light gray");
    ui->dOUT3->setStyleSheet("background-color: light gray");
    ui->dOUT4->setStyleSheet("background-color: light gray");

}


void MainWindow::displayInputs(){

    if (dInpArr[0] == '0')
        ui->dINP1->setStyleSheet("background-color: red");
    else if (dInpArr[0] == '1')
        ui->dINP1->setStyleSheet("background-color: green");

    if (dInpArr[1] == '0')
        ui->dINP2->setStyleSheet("background-color: red");
    else if (dInpArr[1] == '1')
        ui->dINP2->setStyleSheet("background-color: green");

    if (dInpArr[2] == '0')
        ui->dINP3->setStyleSheet("background-color: red");
    else if (dInpArr[2] == '1')
        ui->dINP3->setStyleSheet("background-color: green");

    if (dInpArr[3] == '0')
        ui->dINP4->setStyleSheet("background-color: red");
    else if (dInpArr[3] == '1')
        ui->dINP4->setStyleSheet("background-color: green");

    if (dInpArr[4] == '0')
        ui->dINP5->setStyleSheet("background-color: red");
    else if (dInpArr[4] == '1')
        ui->dINP5->setStyleSheet("background-color: green");

    if (dInpArr[5] == '0')
        ui->dINP6->setStyleSheet("background-color: red");
    else if (dInpArr[5] == '1')
        ui->dINP6->setStyleSheet("background-color: green");

    if (dInpArr[6] == '0')
        ui->dINP7->setStyleSheet("background-color: red");
    else if (dInpArr[6] == '1')
        ui->dINP7->setStyleSheet("background-color: green");

    if (dInpArr[7] == '0')
        ui->dINP8->setStyleSheet("background-color: red");
    else if (dInpArr[7] == '1')
        ui->dINP8->setStyleSheet("background-color: green");

    // dOuts are inverted
    if (dOutReadArr[0] == '1')
        ui->dOUT1->setStyleSheet("background-color: red");
    else if (dOutReadArr[0] == '0')
        ui->dOUT1->setStyleSheet("background-color: green");

    if (dOutReadArr[1] == '1')
        ui->dOUT2->setStyleSheet("background-color: red");
    else if (dOutReadArr[1] == '0')
        ui->dOUT2->setStyleSheet("background-color: green");

    if (dOutReadArr[2] == '1')
        ui->dOUT3->setStyleSheet("background-color: red");
    else if (dOutReadArr[2] == '0')
        ui->dOUT3->setStyleSheet("background-color: green");

    if (dOutReadArr[3] == '1')
        ui->dOUT4->setStyleSheet("background-color: red");
    else if (dOutReadArr[3] == '0')
        ui->dOUT4->setStyleSheet("background-color: green");

    ui->ai0_raw->setText(QString::number(aInpArr[0]));
    ui->ai1_raw->setText(QString::number(aInpArr[1]));
    ui->ai2_raw->setText(QString::number(aInpArr[2]));
    ui->ai3_raw->setText(QString::number(aInpArr[3]));
    ui->ai4_raw->setText(QString::number(aInpArr[4]));
    ui->ai5_raw->setText(QString::number(aInpArr[5]));
    ui->ai6_raw->setText(QString::number(aInpArr[6]));

    aInpArrVal[0] = aInpArr[0] / 22.755555;
    ui->ai0->setText(QString::number(aInpArrVal[0],'f',1));

}

void MainWindow::transferData(){

    if (clientx->clientSocket.state() == QAbstractSocket::ConnectedState){

        clientx->datagram.clear();

        for (int i = 0; i < dOutSize; i++){
            clientx->datagram.append(dOutArr[i]);
        }

        for (int i = 0; i < aOutSize; i++){
            //cout << "ADC" << i <<": " << val << "...";  //DBG
            clientx->datagram.append( 'A' );
            char charVal[3];
            sprintf(charVal, "%d", aOutArr[i]);
            clientx->datagram.append( charVal );
            //clientx->datagram.append( 'Z' );
        }
        clientx->datagram.append( 'Z' );


        clientx->startTransfer();
    }

}

void MainWindow::on_dOUT1_clicked(){

    if (clientx->clientSocket.state() == QAbstractSocket::ConnectedState){

        if (dOutArr[0] == '0') dOutArr[0] = '1'; else dOutArr[0] = '0';

        emit sendData();
    }
}

void MainWindow::on_dOUT2_clicked(){

    if (clientx->clientSocket.state() == QAbstractSocket::ConnectedState){

        if (dOutArr[1] == '0') dOutArr[1] = '1'; else dOutArr[1] = '0';

        emit sendData();
    }
}

void MainWindow::on_dOUT3_clicked(){

    if (clientx->clientSocket.state() == QAbstractSocket::ConnectedState){

        if (dOutArr[2] == '0') dOutArr[2] = '1'; else dOutArr[2] = '0';

        emit sendData();
    }
}

void MainWindow::on_dOUT4_clicked(){

    if (clientx->clientSocket.state() == QAbstractSocket::ConnectedState){

        if (dOutArr[3] == '0') dOutArr[3] = '1'; else dOutArr[3] = '0';

        emit sendData();
    }
}

void MainWindow::on_aOut1_sliderReleased(){

    aOutArr[0] = ui->aOut1->value();
    emit sendData();
}

void MainWindow::on_aOut2_sliderReleased(){

    aOutArr[1] = ui->aOut2->value();
    emit sendData();
}

void MainWindow::on_aOut3_sliderReleased(){

    aOutArr[2] = ui->aOut3->value();
    emit sendData();
}

void MainWindow::on_aOut4_sliderReleased(){

    aOutArr[3] = ui->aOut4->value();
    emit sendData();
}

bool MainWindow::readSettings(){

    if (QFile::exists(INIFILENAME)){

        clientAddress = settings->value("clientAddress0", _CLIENT_ADR).toString();
        cout << clientAddress.toUtf8().constData() << endl;
        return true;

    } else {
        qDebug() << "ini file not found" << endl;
        return false;
    }
}
