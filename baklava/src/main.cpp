#include "raylib.h"


int main()
{
    const int screenWidth = 1280;
    const int screenHeight = 720;

    InitWindow(screenWidth, screenHeight, "Baklava");

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------


        BeginDrawing();
        ClearBackground(RAYWHITE);


        
        EndDrawing();
    }

    CloseWindow();        // Close window and OpenGL context

    return 0;
}