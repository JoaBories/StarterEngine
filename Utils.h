#pragma once
#include "raylib.h"

#include <iostream>
using std::cout;
using std::endl;

#include <random>
using std::random_device;
using std::mt19937;
using std::uniform_int_distribution;

using std::string;

class Utils
{
private:
	Utils();
	~Utils();

public:
	//Math functions
	static float SqrLenght(Vector2 vector);
	static float Lenght(Vector2 vector);
	static Vector2 Normalize(Vector2 vector);
	static Vector2 Distance(Vector2 a, Vector2 b);
	static Vector2 AbsDistance(Vector2 a, Vector2 b);
	static float Min(float a, float b);
	static float Max(float a, float b);
	static float Abs(float value);
	static float FastInvSqrt(float value); // i copied Quake III one
	static float Sqrt(float value);
	static float Clamp(float value, float min, float max);
	static float Lerp(float a, float b, float t);
	static Vector2 Vector2Lerp(Vector2 a, Vector2 b, float t);
	static Color ColorLerp(Color a, Color b, float t);
	static float Sign(float value);

	static int RandInt(int min, int max);

	//Draw functions
	static void DrawTextCentered(string text, Vector2 position, int fontSize);
};

