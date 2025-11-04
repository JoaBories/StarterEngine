#pragma once
#include "AssetBank.h"
#include "Cam2D.h"
#include "GameActor.h"
#include "Fish.h"
#include "Predator.h"

class Engine
{
private :

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

