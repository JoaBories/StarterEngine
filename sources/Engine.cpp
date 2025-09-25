#include "Engine.h"

using MathUtils::RandInt;

Engine::~Engine()
{
	//for (auto& actorList : GameActor::GetActorsLogic())
	//{
	//	for (auto& actor : actorList.second)
	//	{
	//		delete actor;
	//	}
	//}

	//GameActor::mActorLogicList.clear();
	//GameActor::mActorRenderList.clear();
	//GameActor::mActorTagMap.clear();

	// have to reimplement this in gameactor
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
	if (GameActor::GetActorsLogic().empty())
	{
		return;
	}

	for (auto& actorList : GameActor::GetActorsLogic())
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
	if (GameActor::GetActorsLogic().empty())
	{
		return;
	}

	for (auto& actorList : GameActor::GetActorsLogic())
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
	if (GameActor::GetActorsRender().empty())
	{
		return;
	}

	for (auto& actorList : GameActor::GetActorsRender())
	{
		for (auto& actor : actorList.second)
		{
			actor->Draw();
		}
	}
}
