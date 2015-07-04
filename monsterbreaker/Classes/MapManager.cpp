#include "MapManager.h"
#include <stdlib.h>
USING_NS_CC;

MapManager* MapManager::instance = nullptr;
void MapManager::debug(const char * temp)
{
	String str;
	str.appendWithFormat("%s\n", temp);

	for (int i = 0; i < SIZE_X; i++)
	{
		for (int j = 0; j < SIZE_Y; j++)
		{
//			str.appendWithFormat("%d ", map[i][j].type);
//			str.appendWithFormat("%d%d%d%d ", map[i][j].type, map[i][j].exp, map[i][j].lock, map[i][j].visible);
//			str.appendWithFormat("%d%d%d ", map[i][j].type, map[i][j].cnt_sideroom, map[i][j].priority);
			str.appendWithFormat("%d%s ", map[i][j].type, map[i][j].lock ? "t" : "f");
//			str.appendWithFormat("count room : %d ", _cntRoom);
//			str.appendWithFormat("count celar room : %d ", _clearCntRoom);
		}
		str.appendWithFormat("\n");
	}

	CCLOG(str.getCString());
}
void MapManager::create()
{
	for (int i = 0; i < cnt_gen; i++)
	{
		if (i != 0)	// branch
			createBranch(false);
		else			// root
			createBranch(true);
	}
	setRoomType();
}
MapManager* MapManager::getInstance()
{
	if (instance == nullptr)
	{
		instance = new MapManager();
	}
	return instance;
}
void MapManager::freeInstance()
{
	if (instance != nullptr)
	{
		CC_SAFE_DELETE(instance);
	}
}

void MapManager::createBranch(bool first)
{
	if (first)
	{
		std::vector<int> dir;
		int r1 = 0;
		int r2 = 0;
		do
		{
			r1 = rand() % 4;
			r2 = rand() % 4;
		} while (r1 == r2);
		dir.push_back(r1);
		dir.push_back(r2);
		
		for (int i = 0; i < dir.size(); i++)
		{
			switch (dir[i])
			{
			case myEnum::kDir::kDirEast:
				map[_heroX][_heroY + 1].type = myEnum::kRoomType::kRTBranch;
				map[_heroX][_heroY + 1].cnt_sideroom = 1;
				branchRooms.push_back(map[_heroX][_heroY + 1]);
				break;
			case myEnum::kDir::kDirWest:
				map[_heroX][_heroY - 1].type = myEnum::kRoomType::kRTBranch;
				map[_heroX][_heroY - 1].cnt_sideroom = 1;
				branchRooms.push_back(map[_heroX][_heroY + -1]);
				break;
			case myEnum::kDir::kDirSouth:
				map[_heroX + 1][_heroY].type = myEnum::kRoomType::kRTBranch;
				map[_heroX + 1][_heroY].cnt_sideroom = 1;
				branchRooms.push_back(map[_heroX + 1][_heroY]);
				break;
			case myEnum::kDir::kDirNorth:
				map[_heroX - 1][_heroY].type = myEnum::kRoomType::kRTBranch;
				map[_heroX - 1][_heroY].cnt_sideroom = 1;
				branchRooms.push_back(map[_heroX - 1][_heroY]);
				break;
			}			
		}
		map[_heroX][_heroY].cnt_sideroom = 2;
//		_cntRoom = 3;
	}
	else
	{
		int size = branchRooms.size();
		for (int i = 0; i < size; i++)
		{
			Room br = branchRooms.back();
			int x = br.x;
			int y = br.y;
			// e
			if (y + 1 < SIZE_Y && map[x][y + 1].type == myEnum::kRoomType::kRTNone)
				checkSideRoom(x, y + 1);
			// w
			if (y - 1 >= 0 && map[x][y - 1].type == myEnum::kRoomType::kRTNone)
				checkSideRoom(x, y - 1);
			// s
			if (x + 1 < SIZE_X && map[x + 1][y].type == myEnum::kRoomType::kRTNone)
				checkSideRoom(x + 1, y);
			// n
			if (x - 1 >= 0 && map[x - 1][y].type == myEnum::kRoomType::kRTNone)
				checkSideRoom(x - 1, y);

			checkDir(x, y);

			// random sort
			std::vector<int> dir;
			for (int i = 0; i < 4; i++)
				if (map[x][y].dir[i] == true) dir.push_back(i);

			int dirSize = dir.size();
			if (dirSize > 2)
			{
				for (int i = 0; i < 20; i++)
				{
					int temp1 = 0;
					int temp2 = 0;
					do
					{
						temp1 = rand() % dirSize;
						temp2 = rand() % dirSize;
					} while (temp1 == temp2);
					// switch
					int temp = dir[temp1];
					dir[temp1] = dir[temp2];
					dir[temp2] = temp;
				}
			}

			// set count create branch times
			int cnt = 0;
			if (dirSize < cnt_branch) cnt = dirSize;
			else cnt = cnt_branch;

			// create branch
			for (int i = 0; i < cnt; i++)
			{
				switch (dir[i])
				{
				case myEnum::kDir::kDirEast:
					map[x][y + 1].type = myEnum::kRoomType::kRTBranch;
					branchRooms.push_front(map[x][y + 1]);
					break;
				case myEnum::kDir::kDirWest:
					map[x][y - 1].type = myEnum::kRoomType::kRTBranch;
					branchRooms.push_front(map[x][y - 1]);
					break;
				case myEnum::kDir::kDirSouth:
					map[x + 1][y].type = myEnum::kRoomType::kRTBranch;
					branchRooms.push_front(map[x + 1][y]);
					break;
				case myEnum::kDir::kDirNorth:
					map[x - 1][y].type = myEnum::kRoomType::kRTBranch;
					branchRooms.push_front(map[x - 1][y]);
					break;
				}
				map[x][y].type = myEnum::kRoomType::kRTStem;
//				_cntRoom++;
			}

			branchRooms.pop_back();
		}

	}
}

