#ifndef GLOBALS_H
#define GLOBALS_H

#include "server.h"
#include "client.h"

#define INIFILENAME         "settings.ini"
#define _CLIENT_ADR         "localhost"

QString MSG_SERVER_INIT = "Server is listening...";
QString MSG_CLIENT_CONN = "Client connected";
QString MSG_HI = "Hi by Windows";
QString MSG_CONN_YES = "Connected";
QString MSG_CONN_NO = "DisConnected";

extern const int dInpSize = 8;
extern const int dOutSize = 4;
extern const int aInpSize = 7;
extern const int aOutSize = 4;
extern const int dataBufferSizeMax = 48;   // dInpSize+dOutSize+aInpSize*5{A+4digit}+1{Z}
extern const int dataBufferSizeMin = 27;   // dInpSize+dOutSize+aInpSize*2{A+1digit}+1{Z}

char dInpArr[dInpSize+1];
int dInpGpioMap[dInpSize] = {45, 44, 26, 47, 46, 27, 65, 61};

char dOutArr[dOutSize+1];
char dOutReadArr[dOutSize+1];
int dOutGpioMap[dOutSize] = {66, 67, 69, 68};

int aInpArr[aInpSize];
float aInpArrVal[aInpSize];

int aOutArr[aOutSize];

//QString clientAddress = "192.168.2.232"; // BBB ***
QString clientAddress = "192.168.1.48"; // BBB ***
//QString clientAddress = "192.168.1.247"; // BBBak

//QString clientAddress = "192.168.2.241"; // DebianVB
//QString clientAddress = "192.168.2.222"; // Windows

#endif // GLOBALS_H
