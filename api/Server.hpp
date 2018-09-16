#pragma once
#include "api.hpp"
#include "../API.h"
#include "Vehicle.hpp"
namespace mp
{
	class Server : public rw::Server {
	public:
		void setGamemodeText(std::string text) { API::GetModule().SetGamemodeText(text); };
		void setWeather(int weather) { API::GetModule().SetWeather(weather); };
		bool setGravity(float gravity) { return API::GetModule().SetGravity(gravity); };
		int addClass(int model, rw::Vector3 position, float rotation) {
			return API::GetModule().AddPlayerClass(model, position.x, position.y, position.z, rotation, -1, -1, -1, -1, -1, -1);
		};
		int gtPlayerPoolSize() { return API::GetModule().GetPlayerPoolSize(); };
		int getVehiclePoolSize() { return API::GetModule().GetVehiclePoolSize(); };
		int getActorPoolSize() { return API::GetModule().GetActorPoolSize(); };
		rw::Vehicle* createVehicle(int model, rw::Vector3 position, float rotation, int color1, int color2, int respawnDelay) {
			return new mp::Vehicle(model, position, rotation, color1, color2, respawnDelay);
		};

	};
}