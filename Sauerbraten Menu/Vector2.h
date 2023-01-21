#pragma once

struct Vector2
{
	float x, y;

	Vector2()
	{
		this->x = this->y = 0;
	}

	Vector2(float _x, float _y)
	{
		this->x = _x;
		this->y = _y;
	}

	Vector2 operator+(const Vector2& o)
	{
		Vector2 result;
		result.x = o.x + this->x;
		result.y = o.y + this->y;
		return result;
	}

	Vector2 operator-(const Vector2& o)
	{
		Vector2 result;
		result.x = o.x - this->x;
		result.y = o.y - this->y;
		return result;
	}
};