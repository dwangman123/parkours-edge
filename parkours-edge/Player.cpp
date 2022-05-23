//
//  Player.cpp
//  Lab07
//
//  Created by dennis wang on 3/22/22.
//

#include "Player.hpp"
#include "MeshComponent.h"
#include "Game.h"
#include "Renderer.h"
#include "CollisionComponent.h"
#include "PlayerMove.hpp"
#include "CameraComponent.hpp"

Player::Player(class Game* game, Actor* parent):
Actor(game, parent){
    PlayerMove* pm = new PlayerMove(this);
    CameraComponent* CamC = new CameraComponent(this);
    CollisionComponent* ColC = new CollisionComponent(this);
    ColC->SetSize(50, 175, 50);

    
}
