#include "KeyboardHandler.hpp"
#include "SoundManager.hpp"


KeyboardHandler::KeyboardHandler()
{
}


KeyboardHandler::~KeyboardHandler()
{
}

void KeyboardHandler::update(SDL_Event* event){
    

    const Uint8* keystates = SDL_GetKeyboardState(NULL);
    
    hero->velocity.y=HERO_VELOCITY/1.5;
    hero->limitHeroMovement(WIN_HEIGHT);
    hero->velocity.x=0;
    
    //controls omly work when there is no collison
    if(hero->collisionOccured==false){
            if (keystates[SDL_SCANCODE_SPACE]){
                //exit loop
                hero->velocity.y=-HERO_VELOCITY/1.5;

                
                
                
            }else {
                hero->animation->frameDuration=0.085;//setting dragon's flapping speed to normal
            }
            if (keystates[SDL_SCANCODE_LEFT]){
                //exit loop
                
                hero->velocity.x=-100;
                
            } else if(keystates[SDL_SCANCODE_RIGHT]){
                hero->velocity.x=100;
                
            }
    }else {

    }
}
