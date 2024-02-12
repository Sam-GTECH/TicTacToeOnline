#pragma once
#include <string>
#include "json.hpp"
#include <fstream>

using json = nlohmann::json;

class OnlineManager
{
	public:
		OnlineManager();



		json getData(std::string data);
		json getData(std::ifstream file);

		void writeJSON(std::string filename, json data);
		void writeJSON(std::string filename, std::string data);
};