//
//  Block.hpp
//  Lab09
//
//  Created by dennis wang on 3/29/22.
//

#ifndef Block_hpp
#define Block_hpp

#include <stdio.h>
#include "Actor.h"

class Block : public Actor{
public:
    Block(class Game* game, Actor* parent);
    ~Block();
    bool GetMirror(){return mMirror;}
    void SetMirror(bool mirror){mMirror = mirror;}
    
    bool GetRotate(){return rotate;}
    void SetRotate(bool rot){rotate = rot;}
    
    void OnUpdate(float deltaTime);
private:
    bool mMirror = false;
    bool rotate = false;
};

#endif /* Block_hpp */
