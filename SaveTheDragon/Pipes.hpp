#pragma once
#include "Entity.hpp"
class Pipes :
public Entity
{
public:
    int w,h;
public:
    Pipes();
    ~Pipes();
    
    void createPipe(int w, int h);
    virtual void update(float dt);
    virtual void draw();
};
