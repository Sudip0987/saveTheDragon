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
    
  
   
   

    
    SDL_SetRenderDrawColor(renderer, 12, 46, 222, 255);
    SDL_RenderFillRect(renderer, &collisionBox);


}
