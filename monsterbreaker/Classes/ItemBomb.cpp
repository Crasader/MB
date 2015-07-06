#include"ItemBomb.h"
USING_NS_CC;
using namespace ui;

ItemBomb::ItemBomb(cocos2d::Layer * layer, Hero * hero, bool isShop) : Item(layer, hero, 2, isShop)
{
	setName("Bomb");
}
ItemBomb* ItemBomb::create(cocos2d::Layer * layer, Hero * hero, bool isShop)
{
	auto pSprite = new ItemBomb(layer, hero, isShop);
	pSprite->autorelease();
	pSprite->InitSprite();
	return pSprite;
}

void ItemBomb::ClickEvent()
{
	if (hero->getBombCount() < ITEM_MAX_COUNT)
	{
		if (_isShop)
		{
			if (hero->getMoneyCount() >= _cost)
			{
				hero->DecreaseMoneyCount(_cost);
				hero->IncreaseBombCount(1);
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
			hero->IncreaseBombCount(1);
			RemoveThis();
		}
	}
	else
	{
		// beep sound
		SoundManager::getInstance()->playMySoundLogic("X");
	}
}

