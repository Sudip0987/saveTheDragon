//
//  Pipes.hpp
//  SaveTheDragon
//
//  Created by Sudip Sharma on 17/1/19.
//  Copyright © 2019 Sudip Sharma. All rights reserved.
//

/* Pipes_hpp */
#pragma once
#include "Entity.hpp"
class Pipes :
    public Entity
{
private:
    int w,h;
public:

void createPipe(int w, int h);
virtual void draw(); 
};
