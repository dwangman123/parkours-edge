//
//  Block.cpp
//  Lab09
//
//  Created by dennis wang on 3/29/22.
//

#include "Block.hpp"
#include "MeshComponent.h"
#include "CollisionComponent.h"
#include "Game.h"
#include "Mesh.h"
#include "Renderer.h"


Block::Block(Game* game, Actor* parent):
Actor(game, parent){
    SetScale(64.0f);
    MeshComponent* mc = new MeshComponent(this);
    mc->SetMesh(mGame->GetRenderer()->GetMesh("Assets/Cube.gpmesh"));
    CollisionComponent* cc = new CollisionComponent(this);
    cc->SetSize(1, 1, 1);
    mGame->addBlock(this);
}

Block::~Block(){
    mGame->removeBlock(this);
}

void Block::OnUpdate(float deltaTime){
    if (rotate){
        mRotation += Math::Pi/4 * deltaTime;
        //SetRotation(mRotation);
    }
}
