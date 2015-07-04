#include "ChestItem.h"
USING_NS_CC;
using namespace ui;

ChestItem::ChestItem(cocos2d::Layer * layer, Hero * hero, int itemID, bool isShop) : layer(layer), hero(hero), _itemID(itemID), _isShop(isShop)
{

}
void ChestItem::InitChestItemData()
{
	auto dic = __Dictionary::createWithContentsOfFile("Item/Item.plist");
	auto item = (cocos2d::__Dictionary *)dic->objectForKey(String::createWithFormat("%d", _itemID)->getCString());

	_itemName = item->valueForKey("ItemName")->getCString();
	_desc = item->valueForKey("Desc")->getCString();
	_cost = item->valueForKey("Cost")->intValue();	

	node = CSLoader::createNode("Item/ChestItem.csb");
	this->addChild(node);
	
	btn = (cocos2d::ui::Button *)node->getChildByName("btn");
	image = (cocos2d::Sprite *)node->getChildByName("image");

	auto cache = SpriteFrameCache::getInstance();
	cache->addSpriteFramesWithFile("Item/ItemImage.plist", "Item/ItemImage.png");
	image->setDisplayFrame(cache->getSpriteFrameByName(String::createWithFormat("Item/%s.png", _itemName.c_str())->getCString()));

	SetTextLabel();

	// btn
	btn->setUserData(this);
	struct callBackFunctorChestItem
	{
		void operator() (Ref* sender) const
		{
			static_cast<ChestItem*>(static_cast<Node*>(sender)->getUserData())->ClickChestItem();
		}
	};
	Widget::ccWidgetClickCallback callBackChestItem= callBackFunctorChestItem();
	btn->addClickEventListener(callBackChestItem);
	btn->setEnabled(_isShop);
}
ChestItem* ChestItem::create(cocos2d::Layer * layer, Hero * hero, int itemID, bool isShop)
{
	auto pSprite = new ChestItem(layer, hero, itemID, isShop);
	pSprite->autorelease();
	pSprite->InitChestItemData();
	return pSprite;
}

void ChestItem::SetTextLabel()
{
	auto txt = static_cast<cocos2d::ui::Text*>(node->getChildByName("cost"));
	if (_isShop)
		txt->setText(String::createWithFormat("%d", _cost)->getCString());
	else
		txt->setVisible(false);
}

void ChestItem::ClickChestItem()
{
	//
	CCLOG("Clicked Chest Item");
	if (hero->getMoneyCount() >= _cost)
	{
		hero->DecreaseMoneyCount(_cost);
		hero->SetItem(_itemID);

		auto effectManager = static_cast<EffectManager*>(layer->getChildByName("EffectManager"));
		effectManager->ShowItemDes(_itemID);

		auto mm = MapManager::getInstance();
		int x = mm->GetCurrentRoomData().x;
		int y = mm->GetCurrentRoomData().y;
		mm->map[x][y].data["ChestItemClicked"] = 1;

		RemoveThis();
	}
	else
	{
		// beep sound
	}
}

void ChestItem::RemoveThis()
{
	this->removeFromParentAndCleanup(true);
}

