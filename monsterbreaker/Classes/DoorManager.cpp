#include "DoorManager.h"
USING_NS_CC;
using namespace ui;

DoorManager::DoorManager(Hero * hero) : hero(hero)
{
	mapManager = MapManager::getInstance();
	_currentSecretRoom = false;
	_secretView = false;
	_secretViewLockOpen = false;

	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();
	contentSize = Size(visibleSize.width / 10, visibleSize.height / 25);
	startPoint = Vec2(0, contentSize.height * 20);

	setMapType(mapManager->getLevelName());
	_currentSecretRoom = (mapManager->GetCurrentRoomData().type == myEnum::kRoomType::kRTSecret);

	visibleSize = Director::getInstance()->getVisibleSize();

	_isMovingLoadingScene = false;
}
DoorManager::~DoorManager()
{
}

DoorManager* DoorManager::create(Hero * hero)
{
	auto pNode = new DoorManager(hero);
	pNode->autorelease();
	return pNode;
}

void DoorManager::Draw(cocos2d::Layer * layer)
{
	this->layer = layer;
	
	auto bg = Sprite::create(cocos2d::String::createWithFormat("Tile/%s/BG.png", getMapType().c_str())->getCString());
	bg->setPosition(Vec2(visibleSize.width / 2 , bg->getContentSize().height / 2 ));
	layer->addChild(bg, ZINDEX_BG);

	int heroX = mapManager->getHeroX();
	int heroY = mapManager->getHeroY();
	
	// top ( x = 0 )
	if (mapManager->IsN())
	{
		Room rd = mapManager->GetRoomData(heroX - 1, heroY);
		if( !_currentSecretRoom ) SetTileFenceLine(myEnum::kDir::kDirNorth, rd.visible);
		else SetTileFenceLine(myEnum::kDir::kDirNorth, rd.exp);

		if (rd.type != myEnum::kRoomType::kRTNone)
		{
			int x = 0;
			int y = 4;
			auto vec = Vec2(startPoint.x + contentSize.width * y + contentSize.width , startPoint.y - contentSize.height * x + contentSize.height / 2 );
			SetTileDoor(vec, 1, 0, rd, myEnum::kDir::kDirNorth);
		}
	}
	else
		SetTileFenceLine(myEnum::kDir::kDirNorth, false);

	// bottom ( x = 19 )
	if (mapManager->IsS())
	{
		Room rd = mapManager->GetRoomData(heroX + 1, heroY);
		if (!_currentSecretRoom) SetTileFenceLine(myEnum::kDir::kDirSouth, rd.visible);
		else SetTileFenceLine(myEnum::kDir::kDirSouth, rd.exp);
		if (rd.type != myEnum::kRoomType::kRTNone)
		{
			int x = 19;
			int y = 4;
			auto vec = Vec2(startPoint.x + contentSize.width * y + contentSize.width , startPoint.y - contentSize.height * x );
			SetTileDoor(vec, 1, 180, rd, myEnum::kDir::kDirSouth);
		}
	}
	else
		SetTileFenceLine(myEnum::kDir::kDirSouth, false);

	// left ( y = 0 )
	if (mapManager->IsW())
	{
		Room rd = mapManager->GetRoomData(heroX, heroY - 1);
		if (!_currentSecretRoom) SetTileFenceLine(myEnum::kDir::kDirWest, rd.visible);
		else SetTileFenceLine(myEnum::kDir::kDirWest, rd.exp);
		if (rd.type != myEnum::kRoomType::kRTNone)
		{
			int x = 9;
			int y = 0;
			auto vec = Vec2(startPoint.x + contentSize.width * y + contentSize.width / 2, startPoint.y - contentSize.height * x );
			SetTileDoor(vec, 0.7129, -90, rd, myEnum::kDir::kDirWest);
		}
	}
	else
		SetTileFenceLine(myEnum::kDir::kDirWest, false);

	// right ( y = 9 )
	if (mapManager->IsE())
	{
		Room rd = mapManager->GetRoomData(heroX, heroY + 1);
		if (!_currentSecretRoom) SetTileFenceLine(myEnum::kDir::kDirEast, rd.visible);
		else SetTileFenceLine(myEnum::kDir::kDirEast, rd.exp);
		if (rd.type != myEnum::kRoomType::kRTNone)
		{
			int x = 9;
			int y = 9;
			auto vec = Vec2(startPoint.x + contentSize.width * y + contentSize.width / 2 , startPoint.y - contentSize.height * x );
			SetTileDoor(vec, 0.7129, 90, rd, myEnum::kDir::kDirEast);
		}
	}
	else
		SetTileFenceLine(myEnum::kDir::kDirEast, false);

	float tempY = visibleSize.height / 10 * 8;

	auto edgeBody = PhysicsBody::createEdgeBox(Size(visibleSize.width - contentSize.width * 2 + contentSize.height / 2, tempY - contentSize.height * 2 + contentSize.height / 2), PhysicsMaterial(1, 1, 0), contentSize.height / 2);
	edgeBody->setCollisionBitmask(WALL_COLLISION_BITMASK); 
	edgeBody->setContactTestBitmask(true);

	auto edgeNode = Node::create();
	edgeNode->setPosition(Vec2(visibleSize.width / 2 , tempY / 2 + contentSize.height / 2 ));
	edgeNode->setPhysicsBody(edgeBody);
	layer->addChild(edgeNode);

	// create a death zone
	auto deathBody = PhysicsBody::createEdgeBox(Size(visibleSize.width - contentSize.width * 1, tempY - contentSize.height * 2));
	deathBody->setCollisionBitmask(DEATH_COLLISION_BITMASK);
	deathBody->setContactTestBitmask(true);
	deathBody->setDynamic(false);

	auto deathNode = Node::create();
	deathNode->setPosition(Vec2(visibleSize.width / 2, tempY / 2 + contentSize.height * 1.25f));
	deathNode->setPhysicsBody(deathBody);
	layer->addChild(deathNode);

	// add door touch event
	auto size = doors.size();
	for (int i = 0; i < size; i++)
	{
		auto btn = doors.at(i)->btn;
		if (btn != nullptr) 	btn->addTouchEventListener(CC_CALLBACK_2(DoorManager::onTouchDoor, this));
	}
	
	

}

