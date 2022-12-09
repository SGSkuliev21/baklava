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
    InitWindow(screenWidth, screenHeight, "Baklava");

    // Defining the camera
    Camera camera = { 0 };    
    camera.position = Vector3({ 20.0f, 22.0f, 20.0f });
    camera.target = Vector3({ 0.0f, 0.0f, 0.0f });
    camera.up = Vector3({ 0.0f, 1.0f, 0.0f });
    camera.fovy = 35.0f;
    camera.projection = CAMERA_ORTHOGRAPHIC;

    SetConfigFlags(FLAG_MSAA_4X_HINT);

    // Initializing the tower stats: attack power, health, regen, multyKill, size and position
    TowerStats towerStats = { 5.0f, 150.0f, 0.01f, 1, Vector3({3.0f, 9.0f, 3.0f}), Vector3({0.0f, 4.5f, 0.0f}) };
 
    // Initializing enemy system
    const int enemyLimit = 6, debounceTimer = 0.8*fpsCap;
    std::vector<EnemyStats> enemyList;
    enemyList.reserve(enemyLimit);
    int enemyDebounce = 0;

    // Defining the variables for the wave system
    float waveTimerDecrement = 0.0f;
    int wavesLeft = 10;
    EnemyWave mainWave;
    mainWave.wave = 1;
    mainWave.enemiesLeft = 6;
    int enemiesThisWave = 0;
    int waveTimer = 8*fpsCap;

    // Generating equation
    char operationSymbol = ' ';
    Equation equation = generateEquation();
        
    //Defining the variable for the text box
    InputBoxInfo inputBox;
    inputBox.input[4] = '\0';
    inputBox.textBox = {screenWidth / 2.0f - 20, 39, 100, 35};

    Button upgradeDamageButton = { 18.0f, 115.0f, 200.0f, 25.0f };
    Button upgradeRegenButton = { 18.0f, 145.0f, 200.0f, 25.0f };
    Button upgradeMultyKillButton = { 18.0f, 175.0f, 200.0f, 25.0f };

    int score = 0;
    int gold = 0;

    // Setting the fps cap to 60
    SetTargetFPS(fpsCap);

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {


        //Implementing zoom mechaninc
        if (camera.fovy >= 20.0f && camera.fovy <= 35.0f)
            camera.fovy -= GetMouseWheelMove() * 2;
        else if (camera.fovy >= 20.0f)
            camera.fovy -= 0.08f;
        else
            camera.fovy += 0.08f;
        
        // Generates new enemy when under enemy limit and off cooldown      
        if (enemiesThisWave != mainWave.enemiesLeft && mainWave.wave <= wavesLeft)
        {
            if (enemyList.size() < enemyLimit && enemyDebounce == 0)
            {
                enemyList.push_back(generateEnemy(mainWave));

                enemyDebounce = debounceTimer;
                enemiesThisWave++;
            }
            enemyDebounce--;
        }
        else if (waveTimer != 0)
        {
            waveTimer--;
        }
        else
        {
            waveTimer = (8 * fpsCap) - waveTimerDecrement;
            waveTimerDecrement += 0.05;
            enemiesThisWave = 0;
            mainWave.wave = mainWave.wave++;
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

                for (size_t i = 0; i < towerStats.multyKill; i++)
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

                std::cout << "Next time" << std::endl;

            }
            
            equation = generateEquation();

        }


        BeginMode3D(camera);

        
            
        DrawGrid(50, 1.0f);

            for (size_t i = 0; i < enemyList.size(); i++)
            {
                drawEnemy(enemyList[i], RED, BROWN);

                enemyList[i].linePos -= 1.8f * GetFrameTime();

                if (enemyList[i].linePos <= 1.8f)
                {
                    towerStats.towerHealth -= enemyList[i].damage;
                    enemyList.erase(enemyList.begin() + i);
                }
            }
 
            if (towerStats.towerHealth > 0) {
                drawTower(towerStats, BLUE, DARKBLUE);
            }

                   
        EndMode3D();

        //Drawing the UI
        DrawText(TextFormat("%i %c %i = ", equation.firstNumber, operationSymbol, equation.secondNumber), (screenWidth / 2.0f) - 100, 50, 20, BLACK);
        DrawText(TextFormat("Score: %i", score), 10, 50, 30, BLACK);
        DrawText(TextFormat("Gold: %i", gold), 10, 80, 25, BLACK);
        drawUpgradeMenu(upgradeDamageButton, upgradeRegenButton, upgradeMultyKillButton);
        drawInputBox(inputBox);


        upgradeRegen(towerStats, gold, upgradeRegenButton);
        upgradeDamage(towerStats, gold, upgradeDamageButton);
        upgradeMultyKill(towerStats, gold, upgradeMultyKillButton);

        std::cout << towerStats.multyKill << std::endl;

        DrawFPS(10, 10);

        EndDrawing();
    }

    CloseWindow();        // Close window and OpenGL context

    return 0;
}

