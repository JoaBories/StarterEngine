#include "SceneManager.h"

SceneManager* SceneManager::mpInstance = nullptr;

SceneManager* SceneManager::GetInstance()
{
	if (!mpInstance)
	{
		mpInstance = new SceneManager();
	}

	return mpInstance;
}

void SceneManager::ChangeScene(Scenes newScene)
{
	GameActor::Killa();

	mCurrentScene = newScene;

	switch (newScene)
	{
	case SceneDefault:
		break;

	default:
		break;
	}
}

void SceneManager::Update()
{
	switch (mCurrentScene)
	{
	case SceneDefault:
		break;

	default:
		break;
	}
}
