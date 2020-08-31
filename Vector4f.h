#pragma once
#include <math.h>

class Vector4f
{
public:
	union
	{
		struct 
		{
			float x, y, z, t;
		};
		float v[4];
	};

	inline Vector4f() : x(0), y(0), z(0), t(1) {}
	inline Vector4f(const float a, const float b, const float c) : x(a), y(b), z(c), t(1) {}
	inline Vector4f(const float a, const float b, const float c, const float d) : x(a), y(b), z(c), t(d) {}
	inline Vector4f(const Vector4f& copy) : x(copy.x), y(copy.y), z(copy.z), t(copy.t) {}

	inline Vector4f& operator= (const Vector4f& other)
	{
		x = other.x; y = other.y; z = other.z;
		return *this;
	}

	inline int operator== (const Vector4f& other) const
	{
		return (x == other.x && y == other.y && z == other.z);
	}
	
	inline int operator!= (const Vector4f& other) const
	{
		return (x != other.x || y != other.y || z != other.z);
	}

	inline void set(float newX, float newY, float newZ)
	{
		x = newX; y = newY; z = newZ; t = 1;
	}

	inline void set(float newX, float newY, float newZ, float newT)
	{
		x = newX; y = newY; z = newZ; t = newT;
	}

	inline void zero()
	{
		x = y = z = 0;
		t = 1;
	}

	inline static Vector4f one()
	{
		return Vector4f(1, 1, 1, 1);
	}

};
