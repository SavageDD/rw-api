#include "api.hpp"
#include "../API.h"
#include <unordered_map>
#include "Player.hpp"
#include "Server.hpp"
#include "json.hpp"
#include <fstream>
#include "color.hpp"
using json = nlohmann::json;

API * API::API_INSTANCE = nullptr;
std::unordered_map<int, mp::Player*> players;
std::vector<rw::Plugin*> plugins;
mp::Server* server = new mp::Server();
bool ch_versoin = true;

rw::version version_support = rw::version::Alpha_01;

enum LabelType {
	Error,
	Warning,
	Note,
};


void SendLabel(LabelType type)
{
	switch (type)
	{
	case Error:
		color::set(color::red);
		std::cout << "[ERROR]";
		break;
	case Warning:
		color::set(color::yellow);
		std::cout << "[WARNING]";
		break;
	case Note:
		color::set(color::silver);
		std::cout << "[NOTE]";
		break;
	}
	color::set(color::white);
}

void load(std::string name)
{
	HMODULE lib = LoadLibrary(("mods/" + name).c_str());
	if (lib)
	{
		FARPROC load = GetProcAddress(lib, "registerPlugin");
		if (load)
		{
			rw::Plugin* plugin = ((rw::Plugin*(*)(rw::Server*))load)(server);
			plugins.push_back(plugin);
			if (plugin->pluginVersion() != version_support && ch_versoin)
			{
				SendLabel(Warning);
				std::cout << " Version of the plugin unsupported | " << name << std::endl;
			}
			plugin->serverListener()->onLoad();
		}
		else {
			SendLabel(Warning);
			std::cout << " Invalid plugin | " << name << std::endl;
		}
	}
	else
	{
		SendLabel(Warning);
		std::cout << " The plugin not found | " << name << std::endl;
	}
}

API_CALL bool Validate(API * api)
{
	color::set(color::white);
	SendLabel(Note);
	std::cout << " API module loaded" << std::endl;
	API::API_INSTANCE = api;
	json config;

	std::ifstream i("config.json");
	if (!i.good())
	{
		config["check_version"] = true;
		config["plugins"] = { "" };
		std::ofstream o("config.json");
		o << std::setw(4) << config << std::endl;
		o.close();
	}
	else 
	{
		try
		{
			i >> config;

		}
		catch (json::parse_error &e)
		{
			SendLabel(Error);
			std::cerr << " " << e.what() << std::endl;
		}
	}
	if (!config.count("check_version") || !config.count("plugins"))
	{
		SendLabel(Error);
		std::cout << " Invalid config" << std::endl;
		exit(0);
	}


	ch_versoin = config["check_version"].get<bool>();
	json pList = config["plugins"].get<json>();
	for (json::iterator it = pList.begin(); it != pList.end(); ++it)
	{
		std::string plugin = (*it).get<std::string>();
		if (plugin.length() > 0)
			load(plugin);
	}
	return true;
}

API_CALL void OnModuleInit()
{
	for (std::vector<rw::Plugin*>::iterator it = plugins.begin(); it != plugins.end(); it++)
	{
		rw::ServerListener* listener = (*it)->serverListener();
		if (listener)
			listener->onGameInit();
	}
}

API_CALL bool OnPlayerConnect(int playerID)
{
	for (std::vector<rw::Plugin*>::iterator it = plugins.begin(); it != plugins.end(); it++)
	{
		rw::PlayerListener* listener = (*it)->playerListener();
		mp::Player* player = new mp::Player((short)playerID);
		players[playerID] = player;
		if (listener)
			listener->clientJoin(player);
	}
	return true;
}

API_CALL bool OnPlayerDisconnect(int playerID, int reason)
{
	for (std::vector<rw::Plugin*>::iterator it = plugins.begin(); it != plugins.end(); it++)
	{
		rw::PlayerListener* listener = (*it)->playerListener();
		mp::Player* player = players[playerID];
		if (player) {
			if (listener)
				listener->clientQuit(player, reason);
			delete player;
			players.erase(playerID);
		}
	}
	return true;
}


API_CALL bool OnPlayerRequestClass(int playerID, int classid)
{
	for (std::vector<rw::Plugin*>::iterator it = plugins.begin(); it != plugins.end(); it++)
	{
		rw::PlayerListener* listener = (*it)->playerListener();
		mp::Player* player = players[playerID];
		if (player && listener)
			listener->playerRequestClass(player, classid);
	}
	return true;
}

API_CALL bool OnPlayerSpawn(int playerID)
{
	for (std::vector<rw::Plugin*>::iterator it = plugins.begin(); it != plugins.end(); it++)
	{
		rw::PlayerListener* listener = (*it)->playerListener();
		mp::Player* player = players[playerID];
		if (player && listener)
			listener->playerSpawn(player);
	}
	return true;
}

API_CALL bool OnPlayerDeath(int playerID, int killerID, int reason)
{
	for (std::vector<rw::Plugin*>::iterator it = plugins.begin(); it != plugins.end(); it++)
	{
		rw::PlayerListener* listener = (*it)->playerListener();
		mp::Player* player = players[playerID];
		mp::Player* killer = players[killerID];
		if (player && listener)
			listener->playerDeath(player, killer, reason);
	}
	return true;
}

API_CALL bool OnPlayerCommandText(int playerID, std::string text)
{
	for (std::vector<rw::Plugin*>::iterator it = plugins.begin(); it != plugins.end(); it++)
	{
		rw::PlayerListener* listener = (*it)->playerListener();
		mp::Player* player = players[playerID];
		if (player && listener)
			listener->playerCommand(player, text);
	}
	return true;
}

API_CALL bool OnPlayerRequestSpawn(int playerID)
{
	for (std::vector<rw::Plugin*>::iterator it = plugins.begin(); it != plugins.end(); it++)
	{
		rw::PlayerListener* listener = (*it)->playerListener();
		mp::Player* player = players[playerID];
		if (player && listener)
			listener->playerRequestSpawn(player);
	}
	return true;
}

API_CALL bool OnPlayerUpdate(int playerID)
{
	for (std::vector<rw::Plugin*>::iterator it = plugins.begin(); it != plugins.end(); it++)
	{
		rw::PlayerListener* listener = (*it)->playerListener();
		mp::Player* player = players[playerID];
		if (player && listener)
			listener->playerUpdate(player);
	}
	return true;
}