void DoorManager::SetTileFenceLine(int kDir, bool hasDoor)
{
	if (kDir == myEnum::kDir::kDirEast)
	{
		for (int x = 0; x < 20; x++)
		{
			if (x == 9 || x == 10)
			{
				if (hasDoor)
				{
					continue;
				}
			}
			SetTileFence(x, 9);
		}
	}
	else if (kDir == myEnum::kDir::kDirWest)
	{
		for (int x = 0; x < 20; x++)
		{
			if (x == 9 || x == 10)
			{
				if (hasDoor)
				{
					continue;
				}
			}
			SetTileFence(x, 0);
		}
	}
	else if (kDir == myEnum::kDir::kDirSouth)
	{
		for (int y = 0; y < 10; y++)
		{
			if (y == 4 || y == 5)
			{
				if (hasDoor)
				{
					continue;
				}
			}
			SetTileFence(19, y);
		}
	}
	else if (kDir == myEnum::kDir::kDirNorth)
	{
		for (int y = 0; y < 10; y++)
		{
			if (y == 4 || y == 5)
			{
				if (hasDoor)
				{
					continue;
				}
			}
			SetTileFence(0, y);
		}
	}
}

void DoorManager::SetTileFence(int x, int y)
{
	auto spr = Sprite::create(cocos2d::String::createWithFormat("Tile/%s/Fence.png", getMapType().c_str())->getCString());
	spr->setPosition(startPoint.x + contentSize.width * y + contentSize.width / 2 , startPoint.y - contentSize.height * x + contentSize.height / 2 );
	layer->addChild(spr, ZINDEX_BRICK_SPRITE);
}

