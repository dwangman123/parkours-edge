//
//  SecurityCone.hpp
//  Lab11
//
//  Created by dennis wang on 4/19/22.
//

#ifndef SecurityCone_hpp
#define SecurityCone_hpp

#include <stdio.h>
#include "Actor.h"
class SecurityCone: public Actor{
public:
    SecurityCone(class Game* game, Actor* parent);
    
    void OnUpdate(float deltaTime);
private:
    class MeshComponent* mMC;
    float timer = 0;
    bool death = false;
    float deathT = 0;
    
    int SecDetected;
    bool WtoY = true;
};

#endif /* SecurityCone_hpp */
