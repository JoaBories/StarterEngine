#include "raylib.h"
#include "Engine.h"

void Init();
void DeInit();
void UpdateDraw();
void Update();
void Draw();

Engine engine;

int screenHeight = 600; // Window Size
int screenWidth = 700;  //

Color backgroundColor = BLACK;

const char* gameName = "Starter Engine"; //Name of the window

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
    InitWindow(screenWidth, screenHeight, gameName);
    SetTargetFPS(300);

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
    ClearBackground(backgroundColor);

    Draw();
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

