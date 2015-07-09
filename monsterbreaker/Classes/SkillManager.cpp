#include "SkillManager.h"
USING_NS_CC;
using namespace ui;

SkillManager::SkillManager(Hero * hero) : hero(hero)
{
	visibleSize = Director::sharedDirector()->getVisibleSize();
	origin = Director::sharedDirector()->getVisibleOrigin();
	_clickEnabled = false;

}
SkillManager::~SkillManager()
{

}

SkillManager* SkillManager::create(Hero * hero)
{
	auto pNode = new SkillManager(hero);	
	pNode->autorelease();
	pNode->InitSkill();
	return pNode;
}

void SkillManager::update(float dt)
{
	int current = hero->getSkillCurrentPoint();
	int max = hero->getSkillMaxPoint();
	
	float result = (float) current / max;
	gaugeCurrent->setScaleX(result);

	auto gapX = gaugeMax->getPositionX() - gaugeMax->getContentSize().width  * 0.5f;
	gaugeCurrent->setPosition(gapX + gaugeCurrent->getContentSize().width * result * 0.5f, gaugeCurrent->getPositionY());

}

void SkillManager::InitSkill()
{
	node = CSLoader::createNode("Skill/Skill.csb");

	gaugeCurrent = node->getChildByName("GaugeFront");
	gaugeFrame = static_cast<Sprite*>(node->getChildByName("GaugeFrame"));
	gaugeMax = node->getChildByName("GaugeBack");
	skillImage = static_cast<Sprite*>(node->getChildByName("SkillImage"));
	btn = static_cast<cocos2d::ui::Button*>(node->getChildByName("Btn"));
	btn->addTouchEventListener(CC_CALLBACK_2(SkillManager::ClickSkillBtn, this));

	SetSkillImage();

	this->addChild(node, ZINDEX_STATUS_SKILL);

}

void SkillManager::SetSkillImage()
{
	int skill = hero->getSkillID();
	
	// set skill image
	skillImage->setDisplayFrame(GetSkillSpriteFrame(skill));

	int max = hero->getSkillMaxPoint();

	if (max == 1)
		gaugeFrame->setOpacity(0);
	else
		gaugeFrame->setOpacity(255);

}

cocos2d::SpriteFrame * SkillManager::GetSkillSpriteFrame(int skillID)
{
	auto cache = SpriteFrameCache::sharedSpriteFrameCache();
	cocos2d::SpriteFrame * result = nullptr;
	switch (skillID)
	{
	case SKILL_FIRST_AID:
		result = cache->getSpriteFrameByName("Skill/FirstAid.png");
		break;
	case SKILL_FIRE_BALL:
		result = cache->getSpriteFrameByName("Skill/FireBall.png");
		break;
	case SKILL_LIGHTNING:
		result = cache->getSpriteFrameByName("Skill/Lightning.png");
		break;
	}
	if (result == nullptr)
	{
		//CC_ASSERT("Skill Image Is NULL (%d)", skillID);
	}

	return result;
}


void SkillManager::CheckSkillUseable()
{
	int skillID = hero->getSkillID();
	if (skillID == SKILL_FIRST_AID) setClickEnabled(true);
	else setClickEnabled(false);
}

void SkillManager::DrawAndSetPosition(cocos2d::Layer * layer)
{
	this->layer = layer;
	auto frame = node->getChildByName("Frame");
	this->setPosition(visibleSize.width *0.5f, visibleSize.height - frame->getContentSize().height * 0.5f);
	layer->addChild(this, ZINDEX_STATUS_SKILL, "SkillManager");
	this->scheduleUpdate();
}

void SkillManager::ClickSkillBtn(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type)
{
	switch (type){
	case Widget::TouchEventType::BEGAN:
		break;
	case Widget::TouchEventType::MOVED:
		break;
	case Widget::TouchEventType::ENDED:
	{
		if (_clickEnabled)
		{
			hero->SkillUse();
			SoundManager::getInstance()->playMySoundLogic("Shining");
		}
		else
		{
			// X sound
			SoundManager::getInstance()->playMySoundLogic("X");
		}
	}
	break;
	case Widget::TouchEventType::CANCELED:
		break;
	default:
		break;
	}
}

