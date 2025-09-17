#include "Engine.h"

using MathUtils::RandInt;

Engine::~Engine()
{
	for (auto& actorList : GameActor::mActorLogicList)
	{
		for (auto& actor : actorList.second)
		{
			delete actor;
		}
	}

	GameActor::mActorLogicList.clear();
	GameActor::mActorRenderList.clear();
	GameActor::mActorTagMap.clear();
}

void Engine::Init()
{
	mAssetBank = AssetBank::GetInstance();
	mCamera = Cam2D::GetInstance();

	mAssetBank->Init();

	InitActors(); // for actors created before (if there is)

	GlobalVariables::EngineRunning = true;
}

void Engine::InitActors()
{
	if (GameActor::mActorLogicList.empty())
	{
		return;
	}

	for (auto& actorList : GameActor::mActorLogicList)
	{
		for (auto& actor : actorList.second)
		{
			actor->Init();
		}
	}
}

void Engine::Update()
{
	mCamera->Update();

	UpdateActors();

	GameActor::KillPendingActors();
}

void Engine::UpdateActors()
{
	if (GameActor::mActorLogicList.empty()) 
	{
		return;
	}

	for (auto& actorList : GameActor::mActorLogicList) 
	{
		for (auto& actor : actorList.second)
		{
			actor->Update();
		}
	}
}

void Engine::Draw()
{
	DrawActors();

	if (GlobalVariables::ShowFPS)
	{
		DrawFPS(100, 100);
	}
}

void Engine::DrawActors()
{
	if (GameActor::mActorRenderList.empty())
	{
		return;
	}

	for (auto& actorList : GameActor::mActorRenderList)
	{
		for (auto& actor : actorList.second)
		{
			actor->Draw();
		}
	}
}
