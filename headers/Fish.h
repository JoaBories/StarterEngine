#pragma once
#include "GameActor.h"
#include "Render2D.h"
#include "Predator.h"
#include <unordered_map>

using Struct::Vect2F;
using Struct::Collision;

class Fish : public GameActor
{

protected :

	Render2D mRender;

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
	void ResolveAlignment(std::unordered_map<Fish*, float> neighbors);
	void ResolveSeparation(std::unordered_map<Fish*, float> neighbors);
	void ResolveCohesion(std::unordered_map<Fish*, float> neighbors);

	void ResolvePredatorRules();
	void ResolvePredatorFlee(Predator* predator);		//Same forces but different behaviour in theory.
	void ResolvePredatorSeparation(Predator* predator);	//I can comeback later to refine.

	vector<std::unordered_map<Fish*, float>> GetNeighbors() const;

public :

	Fish() = default;
	~Fish() = default;

	Fish(Vect2F pos, float size = 15.0f);

	inline float GetSize() const { return mSize; };
	inline Vect2F GetVel() const { return mVelocity; };

	void Init() override;
	void Update() override;
	void Draw() override;

	void DrawDebug() const;
};

