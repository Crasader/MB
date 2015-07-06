#include "Merchant.h"
USING_NS_CC;

Merchant::Merchant(cocos2d::Layer * layer, Hero * hero) : layer(layer), hero(hero)
{

}
Merchant* Merchant::create(cocos2d::Layer * layer, Hero * hero)
{
	auto pSprite = new Merchant(layer, hero);
	pSprite->autorelease();
	pSprite->InitSprite();
	return pSprite;
}

void Merchant::Die()
{
	int x = MapManager::getInstance()->getHeroX();
	int y = MapManager::getInstance()->getHeroY();
	MapManager::getInstance()->map[x][y].data["merchant"] = 1;

	CCLOG("DIE merchant :: %d", MapManager::getInstance()->GetCurrentRoomData().data["merchant"]);
	int r = rand() % 4;
	Vec2 vec = getPosition();
	vec.x -= size.width;
	vec.y -= size.height;
	for (int i = 0; i < r; i++)
	{
		auto item = ItemCoin::create(layer, hero);
		item->setPosition(this->getPosition());
		layer->addChild(item, ZINDEX_ITEM_SPRITE);

		auto act = MoveTo::create(0.5f, Vec2(vec.x + size.width * 0.5f * i, vec.y));
		item->runAction(act);
	}	
}


void Merchant::InitSprite()
{
	auto merchant = Sprite::create("Shop/Merchant.png");
	size = merchant->getContentSize();
	this->addChild(merchant);

	auto body = PhysicsBody::createCircle(merchant->getContentSize().width *0.5f);
	body->setContactTestBitmask(true);
	body->setCollisionBitmask(MERCHANT_COLLISION_BITMASK);
	merchant->setPhysicsBody(body);
	body->getNode()->setUserData(this);

}

