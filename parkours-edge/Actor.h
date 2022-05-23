#pragma once
#include <vector>
#include <SDL2/SDL_stdinc.h>
#include "Math.h"

enum class ActorState
{
	Active,
	Paused,
	Destroy
};

class Actor
{
public:
	Actor(class Game* game, Actor* parent);
	virtual ~Actor();

	// Update function called from Game (not overridable)
	void Update(float deltaTime);
	// ProcessInput function called from Game (not overridable)
	void ProcessInput(const Uint8* keyState);

	// Getters/setters
	const Vector3& GetPosition() const { return mPosition; }
	void SetPosition(const Vector3& pos) { mPosition = pos; }
	float GetScale() const { return mScale; }
	void SetScale(float scale) { mScale = scale; }
	float GetRotation() const { return mRotation; }
	void SetRotation(float rotation) { mRotation = rotation; }
	
	ActorState GetState() const { return mState; }
	void SetState(ActorState state) { mState = state; }

	class Game* GetGame() { return mGame; }
    
    Vector3 GetForward(){return Vector3(Math::Cos(mRotation), Math::Sin(mRotation), 0.0f);}
	
    Vector3 GetRight() {return Vector3(Math::Cos(mRotation + Math::PiOver2) , Math::Sin(mRotation+ Math::PiOver2), 0.0f);}
    
    Quaternion getQuat (){return mQuaternion;}
    void setQuat(Quaternion quat){mQuaternion = quat;}
    
    Vector3 GetQuatForward();
    
	// Returns component of type T, or null if doesn't exist
	template <typename T>
	T* GetComponent() const
	{
		for (auto c : mComponents)
		{
			T* t = dynamic_cast<T*>(c);
			if (t != nullptr)
			{
				return t;
			}
		}
		
		return nullptr;
	}
    
    const Matrix4& GetWorldTransform() const { return mWorldTransform; }
    
    void CalcWorldTransform();
    Matrix4 GetWorldRotTrans();
    
    Vector3 GetWorldPosition(){return mWorldTransform.GetTranslation();}
    Vector3 GetWorldForward(){return mWorldTransform.GetXAxis();}
    
    void AddChild(Actor* child);
    void RemoveChild(Actor* child);
    
    Actor* GetParent(){return mParent;}
protected:
	// Any actor-specific update code (overridable)
	virtual void OnUpdate(float deltaTime);
	// Any actor-specific update code (overridable)
	virtual void OnProcessInput(const Uint8* keyState);
	
	class Game* mGame;
	// Actor's state
	ActorState mState;

	// Transform
	Vector3 mPosition;
	float mScale;
	float mRotation;
	
	// Components
	std::vector<class Component*> mComponents;
private:
	friend class Component;
	// Adds component to Actor (this is automatically called
	// in the component constructor)
	void AddComponent(class Component* c);
    
    Matrix4 mWorldTransform;
    
    float rollAngle;
    
    Quaternion mQuaternion;
    
    Actor* mParent;
    std::vector<Actor*> mChildren;
    bool mInheritScale = false;
    
};
