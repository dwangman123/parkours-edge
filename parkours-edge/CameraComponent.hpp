//
//  CameraComponent.hpp
//  Lab08
//
//  Created by dennis wang on 3/29/22.
//

#ifndef CameraComponent_hpp
#define CameraComponent_hpp

#include <stdio.h>
#include "Component.h"
#include "Math.h"
#include "Actor.h"

class CameraComponent: public Component{
public:
    CameraComponent(class Actor* owner);
    
    void Update(float deltaTime);
    
    float GetPitchSpeed() const {return mPitchSpeed;}
    void SetPitchSpeed(float speed){mPitchSpeed = speed;}
    
    void SetWallRun(bool cond, int side) {WallRun = cond; mSide = side;}
    
    int getSide(){return mSide;}
    
private:
    float mPitchAngle = 0.0f;
    float mPitchSpeed = 0.0f;
    
    bool WallRun = false;
    float mRotationAngle = 0.0f;
    const float mRotationSpeed = 0.50f;
    int mSide = 0; //1 = Left, 2 = Right, 3 = Front, 4 = Back
    
};

#endif /* CameraComponent_hpp */
