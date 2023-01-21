#include "Utils.h"

#include <sstream>
#include <string>
#include <iostream>

#include <thread>       
#include <chrono>       

HWND window;

int Utils::HEXtoDEC(uintptr_t hexVal) {
	std::stringstream stream;
	stream << std::dec << hexVal;

	return atoi(stream.str().c_str());
}

BOOL CALLBACK enumWind(HWND handle, LPARAM lp) {
    DWORD procId;
    GetWindowThreadProcessId(handle, &procId);
    if (GetCurrentProcessId() != procId)
        return TRUE;

    window = handle;
    return FALSE;
}

ImVec2 Utils::GetWindowRes() {
    window = NULL;
    EnumWindows(enumWind, NULL);

    RECT size;
    GetWindowRect(window, &size);

    return ImVec2(size.right - size.left - 5, size.bottom - size.top - 29);
}

// I hope this is a safe way to do it
void Utils::TypewriterPrint(std::string msg, int speed) {
    for (size_t i = 0; i < strlen(msg.c_str()); i++)
    {
        i < strlen(msg.c_str()) ? std::cout << msg[i] : std::cout << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000 / speed));
    }
}