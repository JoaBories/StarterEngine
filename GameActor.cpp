#include "GameActor.h"

map<int, vector<GameActor*>> GameActor::mActorLogicList;
map<int, vector<GameActor*>> GameActor::mActorRenderList;

vector<GameActor*> GameActor::mPendingDestroy;

void GameActor::AddActorToRenderList(int renderPriority, GameActor* actor)
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

void GameActor::AddActorToLogicList(int logicPriority, GameActor* actor)
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

GameActor::GameActor():
	mLogicPriority{ 0 },
	mRenderPriority{ 0 },
	mTransform{},
	mActive{ true }
{
	AddActorToLogicList(0, this);
	AddActorToRenderList(0, this);
}

GameActor::~GameActor()
{
}

GameActor::GameActor(int logicPriority, int renderPriority, Transform2D transform):
	mLogicPriority{ logicPriority },
	mRenderPriority{ renderPriority },
	mTransform{ transform },
	mActive{ true }
{
	AddActorToLogicList(logicPriority, this);
	AddActorToRenderList(renderPriority, this);
}

void GameActor::Destroy()
{
	mPendingDestroy.push_back(this);
}
