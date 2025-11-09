#include "Fish.h"

using MathUtils::RandVect2Normalized;
using MathUtils::Clamp;
using MathUtils::Vect2FromRot;

Collision Fish::GetScreenCollision()
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
	else if(mTransform.position.y + mSize >= GetScreenHeight())
	{
		result.collided = true;
		result.axis.y = -1.0f;
	}

	return result;
}

void Fish::ResolveScreenCollisions()
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

void Fish::ResolveNeighborsRules()
{
	vector<std::unordered_map<Fish*, float>> allNeighbors = GetNeighbors();

	if (allNeighbors[0].size() > 0)
	{
		ResolveSeparation(allNeighbors[0]);
	}

	if (allNeighbors[1].size() > 0)
	{
		ResolveAlignment(allNeighbors[1]);
	}

	if (allNeighbors[2].size() > 0)
	{
		ResolveCohesion(allNeighbors[2]);
	}
}

void Fish::ResolveAlignment(std::unordered_map<Fish*, float> neighbors)
{
	Vect2F force = Vect2F::zero;
	Vect2F ttNeighborsVel = Vect2F::zero;
	float ttNeighbors;

	for (const auto& neighbor : neighbors)
	{
		ttNeighborsVel += neighbor.first->GetVel() * (neighbor.second / mAlignment);
		ttNeighbors = (neighbor.second / mAlignment);
	}

	force = ttNeighborsVel / ttNeighbors;

	mForce += force.normalized() * 0.9f;
}

void Fish::ResolveSeparation(std::unordered_map<Fish*, float> neighbors)
{
	Vect2F force = Vect2F::zero;
	Vect2F ttNeighborsDis = Vect2F::zero;

	for (const auto& neighbor : neighbors)
	{
		ttNeighborsDis += (mTransform.position - neighbor.first->GetTransform().position) * (neighbor.second / mAlignment);
	}

	mForce += ttNeighborsDis.normalized() * 2.0f;
}

void Fish::ResolveCohesion(std::unordered_map<Fish*, float> neighbors)
{
	Vect2F force = Vect2F::zero;
	Vect2F ttNeighborsPos = Vect2F::zero;
	float ttNeighbors;

	for (const auto& neighbor : neighbors)
	{
		ttNeighborsPos += (neighbor.first->GetTransform().position - mTransform.position) * (neighbor.second / mAlignment);
		ttNeighbors = (neighbor.second / mAlignment);
	}

	force = ttNeighborsPos / ttNeighbors;

	mForce += force.normalized() * 0.6f;
}

void Fish::ResolvePredatorRules()
{
	mSpeed = 50.0f;

	float shortestDistance = INFINITY;
	float shortestHuntingDistance = INFINITY;
	Predator* nearestPredator = nullptr;
	Predator* nearestHuntingPredator = nullptr;

	for (GameActor* actor : GameActor::GetActorsByTag(TagPredator))
	{
		Predator* mPredator = dynamic_cast<Predator*>(GetActorsByTag(TagPredator)[0]);

		if (mPredator)
		{
			float distancePredator = (mTransform.position - mPredator->GetTransform().position).sqrLength();

			if (mPredator->IsHunting())
			{
				if (distancePredator < shortestHuntingDistance)
				{
					shortestHuntingDistance = distancePredator;
					nearestHuntingPredator = mPredator;
				}
			}

			if (distancePredator < shortestDistance)
			{
				shortestDistance = distancePredator;
				nearestPredator = mPredator;
			}
		}
	}

	if (nearestPredator)
	{
		if (shortestDistance < mAlignment * mAlignment)
		{
			mSpeed = 60.0f;
			ResolvePredatorSeparation(nearestPredator);
		}
	}

	if (nearestHuntingPredator)
	{
		mSpeed = 60.0f;

		if (shortestHuntingDistance < mCohesion * mCohesion)
		{
			ResolvePredatorFlee(nearestHuntingPredator);
		}
	}
}

void Fish::ResolvePredatorFlee(Predator* predator)
{
	mForce = (mTransform.position - predator->GetTransform().position).normalized();
}

void Fish::ResolvePredatorSeparation(Predator* predator)
{
	mForce = (mTransform.position - predator->GetTransform().position).normalized();
}

