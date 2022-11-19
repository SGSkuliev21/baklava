#include "raylib.h"
#include "../headerFiles/camera.h"

int main()
{
    const int screenWidth = 1280;
    const int screenHeight = 720;

    InitWindow(screenWidth, screenHeight, "Baklava");

    //Difining the camera position
    Camera camera = { 0 };
    cameraSetUp(
        camera,
        60.0f, // FOV
        Vector3({12.0f, 12.0f, 12.0f}), // position
        Vector3({0.0f, 0.0f, 0.0f}) // target
    );


    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        
        BeginDrawing();

            ClearBackground(RAYWHITE);

            BeginMode3D(camera);

              DrawCube({0.0f, 0.0f, 0.0f}, 1.5f, 3.5f, 1.5f, MAROON);
            
            EndMode3D();

        EndDrawing();
    }

    CloseWindow();        // Close window and OpenGL context

    return 0;
}