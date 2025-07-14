#pragma once
#include "raylib.h"

#include <random>
using std::random_device;
using std::mt19937;
using std::uniform_int_distribution;

#include <cmath>

#pragma region Structs

// rm for right member

struct Vect2F 
{
	float x;
	float y;

	static const Vect2F zero;
	static const Vect2F one;
	static const Vect2F up;
	static const Vect2F down;
	static const Vect2F right;
	static const Vect2F left;

	Vect2F() = default;
	Vect2F(float x_, float y_) : x{ x_ }, y{ y_ } {}
	Vect2F(Vector2 vector2_) : x{ vector2_.x }, y{ vector2_.y } {}

	//Addition
	Vect2F operator+(const Vect2F& rm) const { return { x + rm.x, y + rm.y }; }

	//Substraction
	Vect2F operator-(const Vect2F& rm) const { return { x - rm.x, y - rm.y }; }

	//Scale
	//Up
	Vect2F operator*(const float& rm) const { return { x * rm, y * rm }; }
	Vect2F operator*(const int& rm) const { return { x * rm, y * rm }; }
	//Down
	Vect2F operator/(const float& rm) const { return { x / rm, y / rm }; }
	Vect2F operator/(const int& rm) const { return { x / rm, y / rm }; }

	//Multiplication
	Vect2F operator*(const Vect2F& rm) const { return { x * rm.x, y * rm.y }; }

	//Division
	Vect2F operator/(const Vect2F& rm) const { return { x / rm.x, y / rm.y }; }

	//Boolean
	bool operator==(const Vect2F& rm) const;
	bool operator!=(const Vect2F& rm) const { return !(*this == rm); }

	//Functions
	float dot(const Vect2F& other) const { return x * other.x + y * other.y; }

	float sqrLength() const { return x * x + y * y; }
	float length() const { return sqrtf(this->sqrLength()); }

	Vect2F absolute() const;
	Vect2F normalized() const;

	Vector2 toRaylib() const { return { x, y }; }
};

struct Vect2I
{
	int x;
	int y;

	static const Vect2I zero;
	static const Vect2I one;
	static const Vect2I up;
	static const Vect2I down;
	static const Vect2I right;
	static const Vect2I left;

	Vect2I() = default;
	Vect2I(int x_, int y_) : x{ x_ }, y{ y_ } {}

	//Addition
	Vect2I operator+(const Vect2I& rm) const { return { x + rm.x, y + rm.y }; }

	//Substraction
	Vect2I operator-(const Vect2I& rm) const { return { x - rm.x, y - rm.y }; }

	//Scale
	//Up
	Vect2I operator*(const int& rm) const { return { x * rm, y * rm }; }
	//Down
	Vect2I operator/(const int& rm) const { return { x / rm, y / rm }; }

	//Multiplication
	Vect2I operator*(const Vect2I& rm) const { return { x * rm.x, y * rm.y }; }

	//Division
	Vect2I operator/(const Vect2I& rm) const { return { x / rm.x, y / rm.y }; }

	//Boolean
	bool operator==(const Vect2I& rm) const { return (x == rm.x && y == rm.y); }
	bool operator!=(const Vect2I& rm) const { return !(*this == rm); }

	//Functions
	int dot(const Vect2I& other) const { return x * other.x + y * other.y; }
	 
	int sqrLength() const { return x * x + y * y; }
	float length() const { return sqrtf((float) this->sqrLength()); }

	Vect2I absolute() const;

	Vector2 toRaylib() const { return { (float) x, (float) y }; }
};

struct Vect3F
{
	float x;
	float y;
	float z;

	static const Vect3F zero;
	static const Vect3F one;
	static const Vect3F forward;
	static const Vect3F back;
	static const Vect3F up;
	static const Vect3F down;
	static const Vect3F right;
	static const Vect3F left;

	Vect3F() = default;
	Vect3F(float x_, float y_, float z_) : x{ x_ }, y{ y_ }, z{ z_ } {}
	Vect3F(Vector3 vector3_) : x{ vector3_.x }, y{ vector3_.y }, z{ vector3_.z } {}

