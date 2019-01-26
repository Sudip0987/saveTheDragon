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
}


Hero::~Hero()
{
}

void Hero::setAnimation(Animation* animation){
    this->animation = animation;
}

//overriding
void Hero::update(float dt){
    
   
   
    //use basic entity movement to move around
    
    
    
    updateMovement(dt);
    
    
    //update animations too
    animation->update(dt);
}

int Hero::getHeight() {
    return pos.y;
}


void Hero::draw(){
    if (animation != NULL){
        if (faceRight)
            animation->draw(pos.x, pos.y,false);
        else
            animation->draw(pos.x, pos.y, true);
    }
}
void Hero::limitHeroMovement(int height){
    if(pos.y>=height-100){
        velocity.y=0;
    }else if (pos.y<=0){
        setPosition(Vector(100,0));
    }
}
