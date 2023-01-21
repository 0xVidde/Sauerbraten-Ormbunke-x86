// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"

#include "Hack.h"

#include "Include/imgui_hook.h"
#include "Include/imgui/imgui.h"

#include "Include/kiero/minhook/include/MinHook.h"


void HackThread(HMODULE hModule) {
    FILE* pFile = nullptr;
    AllocConsole();
    freopen_s(&pFile, "CONOUT$", "w", stdout);
    ImGuiHook::Load(RenderMain);

    Utils::TypewriterPrint("Successfully Loaded OrmBunke!\n\n", 35);

    Utils::TypewriterPrint("--- Keybinds ---\n", 60);
    Utils::TypewriterPrint("[NUM 0] << Toggle ESP\n", 60);
    Utils::TypewriterPrint("[NUM 1] << Filled Box ESP\n", 60);
    Utils::TypewriterPrint("[NUM 2] << Box ESP\n", 60);
    Utils::TypewriterPrint("[NUM 3] << Tracer ESP\n", 60);
    Utils::TypewriterPrint("[NUM 4] << Name ESP\n", 60);
    Utils::TypewriterPrint("[NUM 5] << Toggle Aimbot (Left Shift)\n\n", 60);

    Utils::TypewriterPrint("[Up Arrow] << Increase Aimbot Smoothness\n", 60);
    Utils::TypewriterPrint("[Down Arrow] << Decrease Aimbot Smoothness\n\n", 60);
    Utils::TypewriterPrint("[END] << Close\n", 43);
    Utils::TypewriterPrint("----------------\n", 43);


    while (!GetAsyncKeyState(VK_END)) {
        HackRun();

        Sleep(1);
    }

    printf("\n\nExiting...");
    printf("\n\nYou Can Now Close This Console.");

    FreeConsole();
    ImGuiHook::Unload();
    FreeLibraryAndExitThread(hModule, 1);
}


BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        CloseHandle(CreateThread(0, 0, (LPTHREAD_START_ROUTINE)HackThread, hModule, 0, 0));
        break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

