#include "Cam2D.h"

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

Rect2 Cam2D::GetCamSpace() const
{
    Vect2F halfSize = { GetScreenWidth() * mZoom * 0.5f, GetScreenHeight() * mZoom * 0.5f };
    Rect2 camSpace = { mPosition, halfSize, 0 };

    return camSpace;
}

Cam2D* Cam2D::GetInstance()
{
    if (!instance) 
    {
        instance = new Cam2D();
    }

    return instance;
}
