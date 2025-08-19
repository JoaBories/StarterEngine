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

	for (int i = 0; i < 10000; i++)
	{
		new Box(0, { (float)RandInt(1, 30), (float)RandInt(1, 30) }, { { (float)RandInt(-300, 300), (float)RandInt(-300, 300)}, Vect2F::one, (float)RandInt(0,360)});
	}
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

	GameActor::KillActors();
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

	DrawFPS(100, 100);
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
