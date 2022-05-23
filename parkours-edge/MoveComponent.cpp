#include "MoveComponent.h"
#include "Actor.h"
#include "SDL2/SDL.h"

MoveComponent::MoveComponent(class Actor* owner)
:Component(owner, 50)
,mAngularSpeed(0.0f)
,mForwardSpeed(0.0f)
{
	
}

void MoveComponent::Update(float deltaTime)
{
	// TODO: Implement in Part 2
    float angVelocity = mAngularSpeed;
    mOwner->SetRotation(mOwner->GetRotation() + (angVelocity * deltaTime));
    
    Vector3 posVelocity = mOwner->GetForward() * mForwardSpeed;
    mOwner->SetPosition(mOwner->GetPosition() + (posVelocity * deltaTime));
    
    Vector3 strafeVelocity = mOwner->GetRight() * mStrafeSpeed;
    mOwner->SetPosition(mOwner->GetPosition() + (strafeVelocity * deltaTime));;
}