void MapManager::checkDir(int x, int y)
{
	// e
	if (y + 1 < SIZE_Y && map[x][y + 1].type == myEnum::kRoomType::kRTNone && map[x][y + 1].cnt_sideroom == 1)
		map[x][y].dir[myEnum::kDir::kDirEast] = true;
	// w
	if (y - 1 >= 0 && map[x][y - 1].type == myEnum::kRoomType::kRTNone && map[x][y - 1].cnt_sideroom == 1)
		map[x][y].dir[myEnum::kDir::kDirWest] = true;
	// s
	if (x + 1 < SIZE_X && map[x + 1][y].type == myEnum::kRoomType::kRTNone && map[x + 1][y].cnt_sideroom == 1)
		map[x][y].dir[myEnum::kDir::kDirSouth] = true;
	// n
	if (x - 1 >= 0 && map[x - 1][y].type == myEnum::kRoomType::kRTNone && map[x - 1][y].cnt_sideroom == 1)
		map[x][y].dir[myEnum::kDir::kDirNorth] = true;

}
void MapManager::checkSideRoom(int x, int y)
{
	map[x][y].cnt_sideroom = 0;
	// e
	if (y + 1 < SIZE_Y && map[x][y + 1].type != myEnum::kRoomType::kRTNone)
		map[x][y].cnt_sideroom++;
	// w
	if (y - 1 >= 0 && map[x][y - 1].type != myEnum::kRoomType::kRTNone)
		map[x][y].cnt_sideroom++;
	// s
	if (x + 1 < SIZE_X && map[x + 1][y].type != myEnum::kRoomType::kRTNone)
		map[x][y].cnt_sideroom++;
	// n
	if (x - 1 >= 0 && map[x - 1][y].type != myEnum::kRoomType::kRTNone)
		map[x][y].cnt_sideroom++;
}

