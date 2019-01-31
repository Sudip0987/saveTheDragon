#pragma once
#include "Entity.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Ground :
public Entity
{
public:
    int w,h;
    const int WIN_HEIGHT=700;
    const int WIN_WIDTH=1000;
    const int HERO_VELOCITY=300;
    const int PIPE_VElOCITY = -150;
    const int MIN_VERTICAL_SPACING=700;
    const int MAX_VERTICAL_SPACING=1000;
    const int hW=128;
    const int PIPE_HORIZONTAL_SPACING=250;

    //texture pointer

    SDL_Rect sourceRectangle;
    SDL_Rect destinationRectangle;
public:
    Ground();
    ~Ground();
    void createGround(int w, int h);
    virtual void update(float dt);
    virtual void draw();
};
