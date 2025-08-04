#pragma once
#include "GameActor.h"

class Ball : public GameActor
{
private:
	Vect2F mVelocity;
	float mRadius;
	Color mColor;

	void ResolveScreenCollisions();

public:

	Ball() = default;
	Ball(Vect2F startVelocity, float radius, Color color);
	~Ball() = default;
	

	// Inherited via GameActor
	void Update() override;
	void Draw() override;
};

