#pragma once
#include <SDL2/SDL.h>
#include <limits>
#include <algorithm>
#include <list>
#include <iostream>
#include "Vector.hpp"

using namespace std;

class Entity
{
protected:
    SDL_Renderer* renderer;
    
    
    
public:
    Entity();
    ~Entity();
    
    Vector pos; //our entities xy position
    Vector velocity; //how fast to move in any direction
    
    //FOR COLLISIONS
    bool bumpIntoSolids = false; //do I run into stuff?
    bool solid = false; //do things run into me?
    SDL_Rect collisionBox;
    bool collisionOccured=false;
    void setRenderer(SDL_Renderer* renderer);
    Vector getPosition();
    void setPosition(Vector pos);
    Vector getVelocity();
    void setVelocity(Vector velocity);
    
    virtual void update(float dt);
    virtual void updateMovement(float dt);
    virtual void updateCollisionBox();
    virtual void updateCollisions(float dt);
    virtual void draw();
    
    void checking();
    float SweptAABB(SDL_Rect movingBox, Vector vec, SDL_Rect otherBox, float &normalX, float &normalY);
    SDL_Rect GetSweptBroadphaseBox(SDL_Rect b, Vector vec);
    bool AABBCheck(SDL_Rect b1, SDL_Rect b2);
    
    static list<Entity*> *entities;
};