void MapManager::initAllRoomdata()
{
	for (int i = 0; i < SIZE_X; i++)
	{
		for (int j = 0; j < SIZE_Y; j++)
		{
			map[i][j].x = i;
			map[i][j].y = j;
			map[i][j].lock = false;
			map[i][j].visible = false;
			map[i][j].exp = false;
			map[i][j].type = myEnum::kRoomType::kRTNone;
			map[i][j].data.clear();
			for (int k = 0; k < 4; k++)
				map[i][j].dir[k] = false;
			map[i][j].data.clear();
			map[i][j].data2.clear();
		}
	}
}

void MapManager::init(const char * levelName)
{
	setLevelName(levelName);
	readLevelData();
	int sp_x = SIZE_X / 2;
	int sp_y = SIZE_Y / 2;
	_heroX = sp_x;
	_heroY = sp_y;
	initAllRoomdata();
	//for (int i = 0; i < SIZE_X; i++)
	//{
	//	for (int j = 0; j < SIZE_Y; j++)
	//	{
	//		map[i][j].x = i;
	//		map[i][j].y = j;
	//		map[i][j].lock = false;
	//		map[i][j].visible = false;
	//		map[i][j].exp = false;
	//		map[i][j].type = myEnum::kRoomType::kRTNone;
	//		map[i][j].data.clear();
	//		for (int k = 0; k < 4; k++)
	//			map[i][j].dir[k] = false;
	//		map[i][j].data.clear();
	//		map[i][j].data2.clear();
	//		
	//	}
	//}
	// init start room data
	map[_heroX][_heroY].exp = true;
	map[_heroX][_heroY].visible = true;
	map[_heroX][_heroY].type = myEnum::kRoomType::kRTStart;
	branchRooms.clear();

//	_cntRoom = 0;
//	_clearCntRoom = 1;

	//create();
}

void MapManager::readLevelData()
{
	auto dic = __Dictionary::createWithContentsOfFile(__String::create("Level/Level.plist")->getCString());
	auto levelPattern = (cocos2d::__Dictionary *)dic->objectForKey(levelName.c_str());

	bossCount = levelPattern->valueForKey("Boss")->intValue();
	helpCount = levelPattern->valueForKey("Help")->intValue();
	shopCount = levelPattern->valueForKey("Shop")->intValue();
	treasureCount = levelPattern->valueForKey("Treasure")->intValue();
	secretCount = levelPattern->valueForKey("Secret")->intValue();

	cnt_gen = levelPattern->valueForKey("cnt_gen")->intValue();

}

