#include "checkclient.h"
#include "client.h"

#include <iostream>

using namespace std;

extern Client *clientx;

checkClient::checkClient(){

    stopped = false;
}

void checkClient::run(){

    if (!stopped){
//        delete[] w->videoList;
//        emit this->saveFinished();
    }
    stopped = false;
}

void checkClient::connect(){

    //cout <<"checkClient::connect(), socket state/error:" << clientx->clientSocket.state() << " / " << clientx->clientSocket.error() << endl;    //DBG

    if (clientx->clientSocket.state() != QAbstractSocket::ConnectingState &&
        clientx->clientSocket.state() != QAbstractSocket::ConnectedState ){
        cout << "checkClient" << endl;    //DBG
        clientx->start();
    }

    if (clientx->clientSocket.state() == QAbstractSocket::ConnectedState )
        emit Connected();
    else
        emit notConnected();

}

void checkClient::stop(){

    stopped = true;

}

checkClient::~checkClient(){
}

