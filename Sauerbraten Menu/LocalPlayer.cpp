#include "LocalPlayer.h"

#include "Offsets.h"
#include "Utils.h"

#include <iostream>

LocalPlayer* LocalPlayer::Get() {
	uintptr_t modBase = (uintptr_t)GetModuleHandle("sauerbraten.exe");
	LocalPlayer* p = (LocalPlayer*)*(uintptr_t*)(modBase + Offsets::dwLocalPlayer);

	return p;
}

uintptr_t LocalPlayer::GetBaseMod() {
    return (uintptr_t)GetModuleHandle("sauerbraten.exe");
}

int LocalPlayer::GetHealth() {
	return Utils::HEXtoDEC(this->Health);
}

int LocalPlayer::GetFOV() {
    return *(int*)(this->GetBaseMod() + Offsets::dwFOV);
}

int LocalPlayer::GetArmor() {
	return Utils::HEXtoDEC(this->Armor);
}

Vector3 LocalPlayer::GetBodyPosition() {
	return this->BodyPosition;
}

Vector3 LocalPlayer::GetHeadPosition() {
    return this->HeadPosition;
}

Vector2 LocalPlayer::GetViewAngles() {
	return this->ViewAngles;
}
 
void LocalPlayer::AimAt(Vector3 pos) {
	Vector2 angle = Math::CalcAngle(this->HeadPosition, pos);

	this->ViewAngles.x = angle.x;
	this->ViewAngles.y = angle.y;
}

void LocalPlayer::AimAtSmooth(Vector3 pos, float smooth) {
    Vector2 angle = Math::CalcAngle(this->HeadPosition, pos);
    Vector2 diffs = angle - this->ViewAngles;

    if (diffs.x > 180)
        diffs.x -= 360;

    if (diffs.x < -180)
        diffs.x += 360;

    this->ViewAngles.x -= diffs.x / smooth;
    this->ViewAngles.y -= diffs.y / smooth;
}


Player* LocalPlayer::GetClosestEnemy() {
    float closestDitance = 1000000;
    int closesDistanceIndex = 1;

    uintptr_t entityList = *(uintptr_t*)(this->GetBaseMod() + Offsets::dwEntityList);

    for (size_t i = 0; i < Player::GetPlayerCount(); i++)
    {
        Player* player = Player::GetPlayer(i);

        if (!player || player == NULL || player == nullptr)
            continue;

        if ((uintptr_t)player == (uintptr_t)this)
            continue;

        if (player->GetHealth() < 1)
            continue;

        if (this->HeadPosition.Distance(player->GetHeadPosition()) < closestDitance) {
            closestDitance = this->HeadPosition.Distance(player->GetHeadPosition());
            closesDistanceIndex = i;
        }
    }

    if (closesDistanceIndex == -1)
        return NULL;

    return Player::GetPlayer(closesDistanceIndex);
}

Player* LocalPlayer::GetClosestEnemyByFov(float fov) {
    float closestAngle = 1000000;
    int closesDistanceIndex = -1;

    uintptr_t entityList = *(uintptr_t*)(this->GetBaseMod() + Offsets::dwEntityList);

    for (size_t i = 0; i < Player::GetPlayerCount(); i++)
    {
        Player* player = Player::GetPlayer(i);

        if (!player || player == NULL || player == nullptr)
            continue;

        if ((uintptr_t)player == (uintptr_t)this)
            continue;

        if (player->GetHealth() < 1)
            continue;

        Vector2 diffs = (Math::CalcAngle(this->HeadPosition, player->GetHeadPosition()) - this->ViewAngles).Abs();

        if (diffs.x > 180)
            diffs.x -= 360;

        if (diffs.x < -180)
            diffs.x += 360;

        std::cout << diffs.Length2D() << std::endl;

        if (diffs.Length2D() > fov)
            continue;

        if (diffs.Length2D() < closestAngle) {
            closestAngle = diffs.Length2D();
            closesDistanceIndex = i;
        }
    }

    if (closesDistanceIndex == -1)
        return NULL;

    return Player::GetPlayer(closesDistanceIndex);
}

void LocalPlayer::TeleportTo(Vector3 pos) {
    this->HeadPosition = pos;
}

ViewMatrix LocalPlayer::GetViewMatrix()
{
    ViewMatrix mat;
    memcpy(&mat.matrix, (PBYTE*)(this->GetBaseMod() + Offsets::dwViewMatrix), sizeof(mat.matrix));

    return mat;
}

const char* LocalPlayer::GetName() {
    return (const char*)this->Name;
}

// Unused, couldn't get the math right :skull:
void LocalPlayer::FlyInCameraDir(float speed) {
    Math::MoveInCameraDirection(this->ViewAngles, this->HeadPosition, speed);
}