#pragma once

using namespace std;

class ClassDbMsg {
public:
	static int StatusLoginAuthentication;
	static int CountFindedUnusefulMessages;
	static int CountAllMessages;
	static int CallBack(void *data, int argc, char **argv, char **azColName);
	static int CallBackRetunCount(void *data, int argc, char **argv, char **azColName);
	static int CallBackUserAtuention(void *data, int argc, char **argv, char **azColName);
	static int CallBackCountAllMessages(void *data, int argc, char **argv, char **azColName);
	void InsertMsg(sqlite3 *db, string msg, string user, string time, string ip, int port);
	void ShowAllMsg(sqlite3 *db);
	void ShowMsgForUser(sqlite3 *db);
	void ClearUnusefulMsg(sqlite3 *db);
	void DeleteOneMsg(sqlite3 *db);
	void ShowMsgForUserById(sqlite3 *db, int id);
	void EditOneMsgById(sqlite3 *db);
	void SearchMsgByText(sqlite3 *db);
	void LoginAuthentication(sqlite3 *db);
};

