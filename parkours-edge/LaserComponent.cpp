//
//  LaserComponent.cpp
//  Lab10
//
//  Created by dennis wang on 4/7/22.
//

#include "LaserComponent.hpp"
#include "Shader.h"
#include "VertexArray.h"
#include "Texture.h"
#include "Mesh.h"
#include "Actor.h"
#include "Renderer.h"
#include "Game.h"
#include "SegmentCast.h"
#include "Block.hpp"
#include "Player.hpp"
#include "PlayerMove.hpp"
#include "SDL2/SDL_mixer.h"


LaserComponent::LaserComponent(class Actor* owner):
MeshComponent(owner, true){
    SetMesh(mOwner->GetGame()->GetRenderer()->GetMesh("Assets/Laser.gpmesh"));
}

void LaserComponent::Update(float deltaTime){
    mLineSegs.clear();
    
    LineSegment lineSeg;
    lineSeg.mStart = mOwner->GetWorldPosition();
    Vector3 forward = mOwner->GetWorldForward();
    //forward.Normalize();
    lineSeg.mEnd = lineSeg.mStart + forward * 500.0f;
    mLineSegs.push_back(lineSeg);

    CastInfo ci;
    
    if (SegmentCast((Actor*) mOwner->GetGame()->getPlayer(), mLineSegs.back(), ci)){
        Mix_Chunk* s = mOwner->GetGame()->GetSound("Assets/Sounds/Laser.wav");
        Mix_PlayChannel(-1, s, 0);
        mLineSegs.back().mEnd = ci.mPoint;
        mOwner->GetGame()->getPlayer()->GetComponent<PlayerMove>()->Respawn();
    }else{
        if (SegmentCast(mOwner->GetGame()->getBlocks(), mLineSegs.back(), ci, mOwner->GetParent())){
            mLineSegs.back().mEnd = ci.mPoint;
            
            bool reflected = true;
            
            if ((reinterpret_cast <Block*>(ci.mActor))->GetMirror()){
                LineSegment second;
                second.mStart = ci.mPoint;
                Vector3 forwardR = lineSeg.mEnd - lineSeg.mStart;
                forwardR.Normalize();
                second.mEnd = second.mStart + Vector3::Reflect(forwardR, ci.mNormal) * 500.0f;
                mLineSegs.push_back(second);
                
                while (reflected){
                    if (SegmentCast(mOwner->GetGame()->getBlocks(), second, ci, ci.mActor)){
                        if ((reinterpret_cast <Block*>(ci.mActor))->GetMirror()){
                            LineSegment newL;
                            newL.mStart = ci.mPoint;
                            Vector3 forwardNL = second.mEnd - second.mStart;
                            forwardNL.Normalize();
                            newL.mEnd = newL.mStart + Vector3::Reflect(forwardNL, ci.mNormal) * 500.0f;
                            mLineSegs.push_back(newL);
                            second = newL;
                        }else{
                            reflected = false;
                        }
                    }else{
                        reflected = false;
                    }
                }
                
            }
            
        }
    }
    
    
    
    
    
        
    
    
}

void LaserComponent::Draw(class Shader* shader){
    if (mMesh)
    {
        // Set the world transform
       
        // Set the active texture
        Texture* t = mMesh->GetTexture(mTextureIndex);
        if (t)
        {
            t->SetActive();
        }
        // Set the mesh's vertex array as active
        VertexArray* va = mMesh->GetVertexArray();
        va->SetActive();
        // Draw
        for (auto l: mLineSegs){
            shader->SetMatrixUniform("uWorldTransform",GetWorldMat(l));
            glDrawElements(GL_TRIANGLES, va->GetNumIndices(), GL_UNSIGNED_INT, nullptr);
        }
        
    }
}

Matrix4 LaserComponent::GetWorldMat(LineSegment ls){
    Matrix4 scale = Matrix4::CreateScale(ls.Length(), 1.0f, 1.0f);
    //Matrix4 rotation = Matrix4::CreateRotationZ(mOwner->GetRotation());
    Vector3 oldDir = Vector3::UnitX;
    Vector3 newDir = ls.mEnd - ls.mStart;
    newDir.Normalize();
    Quaternion quat;
    if (Vector3::Dot(oldDir, newDir) == 1){
        quat = Quaternion::Identity;
    }else if (Vector3::Dot(oldDir, newDir) == -1){
        quat = Quaternion(Vector3::UnitZ, Math::Pi);
    }else{
        Vector3 axis = Vector3::Cross(oldDir, newDir);
        axis.Normalize();
        float angle = Math::Acos(Vector3::Dot(oldDir, newDir));
        quat = Quaternion(axis, angle);
    }
    
    Matrix4 rotation = Matrix4::CreateFromQuaternion(quat);
    Matrix4 translation = Matrix4::CreateTranslation(ls.PointOnSegment(0.50f));
    
    Matrix4 mat = scale * rotation * translation;
    return mat;
}
