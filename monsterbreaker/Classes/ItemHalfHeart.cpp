#include"ItemHalfHeart.h"
USING_NS_CC;
using namespace ui;

ItemHalfHeart::ItemHalfHeart(cocos2d::Layer * layer, Hero * hero, bool isShop) : Item(layer, hero, 2, isShop)
{
	setName("HalfHeart");

}
ItemHalfHeart* ItemHalfHeart::create(cocos2d::Layer * layer, Hero * hero, bool isShop)
{
	auto pSprite = new ItemHalfHeart(layer, hero, isShop);
	pSprite->autorelease();
	pSprite->InitSprite();
	return pSprite;
}
void ItemHalfHeart::ClickEvent()
{
	if (hero->getCurrentHp() < hero->getMaxHp())
	{
		if (_isShop)
		{
			if (hero->getMoneyCount() >= _cost)
			{
				hero->DecreaseMoneyCount(_cost);
				hero->IncreaseCurrentHp(1);
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
			hero->IncreaseCurrentHp(1);
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
