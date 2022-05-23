//
//  LaserMine.cpp
//  Lab10
//
//  Created by dennis wang on 4/7/22.
//

#include "LaserMine.hpp"
#include "Actor.h"
#include "Mesh.h"
#include "MeshComponent.h"
#include "Renderer.h"
#include "Game.h"
#include "LaserComponent.hpp"

LaserMine::LaserMine(class Game* game, Actor* parent):
Actor(game, parent){
    MeshComponent* mc = new MeshComponent(this);
    mc->SetMesh(mGame->GetRenderer()->GetMesh("Assets/LaserMine.gpmesh"));
    LaserComponent* lc = new LaserComponent(this);
}
