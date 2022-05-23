//
//  Arrow.hpp
//  Lab11
//
//  Created by dennis wang on 4/12/22.
//

#ifndef Arrow_hpp
#define Arrow_hpp

#include <stdio.h>
#include "Actor.h"

class Arrow : public Actor {
public:
    Arrow(class Game* game, Actor* parent);
    
    void OnUpdate(float deltaTime);
};

#endif /* Arrow_hpp */
