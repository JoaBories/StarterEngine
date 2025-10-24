#pragma once
#include "Cam2D.h"
#include "SceneManager.h"

class Engine
{
private :

	SceneManager* mSceneManager;
	AssetBank* mAssetBank;
	Cam2D* mCamera;

public :
	Engine() = default;
	~Engine();

	void Init();
	void InitActors();

	void Update();
	void UpdateActors();

	void Draw();
	void DrawActors();
};

