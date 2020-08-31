#pragma once
#include <math.h>

class Vector3f 
{
public:
	union
	{
		struct 
		{
			float x, y, z;
		};
		float v[3];
	};

	inline Vector3f() : x(0), y(0), z(0) {}
	inline Vector3f(const float a, const float b, const float c) : x(a), y(b), z(c) {}
	inline Vector3f(const Vector3f& copy) : x(copy.x), y(copy.y), z(copy.z) {}

	inline Vector3f& operator= (const Vector3f& other)
	{
		x = other.x; y = other.y; z = other.z;
		return *this;
	}

	inline int operator== (const Vector3f& other) const 
	{
		return (x == other.x && y == other.y && z == other.z);
	}
	
	inline int operator!= (const Vector3f& other) const 
	{
		return (x != other.x || y != other.y || z != other.z);
	}

	inline Vector3f operator+ (const Vector3f& other) const 
	{
		return Vector3f(x + other.x, y + other.y, z + other.z);
	}

	inline Vector3f operator- (const Vector3f& other) const 
	{
		return Vector3f(x - other.x, y - other.y, z - other.z);
	}

	inline Vector3f operator* (const float& value) const 
	{
		return Vector3f(x * value, y * value, z * value);
	}

	inline Vector3f operator/ (const float& value) const 
	{
		return Vector3f(x / value, y / value, z / value);
	}

	inline Vector3f& operator+= (const Vector3f& other) 
	{
		x += other.x;
		y += other.y;
		z += other.z;
		return *this;
	}
	inline Vector3f& operator-= (const Vector3f& other) 
	{
		x -= other.x;
		y -= other.y;
		z -= other.z;
		return *this;
	}

	inline Vector3f& operator*= (const float& value) 
	{
		x *= value;
		y *= value;
		z *= value;
		return *this;
	}

	inline Vector3f& operator/= (const float& value) 
	{
		x /= value;
		y /= value;
		z /= value;
		return *this;
	}

	inline float length() const 
	{
		float len = (x * x) + (y * y) + (z * z);
		return (float)sqrt(len);
	}

	inline float lengthSq() const
	{
		return (x * x) + (y * y) + (z * z);
	}

	inline float dotProduct(const Vector3f& other) const
	{
		return (x * other.x) + (y * other.y) + (z * other.z);
	}

	inline Vector3f crossProduct(const Vector3f& other) const
	{
		return Vector3f(
			(y * other.z) - (z * other.y),
			(z * other.x) - (x * other.z),
			(x * other.y) - (y * other.x)
		);
	}

	inline void normalize() 
	{
		float len = length();
		if (len == 0)return;
		len = 1.0f / len;
		x *= len;
		y *= len;
		z *= len;
	}

	inline float distance(const Vector3f& other) const
	{
		return (Vector3f(other.x - x, other.y - y, other.z - z)).length();
	}

	inline float distanceSq(const Vector3f& other) const
	{
		return (Vector3f(other.x - x, other.y - y, other.z - z)).lengthSq();
	}

	inline void set(float newX, float newY, float newZ)
	{
		x = newX; y = newY; z = newZ;
	}

	inline void zero() 
	{
		x = y = z = 0;
	}

	inline static Vector3f one()
	{
		return Vector3f(1, 1, 1);
	}

};
