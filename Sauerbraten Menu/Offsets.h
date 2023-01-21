#pragma once

#include <Windows.h>

namespace Offsets {
	static uintptr_t dwEntityList = 0x2B80F8;
	static uintptr_t dwPlayerCount = 0x2B8728;
	static uintptr_t dwLocalPlayer = 0x21E89C;
	static uintptr_t dwViewMatrix = 0x2A3D70;
	static uintptr_t dwFOV = 0x2A3CAC;

	static uintptr_t windowWidthPtr = 0x2B6D34;
	static uintptr_t windowHeightPtr = 0x2B6D38;
}