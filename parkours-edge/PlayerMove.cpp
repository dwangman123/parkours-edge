//
//  PlayerMove.cpp
//  Lab07
//
//  Created by dennis wang on 3/22/22.
//

#include "PlayerMove.hpp"
#include "Actor.h"
#include "SDL2/SDL.h"
#include "Math.h"
#include "Game.h"
#include "Renderer.h"
#include "Random.h"
#include "Player.hpp"
#include "CameraComponent.hpp"
#include "SDL2/SDL_mixer.h"

PlayerMove::PlayerMove(class Actor* owner):
MoveComponent(owner){
    ChangeState(Falling);
    Mix_Chunk* s = mOwner->GetGame()->GetSound("Assets/Sounds/Running.wav");
    SoundChannel = Mix_PlayChannel(-1, s, -1);
    Mix_Pause(SoundChannel);
}

PlayerMove::~PlayerMove(){
    Mix_HaltChannel(SoundChannel);
}

void PlayerMove::Update(float deltaTime){
    if (mCurrentState == OnGround){
        UpdateOnGround(deltaTime);
    }else if (mCurrentState == Jump){
        UpdateJump(deltaTime);
    }else if (mCurrentState == WallClimb){
        UpdateWallClimb(deltaTime);
    }else if (mCurrentState == WallRun){
        UpdateWallRun(deltaTime);
    }else {
        UpdateFalling(deltaTime);
    }
    
    if (mOwner->GetPosition().z <= -750.0f){
        Respawn();
    }
    
    if ((mCurrentState == OnGround && mVelocity.Length() >= 50.0f) || mCurrentState == WallClimb || mCurrentState == WallRun){
        Mix_Resume(SoundChannel);
    }else{
        Mix_Pause(SoundChannel);
    }
}

void PlayerMove::ProcessInput(const Uint8* keyState){
    if (keyState[SDL_SCANCODE_W] == keyState[SDL_SCANCODE_S]){
        AddForce(mOwner->GetForward() * 0.0f);
        
    }else if (keyState[SDL_SCANCODE_S]){
        AddForce(mOwner->GetForward() * -700.0f);
        
    }else if (keyState[SDL_SCANCODE_W]){
        AddForce(mOwner->GetForward() * 700.0f);
        
    }else{
        AddForce(mOwner->GetForward() * 0.0f);
    }
    
    if (keyState[SDL_SCANCODE_D] == keyState[SDL_SCANCODE_A]){
        AddForce(mOwner->GetRight() * 0.0f);
        
    }else if (keyState[SDL_SCANCODE_D]){
        AddForce(mOwner->GetRight() * 700.0f);
        
    }else if (keyState[SDL_SCANCODE_A]){
        AddForce(mOwner->GetRight() * -700.0f);
        
    }else{
        AddForce(mOwner->GetRight() * 0.0f);
        
    }
    
    if (keyState[SDL_SCANCODE_SPACE]){
        if (!jumpLE && mCurrentState == OnGround){
            Mix_Chunk* s = mOwner->GetGame()->GetSound("Assets/Sounds/Jump.wav");
            Mix_PlayChannel(-1, s, 0);
            AddForce(mJumpForce);
            ChangeState(Jump);
            jumpLE = true;
        }
    }else{
        jumpLE = false;
    }
    
    int x, y;
    SDL_GetRelativeMouseState(&x, &y);
    float angularSpeed = x / 500.0f * Math::Pi * 10.0f;
    float pitchSpeed = y / 500.0f * Math::Pi * 10.0f;
    SetAngularSpeed(angularSpeed);
    mOwner->GetComponent<CameraComponent>()->SetPitchSpeed(pitchSpeed);
    
}

void PlayerMove::UpdateOnGround(float deltaTime){
    PhysicsUpdate(deltaTime);
    std::vector<Actor*> blocks = mOwner->GetGame()->getBlocks();
    class CollisionComponent* cc = mOwner->GetComponent<CollisionComponent>();
    bool NoTop = true;
    for (auto b : blocks){
        CollSide side = FixCollision(cc, b->GetComponent<CollisionComponent>());
        if (side == CollSide::Top){
            NoTop = false;
        }
        
        if (side == CollSide::Left || side == CollSide::Right || side == CollSide::Front
            || side == CollSide::Back){
            if (CanWallClimb(side)){
                mWallClimbTimer = 0.0f;
                ChangeState(WallClimb);
                return;
            }
            
        }
    }
    if (NoTop){
        ChangeState(Falling);
    }
}

