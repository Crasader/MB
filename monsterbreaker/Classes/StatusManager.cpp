#include"StatusManager.h"
USING_NS_CC;
StatusManager::StatusManager()
{
	auto cache = SpriteFrameCache::sharedSpriteFrameCache();
	cache->addSpriteFramesWithFile("Heart/Heart.plist", "Heart/Heart.png");
}
StatusManager::~StatusManager()
{
	
}

StatusManager* StatusManager::create(Hero * hero)
{
	auto pNode = new StatusManager();
	pNode->autorelease();
	pNode->InitStatus(hero);
	return pNode;
}

void StatusManager::InitStatus(Hero * hero)
{
	visibleSize = Director::getInstance()->getVisibleSize();
	this->hero = hero;
	// top ui 
	topBG = Sprite::create("GameScene/TopUI.png");
	topBG->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - topBG->getContentSize().height / 2));
	// hp label
	hpLabel = Label::createWithTTF("HP", "fonts/Marker Felt.ttf", 32);
	hpLabel->setPosition(Vec2(hpLabel->getContentSize().width * 2, visibleSize.height - hpLabel->getContentSize().height * 2));
	hpLabel->setColor(Color3B::RED);
	
	// spLabel
	if (hero->getName().compare("Warrior") == 0)
	{
		spLabel = Label::createWithTTF("AP", "fonts/Marker Felt.ttf", 32);
		spLabel->setColor(Color3B::BLACK);
	}
	else if (hero->getName().compare("Magician")== 0)
	{
		spLabel = Label::createWithTTF("MP", "fonts/Marker Felt.ttf", 32);
		spLabel->setColor(Color3B::BLUE);
	}
	spLabel->setPosition(Vec2(hpLabel->getPositionX(), hpLabel->getPositionY() - spLabel->getContentSize().height * 2));

	// hp & sp sprite
	InitHp();
	InitSp(hero->getName().c_str());
	SetMaxHp(hero->getMaxHp());
	SetMaxSp(hero->getMaxSp());
	SetCurrentHp(hero->getCurrentHp());
	SetCurrentSp(hero->getCurrentSp());

	// etc 
	keySprite = Sprite::create("GameScene/key.png");
	bombSprite = Sprite::create("GameScene/bomb.png");
	moneySprite = Sprite::create("GameScene/money.png");

	float gapX = (visibleSize.width/3 - keySprite->getContentSize().width * 6) / 4;
	float etcY = spLabel->getPositionY() - spLabel->getContentSize().height * 2;
	keySprite->setPosition(gapX + keySprite->getContentSize().width / 2, etcY);
	bombSprite->setPosition(gapX * 2 + keySprite->getContentSize().width * 2 + bombSprite->getContentSize().width / 2, etcY);
	moneySprite->setPosition(gapX * 3 + keySprite->getContentSize().width * 4 + moneySprite->getContentSize().width / 2, etcY);

	// key Label
	keyCountLabel = LabelAtlas::create(cocos2d::__String::createWithFormat("%02d", hero->getKeyCount())->getCString(), "fonts/atlas.png", 16, 24, '.');
	keyCountLabel->setPosition(keySprite->getPositionX() + keySprite->getContentSize().width, keySprite->getPositionY());
	// bomb Label
	bombCountLabel = LabelAtlas::create(cocos2d::__String::createWithFormat("%02d", hero->getBombCount())->getCString(), "fonts/atlas.png", 16, 24, '.');
	bombCountLabel->setPosition(bombSprite->getPositionX() + bombSprite->getContentSize().width, bombSprite->getPositionY());
	// money Label
	moneyCountLabel = LabelAtlas::create(cocos2d::__String::createWithFormat("%02d", hero->getMoneyCount())->getCString(), "fonts/atlas.png", 16, 24, '.');
	moneyCountLabel->setPosition(moneySprite->getPositionX() + moneySprite->getContentSize().width, moneySprite->getPositionY());

}
void StatusManager::InitHp()
{
	for (int i = 0; i < 5; i++)
	{
		auto sprVoid = Sprite::createWithSpriteFrameName("HeartVoid.png");
		sprVoid->setPosition(Vec2(hpLabel->getPositionX() + sprVoid->getContentSize().width + sprVoid->getContentSize().width * i, hpLabel->getPositionY()));
		sprVoid->setVisible(false);
		voidHpSprite.pushBack(sprVoid);
		auto sprLeft = Sprite::createWithSpriteFrameName("HeartLeft.png");
		sprLeft->setPosition(Vec2(sprVoid->getPosition()));
		sprLeft->setVisible(false);
		leftHpSprite.pushBack(sprLeft);
		auto sprRight = Sprite::createWithSpriteFrameName("HeartRight.png");
		sprRight->setPosition(Vec2(sprVoid->getPosition()));
		sprRight->setVisible(false);
		rightHpSprite.pushBack(sprRight);
	}
}
void StatusManager::InitSp(const char * hName)  
{
	for (int i = 0; i < 5; i++)
	{		
		auto sprVoid = Sprite::createWithSpriteFrameName(cocos2d::__String::createWithFormat("%sHeartVoid.png", hName)->getCString());
		sprVoid->setPosition(Vec2(spLabel->getPositionX() + sprVoid->getContentSize().width + sprVoid->getContentSize().width * i, spLabel->getPositionY()));
		sprVoid->setVisible(false);
		voidSpSprite.pushBack(sprVoid);
		auto sprLeft = Sprite::createWithSpriteFrameName(cocos2d::__String::createWithFormat("%sHeartLeft.png", hName)->getCString());
		sprLeft->setPosition(Vec2(sprVoid->getPosition()));
		sprLeft->setVisible(false);
		leftSpSprite.pushBack(sprLeft);
		auto sprRight = Sprite::createWithSpriteFrameName(cocos2d::__String::createWithFormat("%sHeartRight.png", hName)->getCString());
		sprRight->setPosition(Vec2(sprVoid->getPosition()));
		sprRight->setVisible(false);
		rightSpSprite.pushBack(sprRight);
	}
}

