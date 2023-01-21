#pragma once

#include "ViewMatrix.h"
#include "Vector4.h"
#include "Vector3.h"
#include "Vector2.h"

namespace Math {
	Vector2 CalcAngle(Vector3 src, Vector3 dst);

	bool WorldToScreen(Vector3 pos, Vector3& screen, float matrix[16], int windowWidth, int windowHeight);

	float DegreeToRadian(float degree);
	Vector3 DegreeToRadian(Vector3 degrees);
	void MoveInCameraDirection(Vector2 currAngle, Vector3& src, float dist);
}