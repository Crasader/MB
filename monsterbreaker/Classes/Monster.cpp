#include"Monster.h"
#include "Definitions.h"
#include "MyBodyParser.h"
USING_NS_CC;

Monster::Monster() : timer(kTimerUp), mood(myEnum::kMoods::kMoodStay), dir(myEnum::kDir::kDirSouth), stayTime(2.0f), attackTime(1.0f), moveTime(2.0f)
{
	visibleSize = Director::getInstance()->getVisibleSize();
}

Monster::~Monster()
{

}

void Monster::SetMood(int newMood)
{
	mood = newMood;
	timer = kTimerUp;
}

void Monster::ChooseMood()
{
	float r = CCRANDOM_0_1();
	if (r < 0.3f)
	{
		SetMood(myEnum::kMoods::kMoodStay);
	}
	else if (r > 0.7f)
	{
		SetMood(myEnum::kMoods::kMoodAttack);
	}
	else
	{
		SetMood(myEnum::kMoods::kMoodMove);
	}
}

float Monster::StayTime()
{
	return stayTime;
}
float Monster::MoveTime()
{
	return moveTime;
}
float Monster::AttackTime()
{
	return attackTime;
}

void Monster::update(float dt)
{
	if (IsAlive())
	{
		if (timer != kTimerUp)
			timer -= dt;

		switch (mood)
		{
		case myEnum::kMoods::kMoodStay: MoodStay(dt); break;
		case myEnum::kMoods::kMoodMove: MoodMove(dt); break;
		case myEnum::kMoods::kMoodAttack: MoodAttack(dt); break;
		}
	}
}


void Monster::Die()
{
	GameObject::Die();
	auto r1 = CCRANDOM_0_1();
	if (r1 <= 0.4f){	// get item
		float r2 = CCRANDOM_0_1();

		int r3 = 0;
		if (r2 < 0.6f)
		{
			r3 = static_cast<int>(rand() % ITEM_DROP_USE_ITEM_SIZE + ITEM_DROP_USE_ITEM_START_NUM);
		}
		else
		{
			r3 = static_cast<int>(rand() % ITEM_DROP_HEART_ITEM_SIZE + ITEM_DROP_HEART_START_NUM);
		}
		if (r3 != 0)
		{
			DropItem(r3);
		}
	}
}

void Monster::DropItem(int itemID)
{
	auto hero = static_cast<Hero*>(layer->getChildByName("Hero"));
	int dir = ((int)(CCRANDOM_0_1() * 2) == 0) ? -1 : 1;
	auto act = JumpBy::create(0.5f, Vec2(getContentSize().width * dir, 0), getContentSize().height*0.5f, 1);

	Item* item = nullptr;
	switch (itemID)
	{
	case ITEM_DROP_COIN:
		item = ItemCoin::create(layer, hero);
		break;
	case ITEM_DROP_BOMB:
		item = ItemBomb::create(layer, hero, false);
		break;
	case ITEM_DROP_HALF_HEART:
		item = ItemHalfHeart::create(layer, hero, false);
		break;
	case ITEM_DROP_HALF_SOUL_HEART:
		item = ItemHalfSoulHeart::create(layer, hero, false);
		break;
	case ITEM_DROP_HEART:
		item = ItemHeart::create(layer, hero, false);
		break;
	case ITEM_DROP_KEY:
		item = ItemKey::create(layer, hero, false);
		break;
	case ITEM_DROP_SOUL_HEART:
		item = ItemSoulHeart::create(layer, hero, false);
		break;
	}

	if (item != nullptr)
	{
		item->setPosition(getPosition());
		layer->addChild(item, ZINDEX_ITEM_SPRITE, myEnum::kMyTag::kItemTag);
		item->runAction(act);
	}
	else
	{
		//CC_ASSERT("Item didn't has created (Drop Item ID : %d)", itemID);
	}
}

