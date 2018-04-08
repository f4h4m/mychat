#include "stdafx.h"
#include <conio.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <cstring>
#include <stdio.h>
#include "SQLiteCpp-master\sqlite3\sqlite3.h"
#include "DbMsg.h"

using namespace std;

int ClassDbMsg::CallBack(void *data, int argc, char **argv, char **azColName)
{
	int i;
	for (i = 0; i<argc; i++) {
		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	}
	cout << "========================== \n";
	return 0;
}

int ClassDbMsg::CountAllMessages = 0;

int ClassDbMsg::CallBackCountAllMessages(void *data, int argc, char **argv, char **azColName)
{
	CountAllMessages = stoi(*argv);
	return 0;
}


int ClassDbMsg::CountFindedUnusefulMessages = 0;

int ClassDbMsg::CallBackRetunCount(void *data, int argc, char **argv, char **azColName)
{
	CountFindedUnusefulMessages = stoi(*argv);
	return 0;
}

int ClassDbMsg::StatusLoginAuthentication = 0;


int ClassDbMsg::CallBackUserAtuention(void *data, int argc, char **argv, char **azColName)
{
	if (stoi(*argv)>0)
	{
		ClassDbMsg::StatusLoginAuthentication = 1;
	}
	return 0;
}

void ClassDbMsg::InsertMsg(sqlite3 *db, string msg = "", string user = "", string time = "", string ip = "", int port = 0)
{
	//sqlite3 *db;
	//sqlite3_open("mydb.db", &db);
	char *errorText;
	string query = "INSERT INTO `messages`(`id`,`text`,`user`,`time`,`ip`,`port`) VALUES (NULL,'" + string(msg) + "','" + string(user) + "','" + string(time) + "','" + string(ip) + "','" + to_string(port) + "');";
	int result = sqlite3_exec(db, query.c_str(), NULL, NULL, &errorText);
	//cout << "Error = " << errorText << "\n";
}

void ClassDbMsg::ShowAllMsg(sqlite3 *db)
{
	cout << "============== Show All =============== \n";
	//sqlite3 *db = NULL;
	//sqlite3_open("..//socket2//mydb.db", &db);
	char *errorText = "as";
	string QueryShowAll = "SELECT * FROM `messages`";
	string QueryCountAllMessages = "SELECT COUNT(*) FROM `messages`";
	int ResultShowAll = sqlite3_exec(db, QueryShowAll.c_str(), CallBack, NULL, &errorText);
	int ResultCountAllMessages = sqlite3_exec(db, QueryCountAllMessages.c_str(), CallBackCountAllMessages, NULL, &errorText);
	cout << "(" << CountAllMessages << ") Record Found . \n";
	//cout << "Error = " << errorText << "\n";
}
void ClassDbMsg::ShowMsgForUser(sqlite3 *db)
{
	cout << "============== Show a Special User =============== \n";
	string username;
	cout << "Enter Username :";
	getline(cin, username);
	//sqlite3 *db;
	//sqlite3_open("..//socket2//mydb.db", &db);
	char *errorText;
	string query = "SELECT * FROM `messages` WHERE `user` = '" + username + "'";
	int result = sqlite3_exec(db, query.c_str(), CallBack, NULL, &errorText);
	//cout <<"Error = " << errorText<<"\n";
}

void ClassDbMsg::ShowMsgForUserById(sqlite3 *db, int id = 0)
{
	//sqlite3 *db;
	//sqlite3_open("..//socket2//mydb.db", &db);
	char *errorText;
	string query = "SELECT * FROM `messages` WHERE `id` = '" + to_string(id) + "'";
	int result = sqlite3_exec(db, query.c_str(), CallBack, NULL, &errorText);
	//cout <<"Error = " << errorText<<"\n";
}

void ClassDbMsg::ClearUnusefulMsg(sqlite3 *db)
{
	cout << "============== Clear Unuseful Messages =============== \n";
	//sqlite3 *db;
	//sqlite3_open("..//socket2//mydb.db", &db);
	char *errorText;
	string QueryDelete = "DELETE FROM `messages` WHERE `text` = '' or `user` = '' or `time` = '' or `ip` = '' or `port` = ''";
	string QueryCount = "SELECT COUNT(*) FROM `messages` WHERE `text` = '' or `user` = '' or `time` = '' or `ip` = '' or `port` = ''";
	char SureMenu = '\0';



	int ResultCount = sqlite3_exec(db, QueryCount.c_str(), CallBackRetunCount, NULL, &errorText);
	cout << "Count of finded records = " << CountFindedUnusefulMessages << "\n";
	cout << "Are u Sure ? (y,n)";
	cin >> SureMenu;
	if (SureMenu == 'y')
	{
		int ResultDelete = sqlite3_exec(db, QueryDelete.c_str(), NULL, NULL, &errorText);
		if (ResultDelete == 0)
		{
			cout << "Cleare Unuseful Messages done \n";
		}
		else
		{
			cout << "Error in Clear Unuseful Messages \n";
		}
	}
	//cout <<"Error = " << errorText<<"\n";
}

