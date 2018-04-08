// socket2.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <stdio.h>
#include <iostream>
#include <string>
#include <WinSock2.h>
#include <sys\types.h>
#include <WS2tcpip.h>
#include <Windows.h>
#include <cstring>
#include "SQLiteCpp-master\sqlite3\sqlite3.h"
#include <ctime>
#include <thread>
#include "DbMsg.h"
#include "ServerClientInfo.h"
#include "tools.h"
#include "ConnectClass.h"
#pragma comment(lib,"ws2_32.lib")

using namespace std;
int main()
{
	sqlite3 *db = NULL;
	sqlite3_open("..//MyChat//mydb.db", &db);

	ClassDbMsg ClassDbMsgOBJ;
	//ClassDbMsgOBJ.LoginAuthentication();
	int MenuNumber;
	do
	{
		cout << "========== Menu ============ \n";
		cout << "1-Listening \n";
		cout << "2-Messages \n";
		cout << "3-Clear Screen \n";
		cout << "4-Exit \n";
		cout << ":";
		cin >> MenuNumber;

		switch (MenuNumber)
		{
		case 1:
		{
			ConnectClass ConnectOBJ;
			//ConnectOBJ.test();
			ConnectOBJ.ListenAndInsertWithThread(db);
			//ConnectOBJ.ListenAndInsert(db);

		}
		break;
		case 2:
		{

			int ShowMenuNumber;
			cout << "(Messages)1-Show All\n";
			cout << "(Messages)2-Show of a User \n";
			cout << "(Messages)3-Clear Unuseful\n";
			cout << "(Messages)4-Delete\n";
			cout << "(Messages)5-Edit\n";
			cout << "(Messages)6-Srach\n";
			cout << "(Messages)7-Back \n";
			cout << "(Messages):";
			cin >> ShowMenuNumber;
			getchar();
			switch (ShowMenuNumber)
			{
			case 1:

				ClassDbMsgOBJ.ShowAllMsg(db);
				break;
			case 2:
				ClassDbMsgOBJ.ShowMsgForUser(db);
				break;
			case 3:
				ClassDbMsgOBJ.ClearUnusefulMsg(db);
				break;
			case 4:
				ClassDbMsgOBJ.DeleteOneMsg(db);
				break;
			case 5:
				ClassDbMsgOBJ.EditOneMsgById(db);
				break;
			case 6:
				ClassDbMsgOBJ.SearchMsgByText(db);
			case 7:
				break;
			}
		}
		break;
		case 3:
			system("CLS");
			break;
		default:
			continue;
			break;
		}
	} while (MenuNumber != 4);
	getchar();
	return 0;
}

