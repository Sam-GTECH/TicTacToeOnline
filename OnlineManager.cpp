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