#include "ItemCoin.h"
USING_NS_CC;
using namespace ui;

ItemCoin::ItemCoin(cocos2d::Layer * layer, Hero * hero) : Item(layer, hero, 0, false)
{
	setName("Coin");
}
ItemCoin* ItemCoin::create(cocos2d::Layer * layer, Hero * hero)
{
	auto pSprite = new ItemCoin(layer, hero);
	pSprite->autorelease();
	pSprite->InitSprite();
	return pSprite;
}

void ItemCoin::SetTextLabel()
{
	// nothing >> no cost label
}
void ItemCoin::ClickEvent()
{
	if (hero->getMoneyCount() < ITEM_MAX_COUNT)
	{
		hero->IncreaseMoneyCount(1);
		RemoveThis();
	}
	else
	{
		// beep sound
		SoundManager::getInstance()->playMySoundLogic("X");
	}
}
