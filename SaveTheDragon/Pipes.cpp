#include "Pipes.hpp"

Pipes::Pipes(int w,int h)
{
    bumpIntoSolids = false;
    solid = true;
    collisionBox.w = w;
    collisionBox.h = h;
   
}


Pipes::~Pipes()
{
    
}



void Pipes::update(float dt){
    updateCollisionBox();
  
    updateMovement(dt);
}
void Pipes::draw(){
    
    SDL_SetRenderDrawColor(renderer, 150, 200, 255, 255);
    //SDL_RenderFillRect(renderer, &collisionBox);
    if(pipeTop==true){
    SDL_RenderCopy(renderer, texture, NULL, &collisionBox);
    }else {
        SDL_RenderCopyEx(renderer, texture, NULL, &collisionBox,0,0,SDL_FLIP_VERTICAL);

    }


}
