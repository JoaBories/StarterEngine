#include "Engine.h"

Engine::Engine()
{
}

Engine::~Engine()
{
}

void Engine::Init()
{
	AssetBank::GetInstance()->Init();
}

void Engine::Update()
{
	if (mBallCount < 4000) 
	{
		Vect2F startVel = { (float)Utils::RandInt(-100, 100), (float)Utils::RandInt(-100, 100) };
		startVel = startVel.normalized() * 50;

		new Ball(startVel, 10, WHITE);

		mBallCount++;
	}

	UpdateActors();
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

	DrawText(std::to_string(mBallCount).c_str(), GetScreenWidth() / 2, GetScreenHeight() / 2, 30, GREEN);
	DrawFPS(GetScreenWidth() / 2 - 20, GetScreenHeight() / 2 - 20);
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
