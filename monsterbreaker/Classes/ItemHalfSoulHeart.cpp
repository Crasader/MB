#include "ItemHalfSoulHeart.h"
USING_NS_CC;
using namespace ui;

ItemHalfSoulHeart::ItemHalfSoulHeart(cocos2d::Layer * layer, Hero * hero, bool isShop) : Item(layer, hero, 2, isShop)
{
	setName("HalfSoulHeart");
}
ItemHalfSoulHeart* ItemHalfSoulHeart::create(cocos2d::Layer * layer, Hero * hero, bool isShop)
{
	auto pSprite = new ItemHalfSoulHeart(layer, hero, isShop);
	pSprite->autorelease();
	pSprite->InitSprite();
	return pSprite;
}
void ItemHalfSoulHeart::ClickEvent()
{
	if (hero->getCurrentSp() < hero->getMaxSp())
	{
		if (_isShop)
		{
			if (hero->getMoneyCount() >= _cost)
			{
				hero->DecreaseMoneyCount(_cost);
				hero->IncreaseCurrentSp(1);
//				SaveShopItem1ClickedData();
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
			hero->IncreaseCurrentSp(1);
//			SoundManager::getInstance()->playMySoundLogic("PickUpCoin");
			RemoveThis();
		}
	}
	else
	{
		SoundManager::getInstance()->playMySoundLogic("X");
		// beep sound
	}
}
