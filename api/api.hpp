#pragma once
#include <string>
#include <iostream>

#ifdef _WIN32
#define API_CALL extern "C" __declspec(dllexport) 
#else
#define API_CALL extern "C"
#endif

namespace rw
{
	enum version : char
	{
		Alpha_01,
		Alpha_01_TEST,
		//to do
	};

	class Vector3 {
	public:
		float x, y, z;
		Vector3() : x(0), y(0), z(0) {}
		Vector3(float x, float y, float z) : x(x), y(y), z(z) {}
		Vector3 offset(float x, float y, float z)
		{
			return Vector3(this->x + x, this->y + y, this->z + z);
		}
	};

	class Entity {
	public:
		virtual int id() = 0;
		virtual Vector3 getPosition() = 0;
		virtual void setPosition(Vector3 position) = 0;
		/*not ready*/
		virtual int getModel() = 0;
		/*not ready*/
		virtual void setModel(int model) = 0;
		virtual void setRotation(float angle) = 0;
	};

	class Player : public Entity {
	public:
		virtual std::string getName() = 0;
		virtual void setInterior(int interion) = 0;
		virtual int getInterior() = 0;
		virtual void giveMoney(int money) = 0;
		virtual int  getMoney() = 0;
		virtual void giveWeapon(int weapon, int ammo) = 0;
		virtual void clearWeapons() = 0;
		virtual void setTeam(int team) = 0;
		virtual void message(std::string text) = 0;
		virtual void spawn() = 0;
		virtual void setWeather(int weather) = 0;
	};

	class Vehicle : public Entity {
	public:
		virtual void setColor(int color1, int color2) = 0;
	};

	class Server {
	public:
		virtual void setGamemodeText(std::string text) = 0;
		virtual void setWeather(int weatherID) = 0;
		virtual bool setGravity(float gravity) = 0;
		virtual int addClass(int model, Vector3, float rotation) = 0;
		virtual int getPlayerPoolSize() = 0;
		virtual int getVehiclePoolSize() = 0;
		virtual int getActorPoolSize() = 0;

		virtual Vehicle* createVehicle(int model, rw::Vector3 position, float rotation, int color1, int color2, int respawnDelay) = 0;
	};

	class PlayerListener {
	public:
		virtual void clientJoin(Player* player) {};
		virtual void clientQuit(Player* player, int reason) {};
		virtual void playerSpawn(Player* player) {};
		virtual void playerDeath(Player* player, Player* killer, int reason) {}
		virtual void playerUpdate(Player* player) {}
		virtual void playerRequestClass(Player* player, int classid) {}
		virtual void playerRequestSpawn(Player* player) {}
		virtual void playerCommand(Player* player, std::string text) {}
	};

	class ServerListener {
	public:
		virtual void onLoad() {};
		virtual void onGameInit() {};
	};

	class Plugin {
	public:
		virtual ServerListener* serverListener() { return nullptr; }
		virtual PlayerListener* playerListener() { return nullptr; }
		virtual version pluginVersion() { return version::Alpha_01; }
	};
}