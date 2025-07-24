#include "raylib.h"
#include "Engine.h"

void Init();
void DeInit();
void UpdateDraw();
void Update();
void Draw();

Engine engine;

int screenHeight = 480;
int screenWidth = 480;

Color backgroundColor = BLACK;

const char* gameName = "Starter Project";

int main() {

    Init();
    
    while (!WindowShouldClose()) {
        
        UpdateDraw();
    }

    DeInit();
    
    return 0;
}

void Init()
{
    InitWindow(screenHeight, screenWidth, gameName);
    SetTargetFPS(60);

    engine.Init();
}

void DeInit()
{
    CloseWindow();
}

void UpdateDraw()
{
    Update();

    BeginDrawing();
    Draw();

    ClearBackground(backgroundColor);
    EndDrawing();
}

void Update()
{
    engine.Update();
}

void Draw()
{
    engine.Draw();
}

