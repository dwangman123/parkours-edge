//
//  Player.hpp
//  Lab07
//
//  Created by dennis wang on 3/22/22.
//

#ifndef Player_hpp
#define Player_hpp

#include <stdio.h>
#include "Actor.h"

class Player : public Actor{
public:
    Player(class Game* game, Actor* parent);
    
    void SetRespawn(Vector3 pos){respawn = pos;}
    Vector3 GetRespawn(){return respawn;}
    
    
private:
    Vector3 respawn;
};

#endif /* Player_hpp */



