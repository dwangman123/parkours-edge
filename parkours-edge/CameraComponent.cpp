//
//  CameraComponent.cpp
//  Lab08
//
//  Created by dennis wang on 3/29/22.
//

#include "CameraComponent.hpp"
#include "Actor.h"
#include "Game.h"
#include "Renderer.h"

CameraComponent::CameraComponent(class Actor* owner):
Component(owner){
    
}

void CameraComponent::Update(float deltaTime){
    
    mPitchAngle = Math::Clamp(mPitchAngle + mPitchSpeed * deltaTime, -1 * Math::Pi/4.0f, Math::Pi/4.0f);
    
    if (WallRun){
        if (mSide == 1 || mSide == 3){
            mRotationAngle = Math::Clamp(mRotationAngle + mRotationSpeed * deltaTime, -1 * Math::Pi/2.0f, Math::Pi/2.0f);
            //mRotationAngle = Math::Pi/4.0f;
        }else if (mSide == 2 || mSide == 4){
            mRotationAngle = Math::Clamp(mRotationAngle - mRotationSpeed * deltaTime, -1 * Math::Pi/2.0f, Math::Pi/2.0f);
            //mRotationAngle = -1*Math::Pi/4.0f;
        }else{
            mRotationAngle = 0.0f;
        }
    }else{
        if (Math::Abs(mRotationAngle - mRotationSpeed * deltaTime) < 0.10f){
            mRotationAngle = 0.0f;
            
        }else{
            if (mRotationAngle < 0){
                mRotationAngle = mRotationAngle + mRotationSpeed * deltaTime;
            }else if (mRotationAngle > 0){
                mRotationAngle = mRotationAngle - mRotationSpeed * deltaTime;
            
            }else{
                mRotationAngle = 0.0f;
            }
            
        }
    }
    //mRotationAngle = Math::Clamp(mRotationAngle + mRotationSpeed * deltaTime, -1 * Math::Pi/2.0f, Math::Pi/2.0f);
    
    
    Matrix4 pitch = Matrix4::CreateRotationY(mPitchAngle);
    Matrix4 yaw = Matrix4::CreateRotationZ(mOwner->GetRotation());
    
    Vector3 up = Vector3::UnitZ;
    Matrix4 rotation;
    if (mSide == 1 || mSide == 2){
        rotation = Matrix4::CreateRotationX(mRotationAngle);
    }else if (mSide == 3 || mSide == 4){
        rotation = Matrix4::CreateRotationY(mRotationAngle);
    }else{
        rotation = Matrix4::CreateRotationX(0.0f);
    }
    up = Vector3::Transform(Vector3::UnitZ, rotation);
    
    
    Vector3 camPos = mOwner->GetPosition();
    Vector3 targetPos = mOwner->GetPosition() + (Vector3::Transform(Vector3(1,0,0), pitch * yaw) * 20.0f);
    
    Matrix4 cam = Matrix4::CreateLookAt(camPos, targetPos, up);
    mOwner->GetGame()->GetRenderer()->SetViewMatrix(cam);
    
    
    
    
}

