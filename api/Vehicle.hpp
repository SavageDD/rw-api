#pragma once
#include "api.hpp"
#include "../API.h"
namespace mp
{
	class Vehicle : public rw::Vehicle {
		int _id = 0;
	public:
		Vehicle(int model, rw::Vector3 position, float rotation, int color1, int color2, int respawnDelay) {
			_id = API::GetModule().CreateVehicle(model, position.x, position.y, position.z, rotation, color1, color2, respawnDelay);
		}
		int id() { return _id; };
		rw::Vector3 getPosition() {
			VECTOR pos = API::GetModule().GetVehiclePos(_id);
			return rw::Vector3(pos.X, pos.Y, pos.Z);
		};
		void setPosition(rw::Vector3 position) { }; //to do
		int getModel() { return 0; }; //to do
		void setModel(int model) {}; //to do
		void setRotation(float angle) { }; //to do

		void setColor(int color1, int color2){
			API::GetModule().ChangeVehicleColor(_id, color1, color2);
		};
	};
}