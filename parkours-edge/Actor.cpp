#include "Actor.h"
#include "Game.h"
#include "Component.h"
#include <algorithm>

Actor::Actor(Game* game, Actor* parent)
	:mGame(game)
	,mState(ActorState::Active)
	,mPosition(Vector3::Zero)
	,mScale(1.0f)
	,mRotation(0.0f)
    ,mParent(parent)
{
    if (parent == nullptr){
        mGame->addActor(this);
    }else{
        mParent->AddChild(this);
    }
    
}

Actor::~Actor()
{
	// TODO
    while (!mChildren.empty()){
        delete mChildren.back();
    }
    if (mParent == nullptr){
        mGame->removeActor(this);
    }else{
        mParent->RemoveChild(this);
    }
    
    for (auto comp: mComponents){
        delete comp;
    }
    mComponents.clear();
}

void Actor::Update(float deltaTime)
{
	// TODO
    CalcWorldTransform();
    if (mState == ActorState::Active){
        for (auto comp: mComponents){
            comp->Update(deltaTime);
        }
        OnUpdate(deltaTime);
    }
    CalcWorldTransform();
    for (auto c : mChildren){
        c->Update(deltaTime);
    }
}

void Actor::OnUpdate(float deltaTime)
{
}

void Actor::ProcessInput(const Uint8* keyState)
{
    if (mState == ActorState::Active){
        for (auto comp: mComponents){
            comp->ProcessInput(keyState);
        }
        OnProcessInput(keyState);
    }
}

void Actor::OnProcessInput(const Uint8* keyState)
{
}

void Actor::AddComponent(Component* c)
{
	mComponents.emplace_back(c);
	std::sort(mComponents.begin(), mComponents.end(), [](Component* a, Component* b) {
		return a->GetUpdateOrder() < b->GetUpdateOrder();
	});
}

Vector3 Actor::GetQuatForward(){
    Vector3 forward = Vector3::Transform(Vector3::UnitX, mQuaternion);
    forward.Normalize();
    return forward;
}

void Actor::CalcWorldTransform(){
    Matrix4 scale = Matrix4::CreateScale(mScale);
    Matrix4 rotation = Matrix4::CreateRotationZ(mRotation);
    Matrix4 translation = Matrix4::CreateTranslation(mPosition);
    Matrix4 quat = Matrix4::CreateFromQuaternion(mQuaternion);
    
    mWorldTransform = scale * rotation * quat * translation;
    
    if (mParent != nullptr){
        if (mInheritScale){
            mWorldTransform *= mParent->GetWorldTransform();
        }else{
            mWorldTransform *= mParent->GetWorldRotTrans();
        }
    }

}

Matrix4 Actor::GetWorldRotTrans(){
    Matrix4 wrt;
    Matrix4 rotation = Matrix4::CreateRotationZ(mRotation);
    Matrix4 translation = Matrix4::CreateTranslation(mPosition);
    Matrix4 quat = Matrix4::CreateFromQuaternion(mQuaternion);
    
    wrt = rotation * quat * translation;
    if (mParent != nullptr){
        wrt *= mParent->GetWorldRotTrans();
    }
    return wrt;
}

void Actor::AddChild(Actor* child){
    mChildren.push_back(child);
}

void Actor::RemoveChild(Actor* child){
    auto iter = std::find(mChildren.begin(), mChildren.end(), child);
    if (iter != mChildren.end())
    {
        auto iter2 = mChildren.end() - 1;
        std::iter_swap(iter, iter2);
        mChildren.pop_back();
    }
}