vector<std::unordered_map<Fish*, float>> Fish::GetNeighbors() const
{
	vector<std::unordered_map<Fish*, float>> neighbors = { {}, {}, {} };

	Vect2F normalizedVel = mVelocity.normalized();
	
	float dotTreshold = - (mFov / 180.0f - 1.0f);

	for (GameActor* actor : GameActor::GetActorsByTag(TagFish))
	{
		if (this == actor)
		{
			continue;
		}

		Vect2F diff = (actor->GetTransform().position - mTransform.position).normalized();
		float dotProduct = normalizedVel.dot(diff);

		if (dotProduct <= dotTreshold)
		{
			continue;
		}

		if (Fish* bird = dynamic_cast<Fish*>(actor))
		{
			float distance = (mTransform.position - bird->GetTransform().position).length();
			
			if (distance <= mSeparation)
			{
				neighbors[0][bird] = distance;
			}

			if (distance <= mAlignment)
			{
				neighbors[1][bird] = distance;
			}

			if (distance <= mCohesion)
			{
				neighbors[2][bird] = distance;
			}
		}
	}

	return neighbors;
}

Fish::Fish(Vect2F pos, float size) :
	GameActor(1, 1, { pos, Vect2F::one, 0 }, TagFish),
	mRender{ {Vect2F::zero, {size, size}} },
	mSize{ size },
	mSpeed{ 50.0f },
	mSeparation{ 25 },
	mAlignment{ 50 },
	mCohesion{ 100 },
	mFov{ 240 },
	mForce{ Vect2F::zero }
{
	mVelocity = RandVect2Normalized();
	if (GlobalVariables::EngineRunning)
	{
		Init();
	}
}

void Fish::Init()
{
	mRender.Init("fish");
}

void Fish::Update()
{
	ResolveScreenCollisions();

	mForce = Vect2F::zero;

	ResolveNeighborsRules();

	ResolvePredatorRules();

	mVelocity += mForce.normalized() * GetFrameTime() * mSpeed;
	mVelocity = mVelocity.clamp(mSpeed - 10.0f, mSpeed);

	mTransform.position += mVelocity * GetFrameTime();
}

void Fish::Draw()
{
	float direction = mVelocity.getRot();
	Rect2 currentTextureSpace = mRender.GetTextureSpace();
	mRender.ChangeTextureSpace({ currentTextureSpace.center, currentTextureSpace.halfSize, direction });

	mRender.Draw(mTransform);
}

void Fish::DrawDebug() const
{
	//Vel
	DrawLineEx(mTransform.position.toRaylib(), (mTransform.position + mVelocity * 30).toRaylib(), 2.0f, GREEN);
	
	//Force
	DrawLineEx(mTransform.position.toRaylib(), (mTransform.position + mForce * 30).toRaylib(), 2.0f, BLUE);

	//Fov
	DrawLineEx(mTransform.position.toRaylib(), (mTransform.position + Vect2FromRot(mVelocity.getRot() - mFov / 2) * 300).toRaylib(), 1.0f, DARKGRAY);
	DrawLineEx(mTransform.position.toRaylib(), (mTransform.position + Vect2FromRot(mVelocity.getRot() + mFov / 2) * 300).toRaylib(), 1.0f, DARKGRAY);

	//Neighbors
	vector<std::unordered_map<Fish*, float>> neighbors = GetNeighbors();

	DrawCircleLines( (int)mTransform.position.x, (int)mTransform.position.y, mSeparation, RED);
	for (auto& bird : neighbors[0])
	{
		DrawCircleLines((int)bird.first->GetTransform().position.x, (int)bird.first->GetTransform().position.y, bird.first->GetSize() + 2, RED);
	}

	DrawCircleLines( (int)mTransform.position.x, (int)mTransform.position.y, mAlignment, GREEN);
	for (auto& bird : neighbors[1])
	{
		DrawCircleLines((int)bird.first->GetTransform().position.x, (int)bird.first->GetTransform().position.y, bird.first->GetSize() + 4, GREEN);
	}

	DrawCircleLines( (int)mTransform.position.x, (int)mTransform.position.y, mCohesion, BLUE);
	for (auto& bird : neighbors[2])
	{
		DrawCircleLines((int)bird.first->GetTransform().position.x, (int)bird.first->GetTransform().position.y, bird.first->GetSize() + 6, BLUE);
	}
}
