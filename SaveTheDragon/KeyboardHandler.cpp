#include "KeyboardHandler.hpp"


KeyboardHandler::KeyboardHandler()
{
}


KeyboardHandler::~KeyboardHandler()
{
}

void KeyboardHandler::update(SDL_Event* event){
    const Uint8* keystates = SDL_GetKeyboardState(NULL);
    
    hero->velocity.y=HERO_VELOCITY;
    hero->limitHeroMovement(WIN_HEIGHT);
    hero->velocity.x=0;
    if (keystates[SDL_SCANCODE_UP]){
        //exit loop
        
        hero->velocity.y=-HERO_VELOCITY*1.8;
        
        
    } if (keystates[SDL_SCANCODE_LEFT]){
        //exit loop
        
        hero->velocity.x=-100;
        
    } else if(keystates[SDL_SCANCODE_RIGHT]){
        hero->velocity.x=100;
        
    }
}
