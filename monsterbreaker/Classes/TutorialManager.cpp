#include "TutorialManager.h"

USING_NS_CC;
using namespace ui;


TutorialManager::TutorialManager(cocos2d::Layer * layer, Hero * hero) : layer(layer), hero(hero)
{
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();
	mapManager = MapManager::getInstance();
	isClicked = false;
}
TutorialManager::~TutorialManager()
{
}
TutorialManager* TutorialManager::create(cocos2d::Layer * layer, Hero * hero)
{
	auto pNode = new TutorialManager(layer, hero);
	pNode->autorelease();
	return pNode;
}

void TutorialManager::createTutorialBtn()
{
	aBtn = TutorialBtn::create(layer, myEnum::kTutorial::kAttack);
	mBtn = TutorialBtn::create(layer, myEnum::kTutorial::kMove);
	bBtn = TutorialBtn::create(layer, myEnum::kTutorial::kBomb);
	dBtn = TutorialBtn::create(layer, myEnum::kTutorial::kDamaged);
	sBtn = TutorialBtn::create(layer, myEnum::kTutorial::kSkill);

	aBtn->setPosition(visibleSize.width*0.35f, visibleSize.height*0.6f);
	mBtn->setPosition(visibleSize.width*0.65f, visibleSize.height*0.6f);
	bBtn->setPosition(visibleSize.width*0.35f, visibleSize.height*0.4f);
	dBtn->setPosition(visibleSize.width*0.65f, visibleSize.height*0.4f);
	sBtn->setPosition(visibleSize.width*0.5f, visibleSize.height*0.5f);

	layer->addChild(aBtn, ZINDEX_CHEST_SPRITE);
	layer->addChild(mBtn, ZINDEX_CHEST_SPRITE);
	layer->addChild(bBtn, ZINDEX_CHEST_SPRITE);
	layer->addChild(dBtn, ZINDEX_CHEST_SPRITE);
	layer->addChild(sBtn, ZINDEX_CHEST_SPRITE);

	aBtn->setScale(0.5f);
	mBtn->setScale(0.5f);
	bBtn->setScale(0.5f);
	dBtn->setScale(0.5f);
	sBtn->setScale(0.5f);

	aBtn->btn->addTouchEventListener(CC_CALLBACK_2(TutorialManager::onTutorialBtnTouch, this));
	mBtn->btn->addTouchEventListener(CC_CALLBACK_2(TutorialManager::onTutorialBtnTouch, this));
	bBtn->btn->addTouchEventListener(CC_CALLBACK_2(TutorialManager::onTutorialBtnTouch, this));
	dBtn->btn->addTouchEventListener(CC_CALLBACK_2(TutorialManager::onTutorialBtnTouch, this));
	sBtn->btn->addTouchEventListener(CC_CALLBACK_2(TutorialManager::onTutorialBtnTouch, this));

	auto help = Sprite::createWithSpriteFrameName("Tutorial/help.png");
	help->setPosition(visibleSize.width*0.5f, visibleSize.height*0.7f);
	layer->addChild(help, ZINDEX_TUTORIAL_BTN);
}

void TutorialManager::update(float dt)
{
}
void TutorialManager::pause()
{
	int size = vec.size();
	for (int i = 0; i < size; i++)
	{
		auto obj = vec.at(i);
		obj->pause();
	}
}
void TutorialManager::resume()
{
	int size = vec.size();
	for (int i = 0; i < size; i++)
	{
		auto obj = vec.at(i);
		obj->resume();
	}
}


void TutorialManager::onTutorialBtnTouch(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type)
{
	if (!isClicked)
	{
		switch (type){
		case Widget::TouchEventType::BEGAN:
			break;
		case Widget::TouchEventType::MOVED:
			break;
		case Widget::TouchEventType::ENDED:
		{
			//Open();
			isClicked = true;
			auto target = (TutorialBtn*)((Node*)sender)->getUserData();
			doWork(target->btnType);
		}
		break;
		case Widget::TouchEventType::CANCELED:
			break;
		default:
			break;
		}

	}
}

