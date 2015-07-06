#include"Weapon.h"
USING_NS_CC;
using namespace ui;

Weapon::Weapon(cocos2d::Layer * layer, Hero * hero, const char * weaponType, const char * weaponName, bool clickOk) : layer(layer), hero(hero), _weaponType(weaponType), _weaponName(weaponName), clickOk(clickOk)
{
	visibleSize = Director::getInstance()->getVisibleSize();
}

Weapon::~Weapon()
{

}
void Weapon::SetWeaponData()
{
	auto dic = cocos2d::__Dictionary::createWithContentsOfFile(String::createWithFormat("Weapon/%s/%s/%sInfo.plist", _weaponType.c_str(), _weaponName.c_str(), _weaponName.c_str())->getCString());
	_attackPoint = dic->valueForKey("AttackPoint")->intValue();
	_paddleSize = dic->valueForKey("PaddleSize")->floatValue();
	_paddleName = dic->valueForKey("PaddleName")->getCString();
}

Weapon* Weapon::create(cocos2d::Layer * layer, Hero * hero, const char * weaponType, const char * weaponName, bool clickOk)
{
	auto pSprite = new Weapon(layer, hero, weaponType, weaponName, clickOk);
	pSprite->autorelease();
	pSprite->SetWeaponData();
	pSprite->InitSprite();
	return pSprite;
	
}

void Weapon::InitSprite()
{
	node = CSLoader::createNode(String::createWithFormat("Weapon/%s/%s/%s.csb", _weaponType.c_str(), _weaponName.c_str(), _weaponName.c_str())->getCString());
	this->addChild(node);

	Stay();

	skillNode = node->getChildByName("skillNode");
	skillNode->setVisible(false);

	btn = dynamic_cast<Button*>(node->getChildByName("btn"));
	btn->setUserData(this);
	struct callBackFunctorWeapon
	{
		void operator() (Ref* sender) const
		{
			static_cast<Weapon*>(static_cast<Node*>(sender)->getUserData())->ClickWeapon();
		}
	};
	Widget::ccWidgetClickCallback callBackWeapon = callBackFunctorWeapon();
	btn->addClickEventListener(callBackWeapon);
	btn->setEnabled(clickOk);
}

void Weapon::Swing()
{
	auto act = CSLoader::createTimeline(String::createWithFormat("Weapon/%s/%s/%s.csb", _weaponType.c_str(), _weaponName.c_str(), _weaponName.c_str())->getCString());
	act->gotoFrameAndPlay(60, 90, false);
	node->runAction(act);

	this->runAction(Sequence::create(
		DelayTime::create(0.5f),
		CallFunc::create(std::bind(&Weapon::Stay, this)),
		NULL));

	SoundManager::getInstance()->playMySoundLogic("Swing", "mp3");

}
void Weapon::Skill()
{
	auto act = CSLoader::createTimeline(String::createWithFormat("Weapon/%s/%s/%s.csb", _weaponType.c_str(), _weaponName.c_str(), _weaponName.c_str())->getCString());
	act->gotoFrameAndPlay(90, 150, false);
	node->runAction(act);
	
	this->runAction(Sequence::create(
		DelayTime::create(0.25f),
		CallFunc::create(std::bind(&Weapon::SetSkillVisible, this, true)),
		DelayTime::create(0.5f),
		CallFunc::create(std::bind(&Weapon::SetSkillVisible, this, false)),
		DelayTime::create(0.25f),
		CallFunc::create(std::bind(&Weapon::Stay, this)),
		NULL));

	SoundManager::getInstance()->playMySoundLogic("Skill");

}

void Weapon::SetSkillVisible(bool b)
{
	skillNode->setVisible(b);
}

void Weapon::Stay()
{
	auto act = CSLoader::createTimeline(String::createWithFormat("Weapon/%s/%s/%s.csb", _weaponType.c_str(), _weaponName.c_str(), _weaponName.c_str())->getCString());
	act->gotoFrameAndPlay(0, 60, true);
	node->runAction(act);
}

void Weapon::Die()
{
	this->stopAllActions();
	node->stopAllActions();
}


void Weapon::ClickWeapon()
{
	if (clickOk)
	{
		mm = (MapManager*)layer->getChildByName("MapManager");
		clickOk = false;

		int tempWeapon = Utils::GetInstance()->GetWeaponID(hero->getWeaponName().c_str());
		hero->ChangeWeapon(hero->getWeaponType().c_str(), _weaponName.c_str());
		
		auto weapon = Weapon::create(layer, hero, hero->getWeaponType().c_str(), Utils::GetInstance()->GetWeaponName(tempWeapon).c_str(), true);
		weapon->setPosition(getPosition());
		layer->addChild(weapon, ZINDEX_HERO_WEAPON);

		auto mm = MapManager::getInstance();
		int x = mm->GetCurrentRoomData().x;
		int y = mm->GetCurrentRoomData().y;
		mm->map[x][y].data["weapon"] = tempWeapon;

		SoundManager::getInstance()->playMySoundLogic("Item");
		RemoveAll();
	}
	else
	{
		// beep sound
		SoundManager::getInstance()->playMySoundLogic("X");
	}
	Utils::FreeInstance();
}

void Weapon::RemoveAll()
{
	this->removeFromParentAndCleanup(true);
}

