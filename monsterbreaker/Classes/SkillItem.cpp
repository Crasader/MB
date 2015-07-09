#include "SkillItem.h"
USING_NS_CC;
using namespace ui;

SkillItem::SkillItem(cocos2d::Layer * layer, Hero * hero, int skillID, bool isShop, int currentPoint) : layer(layer), hero(hero), _skillID(skillID), _isShop(isShop), currentPoint(currentPoint)
{
	_cost = 7;
}
void SkillItem::InitSkillItemData()
{
	auto dic = __Dictionary::createWithContentsOfFile("Skill/SkillData.plist");
	auto item = (cocos2d::__Dictionary *)dic->objectForKey(String::createWithFormat("%d", _skillID)->getCString());

	_cost = item->valueForKey("Cost")->intValue();
	maxPoint = item->valueForKey("MaxPoint")->intValue();
	if (_isShop) currentPoint = maxPoint;

	node = CSLoader::createNode("Skill/SkillItem.csb");
	this->addChild(node);
	
	btn = (cocos2d::ui::Button *)node->getChildByName("btn");
	image = (cocos2d::Sprite *)node->getChildByName("image");

	auto sm = (SkillManager *)layer->getChildByName("SkillManager");
	image->setDisplayFrame(sm->GetSkillSpriteFrame(_skillID));
	image->setRotation(90);
	
	SetTextLabel();

	// btn
	btn->setUserData(this);
	struct callBackFunctorSkillItem
	{
		void operator() (Ref* sender) const
		{
			static_cast<SkillItem*>(static_cast<Node*>(sender)->getUserData())->ClickSkillItem();
		}
	};
	Widget::ccWidgetClickCallback callBackSkillItem= callBackFunctorSkillItem();
	btn->addClickEventListener(callBackSkillItem);
}
SkillItem* SkillItem::create(cocos2d::Layer * layer, Hero * hero, int itemID, bool isShop, int currentPoint)
{
	auto pSprite = new SkillItem(layer, hero, itemID, isShop, currentPoint);
	pSprite->autorelease();
	pSprite->InitSkillItemData();
	return pSprite;
}

void SkillItem::SetTextLabel()
{
	auto txt = static_cast<cocos2d::ui::Text*>(node->getChildByName("cost"));
	if (_isShop)
		txt->setText(String::createWithFormat("%d", _cost)->getCString());
	else
		txt->setVisible(false);
}

void SkillItem::ClickSkillItem()
{
	if (_isShop)
	{
		if (hero->getMoneyCount() >= _cost)
		{
			hero->DecreaseMoneyCount(_cost);
			
			// change shop skill item
			int tempSkillID = hero->getSkillID();
			auto newSkillItem = SkillItem::create(layer, hero, tempSkillID, false, hero->getSkillCurrentPoint());
			newSkillItem->setPosition(this->getPosition());
			layer->addChild(newSkillItem, ZINDEX_ITEM_SPRITE, myEnum::kMyTag::kSkillItemTag);

			// change hero skill
			hero->SetSkill(this);
			auto sm = (SkillManager *)layer->getChildByName("SkillManager");
			sm->SetSkillImage();
			sm->CheckSkillUseable();

			SoundManager::getInstance()->playMySoundLogic("Item");

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
		// change shop skill item
		int tempSkillID = hero->getSkillID();

		auto newSkillItem = SkillItem::create(layer, hero, tempSkillID, false, hero->getSkillCurrentPoint());
		newSkillItem->setPosition(this->getPosition());
		layer->addChild(newSkillItem, ZINDEX_ITEM_SPRITE, myEnum::kMyTag::kSkillItemTag);

		// change hero skill
		hero->SetSkill(this);
		auto sm = (SkillManager *)layer->getChildByName("SkillManager");
		sm->SetSkillImage();
		sm->CheckSkillUseable();

		RemoveThis();
	}

}

void SkillItem::RemoveThis()
{
	this->removeFromParentAndCleanup(true);
}

