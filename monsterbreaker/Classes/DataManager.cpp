#include "DataManager.h"

USING_NS_CC;

DataManager::~DataManager()
{

}
DataManager::DataManager(cocos2d::Layer * layer, Hero * hero) : layer(layer), hero(hero)
{
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();
	mapManager = MapManager::getInstance();
	x = mapManager->GetCurrentRoomData().x;
	y = mapManager->GetCurrentRoomData().y;

}

DataManager* DataManager::create(cocos2d::Layer * layer, Hero * hero)
{
	auto pNode = new DataManager(layer, hero);
	pNode->autorelease();
	return pNode;
}

void DataManager::ClearData()
{
	mapManager->map[x][y].data2.clear();
}

void DataManager::SaveData()
{
	auto vector= layer->getChildren();
	int size = vector.size();
	int cnt = 0;
	int cnt2 = 0;
	int cnt3 = 0;
	int cnt4 = 0;
	int cnt5 = 0;
	for (int i = 0; i < size; i++)
	{
		auto obj = vector.at(i);
		// item
		if (obj->getTag() == myEnum::kMyTag::kItemTag)
		{
			auto itemObj = (Item*)obj;
			cnt++;
			mapManager->map[x][y].data2["itemCnt"] = String::createWithFormat("%d", cnt)->getCString();
			mapManager->map[x][y].data2[String::createWithFormat("item%dName", cnt)->getCString() ] = itemObj->getName().c_str();
			mapManager->map[x][y].data2[String::createWithFormat("item%dPositionX", cnt)->getCString()] = String::createWithFormat("%f", itemObj->getPositionX())->getCString();
			mapManager->map[x][y].data2[String::createWithFormat("item%dPositionY", cnt)->getCString()] = String::createWithFormat("%f", itemObj->getPositionY())->getCString();
			mapManager->map[x][y].data2[String::createWithFormat("item%dIsShop", cnt)->getCString()] = (itemObj->getIsShop()) ? "true" : "false";
		}
		// chest item
		if (obj->getTag() == myEnum::kMyTag::kChestItemTag)
		{
			auto chestItemObj = (ChestItem*)obj;
			cnt2++;
			mapManager->map[x][y].data2["chestItemCnt"] = String::createWithFormat("%d", cnt2)->getCString();
			mapManager->map[x][y].data2[String::createWithFormat("chestItem%dID", cnt2)->getCString()] = String::createWithFormat("%d", chestItemObj->getItemID())->getCString();
			mapManager->map[x][y].data2[String::createWithFormat("chestItem%dPositionX", cnt2)->getCString()] = String::createWithFormat("%f", chestItemObj->getPositionX())->getCString();
			mapManager->map[x][y].data2[String::createWithFormat("chestItem%dPositionY", cnt2)->getCString()] = String::createWithFormat("%f", chestItemObj->getPositionY())->getCString();
			mapManager->map[x][y].data2[String::createWithFormat("chestItem%dIsShop", cnt2)->getCString()] = (chestItemObj->getisShop()) ? "true" : "false";
		}
		// skill item
		if (obj->getTag() == myEnum::kMyTag::kSkillItemTag)
		{
			auto skillItemObj= (SkillItem*)obj;
			cnt3++;
			mapManager->map[x][y].data2["skillItemCnt"] = String::createWithFormat("%d", cnt3)->getCString();
			mapManager->map[x][y].data2[String::createWithFormat("skillItem%dID", cnt3)->getCString()] = String::createWithFormat("%d", skillItemObj->getSkillID())->getCString();
			mapManager->map[x][y].data2[String::createWithFormat("skillItem%dPositionX", cnt3)->getCString()] = String::createWithFormat("%f", skillItemObj->getPositionX())->getCString();
			mapManager->map[x][y].data2[String::createWithFormat("skillItem%dPositionY", cnt3)->getCString()] = String::createWithFormat("%f", skillItemObj->getPositionY())->getCString();
			mapManager->map[x][y].data2[String::createWithFormat("skillItem%dIsShop", cnt3)->getCString()] = (skillItemObj->getisShop()) ? "true" : "false";
			mapManager->map[x][y].data2[String::createWithFormat("skillItem%dCurrentPoint", cnt3)->getCString()] = String::createWithFormat("%d", skillItemObj->getCurrentPoint())->getCString();
		}
		// armor item
		if (obj->getTag() == myEnum::kMyTag::kArmorItemTag)
		{
			auto armorItemObj = (ArmorItem*)obj;
			cnt4++;
			mapManager->map[x][y].data2["armorItemCnt"] = String::createWithFormat("%d", cnt4)->getCString();
			mapManager->map[x][y].data2[String::createWithFormat("armorItem%dID", cnt4)->getCString()] = String::createWithFormat("%d", armorItemObj->getArmorID())->getCString();
			mapManager->map[x][y].data2[String::createWithFormat("armorItem%dPositionX", cnt4)->getCString()] = String::createWithFormat("%f", armorItemObj->getPositionX())->getCString();
			mapManager->map[x][y].data2[String::createWithFormat("armorItem%dPositionY", cnt4)->getCString()] = String::createWithFormat("%f", armorItemObj->getPositionY())->getCString();
			mapManager->map[x][y].data2[String::createWithFormat("armorItem%dIsShop", cnt4)->getCString()] = (armorItemObj->getisShop()) ? "true" : "false";
		}
		// brick
		if (obj->getTag() == myEnum::kMyTag::kBlockTag)
		{
			auto brickObj = (Brick*)obj;
			cnt5++;
			mapManager->map[x][y].data2["brickCnt"] = String::createWithFormat("%d", cnt5)->getCString();
			mapManager->map[x][y].data2[String::createWithFormat("brick%dID", cnt5)->getCString()] = String::createWithFormat("%d", brickObj->getBrickTypeID())->getCString();
			mapManager->map[x][y].data2[String::createWithFormat("brick%dPositionX", cnt5)->getCString()] = String::createWithFormat("%f", brickObj->getPositionX())->getCString();
			mapManager->map[x][y].data2[String::createWithFormat("brick%dPositionY", cnt5)->getCString()] = String::createWithFormat("%f", brickObj->getPositionY())->getCString();
		}

	}
}

