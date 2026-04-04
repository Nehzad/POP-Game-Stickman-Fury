#include "rendering.h"
#include <math.h>

void DrawHealthBar(int x, int y, int width, int height, int health, Color fillColor)
{
    DrawRectangle(x, y, width, height, Fade(BLACK, 0.55f));
    DrawRectangle(x, y, (width * health) / 100, height, fillColor);
    DrawRectangleLines(x, y, width, height, WHITE);
}

void DrawStickmanFallback(Fighter f)
{
    float headRadius = 18.0f;
    float headX = f.x;
    float headY = f.y - f.height + 25.0f;

    float neckY = headY + headRadius;
    float hipY = f.y - 35.0f;

    float shoulderY = neckY + 8.0f;
    float leftHandX = f.x - 28.0f;
    float rightHandX = f.x + 28.0f;
    float handY = shoulderY + 28.0f;

    float leftFootX = f.x - 18.0f;
    float rightFootX = f.x + 18.0f;
    float footY = f.y;

    Color c = f.color;

    DrawCircleLines((int)headX, (int)headY, headRadius, c);
    DrawLineEx((Vector2){f.x, neckY}, (Vector2){f.x, hipY}, 4.0f, c);

    Vector2 leftArmEnd = { leftHandX, handY };
    Vector2 rightArmEnd = { rightHandX, handY };

    if (f.attackType == ATTACK_PUNCH)
    {
        if (f.facing == 1) rightArmEnd = (Vector2){ f.x + 45.0f, shoulderY + 6.0f };
        else leftArmEnd = (Vector2){ f.x - 45.0f, shoulderY + 6.0f };
    }
    else if (f.attackType == ATTACK_KICK)
    {
        if (f.facing == 1) rightFootX = f.x + 42.0f;
        else leftFootX = f.x - 42.0f;
    }

    DrawLineEx((Vector2){f.x, shoulderY}, leftArmEnd, 4.0f, c);
    DrawLineEx((Vector2){f.x, shoulderY}, rightArmEnd, 4.0f, c);

    DrawLineEx((Vector2){f.x, hipY}, (Vector2){leftFootX, footY}, 4.0f, c);
    DrawLineEx((Vector2){f.x, hipY}, (Vector2){rightFootX, footY}, 4.0f, c);
}

void DrawAnimatedFighter(Fighter f,
                         Texture2D idleTex,
                         Texture2D runTex,
                         Texture2D jumpTex,
                         Texture2D doubleJumpTex,
                         Texture2D punchTex,
                         Texture2D kickTex,
                         int frameCounter)
{
    AnimationType anim = GetAnimationType(f);
    Texture2D tex = idleTex;

    switch (anim)
    {
        case ANIM_IDLE: tex = idleTex; break;
        case ANIM_RUN: tex = runTex; break;
        case ANIM_JUMP: tex = jumpTex; break;
        case ANIM_DOUBLE_JUMP: tex = doubleJumpTex; break;
        case ANIM_PUNCH: tex = punchTex; break;
        case ANIM_KICK: tex = kickTex; break;
    }

    if (tex.id == 0)
    {
        DrawStickmanFallback(f);
        return;
    }

    int frameCount = GetFrameCount(anim);
    int currentFrame = (frameCounter / 8) % frameCount;
    int frameWidth = tex.width / frameCount;
    int frameHeight = tex.height;

    Rectangle src = {
        (float)(currentFrame * frameWidth),
        0.0f,
        (float)frameWidth,
        (float)frameHeight
    };

    if (f.facing == -1)
    {
        src.x += frameWidth;
        src.width = -(float)frameWidth;
    }

    float scale = 3.2f;

    Rectangle dst = {
        f.x,
        f.y + 2.0f,
        frameWidth * scale,
        frameHeight * scale
    };

    Vector2 origin = {
        (frameWidth * scale) / 2.0f,
        frameHeight * scale
    };

    DrawTexturePro(tex, src, dst, origin, 0.0f, WHITE);
}

void DrawBackgroundScaled(Texture2D bg)
{
    float scaleX = (float)SCREEN_WIDTH / (float)bg.width;
    float scaleY = (float)SCREEN_HEIGHT / (float)bg.height;
    float scale = (scaleX > scaleY) ? scaleX : scaleY;

    float drawW = bg.width * scale;
    float drawH = bg.height * scale;
    float x = (SCREEN_WIDTH - drawW) * 0.5f;
    float y = (SCREEN_HEIGHT - drawH) * 0.5f;

    DrawTexturePro(
        bg,
        (Rectangle){0, 0, (float)bg.width, (float)bg.height},
        (Rectangle){x, y, drawW, drawH},
        (Vector2){0, 0},
        0.0f,
        WHITE
    );
}

void DrawGroundAndShadows(Fighter player, Fighter enemy)
{
    DrawEllipse((int)player.x, (int)(GROUND_Y + 4), 28, 8, Fade(BLACK, 0.35f));
    DrawEllipse((int)enemy.x, (int)(GROUND_Y + 4), 28, 8, Fade(BLACK, 0.35f));

    DrawRectangle(0, (int)GROUND_Y + 8, SCREEN_WIDTH, 92, (Color){34, 28, 22, 230});
    DrawRectangle(0, (int)GROUND_Y + 8, SCREEN_WIDTH, 14, (Color){68, 90, 42, 255});
    DrawRectangle(0, (int)GROUND_Y + 22, SCREEN_WIDTH, 10, (Color){90, 70, 45, 255});
    DrawRectangle(0, (int)GROUND_Y + 32, SCREEN_WIDTH, 68, (Color){52, 40, 30, 255});

    DrawLineEx((Vector2){0, GROUND_Y + 8}, (Vector2){SCREEN_WIDTH, GROUND_Y + 8}, 3.0f, (Color){110, 140, 90, 255});
    DrawLineEx((Vector2){0, GROUND_Y + 20}, (Vector2){SCREEN_WIDTH, GROUND_Y + 20}, 2.0f, Fade(BLACK, 0.25f));

    for (int i = 0; i < SCREEN_WIDTH; i += 18)
    {
        int grassH = 4 + (i % 3);
        DrawLine(i, (int)GROUND_Y + 8, i + 2, (int)GROUND_Y + 8 - grassH, (Color){80, 120, 55, 255});
        DrawLine(i + 5, (int)GROUND_Y + 8, i + 6, (int)GROUND_Y + 8 - (grassH + 2), (Color){95, 135, 65, 255});
    }

    for (int i = 10; i < SCREEN_WIDTH; i += 40)
    {
        DrawCircle(i, (int)GROUND_Y + 44 + (i % 9), 2, Fade(BLACK, 0.18f));
        DrawCircle(i + 12, (int)GROUND_Y + 64 + (i % 7), 2, Fade(BLACK, 0.16f));
    }
}