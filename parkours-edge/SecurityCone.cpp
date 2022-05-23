//
//  SecurityCone.cpp
//  Lab11
//
//  Created by dennis wang on 4/19/22.
//

#include "SecurityCone.hpp"
#include "MeshComponent.h"
#include "Mesh.h"
#include "Game.h"
#include "Renderer.h"
#include "Player.hpp"
#include "PlayerMove.hpp"
#include "SecurityCamera.hpp"


SecurityCone::SecurityCone(class Game* game, Actor* parent):
Actor(game, parent){
    MeshComponent* mc = new MeshComponent(this, true);
    mc->SetMesh(mGame->GetRenderer()->GetMesh("Assets/Cone.gpmesh"));
    mMC = mc;
    SetPosition(Vector3(30, 0 , 0));
    SetScale(3.0f);
}

void SecurityCone::OnUpdate(float deltaTime){
    timer += deltaTime;
    float dist = Vector3::Distance(GetWorldPosition(), mGame->getPlayer()->GetPosition());
    Vector3 CtoP = mGame->getPlayer()->GetPosition() - GetWorldPosition();
    CtoP.Normalize();
    float angle = Math::Acos(Vector3::Dot(CtoP,GetWorldForward()));
    if (death){
        deathT += deltaTime;
        if (deathT >= 0.50){
            mGame->getPlayer()->GetComponent<PlayerMove>()->Respawn();
            death = false;
            deathT = 0;
        }
    }
    if (dist <= 100.0f * GetScale() && angle <= Math::Pi/6){
        ((SecurityCamera*) GetParent())->SetPaused(true);
        mMC->SetTextureIndex(1);
        if (WtoY){
            Mix_Chunk* s = mGame->GetSound("Assets/Sounds/SecurityDetected.wav");
            SecDetected = Mix_PlayChannel(Mix_GroupAvailable(1), s, 0);
            WtoY = false;
        }
        
        if (timer >= 2.0f){
            mMC->SetTextureIndex(2);
            death = true;
        }
    }else{
        if (!WtoY){
            Mix_HaltChannel(SecDetected);
        }
        ((SecurityCamera*) GetParent())->SetPaused(false);
        mMC->SetTextureIndex(0);
        WtoY = true;
        timer = 0;
    }
}