void DoorManager::SetTileDoor(cocos2d::Vec2 vec, float scale, float rotate, const Room & rd, int kDir)
{
	Door * door = nullptr;
	switch (rd.type)
	{
	case myEnum::kRoomType::kRTBoss:
		if (!_currentSecretRoom) door = BossDoor::create(rd, kDir, getMapType().c_str());
		else
		{
			door = SecretDoor::create(rd, kDir, getMapType().c_str());
			if (rd.exp)
			{
				door->setVisible(true);
				door->setLock(false);
			}
			else
			{
				door->setVisible(false);
				door->setLock(true);
			}
			if (_secretView) door->setVisible(true);
			if (_secretViewLockOpen) door->setLock(false);
		}
		break;
	case myEnum::kRoomType::kRTHelp:
		if (!_currentSecretRoom) door = CoinDoor::create(rd, kDir, hero, getMapType().c_str());
		else
		{
			door = SecretDoor::create(rd, kDir, getMapType().c_str());
			if (rd.exp)
			{
				door->setVisible(true);
				door->setLock(false);
			}
			else
			{
				door->setVisible(false);
				door->setLock(true);
			}
			if (_secretView) door->setVisible(true);
			if (_secretViewLockOpen) door->setLock(false);
		}
		break;
	case myEnum::kRoomType::kRTMonster:
		if (!_currentSecretRoom) door = Door::create(rd, kDir, getMapType().c_str());
		else
		{
			door = SecretDoor::create(rd, kDir, getMapType().c_str());
			if (rd.exp)
			{
				door->setVisible(true);
				door->setLock(false);
			}
			else
			{
				door->setVisible(false);
				door->setLock(true);
			}
			if (_secretView) door->setVisible(true);
			if (_secretViewLockOpen) door->setLock(false);
		}
		break;
	case myEnum::kRoomType::kRTSecret:
		if (!_currentSecretRoom)
		{
			door = SecretDoor::create(rd, kDir, getMapType().c_str());
			if (_secretView) door->setVisible(true);
			if (_secretViewLockOpen) door->setLock(false);
		}
		else
		{
			door = SecretDoor::create(rd, kDir, getMapType().c_str());
			if (rd.exp)
			{
				door->setVisible(true);
				door->setLock(false);
			}
			else
			{
				door->setVisible(false);
				door->setLock(true);
			}
			if (_secretView) door->setVisible(true);
			if (_secretViewLockOpen) door->setLock(false);
		}
		break;
	case myEnum::kRoomType::kRTShop:
		if (!_currentSecretRoom) door = KeyDoor::create(rd, kDir, hero, getMapType().c_str());
		else
		{
			door = SecretDoor::create(rd, kDir, getMapType().c_str());
			if (rd.exp)
			{
				door->setVisible(true);
				door->setLock(false);
			}
			else
			{
				door->setVisible(false);
				door->setLock(true);
			}
			if (_secretView) door->setVisible(true);
			if (_secretViewLockOpen) door->setLock(false);
		}
		break;
	case myEnum::kRoomType::kRTStart:
		if (!_currentSecretRoom) door = Door::create(rd, kDir, getMapType().c_str());
		else
		{
			door = SecretDoor::create(rd, kDir, getMapType().c_str());
			if (rd.exp)
			{
				door->setVisible(true);
				door->setLock(false);
			}
			else
			{
				door->setVisible(false);
				door->setLock(true);
			}
			if (_secretView) door->setVisible(true);
			if (_secretViewLockOpen) door->setLock(false);
		}
		break;
	case myEnum::kRoomType::kRTTreasure:
		if (!_currentSecretRoom) door = KeyDoor::create(rd, kDir, hero, getMapType().c_str());
		else
		{
			door = SecretDoor::create(rd, kDir, getMapType().c_str());
			if (rd.exp)
			{
				door->setVisible(true);
				door->setLock(false);
			}
			else
			{
				door->setVisible(false);
				door->setLock(true);
			}
			if (_secretView) door->setVisible(true);
			if (_secretViewLockOpen) door->setLock(false);
		}
		break;
	}
	if (door != nullptr)
	{
		door->setPosition(vec);
		door->setScale(scale);
		door->setRotation(rotate);
		layer->addChild(door, ZINDEX_MOVE_DOOR);

		doors.pushBack(door);
	}

}

void DoorManager::OpenDoors()
{
	for (int i = 0; i < doors.size(); i++)
	{
		doors.at(i)->Open();
	}
}

void DoorManager::SetDoorClickEnable(bool b)
{
	for (int i = 0; i < doors.size(); i++)
	{
		doors.at(i)->setClickOk(b);
	}
}

void DoorManager::onTouchDoor(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type)
{
	switch (type){
	case Widget::TouchEventType::BEGAN:
		break;
	case Widget::TouchEventType::MOVED:
		break;
	case Widget::TouchEventType::ENDED:
	{
		auto door = static_cast<Door *>(dynamic_cast<cocos2d::Node*> (sender)->getUserData());
		if (door->getClickOk())
		{
			if (door->IsOpen())
			{
				if (door->IsDamageDoor()) hero->Damaged(1);
				if (hero->IsAlive()) move(door->getGoToX(), door->getGoToY(), door->getDir());
			}
			else
			{
				if (door->ClickOpen())
				{
					door->Open();
					mapManager->map[door->getGoToX()][door->getGoToY()].lock = false;
					hero->Save();
				}
				else
				{
					// X
					SoundManager::getInstance()->playMySoundLogic("X");
				}
			}
		}
	}
	break;
	case Widget::TouchEventType::CANCELED:
		break;
	default:
		break;
	}
}