void MapManager::setRoomType()
{
	std::vector<Room> rt;

	for (int i = 0; i < SIZE_X; i++)
	{
		for (int j = 0; j < SIZE_Y; j++)
		{
			if (map[i][j].type == myEnum::kRoomType::kRTBranch)
				rt.push_back(map[i][j]);
		}
	}

	int size = rt.size();

	int r1 = 0;
	int r2 = 0;
	for (int i = 0; i < 100; i++)
	{
		do
		{
			r1 = rand()%size;
			r2 = rand()%size;
		} while (r1 == r2);
		Room temp = rt.at(r1);
		rt.at(r1) = rt.at(r2);
		rt.at(r2) = temp;
	}

	// boss, shop, treasure, help
	int index = 0;
	for (int i = 0; i < bossCount; i++)
	{
		map[rt.at(index).x][rt.at(index).y].type = myEnum::kRoomType::kRTBoss;
		index++;
	}
	for (int i = 0; i < shopCount; i++)
	{
		map[rt.at(index).x][rt.at(index).y].type = myEnum::kRoomType::kRTShop;
		if (levelName.compare("G") != 0)
			map[rt.at(index).x][rt.at(index).y].lock = true;
		index++;
	}
	for (int i = 0; i < treasureCount; i++)
	{
		map[rt.at(index).x][rt.at(index).y].type = myEnum::kRoomType::kRTTreasure;
		if (levelName.compare("G") != 0)
			map[rt.at(index).x][rt.at(index).y].lock = true;
		index++;
	}
	for (int i = 0; i < helpCount; i++)
	{
		map[rt.at(index).x][rt.at(index).y].type = myEnum::kRoomType::kRTHelp;
		if (levelName.compare("G") != 0)
			map[rt.at(index).x][rt.at(index).y].lock = true;
		index++;
	}

	debug("before init");
	// secret
	for (int i = 0; i < SIZE_X; i++)
	{
		for (int j = 0; j < SIZE_Y; j++)
		{
			if (map[i][j].type == myEnum::kRoomType::kRTNone)
			{
				checkSideRoom(i, j);
				map[i][j].priority = map[i][j].cnt_sideroom;
			}
		}
	}

	debug("after init");

	Heap<Room> heap;
	heap.setState(Heap<Room>::bigHeap);
	// heap sort
	for (int i = 0; i < SIZE_X; i++)
	{
		for (int j = 0; j < SIZE_Y; j++)
		{
			if (map[i][j].type == myEnum::kRoomType::kRTNone && map[i][j].priority != 0 )
				heap.insert(map[i][j]);
		}
	}

	// set secret room
	for (int i = 0; i < secretCount; i++)
	{
		Room rd = heap.deletemin();
		int x = rd.x;
		int y = rd.y;
		map[x][y].type = myEnum::kRoomType::kRTSecret;
		map[x][y].lock = true;
//		_cntRoom++;
	}

	heap.clear();
	
	// monster
	for (int i = 0; i < SIZE_X; i++)
	{
		for (int j = 0; j < SIZE_Y; j++)
		{
			if (map[i][j].type == myEnum::kRoomType::kRTBranch || map[i][j].type == myEnum::kRoomType::kRTStem)
				map[i][j].type = myEnum::kRoomType::kRTMonster;
		}
	}

}


