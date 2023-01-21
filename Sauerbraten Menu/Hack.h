#pragma once

#include "Offsets.h"

#include "Math.h"
#include "LocalPlayer.h"
#include "Player.h"

#include "Utils.h"

#include <iostream>
#include <WinUser.h>

#include "Include/imgui_hook.h"
#include "Include/imgui/imgui.h"

#include "Include/kiero/minhook/include/MinHook.h"

#pragma region Config

bool conf_AIMBOT_ON = false;
bool conf_SMOOTH = true;
float conf_smoothing = 10;

bool conf_FOV_AIMBOT_ON = false;
bool conf_Draw_FOV_Circle = true;
float conf_Aimbot_FOV = 30;

bool conf_ESP_ON = true;

bool conf_Draw2DBox = false;
bool conf_Draw2DFilledBox = false;
bool conf_DrawTracers = false;
bool conf_DrawName = false;
bool conf_DrawHeadCircle = false;
bool conf_DrawSpine = false;
bool conf_DrawFOVCircle = false;

ImColor conf_TextColor = ImColor(0, 0, 255);
ImColor conf_TracerColor = ImColor(255, 0, 0);
ImColor conf_BoxColor = ImColor(0, 255, 0);
ImColor conf_FilledBoxColor = ImColor(0, 255, 0, 70);

#pragma endregion

void Aimbot(LocalPlayer* localPlayer) {
    if (!conf_AIMBOT_ON)
        return;

    Player* closestPlayer = localPlayer->GetClosestEnemy();

    if (localPlayer->GetHealth() < 1)
        return;

    if (!closestPlayer)
        return;

    if (closestPlayer->GetHealth() < 1)
        return;

    if (closestPlayer && GetAsyncKeyState(VK_SHIFT)) {

        Vector3 headPos = Vector3(closestPlayer->GetHeadPosition().x, closestPlayer->GetHeadPosition().y, closestPlayer->GetHeadPosition().z - 2);

        if (conf_SMOOTH)
            localPlayer->AimAtSmooth(headPos, conf_smoothing);
        else
            localPlayer->AimAt(headPos);
    }
}

void FovAimbot(LocalPlayer* localPlayer) {
    if (!conf_FOV_AIMBOT_ON)
        return;

    Player* closestPlayer = localPlayer->GetClosestEnemyByFov(conf_Aimbot_FOV);

    if (localPlayer->GetHealth() < 1)
        return;

    if (!closestPlayer)
        return;

    if (closestPlayer->GetHealth() < 1)
        return;

    if (closestPlayer && GetAsyncKeyState(VK_SHIFT)) {
        Vector3 headPos = Vector3(closestPlayer->GetHeadPosition().x, closestPlayer->GetHeadPosition().y, closestPlayer->GetHeadPosition().z - 2);

        if (conf_SMOOTH)
            localPlayer->AimAtSmooth(headPos, conf_smoothing);
        else
            localPlayer->AimAt(headPos);
    }
}

void HackRun() {
    LocalPlayer* localPlayer = LocalPlayer::Get();

    Aimbot(localPlayer);
    FovAimbot(localPlayer);

    if (GetAsyncKeyState(VK_NUMPAD0) & 0x1) {
        conf_ESP_ON = !conf_ESP_ON;
        Utils::TypewriterPrint("Toggled Esp.\n", 1000);
    }

    if (GetAsyncKeyState(VK_NUMPAD1) & 0x1) {
        conf_Draw2DFilledBox = !conf_Draw2DFilledBox;
        Utils::TypewriterPrint("Toggled Filled Box Esp.\n", 1000);
    }

    if (GetAsyncKeyState(VK_NUMPAD2) & 0x1) {
        conf_Draw2DBox = !conf_Draw2DBox;
        Utils::TypewriterPrint("Toggled Box Esp.\n", 1000);
    }

    if (GetAsyncKeyState(VK_NUMPAD3) & 0x1) {
        conf_DrawTracers = !conf_DrawTracers;
        Utils::TypewriterPrint("Toggled Tracer Esp.\n", 1000);
    }

    if (GetAsyncKeyState(VK_NUMPAD4) & 0x1) {
        conf_DrawName = !conf_DrawName;
        Utils::TypewriterPrint("Toggled Name Esp.\n", 1000);
    }

    if (GetAsyncKeyState(VK_NUMPAD5) & 0x1) {
        conf_DrawHeadCircle = !conf_DrawHeadCircle;
        Utils::TypewriterPrint("Toggled Head Circle ESP.\n", 1000);
    }

    if (GetAsyncKeyState(VK_NUMPAD6) & 0x1) {
        conf_DrawSpine = !conf_DrawSpine;
        Utils::TypewriterPrint("Toggled Spine ESP.\n", 1000);
    }

    if (GetAsyncKeyState(VK_NUMPAD7) & 0x1) {
        conf_DrawFOVCircle = !conf_DrawFOVCircle;
        Utils::TypewriterPrint("Toggled FOV Circle.\n", 1000);
    }


    if (GetAsyncKeyState(VK_NUMPAD8) & 0x1) {
        conf_FOV_AIMBOT_ON = !conf_FOV_AIMBOT_ON;
        conf_AIMBOT_ON = false;
        Utils::TypewriterPrint("Toggled FOV Aimbot.\n", 1000);
    }

    if (GetAsyncKeyState(VK_NUMPAD9) & 0x1) {
        conf_AIMBOT_ON = !conf_AIMBOT_ON;
        conf_FOV_AIMBOT_ON = false;
        Utils::TypewriterPrint("Toggled Aimbot.\n", 1000);
    }




    if (GetAsyncKeyState(VK_DOWN) & 0x1) {
        if ((conf_smoothing - 2) > 0) {
            conf_smoothing -= 2;
            Utils::TypewriterPrint("Decreased Smoothness.\n", 1000);
        }
    }

    if (GetAsyncKeyState(VK_UP) & 0x1) {
        conf_smoothing += 2;
        Utils::TypewriterPrint("Increased Smoothness.\n", 1000);
    }

    if (GetAsyncKeyState(VK_DOWN) & 0x1) {
        if ((conf_smoothing - 2) > 0) {
            conf_smoothing -= 2;
            Utils::TypewriterPrint("Decreased Smoothness.\n", 1000);
        }
    }

    if (GetAsyncKeyState(VK_RIGHT) & 0x1) {
        conf_Aimbot_FOV += 2;
        Utils::TypewriterPrint("Increased Aimbot FOV.\n", 1000);
    }

    if (GetAsyncKeyState(VK_LEFT) & 0x1) {
        if ((conf_Aimbot_FOV - 5) > 0) {
            conf_Aimbot_FOV -= 5;
            Utils::TypewriterPrint("Decreased Aimbot FOV.\n", 1000);
        }
    }
}

