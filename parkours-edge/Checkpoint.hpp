//
//  Checkpoint.hpp
//  Lab11
//
//  Created by dennis wang on 4/12/22.
//

#ifndef Checkpoint_hpp
#define Checkpoint_hpp

#include <stdio.h>
#include <string>
#include "Actor.h"

class Checkpoint : public Actor{
public:
    Checkpoint(class Game* game, Actor* parent);
    
    void OnUpdate(float deltaTime);
    
    bool GetActive(){return active;}
    void SetActive(bool a);
    
    void setLevel(std::string level){mLevelString = level;}
    
    void SetText(std::string t){text = t;}
private:
    bool active = false;
    class CollisionComponent* mCC;
    class MeshComponent* mMC;
    
    std::string mLevelString = "";
    
    std::string text = "";
    
};


#endif /* Checkpoint_hpp */
