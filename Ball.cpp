#include "Ball.h"

void Ball::ResolveScreenCollisions()
{
	if (mTransform.position.x + mRadius >= GetScreenWidth()) 
	{
		mVelocity.x = -mVelocity.x;
	}
	else if (mTransform.position.x - mRadius <= 0)
	{
		mVelocity.x = -mVelocity.x;
	}

	if (mTransform.position.y + mRadius >= GetScreenHeight())
	{
		mVelocity.y = -mVelocity.y;
	}
	else if (mTransform.position.y - mRadius <= 0)
	{
		mVelocity.y = -mVelocity.y;
	}
}

Ball::Ball(Vect2F startVelocity, float radius, Color color) :
	mVelocity{ startVelocity },
	mRadius{ radius },
	mColor{ color }
{
	mTransform.position = { (float) GetScreenWidth() / 2, (float) GetScreenHeight() / 2 };
}

void Ball::Update()
{
	mTransform.position += mVelocity * GetFrameTime();

	ResolveScreenCollisions();
}

void Ball::Draw()
{
	DrawCircleV(mTransform.position.toRaylib(), mRadius, mColor);
}
