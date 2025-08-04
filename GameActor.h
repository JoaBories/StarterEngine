#pragma once

#include "Utils.h"

#include <map>
#include <vector>
using std::map, std::vector;

struct Transform2D
{
	Vect2F position = Vect2F::zero;
	Vect2F scale = Vect2F::one;
	float rotation;
};

class GameActor
{

private:
	void AddActorToRenderList(int renderPriority, GameActor* actor);
	void AddActorToLogicList(int logicPriority, GameActor* actor);

protected:
	int mLogicPriority;
	int mRenderPriority;

	Transform2D mTransform;

	bool mActive = true;

public:
	static map<int, vector<GameActor*>> mActorLogicList;
	static map<int, vector<GameActor*>> mActorRenderList;

	static vector<GameActor*> mPendingDestroy;

	GameActor();
	~GameActor();

	GameActor(int logicPriority, int renderPriority, Transform2D transform);

	void Destroy();

	virtual void Update() = 0;
	virtual void Draw() = 0;
};

