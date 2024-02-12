#include "OnlineManager.h"



OnlineManager::OnlineManager()
{}



//JSON Manager
json OnlineManager::getData(std::string data)
{
	return json::parse(data);
}

json OnlineManager::getData(std::ifstream file)
{
	return json::parse(file);
}

void OnlineManager::writeJSON(std::string filename, json data)
{
	std::ofstream o(filename + ".json");
	o << std::setw(4) << data << std::endl;
}

void OnlineManager::writeJSON(std::string filename, std::string data)
{
	std::ofstream o(filename + ".json");
	o << std::setw(4) << getData(data) << std::endl;
}

void OnlineManager::sendMessage(const char* message) {

    int iResult = send(ConnectSocket, message, (int)strlen(message), 0);
    if (iResult == SOCKET_ERROR) {
        printf("send failed with error: %d\n", WSAGetLastError());
        closesocket(ConnectSocket);
        WSACleanup();
        exit(1); // Vous pouvez modifier la gestion des erreurs selon vos besoins
    }
    printf("Message Sent: %s\n", message);
}