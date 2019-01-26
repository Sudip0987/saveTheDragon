//
//  Pipes.cpp
//  SaveTheDragon
//
//  Created by Sudip Sharma on 17/1/19.
//  Copyright © 2019 Sudip Sharma. All rights reserved.
//

#include "Pipes.hpp"
void Pipes::createPipe(int w, int h){
    this->w=w;
    this->h=h;
}
void Pipes::draw(){
    int tempx,tempy;
    tempx = (int) pos.x;
    tempy = (int) pos.y;
    SDL_Rect pipeRect={tempx,tempy,50,500};
 
    SDL_SetRenderDrawColor(renderer, 04, 0, 128, 255);
    SDL_RenderFillRect(renderer, &pipeRect);
}
