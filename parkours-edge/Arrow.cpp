//
//  Arrow.cpp
//  Lab11
//
//  Created by dennis wang on 4/12/22.
//

#include "Arrow.hpp"
#include "MeshComponent.h"
#include "Mesh.h"
#include "Game.h"
#include "Renderer.h"
#include "Checkpoint.hpp"
#include "Player.hpp"

Arrow::Arrow(class Game* game, Actor* parent):
Actor(game, parent){
    MeshComponent* mc = new MeshComponent(this);
    mc->SetMesh(mGame->GetRenderer()->GetMesh("Assets/Arrow.gpmesh"));
    SetScale(0.15f);
}

void Arrow::OnUpdate(float deltaTime){
    Quaternion quat;
    if (mGame->getCheckpoints().size() == 0){
        quat = Quaternion::Identity;
        setQuat(quat);
        SetPosition(mGame->GetRenderer()->Unproject(Vector3(0.0f, 250.0f, 0.1f)));
        return;
    }
    Vector3 PtoC = mGame->getCheckpoints().front()->GetPosition() - mGame->getPlayer()->GetPosition();
    Vector3 oldDir = Vector3::UnitX;
    PtoC.Normalize();
    if (Vector3::Dot(oldDir, PtoC) == 1){
        quat = Quaternion::Identity;
    }else if (Vector3::Dot(oldDir, PtoC) == -1){
        quat = Quaternion(Vector3::UnitZ, Math::Pi);
    }else{
        Vector3 axis = Vector3::Cross(oldDir, PtoC);
        axis.Normalize();
        float angle = Math::Acos(Vector3::Dot(oldDir, PtoC));
        quat = Quaternion(axis, angle);
    }
    setQuat(quat);
    SetPosition(mGame->GetRenderer()->Unproject(Vector3(0.0f, 250.0f, 0.1f)));
    
}
