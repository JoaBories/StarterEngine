#include "Predator.h"

using MathUtils::RandVect2Normalized;

Collision Predator::GetScreenCollision()
{
	Collision result = Collision();

	if (mTransform.position.x - mSize <= 0)
	{
		result.collided = true;
		result.axis.x = 1.0f;
	}
	else if (mTransform.position.x + mSize >= GetScreenWidth())
	{
		result.collided = true;
		result.axis.x = -1.0f;
	}

	if (mTransform.position.y - mSize <= 0)
	{
		result.collided = true;
		result.axis.y = 1.0f;
	}
	else if (mTransform.position.y + mSize >= GetScreenHeight())
	{
		result.collided = true;
		result.axis.y = -1.0f;
	}

	return result;
}

void Predator::ResolveScreenCollisions()
{
	Collision coll = GetScreenCollision();

	if (coll)
	{
		//Resolve Position
		if (coll.axis.x == 1.0f)
		{
			mTransform.position.x = 0 + mSize;
		}
		else if (coll.axis.x == -1.0f)
		{
			mTransform.position.x = (float)GetScreenWidth() - mSize;
		}

		if (coll.axis.y == 1.0f)
		{
			mTransform.position.y = 0 + mSize;
		}
		else if (coll.axis.y == -1.0f)
		{
			mTransform.position.y = (float)GetScreenHeight() - mSize;
		}

		//Resolve Velocity
		mVelocity *= {(coll.axis.x != 0) ? -1.0f : 1.0f, (coll.axis.y != 0) ? -1.0f : 1.0f};

		//Resolve Force
		mForce *= {(coll.axis.x != 0) ? -1.0f : 1.0f, (coll.axis.y != 0) ? -1.0f : 1.0f};
	}
}

void Predator::ChooseNewGoal()
{
	Vect2F newGoal = (RandVect2Normalized() + Vect2F::one) / 2 * Vect2F{ (float)GetScreenWidth(), (float)GetScreenHeight() };
	int tries = 0;

	while ((mCurrentGoal-newGoal).sqrLength() < 40000.0f && tries <= 15) // 200²
	{
		newGoal = (RandVect2Normalized() + Vect2F::one) / 2 * Vect2F{ (float)GetScreenWidth(), (float)GetScreenHeight() };
	}

	mCurrentGoal = newGoal;
}

void Predator::ChooseNewPrey()
{
	float shortestLength = INFINITY;
	GameActor* bestPrey = nullptr;

	for (GameActor* fish : GameActor::GetActorsByTag(TagFish))
	{
		float length = (mTransform.position - fish->GetTransform().position).sqrLength();

		if (length < shortestLength) 
		{
			shortestLength = length;
			bestPrey = fish;
		}
	}

	mPrey = bestPrey;
}

Predator::Predator(Vect2F pos, float size) :
	GameActor(0, 0, { pos, Vect2F::one, 0 }, TagPredator),
	mRender{ {Vect2F::zero, {size, size}} },
	mSize{ size },
	mVelocity{ Vect2F::zero },
	mForce{ Vect2F::zero },
	mSpeed{ 50.0f },
	mFov{ 180 },
	mPrey{ nullptr },
	mHunting{ false },
	mCurrentGoal{ Vect2F::zero },
	mTimeSinceLastGoal{ 0.0f },
	mTimeUntilNexHunt{ 0.0f }
{
	mVelocity = RandVect2Normalized();
	mTimeUntilNexHunt = MathUtils::RandFloat(20.0f, 60.0f);
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

	ResolveScreenCollisions();

	if (mHunting)
	{
		mSpeed = 80.0f;
		mTimeUntilNexHunt -= GetFrameTime();

		if (mTimeUntilNexHunt <= 0.0f)
		{
			mTimeUntilNexHunt = MathUtils::RandFloat(20.0f, 60.0f);
			mHunting = false;
		}

		if ((mTransform.position - mPrey->GetTransform().position).sqrLength() <= 100.0f)
		{
			mTimeUntilNexHunt = MathUtils::RandFloat(20.0f, 60.0f);
			mHunting = false;
		}

		mForce = mPrey->GetTransform().position - mTransform.position;
	}
	else
	{
		mSpeed = 50.0f;
		mTimeSinceLastGoal -= GetFrameTime();
		mTimeUntilNexHunt -= GetFrameTime();

		if (mTimeUntilNexHunt <= 0.0f)
		{
			ChooseNewPrey();
			mTimeUntilNexHunt = MathUtils::RandFloat(10.0f, 20.0f);
			mHunting = true;
		}

		if (mTimeSinceLastGoal <= 0.0f)
		{
			ChooseNewGoal();
			mTimeSinceLastGoal = 10.0f;
		}

		if ((mTransform.position - mCurrentGoal).sqrLength() <= 100.0f)
		{
			ChooseNewGoal();
			mTimeSinceLastGoal = 10.0f;
		}

		mForce = mCurrentGoal - mTransform.position;
	}

	mVelocity += mForce.normalized() * GetFrameTime() * mSpeed;
	mVelocity = mVelocity.clamp(20.0f, mSpeed);


	mTransform.position += mVelocity * GetFrameTime();
}

void Predator::Draw()
{
	float direction = mVelocity.getRot();
	Rect2 currentTextureSpace = mRender.GetTextureSpace();
	mRender.ChangeTextureSpace({ currentTextureSpace.center, currentTextureSpace.halfSize, direction });

	mRender.Draw(mTransform);
}

void Predator::DrawDebug() const
{
	DrawCircleV((mTransform.position - Vect2F{ 0,10 }).toRaylib(), 5.0f, (mHunting) ? RED : GREEN);
	DrawLineEx(mTransform.position.toRaylib(), (mTransform.position + mVelocity * 2).toRaylib(), 2.0f, GREEN);


	if (mHunting)
	{
		DrawCircleLines(mPrey->GetTransform().position.x, mPrey->GetTransform().position.y, 10.0f, RED);
		DrawLineV(mPrey->GetTransform().position.toRaylib(), mTransform.position.toRaylib(), RED);

	}
	else
	{
		DrawCircleLines(mCurrentGoal.x, mCurrentGoal.y, 10.0f, GREEN);
		DrawLineV(mCurrentGoal.toRaylib(), mTransform.position.toRaylib(), GREEN);

		Vect2F pos = mTransform.position + Vect2F{ -10.0f  ,10.0f };
		DrawText(std::to_string(mTimeSinceLastGoal).c_str(), pos.x, pos.y, 10, WHITE);
		pos = mTransform.position + Vect2F{ -10.0f  ,20.0f };
		DrawText(std::to_string(mTimeUntilNexHunt).c_str(), pos.x, pos.y, 10, WHITE);
	}
}

