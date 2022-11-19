#include "raylib.h"
#include "../headerFiles/camera.h"
#include "../headerFiles/tower.h"

int main()
{
    const int screenWidth = 1280;
    const int screenHeight = 720;

    InitWindow(screenWidth, screenHeight, "Baklava");

    //Difining the camera position
    Camera camera = { 0 };
    cameraSetUp(
        camera,
        50.0f, // FOV
        Vector3({12.0f, 12.0f, 12.0f}), // position
        Vector3({0.0f, 0.0f, 0.0f}) // target
    );

    //Initializing the tower
    Vector3 cubePosition = {0.0f, 0.0f, 0.0f};
    int dimensions[3] = {1.0f, 3.0f, 1.0f};
    
    //Initializing the tower stats: atack speed, attack power, defense, tower helth, tower regeneration
    Stats stats = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f};
 
    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        
        BeginDrawing();

            ClearBackground(RAYWHITE);

            BeginMode3D(camera);

                creteTower(cubePosition, dimensions, stats, BLUE, DARKBLUE);
                   
            EndMode3D();

        EndDrawing();
    }

    CloseWindow();        // Close window and OpenGL context

    return 0;
}