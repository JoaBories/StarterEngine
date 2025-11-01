#include "Cam2D.h"
#include "GlobalVariables.h"

Cam2D* Cam2D::instance = nullptr;

Cam2D::Cam2D():
    mPosition{ Vect2F::zero },
    mZoom{ 1 }
{
}

void Cam2D::Update()
{
    //Movement if you want
}

Vect2F Cam2D::GetPosition() const
{
    return mPosition;
}

float Cam2D::GetZoom() const
{
    return mZoom;
}

void Cam2D::SetPosition(Vect2F newPosition)
{
    mPosition = newPosition;
}

Rect2 Cam2D::GetCamSpace() const
{
    Vect2F halfSize = { GetScreenWidth() * 0.5f, GetScreenHeight() * 0.5f };
    Vect2F center = { (float)GetScreenWidth(), (float)GetScreenHeight() };
    Rect2 camSpace = { center * 0.5f, halfSize, 0};

    return camSpace;
}

Rect2 Cam2D::GetSafeCamSpace() const
{
    Rect2 safeCamSpace = GetCamSpace();
    safeCamSpace.halfSize *= GlobalVariables::CullingSizeMultiplier;

    return safeCamSpace;
}

Cam2D* Cam2D::GetInstance()
{
    if (!instance) 
    {
        instance = new Cam2D();
    }

    return instance;
}
