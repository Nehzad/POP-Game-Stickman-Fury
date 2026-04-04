#ifndef ASSETS_H
#define ASSETS_H

#include "raylib.h"

typedef struct
{
    Texture2D background;

    Texture2D playerIdle;
    Texture2D playerRun;
    Texture2D playerJump;
    Texture2D playerDoubleJump;
    Texture2D playerPunch;
    Texture2D playerKick;

    Texture2D enemyIdle;
    Texture2D enemyRun;
    Texture2D enemyJump;
    Texture2D enemyDoubleJump;
    Texture2D enemyPunch;
    Texture2D enemyKick;

    Music bgMusic;
    Sound punchSound;
    Sound kickSound;
} GameAssets;

void LoadGameAssets(GameAssets *assets);
void UnloadGameAssets(GameAssets *assets);

#endif