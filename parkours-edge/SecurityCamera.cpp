//
//  SecurityCamera.cpp
//  Lab11
//
//  Created by dennis wang on 4/19/22.
//

#include "SecurityCamera.hpp"
#include "MeshComponent.h"
#include "Mesh.h"
#include "Game.h"
#include "Renderer.h"
#include "SecurityCone.hpp"
#include "SDL2/SDL_mixer.h"
#include "Player.hpp"

SecurityCamera::SecurityCamera(class Game* game, Actor* parent):
Actor(game, parent){
    MeshComponent* mc = new MeshComponent(this);
    mc->SetMesh(mGame->GetRenderer()->GetMesh("Assets/Camera.gpmesh"));
    SecurityCone* sc = new SecurityCone(game, this);
    setQuat(startQ);
    game->addSecCams(this);
}

SecurityCamera::~SecurityCamera(){
    if(Mix_Playing(CamMotor)){
        Mix_HaltChannel(CamMotor);
    }
    mGame->removeSecCams(this);
}

void SecurityCamera::OnUpdate(float deltaTime){
    if (paused){
        Mix_HaltChannel(CamMotor);
        if (!cmsPlayed){
            Mix_Chunk* s = mGame->GetSound("Assets/Sounds/CameraMotorStop.wav");
            CamMotorStop = Mix_PlayChannel(Mix_GroupAvailable(1), s, 0);
            Mix_Volume(CamMotor, GetVolume());
            cmsPlayed = true;
            cmPlayed = false;
        }
        
    }else if (timer > interpTime){
        //pause
        timer += deltaTime;
        Mix_HaltChannel(CamMotor);
        if (!cmsPlayed){
            Mix_Chunk* s = mGame->GetSound("Assets/Sounds/CameraMotorStop.wav");
            CamMotorStop = Mix_PlayChannel(Mix_GroupAvailable(1), s, 0);
            Mix_Volume(CamMotorStop, GetVolume());
            cmsPlayed = true;
            cmPlayed = false;
        }
        if (timer > interpTime + pauseTime){
            timer = 0;
            dir *= -1;
        }
    }else{
        Quaternion curr;
        if (dir > 0){
            curr = Quaternion::Slerp(startQ, endQ, timer/interpTime);
        }else{
            curr = Quaternion::Slerp(endQ, startQ, timer/interpTime);
        }
        setQuat(curr);
        cmsPlayed = false;
        if (!cmPlayed){
            Mix_Chunk* s = mGame->GetSound("Assets/Sounds/CameraMotor.wav");
            CamMotor = Mix_PlayChannel(Mix_GroupAvailable(1), s, 0);
            Mix_Volume(CamMotor, GetVolume());
            cmPlayed = true;
        }
        Mix_Volume(CamMotor, GetVolume());
        timer += deltaTime;
    }
}

int SecurityCamera::GetVolume(){
    float dist = Vector3::Distance(mGame->getPlayer()->GetPosition(), GetPosition());
    if (dist > 1500){
        return 0;
    }else if (dist <= 1500 && dist >= 500){
        return Math::Lerp(128, 0, (dist-500) / 1000);
    }else{
        return 128;
    }
}
