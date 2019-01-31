#pragma once
#include "Entity.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Pipes :
public Entity
{
public:
    int w,h;
public:
    SDL_Rect sourceRectangle;
    SDL_Rect destinationRectangle;

    Pipes(int w,int h);
    ~Pipes();
    void createPipe(int w, int h);
    virtual void update(float dt);
    virtual void draw();
};