void StatusManager::SetKeyCount(int keyNum)
{
	keyCountLabel->setString(cocos2d::__String::createWithFormat("%02d", keyNum)->getCString());
}
void StatusManager::SetBombCount(int bombNum)
{
	bombCountLabel->setString(cocos2d::__String::createWithFormat("%02d", bombNum)->getCString());
}
void StatusManager::SetMoneyCount(int moneyNum)
{
	moneyCountLabel->setString(cocos2d::__String::createWithFormat("%02d", moneyNum)->getCString());
}

void StatusManager::DrawStatus(cocos2d::Layer * layer)
{
	layer->addChild(topBG,ZINDEX_STATUS_BG);
	layer->addChild(hpLabel, ZINDEX_STATUS_LABEL);
	layer->addChild(spLabel, ZINDEX_STATUS_LABEL);
	layer->addChild(keySprite, ZINDEX_STATUS_ETC);
	layer->addChild(keyCountLabel, ZINDEX_STATUS_LABEL);
	layer->addChild(bombSprite, ZINDEX_STATUS_ETC);
	layer->addChild(bombCountLabel, ZINDEX_STATUS_LABEL);
	layer->addChild(moneySprite, ZINDEX_STATUS_ETC);
	layer->addChild(moneyCountLabel, ZINDEX_STATUS_LABEL);

	for (int i = 0; i < 5; i++)
	{
		layer->addChild(voidHpSprite.at(i),ZINDEX_STATUS_BACK_HEART);
		layer->addChild(leftHpSprite.at(i), ZINDEX_STATUS_FRONT_HEART);
		layer->addChild(rightHpSprite.at(i), ZINDEX_STATUS_FRONT_HEART);
		layer->addChild(voidSpSprite.at(i), ZINDEX_STATUS_BACK_HEART);
		layer->addChild(leftSpSprite.at(i), ZINDEX_STATUS_FRONT_HEART);
		layer->addChild(rightSpSprite.at(i), ZINDEX_STATUS_FRONT_HEART);
	}
	layer->addChild(this);
}

void StatusManager::SetCurrentHp(int currentHp)
{
	// left
	int i = 0;
	int count = (currentHp + 1) / 2;
	for (; i < count; i++)
	{
		leftHpSprite.at(i)->setVisible(true);
	}
	for (; i < 5; i++)
	{
		leftHpSprite.at(i)->setVisible(false);
	}
	// right
	i = 0;
	count = (currentHp) / 2;
	for (; i < count; i++)
	{
		rightHpSprite.at(i)->setVisible(true);
	}
	for (; i < 5; i++)
	{
		rightHpSprite.at(i)->setVisible(false);
	}

}
void StatusManager::SetMaxHp(int maxHp)
{
	int i = 0;
	int count = (maxHp + 1) / 2;
	for (; i < count; i++)
	{
		voidHpSprite.at(i)->setVisible(true);
	}
	for (; i < 5; i++)
	{
		voidHpSprite.at(i)->setVisible(false);
	}
}
void StatusManager::SetCurrentSp(int currentSp)
{
	// left
	int i = 0;
	int count = (currentSp + 1) / 2;
	for (; i < count; i++)
	{
		leftSpSprite.at(i)->setVisible(true);
	}
	for (; i < 5; i++)
	{
		leftSpSprite.at(i)->setVisible(false);
	}
	// right
	i = 0;
	count = (currentSp) / 2;
	for (; i < count; i++)
	{
		rightSpSprite.at(i)->setVisible(true);
	}
	for (; i < 5; i++)
	{
		rightSpSprite.at(i)->setVisible(false);
	}
}
void StatusManager::SetMaxSp(int maxSp)
{
	int i = 0;
	int count = (maxSp + 1) / 2;
	for (; i < count; i++)
	{
		voidSpSprite.at(i)->setVisible(true);
	}
	for (; i < 5; i++)
	{
		voidSpSprite.at(i)->setVisible(false);
	}
}

void StatusManager::update(float dt)
{
	SetCurrentHp(hero->getCurrentHp());
	SetMaxHp(hero->getMaxHp());
	SetCurrentSp(hero->getCurrentSp());
	SetMaxSp(hero->getMaxSp());
	SetKeyCount(hero->getKeyCount());
	SetBombCount(hero->getBombCount());
	SetMoneyCount(hero->getMoneyCount());

}

