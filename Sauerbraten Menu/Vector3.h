#pragma once

#define PI 3.14159265359

#include <math.h>

struct Vector3
{
	float x, y, z;

	Vector3()
	{
		this->x = this->y = this->z = 0;
	}

	Vector3(float _x, float _y, float _z)
	{
		this->x = _x;
		this->y = _y;
		this->z = _z;
	}

	Vector3 operator+(const Vector3& o)
	{
		Vector3 result;
		result.x = o.x + this->x;
		result.y = o.y + this->y;
		result.z = o.z + this->z;
		return result;
	}

	Vector3 operator-(const Vector3& o)
	{
		Vector3 result;
		result.x = o.x - this->x;
		result.y = o.y - this->y;
		result.z = o.z - this->z;
		return result;
	}

	float Distance(const Vector3& o)
	{
		Vector3 self(this->x, this->y, this->z);
		Vector3 diff = self - o;
		return sqrt((diff.x * diff.x) + (diff.y * diff.y) + (diff.z * diff.z));
	}
};