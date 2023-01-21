#include "Player.h"

#include "Offsets.h"
#include "Utils.h"

#include <Windows.h>

int Player::GetPlayerCount() {
	uintptr_t modBase = (uintptr_t)GetModuleHandle("sauerbraten.exe");
	int pCount = *(int*)(modBase + Offsets::dwPlayerCount);

	return pCount;
}

Player* Player::GetPlayer(int index) {
	uintptr_t modBase = (uintptr_t)GetModuleHandle("sauerbraten.exe");
	uintptr_t entityList = *(uintptr_t*)(modBase + Offsets::dwEntityList);

	return (Player*)*(uintptr_t*)(entityList + (index * 4));
}

int Player::GetHealth() {
	return Utils::HEXtoDEC(this->Health);
}

int Player::GetArmor() {
	return Utils::HEXtoDEC(this->Armor);
}

Vector3 Player::GetBodyPosition() {
	return this->BodyPosition;
}

Vector3 Player::GetHeadPosition() {
	return this->HeadPosition;
}

Vector2 Player::GetViewAngles() {
	return this->ViewAngles;
}

const char* Player::GetName() {
	return (const char*)this->Name;
}