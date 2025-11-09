#pragma once
#include "GameActor.h"
#include "Render2D.h"

class Predator : public GameActor
{

private:

	Render2D mRender;

	float mSize;
	Vect2F mVelocity;
	Vect2F mForce;
	float mSpeed;
	float mFov;

	GameActor* mPrey;
	bool mHunting;
	Vect2F mCurrentGoal;
	float mTimeSinceLastGoal;
	float mTimeUntilNexHunt;

	Collision GetScreenCollision();
	void ResolveScreenCollisions();

	void ChooseNewGoal();
	void ChooseNewPrey();

public:

	Predator() = default;
	~Predator() = default;

	Predator(Vect2F pos, float size = 30.0f);

	// Inherited via GameActor
	void Init() override;
	void Update() override;
	void Draw() override;

	void DrawDebug() const;

	inline bool IsHunting() const { return mHunting; };
};

