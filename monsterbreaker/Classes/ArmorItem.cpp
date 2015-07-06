#include "ArmorItem.h"
USING_NS_CC;
using namespace ui;

ArmorItem::ArmorItem(cocos2d::Layer * layer, Hero * hero, int armorID, bool isShop) : layer(layer), hero(hero), _armorID(armorID), _isShop(isShop)
{
	_cost = 4;
}
void ArmorItem::InitArmorItemData()
{
	node = CSLoader::createNode("Armor/Armor.csb");
	this->addChild(node);
	
	btn = (cocos2d::ui::Button *)node->getChildByName("btn");
	image = (cocos2d::Sprite *)node->getChildByName("image");
	
	SetTextLabel();

	// btn
	btn->setUserData(this);
	struct callBackFunctorArmorItem
	{
		void operator() (Ref* sender) const
		{
			static_cast<ArmorItem*>(static_cast<Node*>(sender)->getUserData())->ClickArmorItem();
		}
	};
	Widget::ccWidgetClickCallback callBackArmorItem= callBackFunctorArmorItem();
	btn->addClickEventListener(callBackArmorItem);

	// armor data
	auto cache = SpriteFrameCache::getInstance();
	switch (_armorID)
	{
	case ITEM_ARMOR_NORMAL_ARMOR:
		_cost = 4;
		_armorPoint = 2;
		image->setDisplayFrame(cache->getSpriteFrameByName("Armor/NormalArmor.png"));
		break;
	case ITEM_ARMOR_GOLDEN_ARMOR:
		_cost = 6;
		_armorPoint = 4;
		image->setDisplayFrame(cache->getSpriteFrameByName("Armor/GoldenArmor.png"));
		break;
	}

}
ArmorItem* ArmorItem::create(cocos2d::Layer * layer, Hero * hero, int itemID, bool isShop)
{
	auto pSprite = new ArmorItem(layer, hero, itemID, isShop);
	pSprite->autorelease();
	pSprite->InitArmorItemData();
	return pSprite;
}

void ArmorItem::SetTextLabel()
{
	auto txt = static_cast<cocos2d::ui::Text*>(node->getChildByName("cost"));
	if (_isShop)
		txt->setText(String::createWithFormat("%d", _cost)->getCString());
	else
		txt->setVisible(false);
}

void ArmorItem::ClickArmorItem()
{
	if (_isShop)
	{
		if (hero->getMoneyCount() >= _cost)
		{
			hero->DecreaseMoneyCount(_cost);			
			hero->IncreaseMaxSp(_armorPoint);
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
		hero->IncreaseMaxSp(_armorPoint);
		RemoveThis();
	}

}

void ArmorItem::RemoveThis()
{
	this->removeFromParentAndCleanup(true);
}

