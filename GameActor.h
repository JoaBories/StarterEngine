#pragma once

#include "Utils.h"
using Struct::Transform2D;

#include <map>
#include <vector>
using std::map, std::vector;

using std::string;

class GameActor
{

private:
	void AddActorToRenderList(int renderPriority, GameActor* actor);
	void AddActorToLogicList(int logicPriority, GameActor* actor);
	void AddActorToTagMap(string tag, GameActor* actor);

protected:
	int mLogicPriority;
	int mRenderPriority;

	string mTag;

	Transform2D mTransform;

	bool mPendingDestroy;
	bool mActive = true;

public:
	static map<int, vector<GameActor*>> mActorLogicList;
	static map<int, vector<GameActor*>> mActorRenderList;
	static map<string, vector<GameActor*>> mActorTagMap;

	static void KillActors();

	GameActor();
	~GameActor() = default;

	GameActor(int logicPriority, int renderPriority, Transform2D transform, string tag);

	void Destroy();

	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;

	Transform2D GetTransform() const;
	void SetTransform(Transform2D transform);

	string GetTag() const;

	vector<GameActor*> GetActorsByTag(string tag);

	bool IsActive() const;
	void SetActive(bool active);

	bool ShouldBeDestroyed();
};

