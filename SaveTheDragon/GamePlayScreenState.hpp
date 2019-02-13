#pragma once
#include <list>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "GameState.hpp"
#include "GlobalGameState.hpp"
#include <iostream>
#include "Hero.hpp"
#include "Pipes.hpp"
#include "KeyboardHandler.hpp"
#include "ConstVariables.hpp"
#include "GameOverScreen.hpp"
#include "SoundManager.hpp"



using namespace std;

class GamePlayScreenState :
	public GameState
{
public:
	//we're gonna add textures and stuff here as attributes
    
   // ConstVariable* constants;
	SDL_Texture* heroTexture;
	Animation* heroAnimation;
	Hero* hero;

	list<Entity*> entities;//creating seperate entity for the basic objects that can collide with the players
    list<Entity*> pointsEntity;//creating seperate entites for the objects that cannot collide with the players like game points
    

   
    
	KeyboardHandler keyboardHandler;

	//TIME STUFF
	Uint32 lastUpdate; //last sdl_ticks
	float dt = 0;//time since last update

	GamePlayScreenState();
	~GamePlayScreenState();
    SDL_Surface* textSurface;
    SDL_Texture* textTexture;
    TTF_Font* font;
    SDL_Color textColor;
    SDL_Texture* pipeTexture;
    SDL_Surface* pipeImage;
    SDL_Rect textDestination;
	virtual void update();
	virtual void render();
	virtual bool onEnter();
	virtual bool onExit();
	virtual std::string getStateID() const { return "gamePlayState"; }
    void setPipeVerticalPosition(Pipes* topPipe, Pipes* bottomPipe,int horizontalPos);
};

