#include "Engine.h"

using MathUtils::RandInt;
using MathUtils::RandFloat;
using MathUtils::RandVect2Normalized;

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

	for (int i = 0; i < 500; i++)
	{
		new Bird({ RandFloat(0, (float)GetScreenWidth()), RandFloat(0, (float)GetScreenHeight())});
	}
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

	//dynamic_cast<Bird*>(GameActor::GetActorsByTag(TagBird)[0])->DrawDebug(); Draw Debug for one bird

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
