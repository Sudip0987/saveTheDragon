//
//  DrawText.hpp
//  SaveTheDragon
//
//  Created by Sudip Sharma on 2/2/19.
//  Copyright © 2019 Sudip Sharma. All rights reserved.
//

#pragma once
#include "Entity.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include<string>
#include "ConstVariables.hpp"
class DrawText :
public Entity
{
public:
    int w,h;
public:
    SDL_Texture* textTexture;
    SDL_Rect textDestination;
    
    bool pipeTop=false;
    DrawText(int x,int y);
    ~DrawText();
    virtual void update(float dt);
    virtual void draw();
};
