#pragma once
#include "GameActor.h"

using Struct::Vect2F;

class Bird : public GameActor
{

protected :

	float mSize;
	Vect2F mVelocity;
	float mSpeed;
	float mSeparation;
	float mAlignment;
	float mCohesion;
	Vect2F mForce;

public :

	Bird() = default;
	~Bird() = default;

	Bird(Vect2F pos, float size = 5.0f);


	void Init() override;
	void Update() override;
	void Draw() override;

};

