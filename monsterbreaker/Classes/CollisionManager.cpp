#include "CollisionManager.h"
#include "Character.h"

USING_NS_CC;

// default constructor
CollisionManager::CollisionManager()
{

}

// check if collision has occured
bool CollisionManager::HasPhysicsBodiesCollided(cocos2d::PhysicsContact &contact, int collisionBitmask1, int collisionBitmask2)
{
	PhysicsBody *a = contact.getShapeA()->getBody();
	PhysicsBody *b = contact.getShapeB()->getBody();

	if ((a->getCollisionBitmask() == collisionBitmask1 && b->getCollisionBitmask() == collisionBitmask2) ||
		(b->getCollisionBitmask() == collisionBitmask1 && a->getCollisionBitmask() == collisionBitmask2))
	{
		return true;
	}
	else
	{
		return false;
	}
}
GameObject* CollisionManager::GetObjectData(cocos2d::PhysicsBody * ref)
{
	return (GameObject*) ref->getNode()->getUserData();
}
void CollisionManager::DeleteObject(PhysicsBody * target)
{
	target->getNode()->stopAllActions();
	auto ac_fade = FadeOut::create(0.3);

	auto seq = Sequence::create(CallFunc::create(std::bind(&CollisionManager::DestroyBody, this, target))
		, ac_fade
		, CallFunc::create(std::bind(&CollisionManager::DestroyNode, this, target->getNode()))
		, NULL);
	target->getNode()->runAction(seq);
}
void CollisionManager::DestroyBody(cocos2d::PhysicsBody * body)
{
	body->removeFromWorld();
}
void CollisionManager::DestroyNode(cocos2d::Node * node)
{
	layer->removeChild(node);
}

void CollisionManager::SetLayer(cocos2d::Layer * layer)
{
	this->layer = layer;
}

void CollisionManager::DestroyBrick(cocos2d::PhysicsBody * target)
{
	static_cast<Brick*>(target->getNode())->DestroyBlock();
}


