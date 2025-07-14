#include "Utils.h"

float Utils::Min(float a, float b)
{
	return (a <= b) ? a : b;
}

float Utils::Max(float a, float b)
{
	return (a >= b) ? a : b;
}

float Utils::Abs(float value)
{
	return (value < 0) ? -value : value;
}

float Utils::Clamp(float value, float min, float max)
{
	return Max(Min(value, max), min);
}

float Utils::Lerp(float a, float b, float t)
{
	return a + ( b - a ) * Clamp(t, 0, 1);
}

Vector2 Utils::Vector2Lerp(Vector2 a, Vector2 b, float t)
{
	return { Lerp(a.x, b.x, t), Lerp(a.y, b.y, t) };
}

Vector3 Utils::Vector2Lerp(Vector3 a, Vector3 b, float t)
{
	return { Lerp(a.x, b.x, t), Lerp(a.y, b.y, t), Lerp(a.z, b.z, t) };
}

Vect2F Utils::Vect2FLerp(Vect2F a, Vect2F b, float t)
{
	return a + ( b - a ) * Clamp(t, 0, 1);
}

Vect3F Utils::Vect3FLerp(Vect3F a, Vect3F b, float t)
{
	return a + (b - a) * Clamp(t, 0, 1);
}

float Utils::Sign(float value)
{
	return (value >= 0) ? 1.0f : -1.0f;
}

bool Utils::nearlyEqual(const float a, const float b)
{
	float epsilon = 0.000001f;
	return Abs( a - b ) < epsilon;
}

int Utils::RandInt(int min, int max)
{
	static random_device rd;
	static mt19937 gen(rd());

	uniform_int_distribution<> distr(min, max);
	return distr(gen);
}

#pragma region Structs

#pragma region Vectors

//Vect2F

const Vect2F Vect2F::zero = { 0,0 };
const Vect2F Vect2F::one = { 1,1 };
const Vect2F Vect2F::up = { 0,1 };
const Vect2F Vect2F::down = { 0,-1 };
const Vect2F Vect2F::right = { 1,0 };
const Vect2F Vect2F::left = { -1,0 };

Vect2F Vect2F::normalized() const
{
	float l = this->length();
	return { x/l, y/l };
}

Vect2F Vect2F::absolute() const
{
	return { Utils::Sign(this->x), Utils::Sign(this->y) };
}

bool Vect2F::operator==(const Vect2F& rm) const 
{ 
	return (Utils::nearlyEqual(x, rm.x) && Utils::nearlyEqual(y, rm.y)); 
}

//Vect2I

const Vect2I Vect2I::zero = { 0,0 };
const Vect2I Vect2I::one = { 1,1 };
const Vect2I Vect2I::up = { 0,1 };
const Vect2I Vect2I::down = { 0,-1 };
const Vect2I Vect2I::right = { 1,0 };
const Vect2I Vect2I::left = { -1,0 };

Vect2I Vect2I::absolute() const
{
	return { (int) Utils::Sign((float) this->x), (int) Utils::Sign((float) this->y) };
}

//Vect3F

const Vect3F Vect3F::zero = { 0,0,0 };
const Vect3F Vect3F::one = { 1,1,1 };
const Vect3F Vect3F::forward = { 0,0,1 };
const Vect3F Vect3F::back = { 0,0,-1 };
const Vect3F Vect3F::up = { 0,1,0 };
const Vect3F Vect3F::down = { 0,-1,0 };
const Vect3F Vect3F::right = { 1,0,0 };
const Vect3F Vect3F::left = { -1,0,0 };

Vect3F Vect3F::normalized() const
{
	float l = this->length();
	return { x / l, y / l , z / l};
}

Vect3F Vect3F::absolute() const
{
	return { Utils::Sign(this->x), Utils::Sign(this->y), Utils::Sign(this->z) };
}

bool Vect3F::operator==(const Vect3F& rm) const
{
	return (Utils::nearlyEqual(x, rm.x) && Utils::nearlyEqual(y, rm.y) && Utils::nearlyEqual(z, rm.z));
}

//Vect3I

const Vect3I Vect3I::zero = { 0,0,0 };
const Vect3I Vect3I::one = { 1,1,1 };
const Vect3I Vect3I::forward = { 0,0,1 };
const Vect3I Vect3I::back = { 0,0,-1 };
const Vect3I Vect3I::up = { 0,1,0 };
const Vect3I Vect3I::down = { 0,-1,0 };
const Vect3I Vect3I::right = { 1,0,0 };
const Vect3I Vect3I::left = { -1,0,0 };

Vect3I Vect3I::absolute() const
{
	return { (int) Utils::Sign((float) this->x), (int) Utils::Sign((float) this->y), (int) Utils::Sign((float) this->z) };
}

#pragma endregion

#pragma endregion


