#pragma once

using namespace std;

class ConnectClass {
public:
	void ListenAndInsert(sqlite3 *db);
	void ListenAndInsertWithThread(sqlite3 *db);
	void test();
};

