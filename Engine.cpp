#include "Engine.h"

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
}

void Engine::Init()
{
	mAssetBank = AssetBank::GetInstance();
	mCamera = Cam2D::GetInstance();

	mAssetBank->Init();

	InitActors();
	
	new Box(1, 10.0f, { 30, 30 }, { { 300, 200}, Vect2F::one, 0 });
	new Box(2, 10.0f, { 30, 30 }, { { 400, 500}, Vect2F::one, 0 });
	new Box(3, 10.0f, { 30, 30 }, { { 250, 400}, Vect2F::one, 0 });
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
