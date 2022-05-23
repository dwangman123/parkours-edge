//
//  LaserComponent.hpp
//  Lab10
//
//  Created by dennis wang on 4/7/22.
//

#ifndef LaserComponent_hpp
#define LaserComponent_hpp

#include <stdio.h>
#include "MeshComponent.h"
#include "SegmentCast.h"
#include <vector>

class LaserComponent: public MeshComponent{
public:
    LaserComponent(class Actor* owner);
    
    void Update(float deltaTime);
    
    void Draw(class Shader* shader);
    
    class Matrix4 GetWorldMat(LineSegment ls);
    
private:
    std::vector<LineSegment> mLineSegs;
    //LineSegment lineSeg;
};

#endif /* LaserComponent_hpp */