void MapManager::DrawMap(cocos2d::Layer *layer)
{
	// init
	this->layer = layer;
	auto cache = SpriteFrameCache::sharedSpriteFrameCache();
	cache->addSpriteFramesWithFile("Map/Map.plist", "Map/Map.png");
	spriteBatch = SpriteBatchNode::create("Map/Map.png");

	auto visibleSize = Director::getInstance()->getVisibleSize();

	auto mapBGSprite = Sprite::createWithSpriteFrameName("Map/MapBG.png");
	mapBGSprite->setPosition(visibleSize.width - mapBGSprite->getContentSize().width / 2, visibleSize.height - mapBGSprite->getContentSize().height / 2);
	spriteBatch->addChild(mapBGSprite, ZINDEX_STATUS_MAP_BG, "map");

	// calculate start point for room Images
	cocos2d::Size tempSize = Sprite::createWithSpriteFrameName("Map/CurrentRoom.png")->getContentSize();
	int rateX = (SIZE_X - 1) / 2.0;
	int rateY = (SIZE_Y - 1) / 2.0;

	float sX = mapBGSprite->getPosition().x - rateX * tempSize.width;
	float sY = mapBGSprite->getPosition().y + rateY * tempSize.height;

	// curse
	if (_curse)
	{
		auto temp = Sprite::createWithSpriteFrameName("Map/ClosedRoom.png");
		auto tempType = Sprite::createWithSpriteFrameName("Map/Secret.png");
		temp->setPosition(mapBGSprite->getPosition());
		tempType->setPosition(mapBGSprite->getPosition());
		spriteBatch->addChild(temp, 3);
		spriteBatch->addChild(tempType, 4);
	}
	else // not curse
	{
		for (int i = 0; i < SIZE_X; i++)
		{
			for (int j = 0; j < SIZE_Y; j++)
			{
				cocos2d::Sprite * temp = nullptr;
				cocos2d::Sprite * tempType = nullptr;
				switch (map[i][j].type)
				{
				case myEnum::kRoomType::kRTNone:
					break;
				case myEnum::kRoomType::kRTStart:
					if (_allView || map[i][j].visible)
						temp = Sprite::createWithSpriteFrameName("Map/OpenedRoom.png");
					break;
				case myEnum::kRoomType::kRTMonster:
					if (_allView || map[i][j].visible)
					{
						if (map[i][j].exp)
							temp = Sprite::createWithSpriteFrameName("Map/OpenedRoom.png");
						else
							temp = Sprite::createWithSpriteFrameName("Map/ClosedRoom.png");
					}
					break;
				case myEnum::kRoomType::kRTShop:
					if (_allView || map[i][j].visible)
					{
						if (map[i][j].exp)
							temp = Sprite::createWithSpriteFrameName("Map/OpenedRoom.png");
						else
							temp = Sprite::createWithSpriteFrameName("Map/ClosedRoom.png");
						//tempType = Sprite::createWithSpriteFrameName("Map/Shop.png");
					}
					if (_allViewType || map[i][j].visible)
					{
						tempType = Sprite::createWithSpriteFrameName("Map/Shop.png");
					}
					break;
				case myEnum::kRoomType::kRTHelp:
					if (_allView || map[i][j].visible)
					{
						if (map[i][j].exp)
							temp = Sprite::createWithSpriteFrameName("Map/OpenedRoom.png");
						else
							temp = Sprite::createWithSpriteFrameName("Map/ClosedRoom.png");
						//tempType = Sprite::createWithSpriteFrameName("Map/Help.png");
					}
					if (_allViewType || map[i][j].visible)
					{
						tempType = Sprite::createWithSpriteFrameName("Map/Help.png");
					}
					break;
				case myEnum::kRoomType::kRTBoss:
					if (_allView || map[i][j].visible)
					{
						if (map[i][j].exp)
							temp = Sprite::createWithSpriteFrameName("Map/OpenedRoom.png");
						else
							temp = Sprite::createWithSpriteFrameName("Map/ClosedRoom.png");
						//tempType = Sprite::createWithSpriteFrameName("Map/Boss.png");
					}
					if (_allViewType || map[i][j].visible)
					{
						tempType = Sprite::createWithSpriteFrameName("Map/Boss.png");
					}
					break;
				case myEnum::kRoomType::kRTTreasure:
					if (_allView || map[i][j].visible)
					{
						if (map[i][j].exp)
							temp = Sprite::createWithSpriteFrameName("Map/OpenedRoom.png");
						else
							temp = Sprite::createWithSpriteFrameName("Map/ClosedRoom.png");
						//tempType = Sprite::createWithSpriteFrameName("Map/Treasure.png");
					}
					if (_allViewType || map[i][j].visible)
					{
						tempType = Sprite::createWithSpriteFrameName("Map/Treasure.png");
					}
					break;
				case myEnum::kRoomType::kRTSecret:
					if (map[i][j].visible)
					{
						if (map[i][j].exp)
							temp = Sprite::createWithSpriteFrameName("Map/OpenedRoom.png");
						else
							temp = Sprite::createWithSpriteFrameName("Map/ClosedRoom.png");
						tempType = Sprite::createWithSpriteFrameName("Map/Secret.png");
					}
					break;
				}

				if (temp != nullptr)
				{
					temp->setPosition(Vec2(sX + tempSize.width * j, sY - tempSize.height * i));
					spriteBatch->addChild(temp, ZINDEX_STATUS_MAP_ROOM);
				}
				if (tempType != nullptr)
				{
					tempType->setPosition(Vec2(sX + tempSize.width * j, sY - tempSize.height * i));
					spriteBatch->addChild(tempType, ZINDEX_STATUS_MAP_TYPE);
				}
			} // end for j
		} // end for i

		auto hero = Sprite::createWithSpriteFrameName("Map/CurrentRoom.png");
		hero->setPosition(sX + tempSize.width * _heroY, sY - tempSize.height * _heroX);
		spriteBatch->addChild(hero, ZINDEX_STATUS_MAP_ROOM);

	}

	layer->addChild(spriteBatch, ZINDEX_STATUS_MAP_BG, "map");


}
void MapManager::ReDrawMap()
{
	layer->removeChild(spriteBatch);
	DrawMap(layer);
}
//
//void MapManager::Save()
//{
//	auto def = UserDefault::sharedUserDefault();
//	def->setIntegerForKey("m_heroX", _heroX);
//	def->setIntegerForKey("m_heroY", _heroY);
//
//	// current room data save
//	SaveRoomData(_heroX, _heroY);
//	if (IsE())
//		SaveRoomData(_heroX, _heroY + 1);
//	if (IsW())
//		SaveRoomData(_heroX, _heroY - 1);
//	if (IsS())
//		SaveRoomData(_heroX + 1, _heroY);
//	if (IsN())
//		SaveRoomData(_heroX - 1, _heroY);
//
//	def->flush();
//}
void MapManager::SaveRoomData(int x, int y)
{
	GetRoomData(x, y).SaveRoomData();
}

