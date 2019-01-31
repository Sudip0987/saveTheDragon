//
//  Ground.cpp
//  SaveTheDragon
//
//  Created by Sudip Sharma on 28/1/19.
//  Copyright © 2019 Sudip Sharma. All rights reserved.
//

#include "Ground.hpp"
Ground::Ground(){
    
}
Ground::~Ground(){
    
}
void Ground::createGround(int w, int h){
    //to load up an image, first load it up as a surface
    SDL_Surface* knightSurface = IMG_Load("floor.png");
    //then convert to texture
    SDL_Texture* knightTexture = SDL_CreateTextureFromSurface(renderer, knightSurface);
    //dont need surface anymore, free memory up
    SDL_FreeSurface(knightSurface);
    
    //lets use pass by reference to work the width and height of our texture in pixels
    SDL_QueryTexture(knightTexture, NULL, NULL, &sourceRectangle.w,&sourceRectangle.h);
    cout << "texture size is : " << sourceRectangle.w << "x" << sourceRectangle.h << endl;
    
    sourceRectangle.x = 0;
    sourceRectangle.y = 0;
    //sourceRectangle.w = 100;
    //sourceRectangle.h = 100;
    destinationRectangle.x = 0;
    destinationRectangle.y = WIN_HEIGHT-10;
    destinationRectangle.w = WIN_WIDTH; //copy the width of our texture
    destinationRectangle.h = 10;
    
}
void Ground::update(float dt){
    
}
void Ground::draw(){
    
}
