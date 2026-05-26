#include "effects.h"
#include "raylib.h"

#define MAX_HIT_EFFECTS 16

typedef struct
{
    float x;
    float y;
    int damage;
    int timer;
} HitEffect;

static HitEffect hitEffects[MAX_HIT_EFFECTS] = {0};

void AddHitEffect(float x, float y, int damage)
{
    int i;
    int oldest = 0;

    /* Reuse an expired slot, or overwrite the effect that will disappear soonest. */
    for (i = 0; i < MAX_HIT_EFFECTS; i++)
    {
        if (hitEffects[i].timer <= 0)
        {
            oldest = i;
            break;
        }

        if (hitEffects[i].timer < hitEffects[oldest].timer)
        {
            oldest = i;
        }
    }

    hitEffects[oldest].x = x;
    hitEffects[oldest].y = y;
    hitEffects[oldest].damage = damage;
    hitEffects[oldest].timer = 45;
}

void UpdateHitEffects(void)
{
    int i;
    for (i = 0; i < MAX_HIT_EFFECTS; i++)
    {
        if (hitEffects[i].timer > 0)
        {
            hitEffects[i].timer--;
            hitEffects[i].y -= 0.5f;
        }
    }
}

void DrawHitEffects(void)
{
    int i;
    for (i = 0; i < MAX_HIT_EFFECTS; i++)
    {
        if (hitEffects[i].timer > 0)
        {
            float progress = (float)hitEffects[i].timer / 45.0f;
            unsigned char alpha = (unsigned char)(255 * progress);

            DrawText(
                TextFormat("%d", hitEffects[i].damage),
                (int)hitEffects[i].x - 12,
                (int)hitEffects[i].y - 22,
                20,
                (Color){255, 255, 0, alpha}
            );
        }
    }
}