void MapManager::SaveAll()
{
	auto def = UserDefault::sharedUserDefault();
	def->setIntegerForKey("m_heroX", _heroX);
	def->setIntegerForKey("m_heroY", _heroY);
	def->setStringForKey("m_levelName", levelName.c_str());

	for (int i = 0; i < SIZE_X; i++)
	{
		for (int j = 0; j < SIZE_Y; j++)
		{
			SaveRoomData(i, j);
		}
	}

	def->setBoolForKey("saveState", true);
	def->flush();
}


void MapManager::LoadAll()
{
	//	DeleteMapData();
	auto def = UserDefault::sharedUserDefault();
	levelName = def->getStringForKey("m_levelName");
	_heroX = def->getIntegerForKey("m_heroX");
	_heroY = def->getIntegerForKey("m_heroY");

	initAllRoomdata();
	// init
	for (int i = 0; i < SIZE_X; i++)
	{
		for (int j = 0; j < SIZE_Y; j++)
		{
			LoadRoomData(i, j);
		}
	}
}

void MapManager::LoadRoomData(int x, int y)
{
	map[x][y].LoadRoomData();
	//GetRoomData(x, y).LoadRoomData();
}



void MapManager::CheckSideRoom(bool secretVisible, bool secretLockOpen)
{
	// check E
	if (IsE())
		SetVisibleState(_heroX, _heroY + 1, secretVisible, secretLockOpen);
	// check W
	if (IsW())
		SetVisibleState(_heroX, _heroY - 1, secretVisible, secretLockOpen);
	// check S
	if (IsS())
		SetVisibleState(_heroX + 1, _heroY, secretVisible, secretLockOpen);
	// check N
	if (IsN())
		SetVisibleState(_heroX - 1, _heroY, secretVisible, secretLockOpen);
}

void MapManager::SetVisibleState(int x, int y, bool secretVisible, bool secretLockOpen)
{
	if (map[x][y].type != myEnum::kRoomType::kRTNone)
	{
		// default
		if (map[x][y].type != myEnum::kRoomType::kRTSecret)
			map[x][y].visible = true;
		else // secret 
		{
			if (secretVisible)
			{
				map[x][y].visible = true;
			}
			if (secretLockOpen)
			{
				map[x][y].lock = false;
			}
		}
	}
}
Room MapManager::GetRoomData(int x, int y)
{
	return map[x][y];
}
Room MapManager::GetCurrentRoomData() const
{
	return map[_heroX][_heroY];
}
bool MapManager::IsBoundary(int x, int y)
{
	return ((x > 0 && x < SIZE_X) && (y >0 && y < SIZE_Y));
}
bool MapManager::IsE()
{
	return (_heroY + 1 < SIZE_Y);
}
bool MapManager::IsW()
{
	return (_heroY - 1 >= 0);
}
bool MapManager::IsS()
{
	return (_heroX + 1 < SIZE_X);
}
bool MapManager::IsN()
{
	return (_heroX - 1 >= 0);
}
