#include "Bird.h"

using MathUtils::RandVect2Normalized;
using MathUtils::Clamp;
using MathUtils::Vect2FromRot;

Collision Bird::GetScreenCollision()
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

void Bird::ResolveScreenCollisions()
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

void Bird::ResolveNeighborsRules()
{
	vector<vector<Bird*>> allNeighbors = GetNeighbors();

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

void Bird::ResolveAlignment(vector<Bird*> neighbors)
{
	Vect2F force = Vect2F::zero;
	Vect2F ttNeighborsVel = Vect2F::zero;

	for (const Bird* neighbor : neighbors)
	{
		ttNeighborsVel += neighbor->GetVel();
	}

	force = ttNeighborsVel / (int)neighbors.size();

	mForce += force.normalized();
}

void Bird::ResolveSeparation(vector<Bird*> neighbors)
{
	Vect2F force = Vect2F::zero;
	Vect2F ttNeighborsDis = Vect2F::zero;

	for (const Bird* neighbor : neighbors)
	{
		ttNeighborsDis += mTransform.position - neighbor->GetTransform().position;
	}

	mForce += ttNeighborsDis.normalized();
}

void Bird::ResolveCohesion(vector<Bird*> neighbors)
{
	Vect2F force = Vect2F::zero;
	Vect2F ttNeighborsPos = Vect2F::zero;

	for (const Bird* neighbor : neighbors)
	{
		ttNeighborsPos += mTransform.position - neighbor->GetTransform().position;
	}

	force = ttNeighborsPos / (int)neighbors.size() - mTransform.position;

	mForce += force.normalized();
}

vector<vector<Bird*>> Bird::GetNeighbors() const
{
	vector<vector<Bird*>> neighbors = { {}, {}, {} };

	Vect2F normalizedVel = mVelocity.normalized();
	
	float dotTreshold = - (mFov / 180.0f - 1.0f);

	for (GameActor* actor : GameActor::GetActorsByTag(TagBird))
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

		if (Bird* bird = dynamic_cast<Bird*>(actor))
		{
			float distance = (mTransform.position - bird->GetTransform().position).length();
			
			if (distance <= mSeparation)
			{
				neighbors[0].push_back(bird);
			}

			if (distance <= mAlignment)
			{
				neighbors[1].push_back(bird);
			}

			if (distance <= mCohesion)
			{
				neighbors[2].push_back(bird);
			}
		}
	}

	return neighbors;
}

Bird::Bird(Vect2F pos, float size):
	GameActor(0, 0, { pos, Vect2F::one, 0 }, TagBird),
	mSize{ size },
	mSpeed{ 50.0f },
	mSeparation{ 25 },
	mAlignment{ 50 },
	mCohesion{ 100 },
	mFov{ 300 },
	mForce{ Vect2F::zero }
{
	mVelocity = RandVect2Normalized();
}

void Bird::Init()
{
}

void Bird::Update()
{
	ResolveScreenCollisions();

	mForce = GlobalVariables::WindForce;

	ResolveNeighborsRules();

	mVelocity = (mVelocity + mForce * GetFrameTime()).normalized();

	mTransform.position += mVelocity * mSpeed * GetFrameTime();
}

void Bird::Draw()
{
	DrawCircleV(mTransform.position.toRaylib(), mSize, BLACK);
}

void Bird::DrawDebug() const
{
	//Vel
	DrawLineEx(mTransform.position.toRaylib(), (mTransform.position + mVelocity * 30).toRaylib(), 2.0f, GREEN);
	
	//Force
	DrawLineEx(mTransform.position.toRaylib(), (mTransform.position + mForce * 30).toRaylib(), 2.0f, BLUE);

	//Fov
	DrawLineEx(mTransform.position.toRaylib(), (mTransform.position + Vect2FromRot(mVelocity.getRot() - mFov / 2) * 300).toRaylib(), 1.5f, DARKGRAY);
	DrawLineEx(mTransform.position.toRaylib(), (mTransform.position + Vect2FromRot(mVelocity.getRot() + mFov / 2) * 300).toRaylib(), 1.5f, DARKGRAY);

	//Neighbors
	vector<vector<Bird*>> neighbors = GetNeighbors();

	DrawCircleLines(mTransform.position.x, mTransform.position.y, mSeparation, RED);
	for (Bird* bird : neighbors[0])
	{
		DrawCircleLines(bird->GetTransform().position.x, bird->GetTransform().position.y, bird->GetSize() + 2, RED);
	}

	DrawCircleLines(mTransform.position.x, mTransform.position.y, mAlignment, GREEN);
	for (Bird* bird : neighbors[1])
	{
		DrawCircleLines(bird->GetTransform().position.x, bird->GetTransform().position.y, bird->GetSize() + 4, GREEN);
	}

	DrawCircleLines(mTransform.position.x, mTransform.position.y, mCohesion, BLUE);
	for (Bird* bird : neighbors[2])
	{
		DrawCircleLines(bird->GetTransform().position.x, bird->GetTransform().position.y, bird->GetSize() + 6, BLUE);
	}
}
