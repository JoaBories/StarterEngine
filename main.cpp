#include "raylib.h"
#include "headers/Engine.h"

void Init();
void DeInit();
void UpdateDraw();
void Update();
void Draw();

Engine engine;

int screenHeight = 720; // Window Size
int screenWidth = 1720;  //

Color backgroundColor = Color{ 10, 20, 40, 255 };

const char* gameName = "Swarm Sim"; //Name of the window

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
    srand((unsigned int)time(0));

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

