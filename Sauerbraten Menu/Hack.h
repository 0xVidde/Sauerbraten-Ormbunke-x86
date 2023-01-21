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
float conf_smoothing = 10;
bool conf_SMOOTH = true;
bool conf_AIMBOT_ON = false;

bool conf_ESP_ON = false;

bool conf_Draw2DBox = false;
bool conf_Draw2DFilledBox = false;
bool conf_DrawTracers = false;
bool conf_DrawName = false;

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
        conf_AIMBOT_ON = !conf_AIMBOT_ON;
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
            Vector3 bodyScreenPos;
            Vector3 bodyPos = Vector3(player->GetHeadPosition().x, player->GetHeadPosition().y, player->GetHeadPosition().z - 13);
            if (!Math::WorldToScreen(bodyPos, bodyScreenPos, viewMatrix.matrix, windowRes.x, windowRes.y))
                continue;

            Vector3 headScreenPos;
            Vector3 headPos = Vector3(player->GetHeadPosition().x, player->GetHeadPosition().y, player->GetHeadPosition().z + 3);
            if (!Math::WorldToScreen(headPos, headScreenPos, viewMatrix.matrix, windowRes.x, windowRes.y))
                continue;

            float dist = LocalPlayer::Get()->GetHeadPosition().Distance(player->GetHeadPosition());

            float tempX = pow((bodyScreenPos.x, headScreenPos.x), 2);
            float tempY = pow((bodyScreenPos.y, headScreenPos.y), 2);
            float height = sqrt(tempX + tempY);
            height = height / dist;

            const char* name = player->GetName();

            if (conf_DrawTracers)
                pDrawList->AddLine(ImVec2(windowRes.x / 2, windowRes.y), ImVec2(bodyScreenPos.x, bodyScreenPos.y), conf_TracerColor, 2);

            if (conf_Draw2DBox)
                pDrawList->AddRect(
                    ImVec2(headScreenPos.x + (height * 2.5), headScreenPos.y),
                    ImVec2(bodyScreenPos.x - (height * 2.5), bodyScreenPos.y),
                    conf_BoxColor);

            if (conf_Draw2DFilledBox)
                pDrawList->AddRectFilled(
                    ImVec2(headScreenPos.x + (height * 2.5), headScreenPos.y),
                    ImVec2(bodyScreenPos.x - (height * 2.5), bodyScreenPos.y),
                    conf_FilledBoxColor);

            if (conf_DrawName)
                pDrawList->AddText(ImVec2(headScreenPos.x - (height / 3), headScreenPos.y - 8), conf_TextColor, name);
        }
    }

    ImGui::End();
}