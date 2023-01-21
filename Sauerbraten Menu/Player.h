#pragma once

#include "Math.h"

#include <cstdint>

class Player
{
private:
	Player();
public:
	static int GetPlayerCount();
	static Player* GetPlayer(int index);

	int GetHealth();
	int GetArmor();

	const char* GetName();

	Vector3 GetBodyPosition();
	Vector3 GetHeadPosition();

	Vector2 GetViewAngles();

private:
	char pad_0000[48]; //0x0000
	Vector3 HeadPosition; //0x0030
	Vector2 ViewAngles; //0x003C
	char pad_0044[272]; //0x0044
	int32_t Health; //0x0154
	char pad_0158[4]; //0x0158
	int32_t Armor; //0x015C
	char pad_0160[8]; //0x0160
	int32_t WeapondType; //0x0168
	int32_t FireRate; //0x016C
	char pad_0170[104]; //0x0170
	bool IsShooting; //0x01D8
	char pad_01D9[111]; //0x01D9
	char Name[16]; //0x0248
	char pad_0258[780]; //0x0258
	Vector3 BodyPosition; //0x0564
	char pad_0570[2804]; //0x0570
};

