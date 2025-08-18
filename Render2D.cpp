#include "Render2D.h"

Render2D::Render2D(Rect2 textureSpace):
	mAssetBank{ nullptr },
	mCamera{ nullptr },
	mTexture{ nullptr },
	mTextureSpace{ textureSpace }
{
}

void Render2D::Init(string textureName)
{
	mAssetBank = AssetBank::GetInstance();
	mCamera = Cam2D::GetInstance();

	mTexture = mAssetBank->GetATexture(textureName);
}

void Render2D::ChangeTexture(string textureName)
{
	mTexture = mAssetBank->GetATexture(textureName);
}

void Render2D::ChangeTextureSpace(Rect2 textureSpace)
{
	mTextureSpace = textureSpace;
}

Rect2 Render2D::GetTextureSpace(Rect2 textureSpace) const
{
	return mTextureSpace;
}

bool Render2D::ShouldBeDrawn(const Transform2D& objectTransform) const
{
	Rect2 objectSpace = { mTextureSpace.center + objectTransform.position, mTextureSpace.halfSize * objectTransform.scale, mTextureSpace.rotation + objectTransform.rotation };
	Rect2 camSpace = mCamera->GetCamSpace();



	return false;
}

void Render2D::Draw(const Transform2D& objectTransform) const
{
	Rect2 objectSpace = { mTextureSpace.center + objectTransform.position, mTextureSpace.halfSize * objectTransform.scale, mTextureSpace.rotation + objectTransform.rotation };

	if (ShouldBeDrawn(objectTransform))
	{

	}
}
