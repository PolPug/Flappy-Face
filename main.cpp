#include "C:/raylib/raylib/src/raylib.h"
#include "C:/raylib/raylib/src/raymath.h"
#include "Head/Bird.h"
#include "Head/Pipe.h"
#include <vector>
#include <cstdlib>
#include <iostream>
#include <string>

float timerLen = 3.5f;
int screenHeight = 600;
int screenWidth = 400;
bool ExitC = false;
int randomNumber = 0;
float score = 0.0f;
std::string scoreS = "dsaf";
//-----------------------------------------------------
// Bird Class
//-----------------------------------------------------

bool AABBCol(Vector2 A1, Vector2 A2, Vector2 B1, Vector2 B2) {
    // Check for separation along x-axis
    if (A2.x < B1.x || A1.x > B2.x) return false;
    // CHeck for separation along y-axis
    if (A2.y < B1.y || A1.y > B2.y) return false;
    return true;
}
bool AABBadap(Vector2 A, float AX, float AY, Vector2 B, float BX, float BY){
    return AABBCol(A,{A.x+AX,A.y+AY},B,{B.x+BX,B.y+BY});
}


//-----------------------------------------------------
// Main
//-----------------------------------------------------

int main(void) {
    InitWindow(screenWidth, screenHeight, "FB");
    Image icon = LoadImage("Assets/Assets.png");
    ImageCrop(&icon, { 0, 0, 32, 32 });
    SetWindowIcon(icon);
    UnloadImage(icon);

    // Load Bird
    Bird bird;
    bird.Load();
    
    //Load Pipes
    float timer = 0.0f;

    std::vector<Pipe> pipes;
    std::vector<Pipe> pipes2;
    // Load Bird Smol
    Image birdSmol = LoadImage("Assets/Assets.png");
    ImageCrop(&birdSmol, { 0, 0, 16, 16 });
    Texture2D birdSmolT = LoadTextureFromImage(birdSmol);
    UnloadImage(birdSmol);

    // Load numbers 
    std::vector<Texture2D> digitTextures;
    Image numbers = LoadImage("Assets/Assets.png");
    Image digit = ImageFromImage(numbers,Rectangle{12,39,4,7});
    ImageResizeNN(&digit,digit.width *5,digit.height*5);
    digitTextures.push_back(LoadTextureFromImage(digit));
        UnloadImage(digit);
    for (float i=0.0f;i<6.0f;i++){
        Image digit = ImageFromImage(numbers,Rectangle{i*4.0f,32,4,7});
        ImageResizeNN(&digit,digit.width *5,digit.height*5);
        digitTextures.push_back(LoadTextureFromImage(digit));
        UnloadImage(digit);
    }
    for (float i=0.0f;i<3.0f;i++){
        Image digit = ImageFromImage(numbers,Rectangle{i*4.0f,39,4,7});
        ImageResizeNN(&digit,digit.width *5,digit.height*5);
        digitTextures.push_back(LoadTextureFromImage(digit));
        UnloadImage(digit);
    }
    
    /*
    ImageCrop(&numbers, Rectangle{11, 32, 4, 7}); // crop in-place
    ImageResizeNN(&numbers,numbers.width *5,numbers.height*5);
    Texture2D number1T = LoadTextureFromImage(numbers);
    */
    UnloadImage(numbers); 



    SetTargetFPS(60);

    // Main game loop
    while (!WindowShouldClose()) {
        if (!ExitC){
            // Pipes
            timer = timer - GetFrameTime();
            if (timer <= 0){
                randomNumber = rand() % 301;
                pipes.emplace_back(screenWidth+10.0f,300.0f+randomNumber,0);
                pipes2.emplace_back(screenWidth + 10.0f,300.0f - 500.0f + randomNumber - 100.0f,0);
                pipes.back().Load();
                pipes2.back().Load();
                timer = timerLen;
            }
            /*
            for (int i=0; i<pipes.size();i++){
                pipes[i].Update(bird);
            }*/

            // Update bird
           
            for (int i=0; i<pipes.size();i++){
                pipes[i].Update(bird);
            }
            for (int i=0; i<pipes2.size();i++){
                pipes2[i].Update(bird);
            }
            bird.Update();
            // Exit Logic
            if (bird.birdY > screenHeight || bird.birdY < 0) {
                ExitC = true; 
            }
            /*/
            if (ExitC == true){
                break;
            }*/
            // Remove off-screen bottom pipes
            while (!pipes.empty() && pipes[0].positionX + pipes[0].pipeT.width < 0) {
                pipes.erase(pipes.begin());
            }

            // Remove off-screen top pipes
            while (!pipes2.empty() && pipes2[0].positionX + pipes2[0].pipeT.width < 0) {
                pipes2.erase(pipes2.begin());
            }   

        }

        scoreS = std::__cxx11::to_string(score);
        /*
        if (IsKeyPressed(KEY_DOWN)){
            score += 1.0f;
        }*/
        // Draw
        BeginDrawing();
        ClearBackground(PINK);
        for (int i=0; i<pipes.size();i++){
            pipes[i].Draw(false);
            pipes2[i].Draw(true);
        }
        bird.Draw();
        
        int posX = 0;
        int integerPart = static_cast<int>(score);
        std::string digits = std::to_string(integerPart);
        for (char c : digits) {
            int digit = c - '0';
            DrawTexture(digitTextures[digit], posX, 0, WHITE);  
            posX += 25;
        EndDrawing();
        }

        

        

        if(ExitC && IsKeyPressed(KEY_SPACE)){
            bird.birdY = 0;
            bird.birdVelocity = 0;
            pipes.clear();
            pipes2.clear();
            score = 0.0f;
            ExitC = false;
            timer = 0;
        }
        if(IsKeyPressed(KEY_ESCAPE)){
            break;
        }
    }
    
    // De-Initialization
    
      //  int x = 0;
       // std::cin >> x;
    for (int i =0;i<digitTextures.size();i++){
        UnloadTexture(digitTextures[i]);
    }
    UnloadTexture(birdSmolT);
    CloseWindow();
    return 0;
}