void PlayerMove::UpdateJump(float deltaTime){
    AddForce(mGravity);
    PhysicsUpdate(deltaTime);
    class CollisionComponent* cc = mOwner->GetComponent<CollisionComponent>();
    std::vector<Actor*> blocks = mOwner->GetGame()->getBlocks();
    for (auto b : blocks){
        CollSide side = FixCollision(cc, b->GetComponent<CollisionComponent>());
        if (side == CollSide::Bottom){
            mVelocity.z = 0.0f;
        }
        
        if (side == CollSide::Left || side == CollSide::Right || side == CollSide::Front
            || side == CollSide::Back){
            if (CanWallClimb(side)){
                ChangeState(WallClimb);
                mWallClimbTimer = 0.0f;
                return;
            }else if (CanWallRun(side)){
                ChangeState(WallRun);
                mWallRunTimer = 0.0f;
                return;
            }
            
        }
    }
    if (mVelocity.z <= 0.0f){
        ChangeState(Falling);
    }
}

void PlayerMove::UpdateFalling(float deltaTime){
    AddForce(mGravity);
    PhysicsUpdate(deltaTime);
    std::vector<Actor*> blocks = mOwner->GetGame()->getBlocks();
    class CollisionComponent* cc = mOwner->GetComponent<CollisionComponent>();
    for (auto b : blocks){
        if (FixCollision(cc, b->GetComponent<CollisionComponent>()) == CollSide::Top){
            mVelocity.z = 0.0f;
            Mix_Chunk* s = mOwner->GetGame()->GetSound("Assets/Sounds/Land.wav");
            Mix_PlayChannel(-1, s, 0);
            ChangeState(OnGround);
            mOwner->GetComponent<CameraComponent>()->SetWallRun(false, 0);
        }
    }
    
}

void PlayerMove::UpdateWallClimb(float deltaTime){
    AddForce(mGravity);
    mWallClimbTimer += deltaTime;
    if (mWallClimbTimer <= 0.4f){
        AddForce(mWallClimbForce);
    }
    PhysicsUpdate(deltaTime);
 
    bool sideCollided = false;
    std::vector<Actor*> blocks = mOwner->GetGame()->getBlocks();
    class CollisionComponent* cc = mOwner->GetComponent<CollisionComponent>();
    
    for (auto b : blocks){
        CollSide side =FixCollision(cc, b->GetComponent<CollisionComponent>());
        if (side ==CollSide::Right || side == CollSide::Left|| side == CollSide::Back || side == CollSide::Front){
            sideCollided = true;
        }
    }
    
    if (!sideCollided || mVelocity.z <= 0.0f){
        mVelocity.z = 0.0f;
        ChangeState(Falling);
    }
}

void PlayerMove::UpdateWallRun(float deltaTime){
    AddForce(mGravity);
    mWallRunTimer += deltaTime;
    if (mWallRunTimer <= 0.4f){
        AddForce(mWallRunForce);
    }
    PhysicsUpdate(deltaTime);
    
    
    
 
    std::vector<Actor*> blocks = mOwner->GetGame()->getBlocks();
    class CollisionComponent* cc = mOwner->GetComponent<CollisionComponent>();

    for (auto b : blocks){
        CollSide side = FixCollision(cc, b->GetComponent<CollisionComponent>());
        if (side == CollSide::Front){
            mOwner->GetComponent<CameraComponent>()->SetWallRun(true, 3);
        }else if(side == CollSide::Back){
            mOwner->GetComponent<CameraComponent>()->SetWallRun(true, 4);
        }else if (side == CollSide::Left){
            mOwner->GetComponent<CameraComponent>()->SetWallRun(true, 1);
        }else if (side == CollSide::Right){
            mOwner->GetComponent<CameraComponent>()->SetWallRun(true, 2);
        }
    }
    
    
    if (mVelocity.z <= 0.0f){
        mVelocity.z = 0.0f;
        ChangeState(Falling);
        mOwner->GetComponent<CameraComponent>()->SetWallRun(false, mOwner->GetComponent<CameraComponent>()->getSide());
    }
}


