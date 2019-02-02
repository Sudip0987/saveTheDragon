#pragma once
#include "Entity.hpp"
#include "Animation.hpp"
class Hero :
public Entity
{
public:
    Animation* animation = NULL;
    bool faceRight = true;
public:
    Hero();
    ~Hero();
    
    void setAnimation(Animation* animation);
    
    //overriding
    virtual void update(float dt);
    virtual void draw();
    int getHeight();
    
    void limitHeroMovement(int height);
};


