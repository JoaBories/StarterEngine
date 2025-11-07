#pragma once

#include "GlobalVariables.h"

#include "Util.h"
using Struct::Transform2D;

#include <map>
using std::map;

enum Tag
{
	TagDefault,
	TagFish,
	TagPredator
};

class GameActor
{

private:
	void AddActorToRenderList(short renderPriority, GameActor* actor);
	void AddActorToLogicList(short logicPriority, GameActor* actor);
	void AddActorToTagMap(Tag tag, GameActor* actor);

	static map<short, vector<GameActor*>> mActorLogicList;
	static map<short, vector<GameActor*>> mActorRenderList;
	static map<Tag, vector<GameActor*>> mActorTagMap;

protected:
	short mLogicPriority;
	short mRenderPriority;

	Tag mTag;

	Transform2D mTransform;

	bool mPendingDestroy;
	bool mActive = true;

public:
	//Static for all GameActors
	static vector<GameActor*> GetActorsByTag(Tag tag);
	static void KillPendingActors();

	inline static map<short, vector<GameActor*>> GetActorsLogic() { return mActorLogicList; };
	inline static map<short, vector<GameActor*>> GetActorsRender() { return mActorRenderList; };

	//Public for object only
	GameActor();
	~GameActor() = default;

	GameActor(short logicPriority, short renderPriority, Transform2D transform, Tag tag);

	void Destroy();

	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;

	Transform2D GetTransform() const;
	void SetTransform(Transform2D transform);

	Tag GetTag() const;

	bool IsActive() const;
	void SetActive(bool active);

	bool ShouldBeDestroyed() const;
};

