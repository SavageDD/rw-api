/*

	RW:MP Modification
	Copyright 2018 RW:MP Team

*/

#pragma once
#ifdef _WIN32
	#include <windows.h>
#endif

#include <string>
#include <stdio.h>
#include <vector>

/* VECTOR STRUCTURE */
typedef struct _VECTOR {
	float X, Y, Z;
} VECTOR;

#ifdef _WIN32
	#define MP_API extern "C" __declspec(dllexport) 
#else
	#define MP_API extern "C"
#endif

class API_FUNCS 
{
	public:
		/* Utils */
		virtual void print(std::string message) = 0;
		virtual bool SendClientMessage(int playerID, unsigned int color, std::string message) = 0;

		virtual int GetPlayerPoolSize() = 0;
		virtual int GetVehiclePoolSize() = 0;
		virtual int GetActorPoolSize() = 0;

		/* Game functions */
		virtual void SetGamemodeText(std::string gamemode) = 0;
		virtual void SetWeather(int weatherID) = 0;
		virtual bool SetGravity(float gravity) = 0;

		/* Player functions */
		virtual std::string GetPlayerName(int playerID) = 0;
		virtual void SpawnPlayer(int playerID) = 0;
		virtual int AddPlayerClass(int skin, float posX, float posY, float posZ, float rotation, int weapon1, int weaponammo1, int weapon2, int weaponammo2, int weapon3, int weaponammo3) = 0;
		virtual bool SetPlayerPos(int playerID, float posX, float posY, float posZ) = 0;
		virtual VECTOR GetPlayerPos(int playerID) = 0;
		virtual bool SetPlayerInterior(int playerID, int interior) = 0;
		virtual int GetPlayerInterior(int playerID) = 0;
		virtual bool SetPlayerFacingAngle(int playerID, float angle) = 0;
		virtual bool SetPlayerCameraPos(int playerID, float posX, float posY, float posZ) = 0;
		virtual bool SetPlayerCameraLookAt(int playerID, float posX, float posY, float posZ) = 0;
		virtual bool GivePlayerMoney(int playerID, int amount) = 0;
		virtual bool GivePlayerWeapon(int playerID, int weaponID, int ammo) = 0;
		virtual bool ResetPlayerWeapons(int playerID) = 0;
		virtual bool SetPlayerWeather(int playerID, int weatherID) = 0;
		virtual bool SetPlayerTeam(int playerID, int teamID) = 0;
		virtual bool ShowPlayerDialog(int playerID, int dialogid, int style, std::string caption, std::string info, std::string button1, std::string button2) = 0;

		/* Vehicle functions */
		virtual int CreateVehicle(int modelID, float posX, float posY, float posZ, float rotation, int color1, int color2, int delay) = 0;
		virtual int AddStaticVehicle(int modelID, float posX, float posY, float posZ, float rotation, int color1, int color2) = 0;
		virtual bool ChangeVehicleColor(int vehicleID, int color1, int color2) = 0;
		virtual VECTOR GetVehiclePos(int vehicleID) = 0;
};

class API :
	public API_FUNCS
{
	public:
		static API * API_INSTANCE;
		static API& GetModule() { return *API_INSTANCE; }
};