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
    
    hero->velocity.y=ConstVariables::HERO_VELOCITY/1.5;
    hero->limitHeroMovement(ConstVariables::WIN_HEIGHT);
    hero->velocity.x=0;
    
    
    //controls omly work when there is no collison
    
            if (keystates[SDL_SCANCODE_SPACE]){
                //exit loop
                hero->velocity.y=-ConstVariables::HERO_VELOCITY/1.5;

                SoundManager::soundManager.playSound("fly");


                
                
            }else {
                hero->animation->frameDuration=0.085;//setting dragon's flapping speed to normal
            }
    
    
    
    
}
