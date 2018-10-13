#include "client.h"

#include <iostream>
#include <unistd.h>

#ifdef __WIN32__
#include <winsock2.h>
#else
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#endif

using namespace std;

extern QString MSG_CLIENT_CONN;
extern QString clientAddress;

Client::Client(QObject* parent): QObject(parent){

    host.setAddress(clientAddress);
    connect(&clientSocket, SIGNAL(connected()), this, SLOT(connectionEstablished()));
    int enableKeepAlive = 1;
    int fd = clientSocket.socketDescriptor();
    //clientSocket.setSocketOption(QAbstractSocket::KeepAliveOption,1);
    setsockopt(fd, SOL_SOCKET, SO_KEEPALIVE, (char *) &enableKeepAlive, sizeof(enableKeepAlive));
    /*
    int maxIdle = 10; // seconds
    setsockopt(fd, IPPROTO_TCP, TCP_KEEPIDLE, &maxIdle, sizeof(maxIdle));

    int count = 3;  // send up to 3 keepalive packets out, then disconnect if no response
    setsockopt(fd, SOL_TCP, TCP_KEEPCNT, &count, sizeof(count));

    int interval = 2;   // send a keepalive packet out every 2 seconds (after the 5 second idle period)
    setsockopt(fd, SOL_TCP, TCP_KEEPINTVL, &interval, sizeof(interval));*/
}

Client::~Client(){

    clientSocket.close();
}

void Client::start(){

    clientSocket.connectToHost(host, clientPort);
    //clientSocket.waitForConnected(5000);
}

void Client::startTransfer(){

    if (clientSocket.state() == QAbstractSocket::ConnectedState){
//        clientSocket.write(MSG_HI.toLatin1().constData(), 13);
        clientSocket.write(datagram);
    }
}

void Client::connectionEstablished(){

    connected = true;
    //emit clientConnected();
    cout << MSG_CLIENT_CONN.toUtf8().constData() << endl;
}
