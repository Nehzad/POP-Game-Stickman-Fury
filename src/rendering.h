#ifndef RENDERING_H
#define RENDERING_H

#include "fighter.h"
#include "raylib.h"

void DrawHealthBar(int x, int y, int width, int height, int health, Color fillColor);
void DrawStickmanFallback(Fighter f);
void DrawAnimatedFighter(Fighter f,
                         Texture2D idleTex,
                         Texture2D runTex,
                         Texture2D jumpTex,
                         Texture2D doubleJumpTex,
                         Texture2D punchTex,
                         Texture2D kickTex,
                         int frameCounter,
                         bool stabilizeFrameAnchor);
void DrawBackgroundScaled(Texture2D bg);
void DrawGroundAndShadows(Fighter player, Fighter enemy);

#endif
