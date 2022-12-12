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

    //Load font and configure upscaling
    Font mainFont = LoadFontEx("assets/fonts/MainFont.ttf", 108, NULL, 0);
    SetTextureFilter(mainFont.texture, TEXTURE_FILTER_BILINEAR);

    // Defining the camera
    Camera camera = { 0 };    
    camera.position = Vector3({ 20.0f, 22.0f, 20.0f });
    camera.target = Vector3({ 0.0f, 0.0f, 0.0f });
    camera.up = Vector3({ 0.0f, 1.0f, 0.0f });
    camera.fovy = 35.0f;
    camera.projection = CAMERA_ORTHOGRAPHIC;

    // Initializing the tower stats: attack power, health, regen, multiKill, size and position
    TowerStats towerStats = { 5.0f, 150.0f, 0.01f, 1, Vector3({3.0f, 9.0f, 3.0f}), Vector3({0.0f, 4.5f, 0.0f}) };
 
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

    Rectangle upgradeMenu = { -324, 0, 320, 720 };
    Button upgradeMenuButton = { Rectangle{ -4, 39, 60, 206 }, 0, CLITERAL(Color){ 187, 187, 187, 255 }, CLITERAL(Color) { 167, 167, 167, 255 } };
    Button upgradeDamageButton = { 18.0f, 115.0f, 200.0f, 25.0f };
    Button upgradeRegenButton = { 18.0f, 145.0f, 200.0f, 25.0f };
    Button upgradeMultiKillButton = { 18.0f, 175.0f, 200.0f, 25.0f };
    
    bool currentMenuState = false;


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

        if (mainWave.wave > 11)
        {
            fadeToGame();
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

        //Implement zoom mechanic
        float zoomChange = GetMouseWheelMove() * 2;
        if(camera.fovy - zoomChange >= 20.0f && camera.fovy - zoomChange <= 35.0f)
            camera.fovy -= zoomChange;
        else if (camera.fovy - zoomChange < 20.0f)
            camera.fovy = 20.0f;
        else
            camera.fovy = 35.0f;
        
        // Generate new enemy when under enemy limit and off cooldown      
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
        DrawTextEx(mainFont, TextFormat("%i %c %i = ", equation.firstNumber, operationSymbol, equation.secondNumber), Vector2({ (screenWidth / 2.0f) - 100, 40 }), 32, 0, WHITE);
        DrawTextEx(mainFont, TextFormat("Score: %i", score), Vector2({ 10, 50 }), 54, 0, WHITE);
        DrawTextEx(mainFont, TextFormat("Gold: %i", gold), Vector2({ 10, 25 }), 36, 0, WHITE);
        drawInputBox(inputBox);

        setButtonState(upgradeMenuButton);

        if (changeButtonByState(upgradeMenuButton, 60, false, false))
        {
            currentMenuState = !currentMenuState;
        }
        if (upgradeMenu.x >= -324 && upgradeMenu.x <= 4)
        {
            openUpgradeMenu(upgradeMenuButton, upgradeMenu, currentMenuState);
        }
        if (upgradeMenu.x < -324)
        {
            upgradeMenu.x = -324;
            upgradeMenuButton.rec.x = -4;
        }
        if (upgradeMenu.x > 0)
        {
            upgradeMenu.x = 0;
            upgradeMenuButton.rec.x = 324;
        }

        DrawRectangleRec(upgradeMenu, CLITERAL(Color){0, 0, 0, 120});
        DrawTextPro(mainFont, "Upgrades", Vector2({ upgradeMenuButton.rec.x + 50, upgradeMenuButton.rec.y + 20}), Vector2({0.5f, 0.5f}), 90, 44, 0, DARKGRAY);


        Vector2 waveTextSize = MeasureTextEx(mainFont, TextFormat("Wave %i", mainWave.wave), 96, 0);
        if ( waveTextDuration > 0 && enemyList.size() == 0 && mainWave.wave <= 10)
        {
            DrawTextEx(mainFont, TextFormat("Wave %i", mainWave.wave), Vector2({ screenWidth / 2.0f - waveTextSize.x / 2.0f, screenHeight / 2.2f - waveTextSize.y / 2.0f }), 96, 0, WHITE);
            waveTextDuration--;
        }
        else
        {
            waveTextDuration = waveTimer;
        }

        //HEALTHBAR REDO
        Vector2 hpTextSize = MeasureTextEx(mainFont, TextFormat("%i/%i", (int)towerStats.towerHealth, 150), 36, 0);

        DrawRectangle(screenWidth / 2.0f - (150 * 3) / 2, screenHeight - 100, 150 * 3, 60, GRAY);
        DrawRectangleLinesEx(Rectangle{ screenWidth / 2.0f - (150 * 3) / 2, screenHeight - 100, 150 * 3, 60 }, 5, BLACK);
        DrawRectangle((screenWidth / 2.0f - (150 * 3) / 2) + 5, screenHeight - 60, towerStats.towerHealth * 3 - 10, 15, MAROON);
        DrawRectangle((screenWidth / 2.0f - (150 * 3) / 2) + 5, screenHeight - 95, towerStats.towerHealth * 3 - 10, 35, RED);
        DrawTextEx(mainFont, TextFormat("%i/%i", (int)towerStats.towerHealth, 150), Vector2({ screenWidth / 2 - hpTextSize.x / 2, screenHeight - 72 - hpTextSize.y / 2 }), 36, 0, RAYWHITE);

        DrawFPS(10, 10);

        if (mmFadeTimer > 0)
        {
            mmFadeTimer -= 5;
            DrawRectangle(0, 0, screenWidth, screenHeight, CLITERAL(Color){ 0, 0, 0, (unsigned char)mmFadeTimer});
        }

        EndDrawing();
    }

    CloseWindow();        // Close window and OpenGL context

    UnloadFont(mainFont);

    return 0;
}

