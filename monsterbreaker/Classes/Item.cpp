#include "Item.h"
USING_NS_CC;
using namespace ui;

Item::Item(cocos2d::Layer * layer, Hero * hero, int cost, int isShop) : layer(layer), hero(hero), _cost(cost), _isShop(isShop)
{
}
void Item::RemoveThis()
{
//	this->removeAllChildrenWithCleanup(true);
//	layer->removeChild(this);
	this->removeFromParentAndCleanup(true);
}

void Item::InitSprite()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();

	node = CSLoader::createNode(String::createWithFormat("Item/%s.csb", getName().c_str())->getCString());
	node->setPosition(origin.x, origin.y);
	this->addChild(node);

	SetTextLabel();

	btn = dynamic_cast<Button*>(node->getChildByName("btn"));
	btn->setEnabled(true);
	btn->setPosition(Vec2(origin.x, origin.y));
	btn->addTouchEventListener(CC_CALLBACK_2(Item::onTouch, this));

	auto body = PhysicsBody::createCircle(getContentSize().width*0.5f, PhysicsMaterial(100, 1, 0));
	body->setGravityEnable(false);
	this->setPhysicsBody(body);
}
void Item::onTouch(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type)
{
	switch (type){
	case Widget::TouchEventType::BEGAN:
		break;
	case Widget::TouchEventType::MOVED:
		break;
	case Widget::TouchEventType::ENDED:
	{
		ClickEvent();
	}
	break;
	case Widget::TouchEventType::CANCELED:
		break;
	default:
		break;
	}
}

cocos2d::Size Item::getContentSize()
{
	return btn->getContentSize();
}

void Item::SetTextLabel()
{
	auto txt = static_cast<cocos2d::ui::Text*>(node->getChildByName("cost"));
	if (_isShop)
		txt->setText(String::createWithFormat("%d", _cost)->getCString());
	else
		txt->setVisible(false);
}
void Item::ClickEvent()
{

}

//
//void Item::SaveShopItem1ClickedData()
//{
//	auto mm = MapManager::getInstance();
//	int x = mm->GetCurrentRoomData().x;
//	int y = mm->GetCurrentRoomData().y;
//	mm->map[x][y].data["shopItem1Clicked"] = 1;
//
//}