void RenderMain()
{
    ViewMatrix viewMatrix = LocalPlayer::Get()->GetViewMatrix();
    ImVec2 windowRes = Utils::GetWindowRes();

    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::SetNextWindowSize(windowRes);
    ImGui::Begin("Overlay", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_NoBackground);

    auto pDrawList = ImGui::GetWindowDrawList();

    if (conf_ESP_ON) {
        for (size_t i = 0; i < Player::GetPlayerCount(); i++)
        {
            Player* player = Player::GetPlayer(i);

            if (!player || player == (Player*)LocalPlayer::Get())
                continue;

            if (player->GetHealth() < 1)
                continue;

            // Haven't found the real body pos so this make do. (player->BodyPosition addressturned out to be gargade)
            Vector3 boxBottomPos;
            Vector3 bodyPos = Vector3(player->GetHeadPosition().x, player->GetHeadPosition().y, player->GetHeadPosition().z - 13);
            if (!Math::WorldToScreen(bodyPos, boxBottomPos, viewMatrix.matrix, windowRes.x, windowRes.y))
                continue;

            Vector3 boxTopPos;
            Vector3 headTempPos = Vector3(player->GetHeadPosition().x, player->GetHeadPosition().y, player->GetHeadPosition().z + 3);
            if (!Math::WorldToScreen(headTempPos, boxTopPos, viewMatrix.matrix, windowRes.x, windowRes.y))
                continue;

            Vector3 headPos;
            if (!Math::WorldToScreen(player->GetHeadPosition(), headPos, viewMatrix.matrix, windowRes.x, windowRes.y))
                continue;

            float dist = LocalPlayer::Get()->GetHeadPosition().Distance(player->GetHeadPosition());

            float tempX = pow((boxBottomPos.x, boxTopPos.x), 2);
            float tempY = pow((boxBottomPos.y, boxTopPos.y), 2);
            float height = sqrt(tempX + tempY);
            height = height / dist;

            const char* name = player->GetName();

            if (conf_DrawTracers)
                pDrawList->AddLine(ImVec2(windowRes.x / 2, windowRes.y), ImVec2(boxBottomPos.x, boxBottomPos.y), conf_TracerColor, 2);

            if (conf_Draw2DBox)
                pDrawList->AddRect(
                    ImVec2(boxTopPos.x + (height * 2.5), boxTopPos.y),
                    ImVec2(boxBottomPos.x - (height * 2.5), boxBottomPos.y),
                    conf_BoxColor);

            if (conf_Draw2DFilledBox)
                pDrawList->AddRectFilled(
                    ImVec2(boxTopPos.x + (height * 2.5), boxTopPos.y),
                    ImVec2(boxBottomPos.x - (height * 2.5), boxBottomPos.y),
                    conf_FilledBoxColor);

            // Working On Head Circle
            if (conf_DrawHeadCircle)
                pDrawList->AddCircle(ImVec2(headPos.x, headPos.y), 4.5, ImColor(255, 255, 255));

            if (conf_DrawSpine)
                pDrawList->AddLine(ImVec2(headPos.x, headPos.y), ImVec2(boxBottomPos.x, boxBottomPos.y), conf_TracerColor);

            if (conf_DrawName)
                pDrawList->AddText(ImVec2(boxTopPos.x - (height / 3), boxTopPos.y - 8), conf_TextColor, name);
        }

        if (conf_DrawFOVCircle) {
            float rad = tanf(Math::DegreeToRadian(conf_Aimbot_FOV) / 2) / tanf(Math::DegreeToRadian(LocalPlayer::Get()->GetFOV()) / 2) * windowRes.x;

            pDrawList->AddCircle(ImVec2(windowRes.x / 2, windowRes.y / 2), rad, ImColor(255, 255, 255));
        }
    }

    ImGui::End();
}