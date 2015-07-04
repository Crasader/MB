#include "ItemSoulHeart.h"
USING_NS_CC;
using namespace ui;

ItemSoulHeart::ItemSoulHeart(cocos2d::Layer * layer, Hero * hero, bool isShop) : Item(layer, hero, 3, isShop)
{
	setName("SoulHeart");

}
ItemSoulHeart* ItemSoulHeart::create(cocos2d::Layer * layer, Hero * hero, bool isShop)
{
	auto pSprite = new ItemSoulHeart(layer, hero, isShop);
	pSprite->autorelease();
	pSprite->InitSprite();
	return pSprite;
}

void ItemSoulHeart::ClickEvent()
{
	if (hero->getCurrentSp() < hero->getMaxSp())
	{
		if (_isShop)
		{
			if (hero->getMoneyCount() >= _cost)
			{
				hero->DecreaseMoneyCount(_cost);
				hero->IncreaseCurrentSp(2);
				//					SaveShopItem1ClickedData();
//				SoundManager::getInstance()->playMySoundLogic("PickUpCoin");
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
			hero->IncreaseCurrentSp(2);
//			SoundManager::getInstance()->playMySoundLogic("PickUpCoin");
			RemoveThis();
		}
	}
	else
	{
		// beep sound
		SoundManager::getInstance()->playMySoundLogic("X");
	}
}

