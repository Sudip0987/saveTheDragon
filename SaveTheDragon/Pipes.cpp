#include "Pipes.hpp"

Pipes::Pipes()
{
    bumpIntoSolids = false;
    solid = true;
    collisionBox.w = 50;
    collisionBox.h = 500;
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
