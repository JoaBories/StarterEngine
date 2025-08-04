#pragma once
#include "AssetBank.h"

#include "Ball.h"

class Engine
{
private :

	int mBallCount;


public :
	Engine();
	~Engine();

	void Init();

	void Update();
	void UpdateActors();

	void Draw();
	void DrawActors();
};

