//
//  Entity.cpp
//  SaveTheDragon
//
//  Created by Sudip Sharma on 12/1/19.
//  Copyright © 2019 Sudip Sharma. All rights reserved.
//

#include "Entity.hpp"


Entity::Entity()
{
}


Entity::~Entity()
{
}

void Entity::setRenderer(SDL_Renderer* renderer){
    this->renderer = renderer;
}

Vector Entity::getPosition(){
    return pos;
}
void Entity::setPosition(Vector pos){
    this->pos = pos;
}
Vector Entity::getVelocity(){
    return velocity;
}
void Entity::setVelocity(Vector velocity){
    this->velocity = velocity;
}

void Entity::update(float dt){
    //do nothing, unless subclasses do something with it
    
    updateMovement(dt);
}
void Entity::updateMovement(float dt){
    pos.x = pos.x + velocity.x*dt;
    pos.y = pos.y + velocity.y*dt;
    
}
void Entity::draw(){
    //also do nothing for now
}
