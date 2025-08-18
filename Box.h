#pragma once
#include "GameActor.h"

using Struct::Rect2;
using Struct::Collision;

class Box : public GameActor
{
private:

	Rect2 mBox;

	Vect2F mVelocity;

	float mMass;
	float mGravityForce = 9.8f;

	Color mColor;

	void ResolveCollision(Collision coll, Vect2F otherPos);

public:

	Box() = default;
	~Box() = default;

	Box(int priority, float mass, Vect2F halfSize, Transform2D transform);

	// Inherited via GameActor
	void Update() override;
	void Draw() override;
	void Init() override;

	Rect2 GetBox() const;
};