void DataManager::LoadData()
{
	CCLOG("@@@@@@@@@@@@@@@@@@@@@@@@@@@@");
	CCLOG("x:%d y:%d", x, y);
	CCLOG("%s", mapManager->map[x][y].data2["itemCnt"]);
	CCLOG("@@@@@@@@@@@@@@@@@@@@@@@@@@@@");
	int itemSize = std::atoi(mapManager->map[x][y].data2["itemCnt"].c_str());
	for (int i = 1; i <= itemSize; i++)
	{
		auto n = mapManager->map[x][y].data2[String::createWithFormat("item%dName", i)->getCString()].c_str();
		float xPos = std::atof(mapManager->map[x][y].data2[String::createWithFormat("item%dPositionX", i)->getCString()].c_str());
		float yPos = std::atof(mapManager->map[x][y].data2[String::createWithFormat("item%dPositionY", i)->getCString()].c_str());
		bool isShop = (mapManager->map[x][y].data2[String::createWithFormat("item%dIsShop", i)->getCString()].compare("true") == 0) ? true : false;
		CreateItems(n, xPos, yPos, isShop);
	}

	int chestItemSize = std::atoi(mapManager->map[x][y].data2["chestItemCnt"].c_str());
	for (int i = 1; i <= chestItemSize; i++)
	{
		int cID = std::atoi(mapManager->map[x][y].data2[String::createWithFormat("chestItem%dID", i)->getCString()].c_str());
		float xPos = std::atof(mapManager->map[x][y].data2[String::createWithFormat("chestItem%dPositionX", i)->getCString()].c_str());
		float yPos = std::atof(mapManager->map[x][y].data2[String::createWithFormat("chestItem%dPositionY", i)->getCString()].c_str());
		bool isShop = (mapManager->map[x][y].data2[String::createWithFormat("chestItem%dIsShop", i)->getCString()].compare("true") == 0) ? true : false;
		CreateChestItems(cID, xPos, yPos, isShop);
	}

	int skillItemSize = std::atoi(mapManager->map[x][y].data2["skillItemCnt"].c_str());
	for (int i = 1; i <= skillItemSize; i++)
	{
		int sID = std::atoi(mapManager->map[x][y].data2[String::createWithFormat("skillItem%dID", i)->getCString()].c_str());
		float xPos = std::atof(mapManager->map[x][y].data2[String::createWithFormat("skillItem%dPositionX", i)->getCString()].c_str());
		float yPos = std::atof(mapManager->map[x][y].data2[String::createWithFormat("skillItem%dPositionY", i)->getCString()].c_str());
		bool isShop = (mapManager->map[x][y].data2[String::createWithFormat("skillItem%dIsShop", i)->getCString()].compare("true") == 0) ? true : false;
		int currentPoint = std::atoi(mapManager->map[x][y].data2[String::createWithFormat("skillItem%dCurrentPoint", i)->getCString()].c_str());
		CreateSkillItems(sID, xPos, yPos, isShop, currentPoint);
	}

	int armorItemSize = std::atoi(mapManager->map[x][y].data2["armorItemCnt"].c_str());
	for (int i = 1; i <= armorItemSize; i++)
	{
		int aID = std::atoi(mapManager->map[x][y].data2[String::createWithFormat("armorItem%dID", i)->getCString()].c_str());
		float xPos = std::atof(mapManager->map[x][y].data2[String::createWithFormat("armorItem%dPositionX", i)->getCString()].c_str());
		float yPos = std::atof(mapManager->map[x][y].data2[String::createWithFormat("armorItem%dPositionY", i)->getCString()].c_str());
		bool isShop = (mapManager->map[x][y].data2[String::createWithFormat("armorItem%dIsShop", i)->getCString()].compare("true") == 0) ? true : false;
		CreateArmorItems(aID, xPos, yPos, isShop);
	}

	int brickSize = std::atoi(mapManager->map[x][y].data2["brickCnt"].c_str());
	for (int i = 1; i <= brickSize; i++)
	{
		int bID = std::atoi(mapManager->map[x][y].data2[String::createWithFormat("brick%dID", i)->getCString()].c_str());
		float xPos = std::atof(mapManager->map[x][y].data2[String::createWithFormat("brick%dPositionX", i)->getCString()].c_str());
		float yPos = std::atof(mapManager->map[x][y].data2[String::createWithFormat("brick%dPositionY", i)->getCString()].c_str());
		CreateBricks(bID, xPos, yPos);
	}
}

