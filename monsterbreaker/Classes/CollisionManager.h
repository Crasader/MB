#pragma once
#ifndef __COLLISION_MANAGER_H__
#define __COLLISION_MANAGER_H__

#include "cocos2d.h"
#include "GameObject.h"
#include "Brick.h"
class CollisionManager
{
public:
	// default constructor
	CollisionManager();

	cocos2d::Layer *layer;
	void SetLayer(cocos2d::Layer * layer);
	// check if collision has occured
	bool HasPhysicsBodiesCollided(cocos2d::PhysicsContact &contact, int collisionBitmask1, int collisionBitmask2);
	GameObject* GetObjectData(cocos2d::PhysicsBody * ref);
	void DeleteObject(cocos2d::PhysicsBody * target);
	void DestroyBody(cocos2d::PhysicsBody * body);
	void DestroyNode(cocos2d::Node * node);

	void DestroyBrick(cocos2d::PhysicsBody * target);
};

#endif // __COLLISION_MANAGER_H__
