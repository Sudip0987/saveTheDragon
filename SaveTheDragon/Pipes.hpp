#pragma once
#include "Entity.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include<string>
class Pipes :
public Entity
{
public:
    int w,h;
public:
    SDL_Texture* texture;
    bool pipeTop=false;
    Pipes(int w,int h);
    ~Pipes();
    void createPipe(int w, int h);
    virtual void update(float dt);
    virtual void draw();
};