	//Addition
	Vect3F operator+(const Vect3F& rm) const { return { x + rm.x, y + rm.y, z + rm.z }; }

	//Substraction
	Vect3F operator-(const Vect3F& rm) const { return { x - rm.x, y - rm.y, z - rm.z }; }

	//Scale
	//Up
	Vect3F operator*(const float& rm) const { return { x * rm, y * rm, z * rm }; }
	Vect3F operator*(const int& rm) const { return { x * rm, y * rm, z * rm }; }
	//Down
	Vect3F operator/(const float& rm) const { return { x / rm, y / rm, z / rm }; }
	Vect3F operator/(const int& rm) const { return { x / rm, y / rm, z / rm }; }

	//Multiplication
	Vect3F operator*(const Vect3F& rm) const { return { x * rm.x, y * rm.y, z * rm.z}; }

	//Division
	Vect3F operator/(const Vect3F& rm) const { return { x / rm.x, y / rm.y, z / rm.z }; }

	//Boolean
	bool operator==(const Vect3F& rm) const;
	bool operator!=(const Vect3F& rm) const { return !(*this == rm); }

	//Functions
	float dot(const Vect3F& other) const { return x * other.x + y * other.y + z * other.z; }

	float sqrLength() const { return x * x + y * y + z * z; }
	float length() const { return sqrtf(this->sqrLength()); }

	Vect3F absolute() const;
	Vect3F normalized() const;

	Vector3 toRaylib() const { return { x, y, z }; }
};

struct Vect3I
{
	int x;
	int y;
	int z;

	static const Vect3I zero;
	static const Vect3I one;
	static const Vect3I forward;
	static const Vect3I back;
	static const Vect3I up;
	static const Vect3I down;
	static const Vect3I right;
	static const Vect3I left;

	Vect3I() = default;
	Vect3I(int x_, int y_, int z_) : x{ x_ }, y{ y_ }, z{ z_ } {}

	//Addition
	Vect3I operator+(const Vect3I& rm) const { return { x + rm.x, y + rm.y, z + rm.z }; }

	//Substraction
	Vect3I operator-(const Vect3I& rm) const { return { x - rm.x, y - rm.y, z - rm.z }; }

	//Scale
	//Up
	Vect3I operator*(const int& rm) const { return { x * rm, y * rm, z * rm }; }
	//Down
	Vect3I operator/(const int& rm) const { return { x / rm, y / rm, z / rm }; }

	//Multiplication
	Vect3I operator*(const Vect3I& rm) const { return { x * rm.x, y * rm.y, z * rm.z }; }

	//Division
	Vect3I operator/(const Vect3I& rm) const { return { x / rm.x, y / rm.y, z / rm.z }; }

	//Boolean
	bool operator==(const Vect3I& rm) const { return (x == rm.x && y == rm.y && z == rm.z); }
	bool operator!=(const Vect3I& rm) const { return !(*this == rm); }
	
	//Functions
	int dot(const Vect3I& other) const { return x * other.x + y * other.y + z * other.z; }

	int sqrLength() const { return x * x + y * y + z * z; }
	float length() const { return sqrtf((float) this->sqrLength()); }

	Vect3I absolute() const;

	Vector3 toRaylib() const { return { (float)x, (float)y, (float)z }; }
};

#pragma endregion



class Utils
{
private:
	Utils() = default;
	~Utils() = default;

public:
	//Math functions
	static float Min(float a, float b);
	static float Max(float a, float b);
	static float Clamp(float value, float min, float max);
	static float Abs(float value);
	static float Sign(float value);

	static bool nearlyEqual(const float a, const float b);

	static float Lerp(float a, float b, float t);
	static Vector2 Vector2Lerp(Vector2 a, Vector2 b, float t);
	static Vector3 Vector2Lerp(Vector3 a, Vector3 b, float t);
	static Vect2F Vect2FLerp(Vect2F a, Vect2F b, float t);
	static Vect3F Vect3FLerp(Vect3F a, Vect3F b, float t);

	static int RandInt(int min, int max);



};