CollSide PlayerMove::FixCollision(CollisionComponent* self, CollisionComponent* block){
    Vector3 offset;
    CollSide cs = self->GetMinOverlap(block, offset);
    if (cs != CollSide::None){
        mOwner->SetPosition(mOwner->GetPosition() + offset);
    }
    Vector3 normal = Vector3(0,0,0);
    if (cs == CollSide::Back){
        normal = Vector3(-1, 0, 0);
    }else if (cs == CollSide::Front){
        normal = Vector3(1, 0, 0);
    }else if (cs == CollSide::Left){
        normal = Vector3(0, -1, 0);
    }else if (cs == CollSide::Right){
        normal = Vector3(0, 1, 0);
    }
    
    normal *= 700;
    AddForce(normal);
    return cs;
}


void PlayerMove::AddForce(const Vector3& force){
    mPendingForces += force;
}

void PlayerMove::PhysicsUpdate(float deltaTime){
    mAcceleration = mPendingForces * (1.0f/mMass);
    mVelocity += mAcceleration * deltaTime;
    FixXYVelocity();
    mOwner->SetPosition(mOwner->GetPosition() + mVelocity * deltaTime);
    mOwner->SetRotation(mOwner->GetRotation() + (mAngularSpeed * deltaTime));
    mPendingForces = Vector3::Zero;
    
}

void PlayerMove::FixXYVelocity(){
    Vector2 xy = Vector2(mVelocity.x, mVelocity.y);
    if (xy.Length() >= 400.0f){
        xy.Normalize();
        xy *= 400.0f;
    }
    
    if (mCurrentState == OnGround || mCurrentState == WallClimb){
        if (Math::NearZero(mAcceleration.x) || (mAcceleration.x * xy.x < 0)){
            xy.x *= 0.9f;
        }if (Math::NearZero(mAcceleration.y) || (mAcceleration.y * xy.y < 0)){
            xy.y *= 0.9f;
        }
    }
    
    mVelocity.x = xy.x;
    mVelocity.y = xy.y;
}

bool PlayerMove::CanWallClimb(CollSide side){
    Vector2 xy = Vector2(mVelocity.x, mVelocity.y);
    Vector2 xyNormalized = xy;
    xyNormalized.Normalize();
    Vector3 forward = mOwner->GetForward();
    forward.Normalize();
    Vector3 normal;
    if (side == CollSide::Back){
        normal = Vector3(-1, 0, 0);
    }else if (side == CollSide::Front){
        normal = Vector3(1, 0, 0);
    }else if (side == CollSide::Left){
        normal = Vector3(0, -1, 0);
    }else{
        normal = Vector3(0, 1, 0);
    }
    
    Vector2 xyN = Vector2(normal.x, normal.y);
    
    if (Vector3::Dot(normal, forward) < -0.90 && Vector2::Dot(xyN , xyNormalized) < -0.90 && xy.Length() >= 350.0f){
        return true;
    }
    
    return false;
}

bool PlayerMove::CanWallRun(CollSide side){
    Vector3 normal;
    if (side == CollSide::Back){
        normal = Vector3(-1, 0, 0);
    }else if (side == CollSide::Front){
        normal = Vector3(1, 0, 0);
    }else if (side == CollSide::Left){
        normal = Vector3(0, -1, 0);
    }else{
        normal = Vector3(0, 1, 0);
    }
    
    Vector2 xy = Vector2(mVelocity.x, mVelocity.y);
    Vector2 xyN = Vector2(mOwner->GetForward().x, mOwner->GetForward().y);
    
    Vector2 xyNormalized = xy;
    xyNormalized.Normalize();
    Vector3 forward = mOwner->GetForward();
    forward.Normalize();
    
    if (Vector3::Dot(normal, forward) < 0.50 && Vector2::Dot(xyN , xyNormalized)
        > 0.75 && xy.Length() >= 350.0f){
        
        return true;
    }
    
    return false;
}

void PlayerMove::Respawn(){
    mOwner->SetPosition(((Player*)mOwner)->GetRespawn());
    mOwner->SetRotation(0.0f);
    mVelocity = Vector3::Zero;
    mPendingForces = Vector3::Zero;
    ChangeState(Falling);
}
