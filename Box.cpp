#include "Box.h"

#include <iostream>
using std::cout, std::endl;

void Box::ResolveCollision(Collision coll, Vect2F otherPos)
{
	mColor = RED;

	Vect2F resol = coll.getForce();
	Vect2F dir = mTransform.position - otherPos;

	if (dir.dot(resol) < 0) resol = -resol;

	if (resol.sqrLength() > 0)
	{
		mTransform.position += resol;

		Vect2F axis = resol.normalized();
		Vect2F perpendicular = axis * mVelocity.dot(axis);

		mVelocity -= perpendicular;
	}

	return;
}

Box::Box(int priority, float mass, Vect2F halfSize, Transform2D transform) :
	GameActor(priority, priority, transform, (string)"box"),
	mBox{ {0, 0} , halfSize, 0 },
	mMass{ mass },
	mColor{ WHITE },
	mVelocity{ 0, 0 }
{
}

void Box::Update()
{
	mColor = WHITE;

	//Fall
	mVelocity += Vect2F::down * mMass * mGravityForce * GetFrameTime();

	//Collisions
	for(auto& actor : GameActor::GetActorsByTag("box"))
	{
		if (actor != this) {

			Box* box = dynamic_cast<Box*>(actor);
			Rect2 selfToObject = mBox.toObjectSpace(mTransform);
			Rect2 otherToObject = box->GetBox().toObjectSpace(box->GetTransform());

			Collision coll = selfToObject.CheckAABB(otherToObject);

			if (coll)
			{
				ResolveCollision(coll, actor->GetTransform().position);
			}
		}
	}

	Rect2 selfToObject = mBox.toObjectSpace(mTransform);
	Rect2 otherToObject = { {GetScreenWidth() * 0.5f, GetScreenHeight() - 10.0f}, {GetScreenWidth() * 0.5f, 20.0f}, 0};

	Collision coll = selfToObject.CheckAABB(otherToObject);

	if (coll)
	{
		ResolveCollision(coll, { GetScreenWidth() * 0.5f, GetScreenHeight() - 10.0f });
	}

	mTransform.position += Vect2F{mVelocity.x, -mVelocity.y} * GetFrameTime();
}

void Box::Draw()
{
	Rect2 objectSpace = { mTransform.position + mBox.center, mTransform.scale * mBox.halfSize, 0 };

	Rectangle rect = { objectSpace.toRaylib() };

	DrawRectangleRec(rect, mColor);
}

void Box::Init()
{
	return;
}

Rect2 Box::GetBox() const
{
	return mBox;
}