void TutorialManager::doWork(int btnType)
{
	switch (btnType)
	{
	case myEnum::kTutorial::kAttack:
	{
		auto f = FingerPointer::create(layer);
		f->setPosition(visibleSize.width*0.3f, visibleSize.height*0.5f);
		layer->addChild(f, ZINDEX_TUTORIAL_SPRITE);

		f->setClickVisible(false);
		f->setRotation(-45);
		//		f->setOpacity(128);

		f->runAction(Sequence::create(
			DelayTime::create(1.0f),
			CallFunc::create(std::bind(&FingerPointer::setClickVisible, f, true)),
			CallFunc::create(std::bind(&FingerPointer::clickCancle, f, 0.5f)),
			CallFunc::create(std::bind(&FingerPointer::fadeOut, f, 0.5f)),
			DelayTime::create(1.0f),
			CallFunc::create(std::bind(&TutorialManager::removeNode, this, f)),
			NULL));

		auto cache = SpriteFrameCache::sharedSpriteFrameCache();
		cache->addSpriteFramesWithFile("Ball/Ball.plist", "Ball/Ball.png");

//		ball = Node::create();

		auto ball = Sprite::createWithSpriteFrameName(String::createWithFormat("Ball/%s.png", hero->getBallName().c_str())->getCString());
		//ball->addChild(b1);

		auto dp = Vec2(f->getPosition() + Vec2(-ball->getContentSize().width *0.5f, ball->getContentSize().height*0.5f));
		auto startPoint = hero->paddle->getPosition();
		startPoint.y += hero->paddle->getContentSize().height;

		ball->setPosition(startPoint);
		layer->addChild(ball, ZINDEX_TUTORIAL_SPRITE);
		ball->setVisible(false);

		ball->runAction(Sequence::create(
			DelayTime::create(1.5f),
			CallFunc::create(std::bind(&Node::setVisible, ball, true)),
			CallFunc::create(std::bind(&TutorialManager::playAttackSound, this, "FireBall", "wav")),
			//			CallFunc::create(std::bind(&SoundManager::playMySoundLogic, SoundManager::getInstance(), "FireBall")),
			MoveTo::create(1.0f, dp),
			CallFunc::create(std::bind(&Node::setVisible, ball, false)),
			DelayTime::create(1.0f),
			CallFunc::create(std::bind(&TutorialManager::playAttackSound, this, "FireBall", "wav")),
			CallFunc::create(std::bind(&Node::setVisible, ball, true)),
			MoveTo::create(1.0f, startPoint),
			CallFunc::create(std::bind(&TutorialManager::playAttackSound, this, "Solid", "wav")),
			MoveTo::create(1.0f, dp),
			CallFunc::create(std::bind(&TutorialManager::removeNode, this, ball)),
			NULL));

		auto m = Slime::create();
		m->setPosition(dp);
		m->setMaxHp(100);
		m->setCurrentHp(100);
		layer->addChild(m, ZINDEX_TUTORIAL_SPRITE);
		m->setVisible(true);

		m->runAction(Sequence::create(
			DelayTime::create(2.5f),
			CallFunc::create(std::bind(&Monster::Damaged, m, 1)),
			DelayTime::create(3.0f),
			CallFunc::create(std::bind(&Monster::Damaged, m, 1)),
			DelayTime::create(0.5f),
			CallFunc::create(std::bind(&TutorialManager::removeNode, this, m)),
			CallFunc::create(std::bind(&TutorialManager::setIsClicked, this, false)),
			NULL));

		vec.pushBack(f);
		vec.pushBack(ball);
		vec.pushBack(m);

	}
		break;
	case myEnum::kTutorial::kMove:
	{
		auto f = FingerPointer::create(layer);
		f->setPosition(hero->getPosition());
		layer->addChild(f, ZINDEX_TUTORIAL_SPRITE);

		f->setClickVisible(true);
//		f->setOpacity(128);

		f->runAction(Sequence::create(
			MoveTo::create(1.0f, Vec2(visibleSize.width*0.8f, f->getPositionY())),
			MoveTo::create(1.0f, Vec2(visibleSize.width*0.2f, f->getPositionY())),
			CallFunc::create(std::bind(&TutorialManager::removeNode, this, f)),
			CallFunc::create(std::bind(&TutorialManager::setIsClicked, this, false)),
			NULL));
		vec.pushBack(f);
	}
	break;
	case myEnum::kTutorial::kBomb:
	{
		auto f = FingerPointer::create(layer);
		f->setPosition(visibleSize.width*0.5f, visibleSize.height*0.7f);
		layer->addChild(f, ZINDEX_TUTORIAL_SPRITE);

		f->setClickVisible(true);
		f->setRotation(-45);
		//		f->setOpacity(128);

		auto txt = Sprite::createWithSpriteFrameName("Tutorial/ClickAndHold.png");
		txt->setPosition(f->getPosition());
		layer->addChild(txt, ZINDEX_TUTORIAL_SPRITE);

		auto bomb = Bomb::create(layer, hero);
		bomb->setPosition(f->getPosition());
		layer->addChild(bomb, ZINDEX_TUTORIAL_SPRITE);
		bomb->setOpacity(255);

		f->runAction(Sequence::create(
			DelayTime::create(2.0f),
			CallFunc::create(std::bind(&TutorialManager::removeNode, this, f)),
			NULL));
		
		txt->runAction(Sequence::create(
			DelayTime::create(2.0f),
			CallFunc::create(std::bind(&TutorialManager::removeNode, this, txt)),
			NULL));

		bomb->runAction(Sequence::create(
			FadeIn::create(0.5f),
			DelayTime::create(1.0f),
			FadeOut::create(0.5f),
			CallFunc::create(std::bind(&TutorialManager::removeNode, this, bomb)),
			CallFunc::create(std::bind(&TutorialManager::setIsClicked, this, false)),
			NULL));

		vec.pushBack(f);
		vec.pushBack(txt);
		vec.pushBack(bomb);

	}
	break;
	case myEnum::kTutorial::kDamaged:
	{
		auto cache = SpriteFrameCache::sharedSpriteFrameCache();
		cache->addSpriteFramesWithFile("Ball/Ball.plist", "Ball/Ball.png");


		auto ball = Sprite::createWithSpriteFrameName(String::createWithFormat("Ball/%s.png", hero->getBallName().c_str())->getCString());

		auto dp = Vec2(visibleSize.width*0.3f, visibleSize.height*0.5f);
		auto startPoint = hero->paddle->getPosition();
		startPoint.y += hero->paddle->getContentSize().height;
		auto dp2 = Vec2(visibleSize.width*0.1f, dp.y * 0.5f + hero->getPosition().y * 0.5f);
		auto dp3 = Vec2(hero->getPosition().x - hero->getContentSize().width*0.5f, visibleSize.height * 0.04 * 1.5f);

		ball->setPosition(startPoint);
		layer->addChild(ball, ZINDEX_TUTORIAL_SPRITE);
		ball->setVisible(false);

		ball->runAction(Sequence::create(
			CallFunc::create(std::bind(&Node::setVisible, ball, true)),
			CallFunc::create(std::bind(&TutorialManager::playAttackSound, this, "FireBall", "wav")),
			MoveTo::create(1.0f, dp),
			MoveTo::create(0.5f, dp2),
			MoveTo::create(0.5f, dp3),
			CallFunc::create(std::bind(&Node::setVisible, ball, false)),
			DelayTime::create(1.0f),
			MoveTo::create(0.01f, dp),
			
			CallFunc::create(std::bind(&TutorialManager::playAttackSound, this, "FireBall", "wav")),
			CallFunc::create(std::bind(&Node::setVisible, ball, true)),
			MoveTo::create(0.5f, dp2),
			MoveTo::create(0.5f, hero->getPosition()),
			//CallFunc::create(std::bind(&TutorialManager::playAttackSound, this, "Solid", "wav")),
			//MoveTo::create(1.0f, dp),
			CallFunc::create(std::bind(&TutorialManager::removeNode, this, ball)),
			NULL));

		auto m = Slime::create();
		m->setPosition(visibleSize.width*0.3f, visibleSize.height*0.5f);
		m->setMaxHp(100);
		m->setCurrentHp(100);
		layer->addChild(m, ZINDEX_TUTORIAL_SPRITE);
		m->setVisible(true);

		m->runAction(Sequence::create(
			DelayTime::create(1.0f),
			CallFunc::create(std::bind(&Monster::Damaged, m, 1)),
			DelayTime::create(4.0f),
			CallFunc::create(std::bind(&TutorialManager::removeNode, this, m)),
			CallFunc::create(std::bind(&TutorialManager::setIsClicked, this, false)),
			NULL));

		auto color = hero->getColor();
		hero->runAction(
			Sequence::create(
			DelayTime::create(2.0f),
			CallFunc::create(std::bind(&TutorialManager::playAttackSound, this, "HeroDamaged", "wav")),
			TintTo::create(0.1, 255, 0, 0),
			Blink::create(0.2, 2),
			TintTo::create(0.1, color.r, color.g, color.b),
			DelayTime::create(1.5f),
			CallFunc::create(std::bind(&TutorialManager::playAttackSound, this, "HeroDamaged", "wav")),
			TintTo::create(0.1, 255, 0, 0),
			Blink::create(0.2, 2),
			TintTo::create(0.1, color.r, color.g, color.b),
			NULL));

		vec.pushBack(m);
		vec.pushBack(ball);
		vec.pushBack(hero);
	}
	break;
	case myEnum::kTutorial::kSkill:
	{
		auto sm = (SkillManager*)layer->getChildByName("SkillManager");
		
		//
		auto f = FingerPointer::create(layer);
		f->setPosition(sm->getPosition());
		layer->addChild(f, ZINDEX_TUTORIAL_SPRITE);

		f->setClickVisible(true);
		f->setRotation(45);
//		f->setOpacity(128);

		f->runAction(Sequence::create(
			DelayTime::create(1.0f),
			CallFunc::create(std::bind(&TutorialManager::removeNode, this, f)),
			NULL));

		//
		auto f2 = FingerPointer::create(layer);
		f2->setPosition(visibleSize.width*0.5f, visibleSize.height*0.7f);
		layer->addChild(f2, ZINDEX_TUTORIAL_SPRITE);

		f2->setClickVisible(true);
		f2->setVisible(false);
		f2->setRotation(45);
		//		f2->setOpacity(128);

		f2->runAction(Sequence::create(
			DelayTime::create(1.0f),
			CallFunc::create(std::bind(&FingerPointer::setVisible, f2, true)),
			//FadeIn::create(0.5f),
//			DelayTime::create(0.5f),
//			CallFunc::create(std::bind(&FingerPointer::fadeOut, f2, 0.5f)),
			DelayTime::create(1.0f),
			CallFunc::create(std::bind(&TutorialManager::removeNode, this, f2)),
			CallFunc::create(std::bind(&TutorialManager::setIsClicked, this, false)),
			NULL));

		vec.pushBack(f);
		vec.pushBack(f2);
	}
	break;

	}
}

void TutorialManager::removeNode(cocos2d::Node * target)
{
	target->removeFromParentAndCleanup(true);
}

void TutorialManager::playAttackSound(const char * soundName, const char * soundType)
{
	SoundManager::getInstance()->playMySoundLogic(soundName, soundType);
}


