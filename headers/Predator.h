#pragma once
#include "Fish.h"

class Predator : public GameActor
{

private:

	Render2D mRender;

	float mSize;
	Vect2F mVelocity;
	Vect2F mForce;
	float mSpeed;
	float mFov;

	Fish* mPrey;
	bool mHunting;
	Vect2F mCurrentGoal;
	float mTimeSinceLastGoal;

	Collision GetScreenCollision();
	void ResolveScreenCollisions();

	void ChooseNewGoal();

public:

	Predator() = default;
	~Predator() = default;

	Predator(Vect2F pos, float size = 30.0f);

	// Inherited via GameActor
	void Init() override;
	void Update() override;
	void Draw() override;

	void DrawDebug() const;
};

