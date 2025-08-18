#pragma once

#include "Cam2D.h"
#include "AssetBank.h"

#include "GameActor.h"

#include <vector>
using std::vector;

class Render2D
{

private:
	AssetBank* mAssetBank;
	Cam2D* mCamera;

	TextureEntry* mTexture;

	Rect2 mTextureSpace; // offset center, texture size, offset rotation

public:

	Render2D() = default;
	~Render2D() = default;

	Render2D(Rect2 textureSpace);

	void Init(string textureName);

	void ChangeTexture(string textureName);
	void ChangeTextureSpace(Rect2 textureSpace);

	Rect2 GetTextureSpace(Rect2 textureSpace) const;

	bool ShouldBeDrawn(const Transform2D& objectTransform) const;
	void Draw(const Transform2D& objectTransform) const;
};

