#ifndef PIPE_H
#define PIPE_H

#include "raylib.h"
#include "Bird.h"
#include <vector>

class Pipe; // forward declaration

extern std::vector<Pipe> pipes;
extern std::vector<Pipe> pipes2;

class Pipe {
public:
    Pipe(float posX, float posY, int rot);

    void Load();                    // Load texture
    void Update(Bird& bird);        // Update physics
    void Draw(bool flipped);

    float positionX;
    float positionY;
    bool flipped;
    int rotation;
    float pipeSpeed;
    Texture2D pipeT;
   
};

#endif
