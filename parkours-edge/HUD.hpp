//
//  HUD.hpp
//  Lab12
//
//  Created by dennis wang on 4/20/22.
//

#ifndef HUD_hpp
#define HUD_hpp

#include <stdio.h>
#include "UIComponent.h"
#include <string>

class HUD: public UIComponent{
public:
    HUD(class Actor* owner);
    ~HUD();
    void Update(float deltaTime);
    void Draw(class Shader* shader);
    
    void UpdateText(std::string s);
    
    
private:
    class Font* mFont;
    class Texture* mTimerText;
    class Texture* mCoinCount;
    class Texture* mCheckpointText;
    
    class Texture* mRadar;
    class Texture* mArrow;
    class Texture* mBlip;
    
};

#endif /* HUD_hpp */
