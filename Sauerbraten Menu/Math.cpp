#include "Math.h"

Vector2 Math::CalcAngle(Vector3 src, Vector3 dst)
{
	Vector2 angle;
	angle.x = -atan2f(dst.x - src.x, dst.y - src.y) / (float)PI * 180;
	angle.y = asinf((dst.z - src.z) / src.Distance(dst)) * 180 / (float)PI;

	return angle;
}

float Math::DegreeToRadian(float degree)
{
	return degree * (3.14 / 180);
}

Vector3 Math::DegreeToRadian(Vector3 degrees)
{
	Vector3 radians;
	radians.x = degrees.x * (3.14 / 180);
	radians.y = degrees.y * (3.14 / 180);
	radians.z = degrees.z * (3.14 / 180);
	return radians;
}

// Unused because bad math
void Math::MoveInCameraDirection(Vector2 currAngle, Vector3& src, float dist)
{
	Vector3 d;

	d.x = cosf(DegreeToRadian(currAngle.x)) * dist;
	d.y = sinf(DegreeToRadian(currAngle.x)) * dist;
	d.z = sinf(DegreeToRadian(currAngle.y)) * dist;

	src = src + d;
}

// GH on top
bool Math::WorldToScreen(Vector3 pos, Vector3& screen, float matrix[16], int windowWidth, int windowHeight) {
	//Matrix-vector Product, multiplying world(eye) coordinates by projection matrix = clipCoords
	Vector4 clipCoords;
	clipCoords.x = pos.x * matrix[0] + pos.y * matrix[4] + pos.z * matrix[8] + matrix[12];
	clipCoords.y = pos.x * matrix[1] + pos.y * matrix[5] + pos.z * matrix[9] + matrix[13];
	clipCoords.z = pos.x * matrix[2] + pos.y * matrix[6] + pos.z * matrix[10] + matrix[14];
	clipCoords.w = pos.x * matrix[3] + pos.y * matrix[7] + pos.z * matrix[11] + matrix[15];

	if (clipCoords.w < 0.1f)
		return false;

	//perspective division, dividing by clip.W = Normalized Device Coordinates
	Vector3 NDC;
	NDC.x = clipCoords.x / clipCoords.w;
	NDC.y = clipCoords.y / clipCoords.w;
	NDC.z = clipCoords.z / clipCoords.w;

	//Transform to window coordinates
	screen.x = (windowWidth / 2 * NDC.x) + (NDC.x + windowWidth / 2);
	screen.y = -(windowHeight / 2 * NDC.y) + (NDC.y + windowHeight / 2);
	return true;
}