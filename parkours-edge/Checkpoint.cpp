//
//  Checkpoint.cpp
//  Lab11
//
//  Created by dennis wang on 4/12/22.
//

#include "Checkpoint.hpp"
#include "MeshComponent.h"
#include "Mesh.h"
#include "Game.h"
#include "Renderer.h"
#include "CollisionComponent.h"
#include "Player.hpp"
#include <queue>
#include "Actor.h"
#include "SDL2/SDL_mixer.h"
#include "HUD.hpp"


Checkpoint::Checkpoint(class Game* game, Actor* parent):
Actor(game, parent){
    MeshComponent* mc = new MeshComponent(this);
    mc->SetMesh(mGame->GetRenderer()->GetMesh("Assets/Checkpoint.gpmesh"));
    mc->SetTextureIndex(1);
    mMC = mc;
    CollisionComponent* cc = new CollisionComponent(this);
    cc->SetSize(25.0f, 25.0f, 25.0f);
    mCC = cc;
}

void Checkpoint::OnUpdate(float deltaTime){
    CollisionComponent* pCC = mGame->getPlayer()->GetComponent<CollisionComponent>();
    if (pCC->Intersect(mCC) && active == true){
        mGame->getPlayer()->GetComponent<HUD>()->UpdateText(text);
        Mix_Chunk* s = mGame->GetSound("Assets/Sounds/Checkpoint.wav");
        Mix_PlayChannel(-1, s, 0);
        SetState(ActorState::Destroy);
        mGame->getPlayer()->SetRespawn(GetPosition());
        
        if (mGame->getCheckpoints().size() != 0){
            mGame->removeCheckpoint();
            if (mGame->getCheckpoints().size() != 0){
                mGame->getCheckpoints().front()->SetActive(true);
            }
        }
        
        if (mLevelString.size() != 0){
            mGame->setLevel(mLevelString);
        }
        
    }
    
    
    
    
    
}

void Checkpoint::SetActive(bool a){
    active = a;
    mMC->SetTextureIndex(0);
}

