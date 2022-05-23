#include "CollisionComponent.h"
#include "Actor.h"

CollisionComponent::CollisionComponent(class Actor* owner)
:Component(owner)
,mWidth(0.0f)
,mHeight(0.0f)
,mDepth(0.0f)
{
	
}

CollisionComponent::~CollisionComponent()
{
	
}

bool CollisionComponent::Intersect(const CollisionComponent* other)
{
	Vector3 aMin = GetMin();
	Vector3 aMax = GetMax();
	Vector3 bMin = other->GetMin();
	Vector3 bMax = other->GetMax();

	bool no = aMax.x < bMin.x ||
		aMax.y < bMin.y ||
		aMax.z < bMin.z ||
		bMax.x < aMin.x ||
		bMax.y < aMin.y ||
		bMax.z < aMin.z;

	return !no;
}

Vector3 CollisionComponent::GetMin() const
{
	Vector3 v = mOwner->GetPosition();
	v.x -= mDepth * mOwner->GetScale() / 2.0f;
	v.y -= mWidth * mOwner->GetScale() / 2.0f;
	v.z -= mHeight * mOwner->GetScale() / 2.0f;
	return v;
}

Vector3 CollisionComponent::GetMax() const
{
	Vector3 v = mOwner->GetPosition();
	v.x += mDepth * mOwner->GetScale() / 2.0f;
	v.y += mWidth * mOwner->GetScale() / 2.0f;
	v.z += mHeight * mOwner->GetScale() / 2.0f;
	return v;
}

const Vector3& CollisionComponent::GetCenter() const
{
	return mOwner->GetPosition();
}

CollSide CollisionComponent::GetMinOverlap(
	const CollisionComponent* other, Vector3& offset)
{
	offset = Vector3::Zero;
	// TODO: Implement
    
    if (!Intersect(other)){
        return CollSide::None;
    }
    
    float otherMinXdiff = Math::Abs(GetMax().x - other->GetMin().x);
    float min = otherMinXdiff;
    CollSide side = CollSide::Back;
    
    float otherMaxXdiff = Math::Abs(GetMin().x - other->GetMax().x);
    if (otherMaxXdiff < min){
        min = otherMaxXdiff;
        side = CollSide::Front;
    }
    float otherMinYdiff = Math::Abs(GetMax().y - other->GetMin().y);
    if (otherMinYdiff < min){
        min = otherMinYdiff;
        side = CollSide::Left;
    }
    float otherMaxYdiff = Math::Abs(GetMin().y - other->GetMax().y);
    if (otherMaxYdiff < min){
        min = otherMaxYdiff;
        side = CollSide::Right;
    }
    float otherMinZdiff = Math::Abs(GetMax().z - other->GetMin().z);
    if (otherMinZdiff < min){
        min = otherMinZdiff;
        side = CollSide::Bottom;
    }
    float otherMaxZdiff = Math::Abs(GetMin().z - other->GetMax().z);
    if (otherMaxZdiff < min){
        min = otherMaxZdiff;
        side = CollSide::Top;
    }
    
    if (side == CollSide::Front){
        offset.x += min;
    }else if(side == CollSide::Back){
        offset.x -= min;
    }else if (side == CollSide::Left){
        offset.y -= min;
    }else if (side == CollSide::Right){
        offset.y += min;
    }else if (side == CollSide::Top){
        offset.z += min;
    }else{
        offset.z -= min;
    }
    
    return side;

}
