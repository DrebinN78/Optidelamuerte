#pragma once
struct Vector
{
	float x;
	float y;

	Vector()
	{
		x = y = 0;
	}

	Vector(float x, float y)
	{
		this->x = x;
		this->y = y;
	}
};

