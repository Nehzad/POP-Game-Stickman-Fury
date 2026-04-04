#ifndef FIGHTER_H
#define FIGHTER_H

#include "raylib.h"
#include <stdbool.h>

#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 600
#define GROUND_Y 500.0f
#define GRAVITY 0.60f
#define MOVE_SPEED 4.5f
#define JUMP_FORCE -11.5f

typedef enum
{
    ATTACK_NONE = 0,
    ATTACK_PUNCH,
    ATTACK_KICK
} AttackType;

typedef enum
{
    ANIM_IDLE,
    ANIM_RUN,
    ANIM_JUMP,
    ANIM_DOUBLE_JUMP,
    ANIM_PUNCH,
    ANIM_KICK
} AnimationType;

typedef struct
{
    float x, y;
    float width, height;
    float velX, velY;
    int facing;
    int health;
    bool onGround;
    int jumpsUsed;
    AttackType attackType;
    int attackTimer;
    int attackDuration;
    bool attackHitApplied;
    Color color;
} Fighter;

Rectangle GetBodyRect(Fighter f);
Rectangle GetAttackRect(Fighter f);
void StartAttack(Fighter *f, AttackType type);
void UpdateAttack(Fighter *f);
void ApplyPhysics(Fighter *f);
void KeepInsideScreen(Fighter *f);
void ResolveHit(Fighter *attacker, Fighter *target);
AnimationType GetAnimationType(Fighter f);
int GetFrameCount(AnimationType anim);

#endif
