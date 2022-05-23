//
//  Coin.hpp
//  Lab11
//
//  Created by dennis wang on 4/14/22.
//

#ifndef Coin_hpp
#define Coin_hpp

#include <stdio.h>
#include "Actor.h"

class Coin : public Actor{
public:
    Coin(class Game* game, Actor* owner);
    
    void OnUpdate(float deltaTime);
private:
    class CollisionComponent* mCC;
};

#endif /* Coin_hpp */
