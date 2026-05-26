#include "assets.h"

void LoadGameAssets(GameAssets *assets)
{
    assets->background = LoadTexture("resources/Background.png");

    assets->playerIdle = LoadTexture("resources/Punk_idle.png");
    assets->playerRun = LoadTexture("resources/Punk_run.png");
    assets->playerJump = LoadTexture("resources/Punk_jump.png");
    assets->playerDoubleJump = LoadTexture("resources/Punk_doublejump.png");
    assets->playerPunch = LoadTexture("resources/Punk_attack3.png");
    /* The punch sheet reads best as a kick pose for this character set. */
    assets->playerKick = LoadTexture("resources/Punk_punch.png");

    assets->enemyIdle = LoadTexture("resources/Cyborg_idle.png");
    assets->enemyRun = LoadTexture("resources/Cyborg_run.png");
    assets->enemyJump = LoadTexture("resources/Cyborg_jump.png");
    assets->enemyDoubleJump = LoadTexture("resources/Cyborg_doublejump.png");
    assets->enemyPunch = LoadTexture("resources/Cyborg_attack3.png");
    /* Keep enemy and player animation mapping symmetrical. */
    assets->enemyKick = LoadTexture("resources/Cyborg_punch.png");

    assets->bgMusic = LoadMusicStream("resources/bg_music.mp3");
    assets->punchSound = LoadSound("resources/punch.wav");
    assets->kickSound = LoadSound("resources/kick.wav");

    SetMusicVolume(assets->bgMusic, 0.35f);
    SetSoundVolume(assets->punchSound, 0.85f);
    SetSoundVolume(assets->kickSound, 0.90f);
}

void UnloadGameAssets(GameAssets *assets)
{
    UnloadTexture(assets->background);

    UnloadTexture(assets->playerIdle);
    UnloadTexture(assets->playerRun);
    UnloadTexture(assets->playerJump);
    UnloadTexture(assets->playerDoubleJump);
    UnloadTexture(assets->playerPunch);
    UnloadTexture(assets->playerKick);

    UnloadTexture(assets->enemyIdle);
    UnloadTexture(assets->enemyRun);
    UnloadTexture(assets->enemyJump);
    UnloadTexture(assets->enemyDoubleJump);
    UnloadTexture(assets->enemyPunch);
    UnloadTexture(assets->enemyKick);

    UnloadMusicStream(assets->bgMusic);
    UnloadSound(assets->punchSound);
    UnloadSound(assets->kickSound);
}
