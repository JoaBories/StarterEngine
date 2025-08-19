#include "Box.h"

Box::Box(int priority, Vect2F halfSize, Transform2D transform) :
	GameActor(priority, priority, transform, TagBox),
	mRender{ Render2D({{0, 0} , halfSize, 0})}
{
	if (GlobalVariables::EngineRunning)
	{
		Init();
	}
}

void Box::Update()
{
}

void Box::Draw()
{
	mRender.Draw(mTransform);
}

void Box::Init()
{
	mRender.Init("box");

	return;
}