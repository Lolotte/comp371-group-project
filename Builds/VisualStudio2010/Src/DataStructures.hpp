#pragma once

template<typename T>
class Vector3
{
public:
	Vector3() : x(0), y(0), z(0) {}

	Vector3(T x1, T y1, T z1)
		: x(x1), y(y1), z(z1)
	{
	}

	T x;
	T y;
	T z;
};

template<typename T>
class Rect
{
public:
	Rect() : x(0), y(0), width(0), height(0) {}

	Rect(T x1, T y1, T w, T h)
		: x(x1), y(y1), width(w), height(h)
	{
	}

	T x;
	T y;
	T width;
	T height;
};