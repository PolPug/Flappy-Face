#ifndef BIRD_H
#define BIRD_H

#include "raylib.h"


class Bird {
public:
    Bird();

    void Load();    // Load texture
    void Update();  // Update physics
    void Draw();    // Draw to screen

    float birdY;
    float birdVelocity;

private:
    const float gravity = 0.15f;
    const float jump = 4.734234f;
    const float terminalVelocity = 12.0f;
    const int screenHeight = 600;
    const int screenWidth = 400;
public:
    Texture2D birdT;
};

#endif
