#include <vector>
#include <iostream>
#include "raylib.h"
#include "../headerFiles/tower.h"
#include "../headerFiles/enemies.h"
#include "../headerFiles/equation.h"
#include "../headerFiles/inputBox.h"
#include "../headerFiles/upgradeMenu.h"
#include "../headerFiles/mainMenu.h"
#include "../headerFiles/buttonHandler.h"
#include "../headerFiles/victoryScreen.h"
#include "../headerFiles/defeatScreen.h"

int main()
{
    // Initializing the window
    const int fpsCap = 60;
    const int screenWidth = 1280;
    const int screenHeight = 720;
    int frameCounter = 0;
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(screenWidth, screenHeight, "Baklava");

    // Defining the camera
    Camera camera = { 0 };    
    camera.position = Vector3({ 20.0f, 22.0f, 20.0f });
    camera.target = Vector3({ 0.0f, 0.0f, 0.0f });
    camera.up = Vector3({ 0.0f, 1.0f, 0.0f });
    camera.fovy = 35.0f;
    camera.projection = CAMERA_ORTHOGRAPHIC;

    // Initializing the tower stats: attack power, health, regen, multiKill, size and position
    TowerStats towerStats = { 5.0f, 1.0f, 0.01f, 1, Vector3({3.0f, 9.0f, 3.0f}), Vector3({0.0f, 4.5f, 0.0f}) };
 
    // Initializing enemy system
    const int enemyLimit = 6, debounceTimer = 0.8*fpsCap;
    std::vector<EnemyStats> enemyList;
    enemyList.reserve(enemyLimit);
    int enemyDebounce = 0;


    // Defining the variables for the wave system
    int waveTextDuration = 180;
    int wavesLeft = 10;
    EnemyWave mainWave;
    mainWave.wave = 1;
    mainWave.enemiesLeft = 6;
    mainWave.enemiesLeftAlive = mainWave.enemiesLeft;
    int waveTimer = 2 * fpsCap;

    // Generating equation
    char operationSymbol = ' ';
    Equation equation = generateEquation();
        
    //Defining the variable for the text box
    InputBoxInfo inputBox;
    inputBox.input[4] = '\0';
    inputBox.textBox = {screenWidth / 2.0f - 20, 39, 100, 35};

    Button upgradeDamageButton = { 18.0f, 115.0f, 200.0f, 25.0f };
    Button upgradeRegenButton = { 18.0f, 145.0f, 200.0f, 25.0f };
    Button upgradeMultiKillButton = { 18.0f, 175.0f, 200.0f, 25.0f };

    int score = 0;
    int gold = 0;

    //Defining the variable for the hit animation
    bool isDamaged = false;
    int vignettingTimer = 15;

    // Setting the fps cap to 60
    SetTargetFPS(fpsCap);

    //Enter main menu
    int mmFadeTimer = 255;
    if (!mainMenuLoop())
    {
        return 0;
    }

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        frameCounter++;

        if (mainWave.wave > 10)
        {
            if (showVictoryScreen())
            {
                mainWave.wave = 1;
                mainWave.enemiesLeft = 6;
                mainWave.enemiesLeftAlive = mainWave.enemiesLeft;
                waveTimer = 2 * fpsCap;
                enemyList.clear();
                score = 0;
                gold = 0;
                towerStats.multiKill = 1;
                towerStats.towerRegen = 0.01f;
                towerStats.attackPower = 5.0f;
                towerStats.towerHealth = 150.0f;
                inputBox.input[0] = '\0';
            }
            else
            {
                break;
            }
        }
        if (towerStats.towerHealth <= 0.0f)
        {
            if (showDefeatScreen())
            {
                mainWave.wave = 1;
                mainWave.enemiesLeft = 6;
                mainWave.enemiesLeftAlive = mainWave.enemiesLeft;
                waveTimer = 2 * fpsCap;
                enemyList.clear();
                score = 0;
                gold = 0;
                towerStats.multiKill = 1;
                towerStats.towerRegen = 0.01f;
                towerStats.attackPower = 5.0f;
                towerStats.towerHealth = 150.0f;
                inputBox.input[0] = '\0';
            }
            else
            {
                break;
            }
        }

        if (vignettingTimer == 0)
        {
            isDamaged = false;
            vignettingTimer = 15;
        }
        else
        {
            vignettingTimer--;
        }

        //Implementing zoom mechanic
        float zoomChange = GetMouseWheelMove() * 2;
        if(camera.fovy - zoomChange >= 20.0f && camera.fovy - zoomChange <= 35.0f)
            camera.fovy -= zoomChange;
        else if (camera.fovy - zoomChange < 20.0f)
            camera.fovy = 20.0f;
        else
            camera.fovy = 35.0f;
        
        // Generates new enemy when under enemy limit and off cooldown      
        waveSpawnHandler(enemyDebounce, enemyLimit, mainWave, enemyList, waveTimer, fpsCap);

        switch (equation.operation)
	    {
		case 0:
            operationSymbol = '+';
			break;
		case 1:
            operationSymbol = '-';
			break;
		case 2:
            operationSymbol = 'x';
			break;
	    }

        //Regen
        if(towerStats.towerHealth <= 150.0f)
            towerStats.towerHealth += towerStats.towerRegen;

        BeginDrawing();

        ClearBackground(RAYWHITE);
        DrawRectangleGradientH(0, 0, 1280, 720, CLITERAL(Color){1, 97, 33, 255},CLITERAL(Color){2, 171, 58, 255} );
        DrawRectangleGradientV(0, 0, 1280, 720, CLITERAL(Color){1, 97, 33, 255}, CLITERAL(Color) { 2, 171, 58, 255 });
       
        if (IsKeyPressed(KEY_ENTER))
        {
            equationHandler(inputBox, equation, towerStats, mainWave, enemyList, score, gold);
        }


        BeginMode3D(camera);

        if(frameCounter > 2 * fpsCap)
        {
            for (size_t i = 0; i < enemyList.size(); i++)
            {
                drawEnemy(enemyList[i]);

                enemyList[i].linePos -= 1.8f * GetFrameTime();

                if (enemyList[i].linePos <= 1.8f)
                {
                    mainWave.enemiesLeftAlive--;
                    towerStats.towerHealth -= enemyList[i].damage;
                    enemyList.erase(enemyList.begin() + i);
                    isDamaged = true;
                }
            }
        }
 
        if (towerStats.towerHealth > 0) {
            drawTower(towerStats);
        }

        DrawGrid(50, 5.0f);
        EndMode3D();


        if (isDamaged)
        {
            DrawCircleGradient(screenWidth / 2.0f, screenHeight / 2.0f, 750, CLITERAL(Color){0, 0, 0, 0}, CLITERAL(Color) { 180, 0, 0, 100 });
        }

        //Drawing the UI
        DrawText(TextFormat("%i %c %i = ", equation.firstNumber, operationSymbol, equation.secondNumber), (screenWidth / 2.0f) - 100, 50, 20, WHITE);
        DrawText(TextFormat("Score: %i", score), 10, 50, 30, WHITE);
        DrawText(TextFormat("Gold: %i", gold), 10, 80, 25, WHITE);
        drawUpgradeMenu(upgradeDamageButton, upgradeRegenButton, upgradeMultiKillButton);
        drawInputBox(inputBox);


        upgradeRegen(towerStats, gold, upgradeRegenButton);
        upgradeDamage(towerStats, gold, upgradeDamageButton);
        upgradeMultiKill(towerStats, gold, upgradeMultiKillButton);


        if ( waveTextDuration > 0 && enemyList.size() == 0 && mainWave.wave <= 10)
        {
            DrawText(TextFormat("Wave %i", mainWave.wave), screenWidth / 2.0f - 80, screenHeight / 2.0f - 100, 50, WHITE);
            waveTextDuration--;
        }
        else
        {
            waveTextDuration = waveTimer;
        }

        
        DrawRectangleGradientH(screenWidth / 2.0f - (towerStats.towerHealth * 3) / 2, screenHeight - 100, towerStats.towerHealth * 3, 60, CLITERAL(Color) { 0, 89, 0, 255 }, CLITERAL(Color){0, 158, 0, 255});
        DrawRectangleLines(screenWidth / 2.0f - (towerStats.towerHealth * 3) / 2, screenHeight - 100, towerStats.towerHealth * 3, 60, BLACK);
        DrawText("Health:", screenWidth / 2.0f - 60, screenHeight - 136, 40, WHITE);

        DrawFPS(10, 10);

        if (mmFadeTimer > 0)
        {
            mmFadeTimer -= 5;
            DrawRectangle(0, 0, screenWidth, screenHeight, CLITERAL(Color){ 0, 0, 0, (unsigned char)mmFadeTimer});
        }

        EndDrawing();
    }

    CloseWindow();        // Close window and OpenGL context

    return 0;
}