void DataManager::CreateArmorItems(int aID, float x, float y, bool isShop)
{
	auto ch = ArmorItem::create(layer, hero, aID, isShop);
	ch->setPosition(x, y);
	layer->addChild(ch, ZINDEX_CHEST_SPRITE, myEnum::kMyTag::kArmorItemTag);
}

void DataManager::CreateChestItems(int cID, float x, float y, bool isShop)
{
	auto ch = ChestItem::create(layer, hero, cID, isShop);
	ch->setPosition(x, y);
	layer->addChild(ch, ZINDEX_CHEST_SPRITE, myEnum::kMyTag::kChestItemTag);
}

void DataManager::CreateSkillItems(int sID, float x, float y, bool isShop, int currentPoint)
{
	auto sk = SkillItem::create(layer, hero, sID, isShop, currentPoint);
	sk->setPosition(x, y);
	layer->addChild(sk, ZINDEX_CHEST_SPRITE, myEnum::kMyTag::kSkillItemTag);
}

void DataManager::CreateItems(const char * n, float x, float y, bool isShop)
{
	std::string name = n;
	Node * item = nullptr;
	if (name.compare("Bomb") == 0)
	{
		item = ItemBomb::create(layer, hero, isShop);
	}
	else if (name.compare("Coin") == 0)
	{
		item = ItemCoin::create(layer, hero);
	}
	else if (name.compare("HalfHeart") == 0)
	{
		item = ItemHalfHeart::create(layer, hero, isShop);
	}
	else if (name.compare("HalfSoulHeart") == 0)
	{
		item = ItemHalfSoulHeart::create(layer, hero, isShop);
	}
	else if (name.compare("Heart") == 0)
	{
		item = ItemHeart::create(layer, hero, isShop);
	}
	else if (name.compare("Key") == 0)
	{
		item = ItemKey::create(layer, hero, isShop);
	}
	else if (name.compare("SoulHeart") == 0)
	{
		item = ItemSoulHeart::create(layer, hero, isShop);
	}
	if (item != nullptr)
	{
		item->setPosition(x, y);
		layer->addChild(item, ZINDEX_ITEM_SPRITE, myEnum::kMyTag::kItemTag);
	}
}

void DataManager::CreateBricks(int brickID, float x, float y)
{
	Brick * b = nullptr;
	switch (brickID)
	{
	case BRICK_SINGLE_ID:
		b = SingleBrick::create(mapManager->getLevelName().c_str(), brickID);
		break;
	case BRICK_DOUBLE_ID:
		b = DoubleBrick::create(mapManager->getLevelName().c_str(), layer, brickID);
		break;
	case BRICK_SOLID_ID:
		b = SolidBrick::create(mapManager->getLevelName().c_str(), brickID);
		break;
	}
	if (b != nullptr)
	{
		b->setPosition(x, y);
		layer->addChild(b, ZINDEX_BRICK_SPRITE, myEnum::kMyTag::kBlockTag);
	}
	else
	{
		//CC_ASSERT("Didn't Load Brick Data.\nBrick Has NULL PTR (Brick ID : %d)", brickID);
	}
}

