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

//void ItemBomb::SetTextLabel()
//{
//	auto txt = static_cast<cocos2d::ui::Text*>(node->getChildByName("cost"));
//	if (_isShop)
//		txt->setText(String::createWithFormat("%d", _cost)->getCString());
//	else
//		txt->setVisible(false);
//}
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
			hero->IncreaseBombCount(1);
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


//void ItemBomb::InitSprite()
//{
//	auto visibleSize = Director::getInstance()->getVisibleSize();
//	auto origin = Director::getInstance()->getVisibleOrigin();
//
//	node = (CSLoader::createNode("Item/Bomb.csb"));
//	node->setPosition(origin.x, origin.y);
//	this->addChild(node);
//
//	auto txt = static_cast<cocos2d::ui::Text*>(node->getChildByName("cost"));
//	if (_isShop)
//		txt->setText(String::createWithFormat("%d", _cost)->getCString());
//	else
//		txt->setVisible(false);
//
//	btn = dynamic_cast<Button*>(node->getChildByName("btn"));
//	btn->setEnabled(true);
//	btn->setPosition(Vec2(origin.x, origin.y));
//	btn->addTouchEventListener(CC_CALLBACK_2(ItemBomb::onTouch, this));
//
//}
//
//void ItemBomb::onTouch(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type)
//{
//	//if (!clicked)
//	//{
//		switch (type){
//		case Widget::TouchEventType::BEGAN:
//			break;
//		case Widget::TouchEventType::MOVED:
//			break;
//		case Widget::TouchEventType::ENDED:
//		{
//			if (_isShop)
//			{
//				if (hero->getMoneyCount() >= _cost)
//				{
//					hero->DecreaseMoneyCount(_cost);
//					hero->IncreaseBombCount(1);
//					RemoveThis();
////					this->removeAllChildrenWithCleanup(true);
//				}
//			}
//			else
//			{
//				hero->IncreaseBombCount(1);
//				RemoveThis();
//				//this->removeAllChildrenWithCleanup(true);
//			}
//		}
//		break;
//		case Widget::TouchEventType::CANCELED:
//			break;
//		default:
//			break;
//		}
//
//	//}
//}

//cocos2d::Size ItemBomb::getContentSize()
//{
//	return btn->getContentSize();
//}
//void Item::Showdesc(cocos2d::Node * target)
//{
//
//}