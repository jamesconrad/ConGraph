#pragma once

#include <Windows.h>


class vec2
{
public:
	int x, y;
	vec2() { x = y = 0; }
	vec2(int _x, int _y) { x = _x; y = _y; }

	COORD coord()
	{
		COORD c;
		c.X = x;
		c.Y = y;
		return c;
	}

	vec2 operator+ (const vec2 &r)
	{
		return vec2(x + r.x, y + r.y);
	}
	vec2 operator+= (const vec2 &r)
	{
		x += r.x; y += r.y;
	}
	vec2 operator- (const vec2 &r)
	{
		return vec2(x - r.x, y - r.y);
	}
	vec2 operator-= (const vec2 &r)
	{
		x -= r.x; y -= r.y;
	}
	vec2 operator* (const int f)
	{
		return vec2(x*f, y*f);
	}
	vec2 operator*= (const int f)
	{
		x *= f;
		y *= f;
	}
};