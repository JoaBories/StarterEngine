#include "raylib.h"
#include "headers/Engine.h"

void Init();
void DeInit();
void UpdateDraw();
void Update();
void Draw();

Engine engine;

int screenHeight = 600; // Window Size
int screenWidth = 700;  //

Color backgroundColor = RAYWHITE;

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
    srand(time(0));

    InitWindow(screenWidth, screenHeight, gameName);
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

