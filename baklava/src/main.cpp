#include <vector>
#include <iostream>
#include "raylib.h"
#include "../headerFiles/tower.h"
#include "../headerFiles/enemies.h"
#include "../headerFiles/equation.h"
#include "../headerFiles/inputBox.h"
#include "../headerFiles/upgradeMenu.h"

int main()
{
    // Initializing the window
    const int fpsCap = 60;
    const int screenWidth = 1280;
    const int screenHeight = 720;
    int framesCounter = 0;
    InitWindow(screenWidth, screenHeight, "Baklava");

    // Defining the camera
    Camera camera = { 0 };    
    camera.position = Vector3({ 20.0f, 22.0f, 20.0f });
    camera.target = Vector3({ 0.0f, 0.0f, 0.0f });
    camera.up = Vector3({ 0.0f, 1.0f, 0.0f });
    camera.fovy = 35.0f;
    camera.projection = CAMERA_ORTHOGRAPHIC;

    SetConfigFlags(FLAG_MSAA_4X_HINT);

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
    int enemiesThisWave = 0;
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

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        framesCounter++;

        if (vignettingTimer == 0)
        {
            isDamaged = false;
            vignettingTimer = 15;
        }
        else
        {
            vignettingTimer--;
        }

        //Implementing zoom mechaninc
        if (camera.fovy >= 20.0f && camera.fovy <= 35.0f)
            camera.fovy -= GetMouseWheelMove() * 2;
        else if (camera.fovy >= 20.0f)
            camera.fovy -= 0.08f;
        else
            camera.fovy += 0.08f;
        
        // Generates new enemy when under enemy limit and off cooldown      
        if (enemiesThisWave != mainWave.enemiesLeft && mainWave.wave <= wavesLeft && waveTimer == 0)
        {
            if (enemyList.size() <= enemyLimit && enemyDebounce == 0)
            {
                enemyList.push_back(generateEnemy(mainWave));

                enemyDebounce = debounceTimer;
                enemiesThisWave++;
            }
            enemyDebounce--;
        }
        else if (waveTimer == 0)
        {
            mainWave.wave = mainWave.wave++;
            waveTimer = 8 * fpsCap;
            enemiesThisWave = 0;
        }
        else
        {
            waveTimer--;
        }

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
        DrawRectangleGradientH(0, 0, 1280, 720, CLITERAL(Color){14, 51, 27, 255},CLITERAL(Color){51, 184, 100, 255} );
        DrawRectangleGradientV(0, 0, 1280, 720, CLITERAL(Color){14, 51, 27, 100}, CLITERAL(Color) { 51, 184, 100, 100 });
       
        if (IsKeyPressed(KEY_ENTER))
        {
            int playerAnswer = convertedPlayerAnswer(inputBox);

            if (equation.answer == playerAnswer)
            {
                for (size_t i = 0; i < 4; i++)
                {
                    inputBox.input[i] = ' ';
                }
                inputBox.numCount = 0;

                for (size_t i = 0; i < towerStats.multiKill; i++)
                {
                    killEnemy(enemyList, towerStats, score, gold);
                }
            }
            else
            {
				for (size_t i = 0; i < 4; i++)
                {
                    inputBox.input[i] = ' ';
                }
                inputBox.numCount = 0;

                if(score > 0)
                    score -= 10;
            }
            
            equation = generateEquation();

        }


        BeginMode3D(camera);

        if(framesCounter > 120)
        {
            for (size_t i = 0; i < enemyList.size(); i++)
            {
                drawEnemy(enemyList[i]);

                enemyList[i].linePos -= 1.8f * GetFrameTime();

                if (enemyList[i].linePos <= 1.8f)
                {
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

        DrawFPS(10, 10);

        EndDrawing();
    }

    CloseWindow();        // Close window and OpenGL context

    return 0;
}

