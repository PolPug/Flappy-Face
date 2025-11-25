#include "..\Head/Pipe.h"
#include <iostream>

Pipe::Pipe(float posX, float posY, int rot) {
    positionX = posX;
    positionY = posY;
    rotation = rot;
    pipeSpeed = 2.0f;
    flipped = false;
}

void Pipe::Load() {
    Image pipeI = LoadImage("Assets/Assets.png");
    Rectangle cropRect = {36, 0, 8, 45};
    ImageCrop(&pipeI, cropRect);
    ImageResizeNN(&pipeI, pipeI.width * 5, pipeI.height * 10);
    pipeT = LoadTextureFromImage(pipeI);
    UnloadImage(pipeI);
}

void Pipe::Draw(bool flipped) {
    Rectangle src = { 0, 0, (float)pipeT.width, (float)pipeT.height };
    Rectangle dest = { positionX, positionY, (float)pipeT.width, (float)pipeT.height };
    Vector2 origin = {0,0};

    if (flipped) {
    // Draw flipped sprite
    src.height = -src.height;
}

    DrawTexturePro(pipeT, src, dest, origin, 0.0f, WHITE);
  //  DrawRectangleLines(positionX, positionY, pipeT.width,pipeT.height, BLACK);
}


extern bool ExitC;
extern int screenWidth;
extern int screenHeight;
extern float score;
bool AABBCol(Vector2 A1, Vector2 A2, Vector2 B1, Vector2 B2);
bool AABBadap(Vector2 A, float AX, float AY, Vector2 B, float BX, float BY);

void Pipe::Update(Bird& bird) {
    positionX -= pipeSpeed;

    if (AABBadap({positionX, positionY},
             (float)pipeT.width,
             (float)pipeT.height,
             {(float)screenWidth / 2.0f - bird.birdT.width , bird.birdY},
             (float)bird.birdT.width,
             (float)bird.birdT.height)) {
    ExitC = true;
}

    if (positionX < (float)screenWidth /2 && flipped == false){
        score += 0.5f;
        flipped = true;
    }
    
}
