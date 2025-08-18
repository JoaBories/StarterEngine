#pragma once

#include "Utils.h"
using Struct::Vect2F;
using Struct::Rect2;

class Cam2D
{

private:
	Vect2F mPosition;
	float mZoom;

	static Cam2D* instance;

public:
	Cam2D();
	~Cam2D() = default;

	void Update();

	Vect2F GetPosition() const;
	float GetZoom() const;

	Rect2 GetCamSpace() const;

	static Cam2D* GetInstance();
};