void Monster::Damaged(int i)
{
	GameObject::Damaged(i);

	SoundManager::getInstance()->playMySoundLogic("MonsterDamaged");

	hpCurrentSpr->stopAllActions();
	hpBgSpr->stopAllActions();
	hpCurrentSpr->setOpacity(255);
	hpBgSpr->setOpacity(255);

	float r = static_cast<float>(getCurrentHp()) / getMaxHp();
	if (r != 0)
	{
		hpCurrentSpr->setScaleX(r);
		auto sp = hpBgSpr->getPositionX() - hpBgSpr->getContentSize().width * 0.5f;
		hpCurrentSpr->setPositionX(sp + hpCurrentSpr->getContentSize().width * r * 0.5f);
	}
	else
	{
		hpCurrentSpr->setOpacity(0);
	}
	auto fadeOut = FadeOut::create(1.5f);
	hpCurrentSpr->runAction(fadeOut->clone());
	hpBgSpr->runAction(fadeOut->clone());

}

void Monster::MoodStay(float dt)
{
	if (timer == kTimerUp)
	{
		timer = StayTime();
		Animate("Stay", myEnum::kAction::kActionStay);
	}

	else if (timer <= 0.0f)
	{
		ChooseMood();
	}

}

void Monster::MoodMove(float dt)
{
	if (timer == kTimerUp)
	{
		timer = MoveTime();
		dir = CCRANDOM_0_1() * 4;

		switch (dir)
		{
		case myEnum::kDir::kDirEast: Animate("E", myEnum::kAction::kActionMove); break;
		case myEnum::kDir::kDirWest: Animate("W", myEnum::kAction::kActionMove); break;
		case myEnum::kDir::kDirSouth: Animate("S", myEnum::kAction::kActionMove); break;
		case myEnum::kDir::kDirNorth: Animate("N", myEnum::kAction::kActionMove); break;
		}

	}
	else if (timer <= 0.0f)
	{
		ChooseMood();
	}
	else if (timer <= 5.0f)
	{
		switch (dir)
		{
		case myEnum::kDir::kDirEast: this->runAction(MoveBy::create(0.001f, Vec2(+(50 * dt), 0))); break;
		case myEnum::kDir::kDirWest: this->runAction(MoveBy::create(0.001f, Vec2(-(50 * dt), 0))); break;
		case myEnum::kDir::kDirSouth: this->runAction(MoveBy::create(0.001f, Vec2(0, -(50 * dt)))); break;
		case myEnum::kDir::kDirNorth: this->runAction(MoveBy::create(0.001f, Vec2(0, +(50 * dt)))); break;
		}
	}
}

void Monster::BaseMoveMent(float dt)
{
	dir = rand() % 4;
	cocos2d::MoveTo * move;

	auto gapX = visibleSize.width * 0.1f;
	auto gapY = visibleSize.width * 0.04f;

	auto sp = Vec2(gapX * 0.5f, visibleSize.height - gapY * 0.5f - gapY * 10);
	int minX = 1;
	int maxX = 8;
	int minY = 1;
	int maxY = 8;

	auto min = Vec2(sp.x + gapX * minX, sp.y - gapY * minY);
	auto max = Vec2(sp.x + gapX * maxX, sp.y - gapY * maxY);

	auto desVec = this->getPosition();
	switch (dir)
	{
	case myEnum::kDir::kDirEast:
		desVec += Vec2(this->getContentSize().width * 0.5f, 0);
		if (desVec.x >= max.x) desVec.x = max.x;
		move = MoveTo::create(0.5f, desVec);
		break;
	case myEnum::kDir::kDirWest:
		desVec -= Vec2(this->getContentSize().width*0.5f, 0);
		if (desVec.x <= min.x) desVec.x = min.x;
		move = MoveTo::create(0.5f, desVec);
		break;
	case myEnum::kDir::kDirSouth:
		desVec -= Vec2(0, this->getContentSize().height*0.5f);
		if (desVec.y <= max.y) desVec.y = max.y;
		move = MoveTo::create(0.5f, desVec);
		break;
	case myEnum::kDir::kDirNorth:
		desVec += Vec2(0, this->getContentSize().height*0.5f);
		if (desVec.y >= min.y) desVec.y = min.y;
		move = MoveTo::create(0.5f, desVec);
		break;
	}
	this->runAction(move);
}

