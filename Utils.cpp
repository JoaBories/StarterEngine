#include "Utils.h"

#include <iostream>
using std::cout, std::endl;

using Struct::Vect2F;
using Struct::Vect2I;
using Struct::Rect2;
using Struct::Collision;

#pragma region MathUtils

Vect2F MathUtils::Vect2FromRot(float rot)
{
	Vect2F vector = { cosf(rot * DEG2RAD), sinf(rot * DEG2RAD) };
	return vector.normalized();
}

float MathUtils::OverlapOnAxis(const vector<Vect2F>& a, const vector<Vect2F>& b, Vect2F axis) // Check if two polygons (list of points) are overlaping on a certain axis | return overlap : negative -> false / positive -> true
{
	float aMin = FLT_MAX, aMax = -FLT_MAX;
	float bMin = FLT_MAX, bMax = -FLT_MAX;

	for (const auto& point : a) 
	{
		float projection = point.dot(axis);
		aMin = Min(projection, aMin);
		aMax = Max(projection, aMax);
	}

	for (const auto& point : b)
	{
		float projection = point.dot(axis);
		bMin = Min(projection, bMin);
		bMax = Max(projection, bMax);
	}

	return Min(aMax, bMax) - Max(aMin, bMin);
}

bool MathUtils::NearlyEqual(const float a, const float b)
{
	float epsilon = 0.000001f;
	return Abs( a - b ) < epsilon;
}

int MathUtils::RandInt(int min, int max)
{
	static random_device rd;
	static mt19937 gen(rd());

	uniform_int_distribution<> distr(min, max);
	return distr(gen);
}

#pragma endregion

#pragma region Structs

#pragma region Vectors

//Vect2F

const Vect2F Vect2F::zero = { 0,0 };
const Vect2F Vect2F::one = { 1,1 };
const Vect2F Vect2F::up = { 0,1 };
const Vect2F Vect2F::down = { 0,-1 };
const Vect2F Vect2F::right = { 1,0 };
const Vect2F Vect2F::left = { -1,0 };

bool Vect2F::operator==(const Vect2F& rm) const
{ 
	return (MathUtils::NearlyEqual(x, rm.x) && MathUtils::NearlyEqual(y, rm.y)); 
}

float Vect2F::getRot() const
{
	if (x == 0 && y == 0) return 0;

	float a = atan2f(y, x) * RAD2DEG;
	if (a < 0) a += 360.0f;

	return a;
}

Vect2F Vect2F::absolute() const
{
	return { MathUtils::Abs(x), MathUtils::Abs(y) };
}

Vect2F Vect2F::normalized() const
{
	float l = length();
	return { x / l, y / l };
}

//Vect2I

const Vect2I Vect2I::zero = { 0,0 };
const Vect2I Vect2I::one = { 1,1 };
const Vect2I Vect2I::up = { 0,1 };
const Vect2I Vect2I::down = { 0,-1 };
const Vect2I Vect2I::right = { 1,0 };
const Vect2I Vect2I::left = { -1,0 };

float Vect2I::getRot() const
{
	if (x == 0 && y == 0) return 0;

	float a = atan2f((float)y, (float)x) * RAD2DEG;
	if (a < 0) a += 360;
		
	return a;
}

Vect2I Vect2I::absolute() const
{
	return { MathUtils::Abs(x), MathUtils::Abs(y) };
}

#pragma endregion

#pragma region Rectangle

vector<Vect2F> Rect2::getCorners() const
{
	vector<Vect2F> corners(4);

	float cosA = cosf(rotation * DEG2RAD);
	float sinA = sinf(rotation * DEG2RAD);

	Vect2F right = { cosA, sinA };
	Vect2F up = { -sinA, cosA };

	corners[0] = center + right * halfSize.x + up * halfSize.y;
	corners[1] = center + right * -halfSize.x + up * halfSize.y;
	corners[2] = center + right * -halfSize.x + up * -halfSize.y;
	corners[3] = center + right * halfSize.x + up * halfSize.y;

	return corners;
}

Collision Rect2::CheckAABB(const Rect2& other) const
{
	Collision result = Collision();

	Vect2F aMin = { center.x - halfSize.x, center.y - halfSize.y };
	Vect2F aMax = { center.x + halfSize.x, center.y + halfSize.y };
	Vect2F bMin = { other.center.x - other.halfSize.x, other.center.y - other.halfSize.y };
	Vect2F bMax = { other.center.x + other.halfSize.x, other.center.y + other.halfSize.y };

	if (aMin.x <= bMax.x && aMax.x >= bMin.x && aMin.y <= bMax.y && aMax.y >= bMin.y)
	{
		result.collided = true;

		Vect2F overlap = Vect2F();
		overlap.x = MathUtils::Min(aMax.x, bMax.x) - MathUtils::Max(aMin.x, bMin.x);
		overlap.y = MathUtils::Min(aMax.y, bMax.y) - MathUtils::Max(aMin.y, bMin.y);

		if (overlap.x < overlap.y) 
		{
			result.overlap = overlap.x;
			result.axis = (center.x > other.center.x) ? Vect2F::right : Vect2F::left;
		}
		else
		{
			result.overlap = overlap.y;
			result.axis = (center.y > other.center.y) ? Vect2F::up : Vect2F::down;
		}
	}

	return result; // if AABB false collided -> true, axis -> {0,0} and overlap -> 0 by default
}

bool Struct::Rect2::ContainPoint(const Vect2F& point) const
{
	Vect2F aMin = { center.x - halfSize.x, center.y - halfSize.y };
	Vect2F aMax = { center.x + halfSize.x, center.y + halfSize.y };

	return point.x >= aMin.x && point.x <= aMax.x && point.y >= aMin.y && point.y <= aMax.y;
}

Collision Rect2::CheckOBB(const Rect2& other) const
{
	return Collision();
}

#pragma endregion

#pragma endregion

