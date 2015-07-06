#include"ItemHeart.h"
USING_NS_CC;
using namespace ui;

ItemHeart::ItemHeart(cocos2d::Layer * layer, Hero * hero, bool isShop) : Item(layer, hero, 3, isShop)
{
	setName("Heart");

}
ItemHeart* ItemHeart::create(cocos2d::Layer * layer, Hero * hero, bool isShop)
{
	auto pSprite = new ItemHeart(layer, hero, isShop);
	pSprite->autorelease();
	pSprite->InitSprite();
	return pSprite;
}

void ItemHeart::ClickEvent()
{
	if (hero->getCurrentHp() < hero->getMaxHp())
	{
		if (_isShop)
		{
			if (hero->getMoneyCount() >= _cost)
			{
				hero->DecreaseMoneyCount(_cost);
				hero->IncreaseCurrentHp(2);
				RemoveThis();
			}
			else
			{
				// beep sound
				SoundManager::getInstance()->playMySoundLogic("X");
			}
		}
		else
		{
			hero->IncreaseCurrentHp(2);
			RemoveThis();
		}
	}
	else
	{
		// beep sound
		SoundManager::getInstance()->playMySoundLogic("X");
	}
}