void DoorManager::setNextHeroLocationAndSave(int x, int y)
{
	mapManager->setHeroX(x);
	mapManager->setHeroY(y);
	hero->Save();
}
void DoorManager::moveScene(int dir)
{
	cocos2d::Scene * scene = GameScene::createScene();

	if (scene != nullptr)
	{
		switch (dir)
		{
		case myEnum::kDir::kDirEast:
			Director::getInstance()->replaceScene(TransitionMoveInR::create(0.2, scene));
			break;
		case myEnum::kDir::kDirWest:
			Director::getInstance()->replaceScene(TransitionMoveInL::create(0.2, scene));
			break;
		case myEnum::kDir::kDirSouth:
			Director::getInstance()->replaceScene(TransitionMoveInB::create(0.2, scene));
			break;
		case myEnum::kDir::kDirNorth:
			Director::getInstance()->replaceScene(TransitionMoveInT::create(0.2, scene));
			break;
		}
	}
}
void DoorManager::move(int x, int y, int dir)
{
	setNextHeroLocationAndSave(x, y);
	moveScene(dir);
}
void DoorManager::ShowEndingDoor()
{
	auto def = UserDefault::sharedUserDefault();
	auto _un = def->getIntegerForKey("u_ending", 0);

	if (getMapType().compare("G") == 0)
	{
		if (_un == 0 || _un == 1)
		{
			auto spr = EndingDoor::create("MV");
			spr->setPosition(visibleSize.width*0.5f, visibleSize.height * 0.7f);
			layer->addChild(spr, ZINDEX_ENDING_DOOR);
			
			auto btn = spr->btn;
			if (btn != nullptr) 	btn->addTouchEventListener(CC_CALLBACK_2(DoorManager::moveLoadingScene, this));
		}
		else
		{
			auto spr = EndingDoor::create("MV");
			spr->setPosition(visibleSize.width / 3 * 1, visibleSize.height * 0.7f);
			layer->addChild(spr, ZINDEX_ENDING_DOOR);
			auto btn = spr->btn;
			if (btn != nullptr) 	btn->addTouchEventListener(CC_CALLBACK_2(DoorManager::moveLoadingScene, this));

			auto spr2 = EndingDoor::create("HV");
			spr2->setPosition(visibleSize.width / 3 * 2, visibleSize.height * 0.7f);
			layer->addChild(spr2, ZINDEX_ENDING_DOOR);
			auto btn2 = spr2->btn;
			if (btn2 != nullptr) 	btn2->addTouchEventListener(CC_CALLBACK_2(DoorManager::moveLoadingScene, this));

		}
	}
	else if (getMapType().compare("MV") == 0)
	{
		if (_un == 0)
		{
			auto spr = EndingDoor::create("Ending", 1);
			spr->setPosition(visibleSize.width*0.5f, visibleSize.height * 0.7f);
			layer->addChild(spr, ZINDEX_ENDING_DOOR);

			auto btn = spr->btn;
			if (btn != nullptr) 	btn->addTouchEventListener(CC_CALLBACK_2(DoorManager::moveEndingScene, this));
		}
		else
		{
			auto spr = EndingDoor::create("Ending", 1);
			spr->setPosition(visibleSize.width / 3 * 1, visibleSize.height * 0.7f);
			layer->addChild(spr, ZINDEX_ENDING_DOOR);
			auto btn = spr->btn;
			if (btn != nullptr) 	btn->addTouchEventListener(CC_CALLBACK_2(DoorManager::moveEndingScene, this));

			auto spr2 = EndingDoor::create("MC");
			spr2->setPosition(visibleSize.width / 3 * 2, visibleSize.height * 0.7f);
			layer->addChild(spr2, ZINDEX_ENDING_DOOR);
			spr2->setVisible(false);
			spr2->btn->setEnabled(false);
			auto btn2 = spr2->btn;
			if (btn2 != nullptr) 	btn2->addTouchEventListener(CC_CALLBACK_2(DoorManager::moveLoadingScene, this));
			BAWKeyDoors.pushBack(spr2);
		}
	}
	else if (getMapType().compare("MC") == 0)
	{
		if (_un < 4)
		{
			auto spr = EndingDoor::create("Ending", 2);
			spr->setPosition(visibleSize.width*0.5f, visibleSize.height * 0.7f);
			layer->addChild(spr, ZINDEX_ENDING_DOOR);

			auto btn = spr->btn;
			if (btn != nullptr) 	btn->addTouchEventListener(CC_CALLBACK_2(DoorManager::moveEndingScene, this));
		}
		else if(_un == 4)
		{
			auto spr = EndingDoor::create("Ending", 2);
			spr->setPosition(visibleSize.width / 3 * 1, visibleSize.height * 0.7f);
			layer->addChild(spr, ZINDEX_ENDING_DOOR);
			auto btn = spr->btn;
			if (btn != nullptr) 	btn->addTouchEventListener(CC_CALLBACK_2(DoorManager::moveEndingScene, this));

			auto spr2 = EndingDoor::create("Ending", 5);
			spr2->setPosition(visibleSize.width / 3 * 2, visibleSize.height * 0.7f);
			spr2->setScale(2);
			layer->addChild(spr2, ZINDEX_ENDING_DOOR);
			auto btn2 = spr2->btn;
			if (btn2 != nullptr) 	btn2->addTouchEventListener(CC_CALLBACK_2(DoorManager::moveEndingScene, this));
		}
		else if (_un > 4)
		{
			auto spr = EndingDoor::create("Ending", 2);
			spr->setPosition(visibleSize.width / 4 * 1, visibleSize.height * 0.7f);
			layer->addChild(spr, ZINDEX_ENDING_DOOR);
			auto btn = spr->btn;
			if (btn != nullptr) 	btn->addTouchEventListener(CC_CALLBACK_2(DoorManager::moveEndingScene, this));

			auto spr2 = EndingDoor::create("Ending", 5);
			spr2->setPosition(visibleSize.width / 4 * 2, visibleSize.height * 0.7f);
			spr2->setScale(2);
			layer->addChild(spr2, ZINDEX_ENDING_DOOR);
			auto btn2 = spr2->btn;
			if (btn2 != nullptr) 	btn2->addTouchEventListener(CC_CALLBACK_2(DoorManager::moveEndingScene, this));

			auto spr3 = EndingDoor::create("MM");
			spr3->setPosition(visibleSize.width / 4 * 3, visibleSize.height * 0.7f);
			layer->addChild(spr3, ZINDEX_ENDING_DOOR);
			spr3->setVisible(false);
			spr3->btn->setEnabled(false);
			auto btn3 = spr3->btn;
			if (btn3 != nullptr) 	btn3->addTouchEventListener(CC_CALLBACK_2(DoorManager::moveLoadingScene, this));
			TKeyDoors.pushBack(spr3);
		}
	}
	else if (getMapType().compare("HV") == 0)
	{
		if (_un == 2)
		{
			auto spr = EndingDoor::create("Ending",3);
			spr->setPosition(visibleSize.width*0.5f, visibleSize.height * 0.7f);
			layer->addChild(spr, ZINDEX_ENDING_DOOR);

			auto btn = spr->btn;
			if (btn != nullptr) 	btn->addTouchEventListener(CC_CALLBACK_2(DoorManager::moveEndingScene, this));
		}
		else
		{
			auto spr = EndingDoor::create("Ending",3);
			spr->setPosition(visibleSize.width / 3 * 1, visibleSize.height * 0.7f);
			layer->addChild(spr, ZINDEX_ENDING_DOOR);
			auto btn = spr->btn;
			if (btn != nullptr) 	btn->addTouchEventListener(CC_CALLBACK_2(DoorManager::moveEndingScene, this));

			auto spr2 = EndingDoor::create("HC");
			spr2->setPosition(visibleSize.width / 3 * 2, visibleSize.height * 0.7f);
			layer->addChild(spr2, ZINDEX_ENDING_DOOR);
			auto btn2 = spr2->btn;
			if (btn2 != nullptr) 	btn2->addTouchEventListener(CC_CALLBACK_2(DoorManager::moveLoadingScene, this));
			spr2->setVisible(false);
			spr2->btn->setEnabled(false);
			BAWKeyDoors.pushBack(spr2);
		}
	}
	else if (getMapType().compare("HC") == 0)
	{
		if (_un <= 4)
		{
			auto spr = EndingDoor::create("Ending", 4);
			spr->setPosition(visibleSize.width*0.5f, visibleSize.height * 0.7f);
			layer->addChild(spr, ZINDEX_ENDING_DOOR);

			auto btn = spr->btn;
			if (btn != nullptr) 	btn->addTouchEventListener(CC_CALLBACK_2(DoorManager::moveEndingScene, this));
		}
		else if (_un >= 5)
		{
			auto spr = EndingDoor::create("Ending", 4);
			spr->setPosition(visibleSize.width / 4 * 1, visibleSize.height * 0.7f);
			layer->addChild(spr, ZINDEX_ENDING_DOOR);
			auto btn = spr->btn;
			if (btn != nullptr) 	btn->addTouchEventListener(CC_CALLBACK_2(DoorManager::moveEndingScene, this));

			auto spr2 = EndingDoor::create("Ending", 5);
			spr2->setPosition(visibleSize.width / 4 * 2, visibleSize.height * 0.7f);
			spr2->setScale(2);
			layer->addChild(spr2, ZINDEX_ENDING_DOOR);
			auto btn2 = spr2->btn;
			if (btn2 != nullptr) 	btn2->addTouchEventListener(CC_CALLBACK_2(DoorManager::moveEndingScene, this));

			auto spr3 = EndingDoor::create("MM");
			spr3->setPosition(visibleSize.width / 4 * 3, visibleSize.height * 0.7f);
			layer->addChild(spr3, ZINDEX_ENDING_DOOR);
			spr3->setVisible(false);
			spr3->btn->setEnabled(false);
			auto btn3 = spr3->btn;
			if (btn3 != nullptr) 	btn3->addTouchEventListener(CC_CALLBACK_2(DoorManager::moveLoadingScene, this));
			TKeyDoors.pushBack(spr3);
		}
	}
	else if (getMapType().compare("MM") == 0)
	{
		auto spr = EndingDoor::create("Ending", 6);
		spr->setPosition(visibleSize.width*0.5f, visibleSize.height * 0.7f);
		layer->addChild(spr, ZINDEX_ENDING_DOOR);

		auto btn = spr->btn;
		if (btn != nullptr) 	btn->addTouchEventListener(CC_CALLBACK_2(DoorManager::moveEndingScene, this));
	}
}

