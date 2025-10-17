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
	Vect2F mForce;

	Collision GetScreenCollision();
	void ResolveScreenCollisions();

	void ResolveNeighborsRules();
	void ResolveAlignment(vector<Bird*> neighbors);
	void ResolveSeparation(vector<Bird*> neighbors);
	void ResolveCohesion(vector<Bird*> neighbors);

	vector<vector<Bird*>> GetNeighbors() const;

public :

	Bird() = default;
	~Bird() = default;

	Bird(Vect2F pos, float size = 5.0f);

	inline float GetSize() const { return mSize; };
	inline Vect2F GetVel() const { return mVelocity; };

	void Init() override;
	void Update() override;
	void Draw() override;

	void DrawDebug() const;

};

