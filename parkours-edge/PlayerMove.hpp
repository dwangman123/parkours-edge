//
//  PlayerMove.hpp
//  Lab07
//
//  Created by dennis wang on 3/22/22.
//

#ifndef PlayerMove_hpp
#define PlayerMove_hpp

#include <stdio.h>
#include "MoveComponent.h"
#include "Math.h"
#include "CollisionComponent.h"

enum MoveState{
  OnGround, Jump, Falling, WallClimb, WallRun
};

class PlayerMove : public MoveComponent{
public:
    PlayerMove(class Actor* owner);
    ~PlayerMove();
    
    void Update(float deltaTime);
    
    void ProcessInput(const Uint8* keyState);
    
    void ChangeState(MoveState state){mCurrentState = state;}
    
    void UpdateOnGround(float deltaTime);
    void UpdateJump(float deltaTime);
    void UpdateFalling(float deltaTime);
    void UpdateWallClimb(float deltaTime);
    void UpdateWallRun(float deltaTime);
    
    void PhysicsUpdate(float deltaTime);
    void AddForce(const Vector3& force);
    
    bool CanWallClimb(CollSide side);
    bool CanWallRun(CollSide side);
    
    void FixXYVelocity();
    
    void Respawn();
    
    
protected:
    CollSide FixCollision(class CollisionComponent* self, class CollisionComponent* block);
 
private:
    MoveState mCurrentState;
    
    //float mZSpeed = 0.0f;
    //const float GRAVITY = -980.0f;
    //const float JUMP_SPEED = 500.0f;
    
    Vector3 mVelocity;
    Vector3 mAcceleration;
    Vector3 mPendingForces;
    
    float mMass = 1.0f;
    Vector3 mGravity = Vector3(0.0f, 0.0f, -980.0f);
    Vector3 mWallClimbForce = Vector3(0.0, 0.0f, 1800.f);
    Vector3 mJumpForce = Vector3(0.0f, 0.0f, 35000.0f);
    
    float mWallClimbTimer = 0.0f;
    
    Vector3 mWallRunForce = Vector3(0.0f, 0.0f, 1200.0f);
    float mWallRunTimer = 0.0f;
    
    bool jumpLE = false;
    
    int SoundChannel;
    
    
};

#endif /* PlayerMove_hpp */
