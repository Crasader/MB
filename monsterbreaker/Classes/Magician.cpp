#include "Magician.h"
#include "Definitions.h"
USING_NS_CC;

Magician::Magician() 
{
	_name = "Magician";
	_aniName = "Magician";
	_weaponType = "Staff";
}
Magician::~Magician()
{
}

Magician* Magician::create()
{
	auto pSprite = new Magician();
	pSprite->SetHeroData();

	auto cache = SpriteFrameCache::sharedSpriteFrameCache();
	cache->addSpriteFramesWithFile(
		String::createWithFormat("%s/%s/%sImage.plist", pSprite->getType().c_str(), pSprite->getName().c_str(), pSprite->getName().c_str())->getCString(),
		String::createWithFormat("%s/%s/%s.png", pSprite->getType().c_str(), pSprite->getName().c_str(), pSprite->getName().c_str())->getCString()
		);

	if (pSprite->initWithSpriteFrameName(String::createWithFormat("%s.png", pSprite->getName().c_str())->getCString()))
	{
		pSprite->autorelease();
		pSprite->InitSprite();
		pSprite->SetWeapon(pSprite->getWeaponType().c_str(), pSprite->getWeaponName().c_str());
		return pSprite;
	}
	CC_SAFE_DELETE(pSprite);
	return NULL;
}

void Magician::SkillUse()
{
	if (IsSkillUse())
	{
		switch (_skillID)
		{
		case SKILL_FIRST_AID:
			if (!IsFullHp())
			{
				weapon->Skill();
				EmptySkillPoint();
				IncreaseCurrentHp(2);
//				DecreaseCurrentSp(1);
				// effect & sound
				auto effectManager = static_cast<EffectManager*>(layer->getChildByName("EffectManager"));
				effectManager->HealEffect(this->getPosition());
				_skillUseState = true;
			}
			else
			{
				// fail sound
				SoundManager::getInstance()->playMySoundLogic("X");
			}
			break;

		case SKILL_FIRE_BALL:
			if (IsEnoughSp(1))
			{
				EmptySkillPoint();
//				DecreaseCurrentSp(1);
				_skillUseState = true;
			}
			break;

		case SKILL_LIGHTNING:
			if (IsEnoughSp(2))
			{
				EmptySkillPoint();
//				DecreaseCurrentSp(2);
				_skillUseState = true;
			}
			break;

		}
	}
}

void Magician::DoSkillEvent(cocos2d::Vec2 touch)
{
	switch (_skillID)
	{
	case SKILL_FIRE_BALL:
	{
		weapon->Skill();
		auto effectManager = static_cast<EffectManager*>(layer->getChildByName("EffectManager"));
		effectManager->ShiningEffect(getPosition());
		effectManager->FireBallEffect(getPosition(), touch);
	}
	break;

	case SKILL_LIGHTNING:
	{
		weapon->Skill();
		auto effectManager = static_cast<EffectManager*>(layer->getChildByName("EffectManager"));
		effectManager->ShiningEffect(getPosition());
		effectManager->LightningEffect(touch, SKILL_LIGHTNING_DAMAGE);
	}
	break;

	}
}

bool Magician::IsEnoughSp(int needSp)
{
	bool result = false;
	if (getCurrentSp() >= needSp)
		result = true;
	return result;
}

void Magician::DecreaseCurrentSp(int i)
{
	if (_currentSp - i <= 0)
	{
		int temp = i - _currentSp;
		_currentSp = 0;
		DecreaseCurrentHp(temp);
	}
	else
	{
		_currentSp -= i;
		SoundManager::getInstance()->playMySoundLogic("Solid");
		// effect
		auto effectManager = static_cast<EffectManager*>(layer->getChildByName("EffectManager"));
		effectManager->BarrierEffect(this->getPosition());
	}
}
void Magician::Damaged(int i)
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
			this->runAction(
				Sequence::create(
				TintTo::create(0.1, 255, 0, 0),
				Blink::create(0.2, 2),
				TintTo::create(0.1, color.r, color.g, color.b),
				CallFunc::create(std::bind(&GameObject::SetBodyEnable, this, true)),
				CallFunc::create(std::bind(&GameObject::setDamagedState, this, false)),
				NULL));

			DecreaseCurrentSp(i);
		}
	}
}



