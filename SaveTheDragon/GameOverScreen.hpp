#pragma once
#include "GameState.hpp"
#include <SDL2/SDL.h>
#include "GlobalGameState.hpp"
#include <iostream>
#include "GamePlayScreenState.hpp"
#include "DrawText.hpp"
#include "Hero.hpp"
#include "MenuScreenState.hpp"
class GameOverScreen :
public GameState
{
public:
    GameOverScreen();
    ~GameOverScreen();
    SDL_Surface* textSurface;
    SDL_Texture* textTexture;
    TTF_Font* font;
    SDL_Rect textDestination;
    list<Entity*> entities;
   
    
    virtual void update();
    virtual void render();
    virtual bool onEnter();
    virtual bool onExit();
    virtual std::string getStateID() const { return "GameOverState"; }
};

