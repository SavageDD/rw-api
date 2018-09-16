#include "../api/api.hpp"
rw::Server* api = nullptr;

class Hundler : public rw::Plugin, rw::PlayerListener, rw::ServerListener {
public:
	void onLoad() {
		std::cout << "Load" << std::endl;
		api->addClass(0, { 0.0f, 0.0f, 3.0f }, 0.0f);
	}
	rw::ServerListener* serverListener() { return this; }

	void clientJoin(rw::Player* player)
	{
		std::cout << "Player " << player->getName() << "[" << player->id() << "] has connect" << std::endl;
	}
	void playerCommand(rw::Player* player, std::string text)
	{
		if (!text.find("/spawn"))
		{
			player->spawn();
			player->setWeather(8);
			player->message("Hallo CJ!");
		}
		if (!text.find("/veh"))
		{
			api->createVehicle(411, player->getPosition().offset(0.0f, 0.0f, 10.0f), 0.0f, 0, 0, -1);
		}
	}
	void playerSpawn(rw::Player* player)
	{
		player->giveMoney(5000);
	}
	rw::PlayerListener* playerListener() { return this; }
};

API_CALL rw::Plugin* registerPlugin(rw::Server* server)
{
	api = server;
	return new Hundler;
}