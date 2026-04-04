#include "game.h"
#include "raylib.h"

void ResetGame(Fighter *player, Fighter *enemy, bool *gameOver, char *winnerText)
{
    *player = (Fighter){
        .x = 250,
        .y = GROUND_Y,
        .width = 50,
        .height = 120,
        .velX = 0,
        .velY = 0,
        .facing = 1,
        .health = 100,
        .onGround = true,
        .jumpsUsed = 0,
        .attackType = ATTACK_NONE,
        .attackTimer = 0,
        .attackDuration = 0,
        .attackHitApplied = false,
        .color = RED
    };

    *enemy = (Fighter){
        .x = 750,
        .y = GROUND_Y,
        .width = 50,
        .height = 120,
        .velX = 0,
        .velY = 0,
        .facing = -1,
        .health = 100,
        .onGround = true,
        .jumpsUsed = 0,
        .attackType = ATTACK_NONE,
        .attackTimer = 0,
        .attackDuration = 0,
        .attackHitApplied = false,
        .color = WHITE
    };

    *gameOver = false;
    winnerText[0] = '\0';
}