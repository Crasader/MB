#include"Door.h"
USING_NS_CC;
using namespace ui;

Door::Door(const Room & rd, int kDir, const char * mapType)
{
	this->_kDir = kDir;
	_gotoX = rd.x;
	_gotoY = rd.y;
	_lock = rd.lock;
	_roomType = rd.type;
	_roomVisible = rd.visible;
	_mapType = mapType;

	_clickOk = false;
	_isOpen = false;
	_isSecret = false;
}

Door* Door::create(const Room & rd, int kDir, const char * mapType)
{
	auto pSprite = new Door(rd, kDir, mapType);
	pSprite->autorelease();
	pSprite->InitSprite();
	return pSprite;
}

void Door::InitSprite()
{
	auto node = (CSLoader::createNode(String::createWithFormat("Door/%s/Door.csb", _mapType.c_str())->getCString()));
	node->setPosition(this->getContentSize().width / 2, this->getContentSize().height / 2);
	this->addChild(node);

	auto act = CSLoader::createTimeline(String::createWithFormat("Door/%s/Door.csb", _mapType.c_str())->getCString());
	act->gotoFrameAndPlay(0, 0, false);
	node->runAction(act);

	btn = dynamic_cast<Button*>(node->getChildByName("btn"));
	btn->setUserData(this);
	//btn->addTouchEventListener(CC_CALLBACK_2(Door::onTouchDoor, this));

	auto body = PhysicsBody::createBox(btn->getContentSize());
	body->setCollisionBitmask(DOOR_COLLISION_BITMASK);
	body->setDynamic(false);
	node->setPhysicsBody(body);

	this->setVisible(_roomVisible);
}

void Door::Open()
{
	if (!_lock)
	{
		_isOpen = true;
		auto act = CSLoader::createTimeline(String::createWithFormat("Door/%s/Door.csb", _mapType.c_str())->getCString());
		act->gotoFrameAndPlay(0, 60, false);
		this->runAction(act);
	}
}

bool Door::ClickOpen()
{
	_isOpen = true;
	return true;
}

void Door::bombCrush()
{

}

//void Door::setNextHeroLocationAndSave(int x, int y)
//{
//	mapManager->setHeroX(x);
//	mapManager->setHeroY(y);
//	mapManager->Save();
//	hero->Save();
//}
//void Door::moveScene(int roomType, int dir)
//{
//	cocos2d::Scene * scene = nullptr;
//	switch (roomType)
//	{
//	case myEnum::kRoomType::kRTBoss:
//		scene = BossScene::createScene();
//		break;
//	case myEnum::kRoomType::kRTHelp:
//		scene = HelpScene::createScene();
//		break;
//	case myEnum::kRoomType::kRTMonster:
//		scene = MonsterScene::createScene();
//		break;
//	case myEnum::kRoomType::kRTSecret:
//		scene = SecretScene::createScene();
//		break;
//	case myEnum::kRoomType::kRTStart:
//		scene = StartScene::createScene();
//		break;
//	case myEnum::kRoomType::kRTShop:
//		scene = ShopScene::createScene();
//		break;
//	case myEnum::kRoomType::kRTTreasure:
//		scene = TreasureScene::createScene();
//		break;
//	}
//	if (scene != nullptr)
//	{
//		switch (dir)
//		{
//		case myEnum::kDir::kDirEast:
//			Director::getInstance()->replaceScene(TransitionMoveInR::create(0.2, scene));
//			break;
//		case myEnum::kDir::kDirWest:
//			Director::getInstance()->replaceScene(TransitionMoveInL::create(0.2, scene));
//			break;
//		case myEnum::kDir::kDirSouth:
//			Director::getInstance()->replaceScene(TransitionMoveInB::create(0.2, scene));
//			break;
//		case myEnum::kDir::kDirNorth:
//			Director::getInstance()->replaceScene(TransitionMoveInT::create(0.2, scene));
//			break;
//		}
//	}
//}
////
////void Door::onTouchDoor(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type)
////{
////	switch (type){
////	case Widget::TouchEventType::BEGAN:
////		break;
////	case Widget::TouchEventType::MOVED:
////		break;
////	case Widget::TouchEventType::ENDED:
////	{
////		CCLOG("Test!!!!!!!!!!!!");
////		auto door = static_cast<Door *>(dynamic_cast<cocos2d::Node*> (sender)->getUserData());
////		if (door->getClickOk())
////		{
////			if (door->IsOpen())
////			{
////				move(door->getGoToX(), door->getGoToY(), door->getRoomType(), door->getDir());
////			}
////			else
////			{
////				if (door->ClickOpen())
////				{
////					door->Open();
////					mapManager->map[door->getGoToX()][door->getGoToY()].lock = false;
////					mapManager->Save();
////					hero->Save();
////				}
////				else
////				{
////					// X
////					// door sound
////				}
////			}
////		}
////	}
////	break;
////	case Widget::TouchEventType::CANCELED:
////		break;
////	default:
////		break;
////	}
////}
//
//void Door::move(int x, int y, int roomType, int dir)
//{
//	setNextHeroLocationAndSave(x,y);
//	moveScene(roomType, dir);
//}
