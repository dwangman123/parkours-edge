//
//  Coin.cpp
//  Lab11
//
//  Created by dennis wang on 4/14/22.
//

#include "Coin.hpp"
#include "MeshComponent.h"
#include "Mesh.h"
#include "Game.h"
#include "Renderer.h"
#include "CollisionComponent.h"
#include "Player.hpp"
#include "SDL2/SDL_mixer.h"
#include "HUD.hpp"

Coin::Coin(class Game* game, Actor* owner):
Actor(game, owner){
    MeshComponent* mc = new MeshComponent(this);
    mc->SetMesh(mGame->GetRenderer()->GetMesh("Assets/Coin.gpmesh"));
    CollisionComponent* cc = new CollisionComponent(this);
    cc->SetSize(100.0f, 100.0f, 100.0f);
    mCC = cc;
}

void Coin::OnUpdate(float deltaTime){
    
    SetRotation(GetRotation() + Math::Pi * deltaTime);
    CollisionComponent* pCC = mGame->getPlayer()->GetComponent<CollisionComponent>();
    if (pCC->Intersect(mCC)){
        Mix_Chunk* s = mGame->GetSound("Assets/Sounds/Coin.wav");
        mGame->AddCoin();
        Mix_PlayChannel(-1, s, 0);
        SetState(ActorState::Destroy);
    }
}
