#include "DrawText.hpp"

DrawText::DrawText(int x, int y)
{
   
    textDestination.x = x;
    textDestination.y = y;
    
}


DrawText::~DrawText()
{
    
}



void DrawText::update(float dt){
    updateMovement(dt);

 
}
void DrawText::draw(){
    
//    SDL_SetRenderDrawColor(renderer, 150, 200, 255, 255);
    //SDL_RenderFillRect(renderer, &collisionBox);
    SDL_QueryTexture(textTexture, NULL, NULL, &textDestination.w, &textDestination.h);
    SDL_RenderCopy(GlobalGameState::renderer, textTexture, NULL, &textDestination);
    
    
    
}