void DoorManager::moveLoadingScene(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type)
{
	switch (type){
	case Widget::TouchEventType::BEGAN:
		break;
	case Widget::TouchEventType::MOVED:
		break;
	case Widget::TouchEventType::ENDED:
	{
		hero->Save();
		_isMovingLoadingScene = true;
		std::string str = static_cast<EndingDoor*>(static_cast<cocos2d::ui::Button*> (sender)->getUserData())->getType();
		auto scene = LoadingScene::createScene(str.c_str());
		Director::getInstance()->replaceScene(TransitionFade::create(0.5f, scene));
	}
	break;
	case Widget::TouchEventType::CANCELED:
		break;
	default:
		break;
	}

}

void DoorManager::moveEndingScene(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type)
{
	switch (type){
	case Widget::TouchEventType::BEGAN:
		break;
	case Widget::TouchEventType::MOVED:
		break;
	case Widget::TouchEventType::ENDED:
	{
		hero->Save();
		_isMovingLoadingScene = true;
		int endingNum = static_cast<EndingDoor*>(static_cast<cocos2d::ui::Button*> (sender)->getUserData())->getEndingNum();
		auto scene = EndingScene::createScene(endingNum);
		Director::getInstance()->replaceScene(TransitionFade::create(0.5f, scene));
	}
	break;
	case Widget::TouchEventType::CANCELED:
		break;
	default:
		break;
	}

}

