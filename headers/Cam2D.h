#pragma once

#include "Util.h"
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

	void SetPosition(Vect2F newPosition);

	Rect2 GetCamSpace() const;		//Rect2 of what the camera sees
	Rect2 GetSafeCamSpace() const;  //More wider rect for occlusion

	static Cam2D* GetInstance();
};

