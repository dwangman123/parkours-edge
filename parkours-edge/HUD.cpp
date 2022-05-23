//
//  HUD.cpp
//  Lab12
//
//  Created by dennis wang on 4/20/22.
//

#include "HUD.hpp"
#include "Font.h"
#include "Texture.h"
#include <string.h>
#include "Actor.h"
#include "Game.h"
#include "Renderer.h"
#include "Player.hpp"
#include "SecurityCamera.hpp"

HUD::HUD(class Actor* owner):
UIComponent(owner){
    mFont = new Font();
    mFont->Load("Assets/Inconsolata-Regular.ttf");
    mTimerText = mFont->RenderText("00:00.00");
    std::string coins;
    int mCoinNum = mOwner->GetGame()->GetCoin();
    if (mCoinNum < 10){
        coins += "0";
    }
    coins += std::to_string(mCoinNum) += "/55";
    mCoinCount = mFont->RenderText(coins);
    mCheckpointText = mFont->RenderText("    ");
    mRadar = mOwner->GetGame()->GetRenderer()->GetTexture("Assets/Radar.png");
    mArrow = mOwner->GetGame()->GetRenderer()->GetTexture("Assets/RadarArrow.png");
    mBlip = mOwner->GetGame()->GetRenderer()->GetTexture("Assets/Blip.png");
}

HUD::~HUD(){
    mFont->Unload();
    delete mFont;
}

void HUD::Draw(class Shader* shader){
    DrawTexture(shader, mTimerText, Vector2(-420.0f, -325.0f));
    DrawTexture(shader, mCoinCount, Vector2(-445.0f, -290.0f));
    DrawTexture(shader, mCheckpointText, Vector2::Zero);
    DrawTexture(shader, mRadar, Vector2(405.0f, -270.0f));
    DrawTexture(shader, mArrow, Vector2(405.0f, -270.0f));
    
    
    Vector3 playerF = mOwner->GetGame()->getPlayer()->GetForward();
    //Vector2 player = Vector2(player3.x, player3.y);
    float angle = Math::Atan2(playerF.y, playerF.x);
    Matrix3 rot = Matrix3::CreateRotation(angle);
    
    Vector3 playerP = mOwner->GetGame()->getPlayer()->GetWorldPosition();
    Vector2 player2dp = Vector2(playerP.y, playerP.x);
    for (auto s: mOwner->GetGame()->GetSecCams()){
        Vector3 objPos = s->GetWorldPosition();
        Vector2 obj2dpPos = Vector2(objPos.y, objPos.x);
        Vector2 sp = obj2dpPos - player2dp;
        if (sp.Length() < 1500.0f){
            sp = Vector2(sp.x/1500.0f, sp.y/1500.0f);
            sp = Vector2(sp.x*92.0f, sp.y*92.0f);
            sp = Vector2::Transform(sp, rot);
            Vector2 pF = Vector2(playerF.y, playerF.x);
            pF = Vector2::Transform(pF, rot);
            float bRot = Math::Atan2(pF.y, pF.x);
            DrawTexture(shader, mBlip, sp+Vector2(405.0f, -270.0f), 1.0f, bRot);
        }
    }
    
}

void HUD::Update(float deltaTime){
    float mTime = mOwner->GetGame()->GetTime();
    mTime += deltaTime;
    mOwner->GetGame()->SetTime(mTime);
    mTimerText->Unload();
    delete mTimerText;
    int min = (int) mTime / 60;
    int sec = (int) mTime % 60;
    int ms = (int)(mTime * 100) % 100;
    std::string time;
    if (min < 10){
        time += "0";
    }
    time += std::to_string(min) + ":";
    if (sec < 10){
        time += "0";
    }
    time += std::to_string(sec) + ":" + std::to_string(ms);
    mTimerText = mFont->RenderText(time);
    if (mOwner->GetGame()->GetNewCoin()){
        mCoinCount->Unload();
        delete mCoinCount;
        std::string coins;
        int mCoinNum = mOwner->GetGame()->GetCoin();
        if (mCoinNum < 10){
            coins += "0";
        }
        coins += std::to_string(mCoinNum) += "/55";
        mCoinCount = mFont->RenderText(coins);
        mOwner->GetGame()->SetNewCoin(false);
    }
    float CheckTime = mOwner->GetGame()->GetCheckTime();
    CheckTime += deltaTime;
    if (CheckTime > 5.0f){
        UpdateText("       ");
        mOwner->GetGame()->SetCheckTime(0.0f);
    }else{
        mOwner->GetGame()->SetCheckTime(CheckTime);
    }
    
    
    
}

void HUD::UpdateText(std::string s){
    mCheckpointText = mFont->RenderText(s);
}
