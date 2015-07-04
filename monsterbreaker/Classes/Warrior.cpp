#include"Warrior.h"
#include "Definitions.h"
#include "Utils.h"
USING_NS_CC;

Warrior::Warrior()
{
	_name = "Warrior";
	_aniName = "Warrior";
	_weaponType = "Sword";
}

Warrior::~Warrior()
{
}

Warrior* Warrior::create()
{
	auto pSprite = new Warrior();
	pSprite->SetHeroData();

	auto cache = SpriteFrameCache::sharedSpriteFrameCache();
	cache->addSpriteFramesWithFile(
		String::createWithFormat("%s/%s/%sImage.plist", pSprite->getType().c_str(), pSprite->getName().c_str(), pSprite->getName().c_str())->getCString(),
		String::createWithFormat("%s/%s/%s.png", pSprite->getType().c_str(), pSprite->getName().c_str(), pSprite->getName().c_str())->getCString()
		);
	if (pSprite->initWithSpriteFrameName(String::createWithFormat("%s.png", pSprite->getName().c_str())->getCString()))
	{
		pSprite->autorelease();
//		pSprite->setWeaponName("DragonSlayer");
		pSprite->InitSprite();
		pSprite->SetWeapon(pSprite->getWeaponType().c_str(), pSprite->getWeaponName().c_str());

		return pSprite;
	}
	CC_SAFE_DELETE(pSprite);
	return NULL;
}

void Warrior::DecreaseCurrentSp(int i)
{
	if (_currentSp - i <= 0)
	{
		_maxSp = 0;
		int temp = i - _currentSp;
		_currentSp = 0;
		DecreaseCurrentHp(temp);
	}
	else
	{
		_currentSp -= i;
		_maxSp = (_currentSp + 1) / 2 * 2;
		SoundManager::getInstance()->playMySoundLogic("Solid");
	}
}
void Warrior::Damaged(int i)
{
	if (IsAlive())
	{
		if (!IsDamaged())
		{
			_damagedState = true;
			this->getPhysicsBody()->setEnable(false);
			//Animate
			auto color = this->getColor();
			auto sprite = Sprite::create();
			////auto spawn = Spawn::create(TintTo::create(0.1, 255, 0, 0), Blink::create(0.1, 2));
			this->runAction(
				Sequence::create(
				TintTo::create(0.1, 255, 0, 0), 
				Blink::create(0.2, 2), 
				TintTo::create(0.1, color.r, color.g, color.b), 
				CallFunc::create(std::bind(&GameObject::SetBodyEnable, this, true)), 
				CallFunc::create(std::bind(&GameObject::setDamagedState, this, false)), 
				NULL));

			DecreaseCurrentSp(i);
//			SoundManager::getInstance()->playMySoundLogic("HeroDamaged");
		}
	}
}

void Warrior::SkillUse()
{
	if (IsSkillUse())
	{
		if (!IsFullHp())
		{
			weapon->Skill();
			EmptySkillPoint();
			IncreaseCurrentHp(2);	// only First Aid
			// effect & sound
			auto effectManager = static_cast<EffectManager*>(layer->getChildByName("EffectManager"));
			effectManager->HealEffect(this->getPosition());
		}
		else
		{
			// fail sound
		}
	}
}