void DoorManager::update(float dt)
{
	if (hero->HasItem(ITEM_BLACK_AND_WHITE) || hero->HasItem(ITEM_TRUTH))
	{
		int BAWK_cnt = BAWKeyDoors.size();
		for (int i = 0; i < BAWK_cnt; i++)
		{
			auto endingDoor = BAWKeyDoors.at(i);
			endingDoor->setVisible(true);
			endingDoor->btn->setEnabled(true);
		}
		int TK_cnt = TKeyDoors.size();
		for (int i = 0; i < TK_cnt; i++)
		{
			auto endingDoor = TKeyDoors.at(i);
			endingDoor->setVisible(true);
			endingDoor->btn->setEnabled(true);
		}
		this->pause();
	}
}
void DoorManager::visibleAllSecretDoor(bool b)
{
	int cnt = doors.size();
	for (int i = 0; i < cnt; i++){
		auto obj = doors.at(i);
		if (obj->_isSecret)
			obj->setVisible(b);
	}
}
void DoorManager::OpenAllSecretDoor()
{
	int cnt = doors.size();
	for (int i = 0; i < cnt; i++){
		auto obj = doors.at(i);
		if (obj->_isSecret)
		{
			obj->setLock(false);
			obj->setVisible(true);
			obj->Open();
		}
	}
}


