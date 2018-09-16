#pragma once
#include "api.hpp"
#include "../API.h"
namespace mp
{
	class Player : public rw::Player {
		short _id = 0;
		int money = 0;
	public:
		Player(short id) : _id(id) {}
		int id() { return _id; };
		rw::Vector3 getPosition() {
			VECTOR pos = API::GetModule().GetPlayerPos(_id);
			return rw::Vector3(pos.X, pos.Y, pos.Z);
		};
		void setPosition(rw::Vector3 position) {
			API::GetModule().SetPlayerPos(_id, position.x, position.y, position.z);
		};
		int getModel() {
			//not ready
			return 0;
		};
		void setModel(int model) {
			//not ready
		};
		void setRotation(float angle) {
			API::GetModule().SetPlayerFacingAngle(_id, angle);
		};


		std::string getName() {
			return API::GetModule().GetPlayerName(_id);
		};
		void setInterior(int interion) {
			API::GetModule().SetPlayerInterior(_id, interion);
		};
		int getInterior() {
			return API::GetModule().GetPlayerInterior(_id);
		};
		void giveMoney(int money) {
			API::GetModule().GivePlayerMoney(_id, money);
			this->money += money;
		};
		int getMoney() {
			return money;
		};
		void giveWeapon(int weapon, int ammo) {
			API::GetModule().GivePlayerWeapon(_id, weapon, ammo);
		};
		void clearWeapons() {
			API::GetModule().ResetPlayerWeapons(_id);
		};
		void setTeam(int team) {
			API::GetModule().SetPlayerTeam(_id, team);
		};
		void message(std::string text) {
			API::GetModule().SendClientMessage(_id, -1, text);
		};
		void spawn() {
			API::GetModule().SpawnPlayer(_id);
		};
		void setWeather(int weather) {
			API::GetModule().SetPlayerWeather(_id, weather);
		};
	};
}