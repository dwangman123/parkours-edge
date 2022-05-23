//
//  LaserMine.hpp
//  Lab10
//
//  Created by dennis wang on 4/7/22.
//

#ifndef LaserMine_hpp
#define LaserMine_hpp

#include <stdio.h>
#include "Actor.h"

class LaserMine : public Actor{
public:
    LaserMine(class Game* game, Actor* parent);
};

#endif /* LaserMine_hpp */
