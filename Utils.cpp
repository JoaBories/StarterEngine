#include "Utils.h"


Utils::Utils()
{
}

Utils::~Utils()
{
}

float Utils::SqrLenght(Vector2 vector)
{
	return (vector.x * vector.x) + (vector.y * vector.y);
}

float Utils::Lenght(Vector2 vector)
{
	return Sqrt(SqrLenght(vector));
}

Vector2 Utils::Normalize(Vector2 vector)
{
	float l = Lenght(vector);
	return { vector.x/l, vector.y/l };
}

Vector2 Utils::Distance(Vector2 a, Vector2 b)
{
	return { a.x - b.x, a.y - b.y };
}

Vector2 Utils::AbsDistance(Vector2 a, Vector2 b)
{
	Vector2 d = Distance(a, b);
	return { Abs(d.x), Abs(d.y) };
}

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

float Utils::FastInvSqrt(float value)
{
	long i;
	float x2, y;
	const float threehalfs = 1.5F;

	x2 = value * 0.5F;
	y = value;
	i = *(long*)&y;             // evil floating point bit level hacking
	i = 0x5f3759df - (i >> 1);  // what the fuck?
	y = *(float*)&i;
	y = y * (threehalfs - (x2 * y * y));  // 1st iteration
	//y  = y * ( threehalfs - ( x2 * y * y ) );   // 2nd iteration, this can be removed

	return y;
}

float Utils::Sqrt(float value)
{
	return value * FastInvSqrt(value);
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

Color Utils::ColorLerp(Color a, Color b, float t)
{
	Color result = Color();
	result.r = Lerp(a.r, b.r, t);
	result.g = Lerp(a.g, b.g, t);
	result.b = Lerp(a.b, b.b, t);
	result.a = Lerp(a.a, b.a, t);
	return result;
}

float Utils::Sign(float value)
{
	return (value >= 0) ? 1 : -1;
}

int Utils::RandInt(int min, int max)
{
	static random_device rd;
	static mt19937 gen(rd());

	uniform_int_distribution<> distr(min, max);
	return distr(gen);
}

void Utils::DrawTextCentered(string text, Vector2 position, int fontSize)
{
	float xCentered = position.x - (float) MeasureText(text.c_str(), fontSize) / 2;
	float yCentered = position.y - fontSize / 2;
	DrawText(text.c_str(), xCentered, yCentered, fontSize, WHITE);

	return;
}
