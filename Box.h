#pragma once
#include "GameActor.h"
#include "Render2D.h"

using Struct::Rect2;
using Struct::Collision;

class Box : public GameActor
{
private:
	Render2D mRender;

public:
	Box() = default;
	~Box() = default;

	Box(int priority, Vect2F halfSize, Transform2D transform);

	// Inherited via GameActor
	void Update() override;
	void Draw() override;
	void Init() override;
};

