//
//  SecurityCamera.hpp
//  Lab11
//
//  Created by dennis wang on 4/19/22.
//

#ifndef SecurityCamera_hpp
#define SecurityCamera_hpp

#include <stdio.h>
#include "Actor.h"
#include "Math.h"

class SecurityCamera: public Actor{
public:
    SecurityCamera(class Game* game, Actor* owner);
    ~SecurityCamera();
    
    void SetStartQ(Quaternion q){startQ = q;}
    void SetEndQ(Quaternion q){endQ = q;}
    void SetInterpTime(float t){interpTime = t;}
    void SetPauseTime(float t){pauseTime = t;}
    
    void OnUpdate(float deltaTime);
    void SetPaused(bool b){paused = b;}
private:
    Quaternion startQ;
    Quaternion endQ;
    float interpTime;
    float pauseTime;
    
    float timer = 0;
    int dir = 1;
    bool paused = false;
    
    int CamMotor = -1;
    int CamMotorStop = -1;
    
    bool cmsPlayed = false;
    bool cmPlayed = false;
    
    int GetVolume();
};

#endif /* SecurityCamera_hpp */
