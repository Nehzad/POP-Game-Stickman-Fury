#ifndef GAME_H
#define GAME_H

#include "fighter.h"
#include <stdbool.h>

void ResetGame(Fighter *player, Fighter *enemy, bool *gameOver, char *winnerText);

#endif