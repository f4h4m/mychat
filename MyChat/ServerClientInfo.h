#pragma once

using namespace std;

class ServerClientInfo {
private:
	char *CleintIp;
	int ClientPort;
	char *ServerIp;
	int ServerPort;
public:
	char *ReturnClientIp(struct sockaddr_in &clientForIp);
	int ReturnClientPort(struct sockaddr_in &clientForPort);
	int ReturServerPort(struct sockaddr_in &server);
};

