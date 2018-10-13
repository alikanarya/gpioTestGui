#include "server.h"
#include "client.h"

#include <iostream>
#include <unistd.h>

using namespace std;

extern QString MSG_SERVER_INIT;
extern int dInpSize;
extern char dInpArr[];
extern int dOutSize;
extern char dOutReadArr[];
extern int aInpArr[];
extern int aInpSize;
//extern Client *clientx;

Server::Server(QObject* parent): QObject(parent){

    connect(&server, SIGNAL(newConnection()), this, SLOT(acceptConnection()));
    server.listen(QHostAddress::Any, serverPort);
    cout << MSG_SERVER_INIT.toUtf8().constData() << endl;
}

Server::~Server(){

    server.close();
}

void Server::acceptConnection(){

    //cout <<"Server::acceptConnection" << endl;    //DBG
    client = server.nextPendingConnection();
    connect(client, SIGNAL(readyRead()), this, SLOT(startRead()));
}

void Server::startRead(){

    datagram.clear();
    //while (client->waitForReadyRead(300)) {
    while (client->bytesAvailable() > 0) {
        datagram.append(client->readAll());
        client->flush();
    }
    //}

    if (!datagram.isEmpty()) {

        cout << datagram.data() << endl;      //DBG

        bool validData = true;
        if (datagram.size() != 48)
            validData = false;

        for (int k=0; k<dInpSize+dOutSize; k++) {
            if ( !QChar(datagram.at(k)).isDigit() ) {
                validData = false;
                cout << datagram.at(k);
            }
        }

        if (validData) {
            for (int i = 0; i < dInpSize; i++) {
                dInpArr[i] = datagram.data()[i];
            }

            for (int i = 0; i < dOutSize; i++) {
                dOutReadArr[i] = datagram.data()[i + dInpSize];
            }
        }

        if (validData && datagram.at(datagram.size()-1) == 'Z') {

            int pos = dInpSize+dOutSize;
            char ch = datagram.at(pos);
            //cout << ch << endl;      //DBG
            int j = 0, x = 0;

            while (ch != 'Z') {
                //x = 0;
                if (ch == 'A') {
                    char temp[16];
                    j = -1;
                    do {
                        pos++;
                        ch = datagram.at(pos);
                        //cout << " " << ch;
                        if (ch == 'Z') break;
                        if (ch == 'A') break;
                        j++;
                        temp[j] = ch;

                    } while ( ch != 'Z' );

                    temp [j+1] = '\0';
                    if ( x < aInpSize ) {
                        aInpArr[x] = atoi(temp);
                        //cout << " " << aInpArr[x];
                    } else
                        break;
                    x++;
                }
            }
        }
        //cout << endl;
    }

    emit this->readFinished();
    //client->close();
}
