#include "stdafx.h"
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <conio.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <cstring>
#include <WinSock2.h>
#include <sys\types.h>
#include <WS2tcpip.h>
#include <Windows.h>
#include <thread>
#include "SQLiteCpp-master\sqlite3\sqlite3.h"
#include <ctime>
#include "tools.h"
#include "DbMsg.h"
#include "ServerClientInfo.h"
#include "ConnectClass.h"

#pragma comment(lib,"Ws2_32.lib")

//for fix "listen" problem
void ConnectClass::test()
{
	int PORT = 1604;
	WSADATA wsadata;
	int error = WSAStartup(0x0202, &wsadata);
	if (error)
	{
		cout << "Error";
	}
	if (wsadata.wVersion != 0x0202) {
		WSACleanup();
		cout << "Error";
	}
	SOCKET ListenSocket;
	SOCKADDR_IN addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(PORT);
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	ListenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (ListenSocket == INVALID_SOCKET) cout << "INVALID SOCKET" << endl;
	bind(ListenSocket, (LPSOCKADDR)&addr, sizeof(addr));

	if (listen(ListenSocket, 1) == SOCKET_ERROR) {
		wprintf(L"listen failed with error: %ld\n", WSAGetLastError());
		closesocket(ListenSocket);
		WSACleanup();
	}
	cout << "Listen ...";

	SOCKET AcceptSocket;
	wprintf(L"Waiting for client to connect...\n");

	AcceptSocket = accept(ListenSocket, NULL, NULL);
	if (AcceptSocket == INVALID_SOCKET) {
		wprintf(L"accept failed with error: %ld\n", WSAGetLastError());
		closesocket(ListenSocket);
		WSACleanup();
	}
	else
		wprintf(L"Client connected.\n");

	// No longer need server socket
	closesocket(ListenSocket);
}

void ConnectClass::ListenAndInsert(sqlite3 *db)
{
	tools ToolsObj;
	ClassDbMsg ClassDbMsgOBJ;
	ServerClientInfo ServerClientInfoOBJ;
	int port = 1604;
	WSADATA WSAData;
	SOCKET server, client;
	SOCKADDR_IN serverAddr, clientAddr;
	WSAStartup(MAKEWORD(2, 0), &WSAData); //introduction for you want use socket

	server = socket(AF_INET, SOCK_STREAM, 0);

	serverAddr.sin_addr.s_addr = INADDR_ANY;
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(port);

	bind(server, (SOCKADDR *)&serverAddr, sizeof(serverAddr));
	listen(server, 0);

	cout << "Listening for incoming connections..." << endl;
	
	char buffer[1024];
	int clientAddrSize = sizeof(clientAddr);
	if ((client = accept(server, (SOCKADDR *)&clientAddr, &clientAddrSize)) != INVALID_SOCKET)
	{
		cout << "Client connected!" << endl;
		char name[1024];
		recv(client, name, sizeof(name), 0);
		cout << "Client Ip = " << ServerClientInfoOBJ.ReturnClientIp(clientAddr) << "\n";
		cout << "Client Port = " << ServerClientInfoOBJ.ReturnClientPort(clientAddr) << "\n";
		cout << "------------------------------- \n";
		//cout << "Server Ip = " << ServerInfoOBJ.returnServerIp() << "\n";
		cout << "Server Port = " << ServerClientInfoOBJ.ReturServerPort(serverAddr) << "\n";
		while (recv(client, buffer, sizeof(buffer), 0))
		{
			cout << name << "->" << buffer << endl;
			ClassDbMsgOBJ.InsertMsg(db, buffer, name, ToolsObj.GetTime(), ServerClientInfoOBJ.ReturnClientIp(clientAddr), ServerClientInfoOBJ.ReturnClientPort(clientAddr));
			if (strcmp(buffer, "exit") == 0)
			{
				break;
			}
			memset(buffer, 0, sizeof(buffer));
		}
	}
	closesocket(client);
	WSACleanup();
	cout << "Client disconnected." << endl;
}

void  ConnectClass::ListenAndInsertWithThread(sqlite3 *db)
{
	//Connect::ListenAndInsert(db);
	thread TConnectOBJListenAndInsert(&ConnectClass::ListenAndInsert, ConnectClass(), db);
	//cout << "thread Id = " << TConnectOBJListenAndInsert.get_id(), "\n";
	if (TConnectOBJListenAndInsert.joinable())
	{
		TConnectOBJListenAndInsert.join();
	}
}