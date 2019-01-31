//
//  Hero.cpp
//  SaveTheDragon
//
//  Created by Sudip Sharma on 12/1/19.
//  Copyright © 2019 Sudip Sharma. All rights reserved.
//

#include "Hero.hpp"

using namespace std;
Hero::Hero()
{
    bumpIntoSolids = true;
    collisionBox.w = 64;
    collisionBox.h = 64;
    
    
}


Hero::~Hero()
{
}


void Hero::setAnimation(Animation* animation){
    this->animation = animation;
}

//overriding
void Hero::update(float dt){
    
    velocity.x=0.000001;
    
    //use basic entity movement to move around
    
    
    updateCollisions(dt);
    updateMovement(dt);
    
    
    //update animations too
    animation->update(dt);
}

int Hero::getHeight() {
    return pos.y;
}


void Hero::draw(){
    if (animation != NULL){
        if (faceRight){
            animation->draw(pos.x, pos.y,false);
        } else{
            animation->draw(pos.x, pos.y, true);
        
        }
        //SDL_SetRenderDrawColor(renderer, 120, 46, 22, 255);
        //SDL_RenderFillRect(renderer, &collisionBox);
    }
}
void Hero::limitHeroMovement(int height){
    if (pos.y<=0){
        setPosition(Vector(pos.x,0));
    }
    if(pos.x<=0){
        setPosition(Vector(0,pos.y));
        
    }else if(pos.x>=800){
        setPosition(Vector(800,pos.y));
        
    }
}
