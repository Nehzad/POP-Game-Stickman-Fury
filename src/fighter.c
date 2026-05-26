#include "fighter.h"
#include "effects.h"
#include <math.h>

Rectangle GetBodyRect(Fighter f)
{
    return (Rectangle){ f.x - f.width/2.0f, f.y - f.height, f.width, f.height };
}

Rectangle GetAttackRect(Fighter f)
{
    Rectangle body = GetBodyRect(f);

    /* Attack boxes are deliberately smaller than sprites so hits feel fair. */
    if (f.attackType == ATTACK_PUNCH)
    {
        float w = 35.0f, h = 18.0f;
        if (f.facing == 1) return (Rectangle){ body.x + body.width, body.y + 35.0f, w, h };
        else return (Rectangle){ body.x - w, body.y + 35.0f, w, h };
    }
    else if (f.attackType == ATTACK_KICK)
    {
        float w = 45.0f, h = 20.0f;
        if (f.facing == 1) return (Rectangle){ body.x + body.width, body.y + 80.0f, w, h };
        else return (Rectangle){ body.x - w, body.y + 80.0f, w, h };
    }

    return (Rectangle){0, 0, 0, 0};
}

void StartAttack(Fighter *f, AttackType type)
{
    if (f->attackType != ATTACK_NONE) return;

    f->attackType = type;
    f->attackHitApplied = false;

    /* Longer attack duration makes kicks stronger but easier to punish. */
    if (type == ATTACK_PUNCH) f->attackDuration = 16;
    if (type == ATTACK_KICK)  f->attackDuration = 22;

    f->attackTimer = f->attackDuration;
}

void UpdateAttack(Fighter *f)
{
    if (f->attackType == ATTACK_NONE) return;

    f->attackTimer--;

    if (f->attackTimer <= 0)
    {
        f->attackType = ATTACK_NONE;
        f->attackDuration = 0;
        f->attackHitApplied = false;
    }
}

void ApplyPhysics(Fighter *f)
{
    f->x += f->velX;
    f->y += f->velY;
    f->velY += GRAVITY;

    if (f->y >= GROUND_Y)
    {
        f->y = GROUND_Y;
        f->velY = 0;
        f->onGround = true;
        f->jumpsUsed = 0;
    }
    else
    {
        f->onGround = false;
    }
}

void KeepInsideScreen(Fighter *f)
{
    float halfW = f->width / 2.0f;
    if (f->x < halfW) f->x = halfW;
    if (f->x > SCREEN_WIDTH - halfW) f->x = SCREEN_WIDTH - halfW;
}

void ResolveHit(Fighter *attacker, Fighter *target)
{
    if (attacker->attackType == ATTACK_NONE || attacker->attackHitApplied) return;

    Rectangle attackRect = GetAttackRect(*attacker);
    Rectangle targetRect = GetBodyRect(*target);

    if (CheckCollisionRecs(attackRect, targetRect))
    {
        int damage = (attacker->attackType == ATTACK_PUNCH) ? 8 : 12;
        float knockback = (attacker->attackType == ATTACK_PUNCH) ? 10.0f : 14.0f;

        target->health -= damage;
        if (target->health < 0) target->health = 0;

        target->velX = knockback * attacker->facing;
        if (target->onGround) target->velY = -3.5f;

        Rectangle tr = GetBodyRect(*target);
        AddHitEffect(tr.x + tr.width * 0.5f, tr.y + tr.height * 0.35f, damage);

        /* Each attack can only connect once, even if the hitbox overlaps for many frames. */
        attacker->attackHitApplied = true;
    }
}

int GetFrameCount(AnimationType anim)
{
    switch (anim)
    {
        case ANIM_IDLE: return 4;
        case ANIM_RUN: return 6;
        case ANIM_JUMP: return 4;
        case ANIM_DOUBLE_JUMP: return 6;
        case ANIM_PUNCH: return 8;
        case ANIM_KICK: return 6;
        default: return 1;
    }
}

AnimationType GetAnimationType(Fighter f)
{
    if (f.attackType == ATTACK_PUNCH) return ANIM_PUNCH;
    if (f.attackType == ATTACK_KICK) return ANIM_KICK;

    if (!f.onGround)
    {
        if (f.jumpsUsed >= 2) return ANIM_DOUBLE_JUMP;
        return ANIM_JUMP;
    }

    if (fabsf(f.velX) > 1.0f) return ANIM_RUN;
    return ANIM_IDLE;
}