void ClassDbMsg::DeleteOneMsg(sqlite3 *db)
{
	cout << "============== Delete a Message =============== \n";
	int id;
	//sqlite3 *db;
	//sqlite3_open("..//socket2//mydb.db", &db);
	char *errorText;
	char SureMenu = '\0';

	cout << "Enter id :";
	cin >> id;



	ShowMsgForUserById(db, id);
	cout << "Are u Sure ? (y,n)";
	cin >> SureMenu;
	if (SureMenu == 'y')
	{
		string query = "DELETE FROM `messages` WHERE `id` = '" + to_string(id) + "'";
		int result = sqlite3_exec(db, query.c_str(), NULL, NULL, &errorText);
		if (result == 0) {
			cout << "Delete Message (with id " + to_string(id) + ") Done . \n";
		}
		else {
			cout << "Error in Delete Message \n";
		}
	}
	//cout <<"Error = " << errorText<<"\n";
}

void ClassDbMsg::EditOneMsgById(sqlite3 *db)
{
	cout << "============== Edit a Message =============== \n";
	int id;
	//sqlite3 *db;
	//sqlite3_open("..//socket2//mydb.db", &db);
	char *errorText;
	char SureMenu = '\0';

	cout << "Enter id :";
	cin >> id;



	ShowMsgForUserById(db, id);
	cout << "Are u Sure ? (y,n)";
	cin >> SureMenu;
	if (SureMenu == 'y')
	{
		cin.ignore(); // flush the buffer . for new line
		string NewText, NewUser;
		cout << "Enter New Text Message :";
		getline(cin, NewText);

		cout << "Enter New Username :";
		getline(cin, NewUser);

		string query = "UPDATE `messages` SET `user` = '" + NewUser + "', `text`= '" + NewText + "' WHERE `id` = '" + to_string(id) + "'";
		int result = sqlite3_exec(db, query.c_str(), NULL, NULL, &errorText);
		if (result == 0) {
			cout << "Edit Message (with id " + to_string(id) + ") Done . \n";
			cout << "========================== \n";
			ShowMsgForUserById(db, id);
		}
		else {
			cout << "Error in Edit Message \n";
			cout << "Error = " << errorText << "\n";
		}
	}
}


void ClassDbMsg::LoginAuthentication(sqlite3 *db)
{
	cout << "	__          ________ _      _____ ____  __  __ ______  \n";
	cout << "	\\ \\        / /  ____| |    / ____/ __ \\|  \\/  |  ____| \n";
	cout << "	 \\ \\  /\\  / /| |__  | |   | |   | |  | | \\  / | |__  \n";
	cout << "	  \\ \\/  \\/ / |  __| | |   | |   | |  | | |\\/| |  __| \n";
	cout << "	   \\  /\\  /  | |____| |___| |___| |__| | |  | | |____ \n";
	cout << "	    \\/  \\/   |______|______\\_____\\____/|_|  |_|______| \n";

	//sqlite3 *db;
	//sqlite3_open("..//socket2//mydb.db", &db);
	char *errorText;
	do
	{
		string username, password;
		cout << "Username :";
		getline(cin, username);
		cout << "Password :";
		getline(cin, password);

		string query = "SELECT count(*) FROM `users` WHERE `username` = '" + username + "' and `password` = '" + password + "'";
		int result = sqlite3_exec(db, query.c_str(), CallBackUserAtuention, NULL, &errorText);

		if (ClassDbMsg::StatusLoginAuthentication == 0)
		{
			cout << "Username or password is wrong . \n";
		}

	} while (ClassDbMsg::StatusLoginAuthentication != 1);
}

void ClassDbMsg::SearchMsgByText(sqlite3 *db)
{
	cout << "============== Search a Message By Text =============== \n";
	string text;
	char *errorText;
	cout << "Enter Text :";
	getline(cin, text);

	//sqlite3 *db;
	//sqlite3_open("..//socket2//mydb.db", &db);

	string QuerySearch = "SELECT * FROM `messages` WHERE `text` LIKE '%" + text + "%'";
	int result = sqlite3_exec(db, QuerySearch.c_str(), CallBack, NULL, &errorText);
	//cout <<"Error = " << errorText<<"\n";
}
