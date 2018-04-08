#include "stdafx.h"
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <conio.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <strstream>
#include <cstring>
#include <stdio.h>
#include <WinSock2.h>
#include <sys\types.h>
#include <WS2tcpip.h>
#include <Windows.h>
#include <cstring>
#include "SQLiteCpp-master\sqlite3\sqlite3.h"
#include <ctime>
#include "DbMsg.h"
#include "ServerClientInfo.h"
#pragma comment(lib,"Ws2_32.lib")


char *ServerClientInfo::ReturnClientIp(struct sockaddr_in &clientForIp)
{
	CleintIp = inet_ntoa(clientForIp.sin_addr);
	return CleintIp;
}
int ServerClientInfo::ReturnClientPort(struct sockaddr_in &clientForPort)
{
	ClientPort = ntohs(clientForPort.sin_port);
	return ClientPort;
}
int ServerClientInfo::ReturServerPort(struct sockaddr_in &server)
{
	ServerPort = ntohs(server.sin_port);
	return ServerPort;
}