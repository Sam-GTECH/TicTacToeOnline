#pragma once

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define WIN32_LEAN_AND_MEAN

#include <string>
#include "json.hpp"
#include <fstream>
#include <WinSock2.h>
#include <stdio.h>
#include <ws2tcpip.h>
#include <stdlib.h>
//#include <json/json.h>

#pragma comment (lib, "Ws2_32.lib")

#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "27015"
#define PORT 27015
#define IP_ADDRESS "10.1.144.12"
#define DATA_BUFSIZE 8192

using json = nlohmann::json;

class OnlineManager
{
	public:
		OnlineManager();

		struct addrinfo* result = NULL,
			* ptr = NULL,
			hints;
		

		std::map<int, int> c_message;

		json getData(std::string data);
		json getData(std::ifstream file);

		void writeJSON(std::string filename, json data);
		void writeJSON(std::string filename, std::string data);
		void sendMessage(json message);
		bool ConnectServeur();
		HWND createWindowServeur();

protected:
	int iResult;
	SOCKET m_ConnectSocket;
};