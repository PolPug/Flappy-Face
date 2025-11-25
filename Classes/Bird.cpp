#include "..\Head/Bird.h"

Bird::Bird() {
    birdY = 0.0f;
    birdVelocity = 0.0f;
}

void Bird::Load() {
    Image birdI = LoadImage("Assets/Assets.png");
    ImageCrop(&birdI, { 0, 0, 32, 32 });
    birdT = LoadTextureFromImage(birdI);
    UnloadImage(birdI);
}

void Bird::Update() {
    birdVelocity += gravity;
    if (IsKeyPressed(KEY_UP)) {
        birdVelocity = -jump;
    }

    birdY += birdVelocity;

    if (birdVelocity > terminalVelocity) birdVelocity = terminalVelocity;
}

void Bird::Draw() {
    DrawTexture(birdT, screenWidth / 2 - birdT.width , (int)birdY, WHITE);
    //DrawRectangleLines(screenWidth / 2.0f - birdT.width , birdY, birdT.width,birdT.height, BLACK);
}
