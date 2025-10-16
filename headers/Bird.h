#pragma once
#include "GameActor.h"

using Struct::Vect2F;
using Struct::Collision;

class Bird : public GameActor
{

protected :

	float mSize;
	Vect2F mVelocity;
	float mSpeed;
	float mSeparation;
	float mAlignment;
	float mCohesion;
	float mFov;
	Vect2F mAccel;

	Collision GetScreenCollision();
	void ResolveScreenCollisions();

	vector<vector<Bird*>> GetNeighbors() const;

public :

	Bird() = default;
	~Bird() = default;

	Bird(Vect2F pos, float size = 5.0f);

	inline float GetSize() const { return mSize; };

	void Init() override;
	void Update() override;
	void Draw() override;

	void DrawDebug() const;

};

