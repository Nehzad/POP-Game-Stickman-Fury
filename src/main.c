#include "raylib.h"
#include <math.h>
#include <stdbool.h>

#include "fighter.h"
#include "effects.h"
#include "rendering.h"
#include "assets.h"
#include "game.h"

int main(void)
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Stickman Fighter - Red vs White");
    InitAudioDevice();
    SetWindowState(FLAG_WINDOW_RESIZABLE);
    SetTargetFPS(60);

    RenderTexture2D target = LoadRenderTexture(SCREEN_WIDTH, SCREEN_HEIGHT);
    GameAssets assets = {0};

    Fighter player = {0};
    Fighter enemy = {0};

    bool gameOver = false;
    char winnerText[64] = "";

    int enemyAttackCooldown = 0;
    int frameCounter = 0;

    LoadGameAssets(&assets);
    PlayMusicStream(assets.bgMusic);
    ResetGame(&player, &enemy, &gameOver, winnerText);

    while (!WindowShouldClose())
    {
        frameCounter++;
        UpdateMusicStream(assets.bgMusic);

        if (IsKeyPressed(KEY_F11))
            ToggleFullscreen();

        if (!gameOver)
        {
            player.velX = 0;

            if (IsKeyDown(KEY_A))
            {
                player.velX = -MOVE_SPEED;
                player.facing = -1;
            }

            if (IsKeyDown(KEY_D))
            {
                player.velX = MOVE_SPEED;
                player.facing = 1;
            }

            if ((IsKeyPressed(KEY_W) || IsKeyPressed(KEY_SPACE)) && player.jumpsUsed < 2)
            {
                player.velY = JUMP_FORCE;
                player.jumpsUsed++;
                player.onGround = false;
            }

            if (IsKeyPressed(KEY_J))
            {
                StartAttack(&player, ATTACK_PUNCH);
                PlaySound(assets.punchSound);
            }

            if (IsKeyPressed(KEY_K))
            {
                StartAttack(&player, ATTACK_KICK);
                PlaySound(assets.kickSound);
            }

            enemy.velX = 0;

            if (enemy.x < player.x - 55)
            {
                enemy.velX = 2.2f;
                enemy.facing = 1;
            }
            else if (enemy.x > player.x + 55)
            {
                enemy.velX = -2.2f;
                enemy.facing = -1;
            }

            if (enemyAttackCooldown > 0)
                enemyAttackCooldown--;

            float distance = fabsf(enemy.x - player.x);

            if (enemy.attackType == ATTACK_NONE && enemyAttackCooldown == 0 && distance < 70.0f)
            {
                if (GetRandomValue(0, 1) == 0)
                {
                    StartAttack(&enemy, ATTACK_PUNCH);
                    PlaySound(assets.punchSound);
                }
                else
                {
                    StartAttack(&enemy, ATTACK_KICK);
                    PlaySound(assets.kickSound);
                }

                enemyAttackCooldown = 35;
            }

            UpdateAttack(&player);
            UpdateAttack(&enemy);

            ApplyPhysics(&player);
            ApplyPhysics(&enemy);

            player.velX *= 0.82f;
            enemy.velX *= 0.82f;

            KeepInsideScreen(&player);
            KeepInsideScreen(&enemy);

            ResolveHit(&player, &enemy);
            ResolveHit(&enemy, &player);

            UpdateHitEffects();

            Rectangle playerBody = GetBodyRect(player);
            Rectangle enemyBody = GetBodyRect(enemy);

            if (CheckCollisionRecs(playerBody, enemyBody))
            {
                if (player.x < enemy.x)
                {
                    player.x -= 2.0f;
                    enemy.x += 2.0f;
                }
                else
                {
                    player.x += 2.0f;
                    enemy.x -= 2.0f;
                }
            }

            if (player.health <= 0)
            {
                gameOver = true;
                TextCopy(winnerText, "WHITE STICKMAN WINS!");
            }
            else if (enemy.health <= 0)
            {
                gameOver = true;
                TextCopy(winnerText, "RED STICKMAN WINS!");
            }
        }
        else
        {
            if (IsKeyPressed(KEY_R))
            {
                ResetGame(&player, &enemy, &gameOver, winnerText);
                enemyAttackCooldown = 0;
            }
        }

        BeginTextureMode(target);
        ClearBackground(BLACK);

        DrawBackgroundScaled(assets.background);
        DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, Fade(BLACK, 0.14f));
        DrawGroundAndShadows(player, enemy);

        DrawRectangle(0, 0, SCREEN_WIDTH, 95, Fade(BLACK, 0.45f));
        DrawText("STICKMAN FIGHTER", 360, 20, 30, RAYWHITE);
        DrawText("A/D move | W or SPACE jump/double jump | J punch | K kick | R restart | F11 fullscreen",
                 120, 60, 20, LIGHTGRAY);

        DrawHealthBar(60, 100, 300, 24, player.health, RED);
        DrawText("RED", 60, 75, 20, RED);

        DrawHealthBar(640, 100, 300, 24, enemy.health, WHITE);
        DrawText("WHITE", 640, 75, 20, WHITE);

        DrawAnimatedFighter(player,
                            assets.playerIdle,
                            assets.playerRun,
                            assets.playerJump,
                            assets.playerDoubleJump,
                            assets.playerPunch,
                            assets.playerKick,
                            frameCounter);

        DrawAnimatedFighter(enemy,
                            assets.enemyIdle,
                            assets.enemyRun,
                            assets.enemyJump,
                            assets.enemyDoubleJump,
                            assets.enemyPunch,
                            assets.enemyKick,
                            frameCounter);

        DrawHitEffects();

        if (gameOver)
        {
            DrawRectangle(250, 180, 500, 160, Fade(BLACK, 0.75f));
            DrawRectangleLines(250, 180, 500, 160, RAYWHITE);
            DrawText(winnerText, 330, 220, 32, YELLOW);
            DrawText("Press R to restart", 390, 270, 24, RAYWHITE);
        }

        EndTextureMode();

        BeginDrawing();
        ClearBackground(BLACK);

        int winW = GetScreenWidth();
        int winH = GetScreenHeight();
        float scaleX = (float)winW / SCREEN_WIDTH;
        float scaleY = (float)winH / SCREEN_HEIGHT;
        float scale = fminf(scaleX, scaleY);

        float destW = SCREEN_WIDTH * scale;
        float destH = SCREEN_HEIGHT * scale;
        float offsetX = (winW - destW) / 2.0f;
        float offsetY = (winH - destH) / 2.0f;

        DrawTexturePro(
            target.texture,
            (Rectangle){0, 0, (float)target.texture.width, -(float)target.texture.height},
            (Rectangle){offsetX, offsetY, destW, destH},
            (Vector2){0, 0},
            0.0f,
            WHITE
        );

        EndDrawing();
    }

    StopMusicStream(assets.bgMusic);
    UnloadGameAssets(&assets);
    UnloadRenderTexture(target);

    CloseAudioDevice();
    CloseWindow();

    return 0;
}