void Monster::BaseMoveMent2(float dt)
{
	dir = rand() % 2;
	cocos2d::MoveTo * move;

	auto gapX = visibleSize.width * 0.1f;
	auto gapY = visibleSize.width * 0.04f;

	auto sp = Vec2(gapX * 0.5f, visibleSize.height - gapY * 0.5f - gapY * 10);
	int minX = 2;
	int maxX = 7;
	int minY = 1;
	int maxY = 8;

	auto min = Vec2(sp.x + gapX * minX, sp.y - gapY * minY);
	auto max = Vec2(sp.x + gapX * maxX, sp.y - gapY * maxY);

	auto desVec = this->getPosition();
	switch (dir)
	{
	case myEnum::kDir::kDirEast:
		desVec += Vec2(this->getContentSize().width * 0.5f, 0);
		if (desVec.x >= max.x) desVec.x = max.x;
		move = MoveTo::create(0.5f, desVec);
		break;
	case myEnum::kDir::kDirWest:
		desVec -= Vec2(this->getContentSize().width*0.5f, 0);
		if (desVec.x <= min.x) desVec.x = min.x;
		move = MoveTo::create(0.5f, desVec);
		break;
	}
	this->runAction(move);
}

void Monster::MoodAttack(float dt)
{
	if (timer == kTimerUp)
	{
		timer = AttackTime();
		Animate("Attack", myEnum::kAction::kActionAttack);
		// fire a ball
		auto sp = this->getPosition();
		sp.y -= this->getContentSize().height;
		auto dp = Vec2(sp.x - CCRANDOM_MINUS1_1(), sp.y - 1);

		Fire(layer, sp, dp);
	}
	else if (timer <= 0.0f)
	{
		ChooseMood();
	}
}

void Monster::SetMonsterData()
{
	auto dic = cocos2d::__Dictionary::createWithContentsOfFile(String::createWithFormat("Monster/%s/%s.plist", _name.c_str(), _name.c_str())->getCString());
	_attackPoint = dic->valueForKey("AttackPoint")->intValue();
	_maxHp = dic->valueForKey("MaxHp")->intValue();
	_currentHp = dic->valueForKey("CurrentHp")->intValue();
	_team = dic->valueForKey("Team")->intValue();
	_ballName = dic->valueForKey("BallName")->getCString();
	_ballCurrentCount = dic->valueForKey("BallCurrentCount")->intValue();
	_ballCount = dic->valueForKey("BallCount")->intValue();
	_ballSize = dic->valueForKey("BallSize")->floatValue();
	_ballVelocity = dic->valueForKey("BallVelocity")->floatValue();
	_type = dic->valueForKey("Type")->getCString();
	_name = dic->valueForKey("Name")->getCString();
	_alive = true;
	_damagedState = false;
}
void Monster::InitSprite()
{
	auto body = PhysicsBody::createBox(cocos2d::Size(this->getContentSize().width, this->getContentSize().height / 2), PhysicsMaterial(100, 1, 1));
		body->setDynamic(true);
		body->setRotationEnable(false);
		body->setCollisionBitmask(MONSTER_BODY_COLLISION_BITMASK);
		body->setContactTestBitmask(true);
		this->setPhysicsBody(body);
	this->setUserData(this);

	hpBgSpr = Sprite::create("Monster/hpBg.png");
	this->addChild(hpBgSpr, ZINDEX_MONSTER_HP);
	hpCurrentSpr = Sprite::create("Monster/hpCurrent.png");
	this->addChild(hpCurrentSpr, ZINDEX_MONSTER_HP);
	auto origin = Director::getInstance()->getVisibleOrigin();
	hpBgSpr->setPosition(Vec2(this->getContentSize().width / 2, this->getPosition().y + this->getContentSize().height + hpBgSpr->getContentSize().height / 2 ));
	hpCurrentSpr->setPosition(hpBgSpr->getPosition());
	hpBgSpr->setOpacity(0);
	hpCurrentSpr->setOpacity(0);

}
void Monster::Draw(cocos2d::Layer * layer)
{
	this->layer = layer;
	layer->addChild(this, ZINDEX_MONSTER_SPRITE, "Montser");

}

void Monster::StartAnimation()
{
	this->Animate("Stay", myEnum::kAction::kActionStay);
}


