#include "GameActor.h"
#include "GlobalVariables.h"

map<short, vector<GameActor*>> GameActor::mActorLogicList;
map<short, vector<GameActor*>> GameActor::mActorRenderList;
map<Tag, vector<GameActor*>> GameActor::mActorTagMap;

void GameActor::AddActorToRenderList(short renderPriority, GameActor* actor)
{
	if (mActorRenderList.find(renderPriority) == mActorRenderList.end()) 
	{
		mActorRenderList[renderPriority] = vector<GameActor*>{ actor };
	}
	else
	{
		mActorRenderList[renderPriority].push_back(actor);
	}
}

void GameActor::AddActorToLogicList(short logicPriority, GameActor* actor)
{
	if (mActorLogicList.find(logicPriority) == mActorLogicList.end())
	{
		mActorLogicList[logicPriority] = vector<GameActor*>{ actor };
	}
	else
	{
		mActorLogicList[logicPriority].push_back(actor);
	}
}

void GameActor::AddActorToTagMap(Tag tag, GameActor* actor)
{
	if (mActorTagMap.find(tag) == mActorTagMap.end())
	{
		mActorTagMap[tag] = vector<GameActor*>{ actor };
	}
	else
	{
		mActorTagMap[tag].push_back(actor);
	}
}

void GameActor::KillPendingActors()
{
	if (mActorLogicList.empty())
	{
		return;
	}

	for (auto& actorList : mActorLogicList)
	{
		for (size_t i = 0; i < actorList.second.size(); i++)
		{
			if (actorList.second[i]->ShouldBeDestroyed())
			{
				delete actorList.second[i];

				actorList.second.erase(actorList.second.begin() + i);
			};
		}
	}

	if (mActorRenderList.empty())
	{
		return;
	}

	for (auto& actorList : mActorRenderList)
	{
		for (size_t i = 0; i < actorList.second.size(); i++)
		{
			if (actorList.second[i]->ShouldBeDestroyed())
			{
				delete actorList.second[i];

				actorList.second.erase(actorList.second.begin() + i);
			};
		}
	}

	if (mActorTagMap.empty())
	{
		return;
	}

	for (auto& actorList : mActorTagMap)
	{
		for (size_t i = 0; i < actorList.second.size(); i++)
		{
			if (actorList.second[i]->ShouldBeDestroyed())
			{
				delete actorList.second[i];

				actorList.second.erase(actorList.second.begin() + i);
			};
		}
	}
}

GameActor::GameActor() :
	mLogicPriority{ 0 },
	mRenderPriority{ 0 },
	mPendingDestroy{ false },
	mTransform{},
	mTag{ TagDefault },
	mActive{ true }
{
	AddActorToLogicList(mLogicPriority, this);
	AddActorToRenderList(mRenderPriority, this);
	AddActorToTagMap(mTag, this);
}

GameActor::GameActor(short logicPriority, short renderPriority, Transform2D transform, Tag tag):
	mLogicPriority{ logicPriority },
	mRenderPriority{ renderPriority },
	mPendingDestroy{ false },
	mTransform{ transform },
	mTag{ tag },
	mActive{ true }
{
	AddActorToLogicList(logicPriority, this);
	AddActorToRenderList(renderPriority, this);
	AddActorToTagMap(mTag, this);
}

void GameActor::Destroy()
{
	mPendingDestroy = true;
}

Transform2D GameActor::GetTransform() const
{
	return mTransform;
}

void GameActor::SetTransform(Transform2D transform)
{
	mTransform = transform;
}

Tag GameActor::GetTag() const
{
	return mTag;
}

vector<GameActor*> GameActor::GetActorsByTag(Tag tag)
{
	if (mActorTagMap.find(tag) == mActorTagMap.end())
	{
		return vector<GameActor*>{};
	}

	return mActorTagMap[tag];
}

bool GameActor::IsActive() const
{
	return mActive;
}

void GameActor::SetActive(bool active)
{
	mActive = active;
}

bool GameActor::ShouldBeDestroyed() const
{
	return mPendingDestroy;
}
