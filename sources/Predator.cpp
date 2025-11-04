#include "Predator.h"

using MathUtils::RandVect2Normalized;

Predator::Predator(Vect2F pos, float size) :
	GameActor(0, 0, { pos, Vect2F::one, 0 }, TagPredator),
	mRender{ {Vect2F::zero, {size, size}} },
	mSize{ size },
	mVelocity{ Vect2F::zero },
	mForce{ Vect2F::zero },
	mSpeed{ 50.0f },
	mFov{ 180 }
{
	mVelocity = RandVect2Normalized();
	if (GlobalVariables::EngineRunning)
	{
		Init();
	}
}

void Predator::Init()
{
	mRender.Init("predator");
}

void Predator::Update()
{
}

void Predator::Draw()
{
	float direction = mVelocity.getRot();
	Rect2 currentTextureSpace = mRender.GetTextureSpace();
	mRender.ChangeTextureSpace({ currentTextureSpace.center, currentTextureSpace.halfSize, direction });

	mRender.Draw(mTransform);
}
