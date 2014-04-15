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

	void add(Vector3 const& other)
	{
		this->x += other.x;
		this->y += other.y;
		this->z += other.z;
	}

	T x;
	T y;
	T z;
};

template<typename T>
Vector3<T> add(Vector3<T> const& v1, Vector3<T> const& v2)
{
	Vector3<T> result;

	result.x = v1.x + v2.x;
	result.y = v1.y + v2.y;
	result.z = v1.z + v2.z;
}

template<typename T>
class Vector2
{
public:
	Vector2() : x(0), y(0) {}

	Vector2(T x1, T y1)
		: x(x1), y(y1)
	{
	}

	T x;
	T y;
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