#include "ItemKey.h"
USING_NS_CC;
using namespace ui;

ItemKey::ItemKey(cocos2d::Layer * layer, Hero * hero, bool isShop) : Item(layer, hero, 2, isShop)
{
	setName("Key");

}
ItemKey* ItemKey::create(cocos2d::Layer * layer, Hero * hero, bool isShop)
{
	auto pSprite = new ItemKey(layer, hero, isShop);
	pSprite->autorelease();
	pSprite->InitSprite();
	return pSprite;
}

void ItemKey::ClickEvent()
{
	if (hero->getKeyCount() < ITEM_MAX_COUNT)
	{
		if (_isShop)
		{
			if (hero->getMoneyCount() >= _cost)
			{
				hero->DecreaseMoneyCount(_cost);
				hero->IncreaseKeyCount(1);
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
			hero->IncreaseKeyCount(1);
			RemoveThis();
		}
	}
	else
	{
		// beep sound
		SoundManager::getInstance()->playMySoundLogic("X");
	}
}
