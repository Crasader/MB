#include "Room.h"
USING_NS_CC;
void Room::SaveRoomData()
{
	auto def = UserDefault::sharedUserDefault();
	if (type != myEnum::kRoomType::kRTNone)
	{
		def->setBoolForKey(String::createWithFormat("m_%d%dNone", x, y)->getCString(), false);

		// init
		def->setBoolForKey(String::createWithFormat("m_%d%dLock", x, y)->getCString(), lock);
		def->setBoolForKey(String::createWithFormat("m_%d%dVisible", x, y)->getCString(), visible);
		def->setBoolForKey(String::createWithFormat("m_%d%dExp", x, y)->getCString(), exp);
		def->setIntegerForKey(String::createWithFormat("m_%d%dType", x, y)->getCString(), type);

		// help
		if (type == myEnum::kRoomType::kRTHelp)
		{
			def->setIntegerForKey(String::createWithFormat("m_%d%dc1", x, y)->getCString(), data["c1"]);
			def->setIntegerForKey(String::createWithFormat("m_%d%dc2", x, y)->getCString(), data["c2"]);
			def->setIntegerForKey(String::createWithFormat("m_%d%dc2", x, y)->getCString(), data["c3"]);

			def->setIntegerForKey(String::createWithFormat("m_%d%dHMClicked", x, y)->getCString(), data["HMClicked"]);
			def->setIntegerForKey(String::createWithFormat("m_%d%dweapon", x, y)->getCString(), data["weapon"]);
			def->setIntegerForKey(String::createWithFormat("m_%d%dc3Item", x, y)->getCString(), data["c3Item"]);
		}

		// shop
		if (type == myEnum::kRoomType::kRTShop)
		{
			def->setIntegerForKey(String::createWithFormat("m_%d%dmerchant", x, y)->getCString(), data["merchant"]);
			def->setIntegerForKey(String::createWithFormat("m_%d%dshopItem1", x, y)->getCString(), data["shopItem1"]);
			def->setIntegerForKey(String::createWithFormat("m_%d%dshopItem2", x, y)->getCString(), data["shopItem2"]);
			def->setIntegerForKey(String::createWithFormat("m_%d%dshopItem3", x, y)->getCString(), data["shopItem3"]);
			def->setIntegerForKey(String::createWithFormat("m_%d%dshopItem4", x, y)->getCString(), data["shopItem4"]);


			int chestItemSize = std::atoi(data2["chestItemCnt"].c_str());
			def->setStringForKey(String::createWithFormat("m_%d%dchestItemCnt", x, y)->getCString(), data2["chestItemCnt"]);
			for (int i = 1; i <= chestItemSize; i++)
			{
				def->setStringForKey(String::createWithFormat("m_%d%dchestItem%dID", x, y, i)->getCString(), data2[String::createWithFormat("chestItem%dID", i)->getCString()].c_str());
				def->setStringForKey(String::createWithFormat("m_%d%dchestItem%dPositionX", x, y, i)->getCString(), data2[String::createWithFormat("chestItem%dPositionX", i)->getCString()].c_str());
				def->setStringForKey(String::createWithFormat("m_%d%dchestItem%dPositionY", x, y, i)->getCString(), data2[String::createWithFormat("chestItem%dPositionY", i)->getCString()].c_str());
				def->setStringForKey(String::createWithFormat("m_%d%dchestItem%dIsShop", x, y, i)->getCString(), data2[String::createWithFormat("chestItem%dIsShop", i)->getCString()].c_str());
			}

			int skillItemSize = std::atoi(data2["skillItemCnt"].c_str());
			def->setStringForKey(String::createWithFormat("m_%d%dskillItemCnt", x, y)->getCString(), data2["skillItemCnt"]);
			for (int i = 1; i <= skillItemSize; i++)
			{
				def->setStringForKey(String::createWithFormat("m_%d%dskillItem%dID", x, y, i)->getCString(), data2[String::createWithFormat("skillItem%dID", i)->getCString()].c_str());
				def->setStringForKey(String::createWithFormat("m_%d%dskillItem%dPositionX", x, y, i)->getCString(), data2[String::createWithFormat("skillItem%dPositionX", i)->getCString()].c_str());
				def->setStringForKey(String::createWithFormat("m_%d%dskillItem%dPositionY", x, y, i)->getCString(), data2[String::createWithFormat("skillItem%dPositionY", i)->getCString()].c_str());
				def->setStringForKey(String::createWithFormat("m_%d%dskillItem%dIsShop", x, y, i)->getCString(), data2[String::createWithFormat("skillItem%dIsShop", i)->getCString()].c_str());
				def->setStringForKey(String::createWithFormat("m_%d%dskillItem%dCurrentPoint", x, y, i)->getCString(), data2[String::createWithFormat("skillItem%dCurrentPoint", i)->getCString()].c_str());
			}

			int armorItemSize = std::atoi(data2["armorItemCnt"].c_str());
			def->setStringForKey(String::createWithFormat("m_%d%darmorItemCnt", x, y)->getCString(), data2["armorItemCnt"]);
			for (int i = 1; i <= armorItemSize; i++)
			{
				def->setStringForKey(String::createWithFormat("m_%d%darmorItem%dID", x, y, i)->getCString(), data2[String::createWithFormat("armorItem%dID", i)->getCString()].c_str());
				def->setStringForKey(String::createWithFormat("m_%d%darmorItem%dPositionX", x, y, i)->getCString(), data2[String::createWithFormat("armorItem%dPositionX", i)->getCString()].c_str());
				def->setStringForKey(String::createWithFormat("m_%d%darmorItem%dPositionY", x, y, i)->getCString(), data2[String::createWithFormat("armorItem%dPositionY", i)->getCString()].c_str());
				def->setStringForKey(String::createWithFormat("m_%d%darmorItem%dIsShop", x, y, i)->getCString(), data2[String::createWithFormat("armorItem%dIsShop", i)->getCString()].c_str());
			}

		}

		// secret
		if (type == myEnum::kRoomType::kRTSecret)
		{
			def->setIntegerForKey(String::createWithFormat("m_%d%ditemOpened", x, y)->getCString(), data["itemOpened"]);
			def->setIntegerForKey(String::createWithFormat("m_%d%dsecondBG", x, y)->getCString(), data["secondBG"]);
		}

		// block (data) all

		int itemSize = std::atoi(data2["itemCnt"].c_str());
		def->setStringForKey(String::createWithFormat("m_%d%ditemCnt", x, y)->getCString(), data2["itemCnt"]);
		for (int i = 1; i <= itemSize; i++)
		{
			def->setStringForKey(String::createWithFormat("m_%d%ditem%dName", x, y, i)->getCString(), data2[String::createWithFormat("item%dName", i)->getCString()].c_str());
			def->setStringForKey(String::createWithFormat("m_%d%ditem%dPositionX", x, y, i)->getCString(), data2[String::createWithFormat("item%dPositionX", i)->getCString()].c_str());
			def->setStringForKey(String::createWithFormat("m_%d%ditem%dPositionY", x, y, i)->getCString(), data2[String::createWithFormat("item%dPositionY", i)->getCString()].c_str());
			def->setStringForKey(String::createWithFormat("m_%d%ditem%dIsShop", x, y, i)->getCString(), data2[String::createWithFormat("item%dIsShop", i)->getCString()].c_str());
		}

		if (type == myEnum::kRoomType::kRTBoss || type == myEnum::kRoomType::kRTMonster)
		{
			int brickSize = std::atoi(data2["brickCnt"].c_str());
			def->setStringForKey(String::createWithFormat("m_%d%dbrickCnt", x, y)->getCString(), data2["brickCnt"]);
			for (int i = 1; i <= brickSize; i++)
			{
				def->setStringForKey(String::createWithFormat("m_%d%dbrick%dID", x, y, i)->getCString(), data2[String::createWithFormat("brick%dID", i)->getCString()].c_str());
				def->setStringForKey(String::createWithFormat("m_%d%dbrick%dPositionX", x, y, i)->getCString(), data2[String::createWithFormat("brick%dPositionX", i)->getCString()].c_str());
				def->setStringForKey(String::createWithFormat("m_%d%dbrick%dPositionY", x, y, i)->getCString(), data2[String::createWithFormat("brick%dPositionY", i)->getCString()].c_str());
			}
		}

	}
	else
	{
		def->setBoolForKey(String::createWithFormat("m_%d%dNone", x, y)->getCString(), true);

	}
	def->flush();

}

void Room::LoadRoomData()
{
	auto def = UserDefault::sharedUserDefault();

	data.clear();
	data2.clear();

	bool none = def->getBoolForKey(String::createWithFormat("m_%d%dNone", x, y)->getCString(), true);
//	if (none)
//	{
//		lock = false;
//		visible = false;
//		exp = false;
//		type = myEnum::kRoomType::kRTNone;
//	}
//	else
//	{
	if (!none)
	{
		// init
		lock = def->getBoolForKey(String::createWithFormat("m_%d%dLock", x, y)->getCString(), false);
		visible = def->getBoolForKey(String::createWithFormat("m_%d%dVisible", x, y)->getCString(), false);
		exp = def->getBoolForKey(String::createWithFormat("m_%d%dExp", x, y)->getCString(), false);
		type = def->getIntegerForKey(String::createWithFormat("m_%d%dType", x, y)->getCString(), 0);

		// help
		if (type == myEnum::kRoomType::kRTHelp)
		{
			data["c1"] = def->getIntegerForKey(String::createWithFormat("m_%d%dc1", x, y)->getCString(), 0);
			data["c2"] = def->getIntegerForKey(String::createWithFormat("m_%d%dc2", x, y)->getCString(), 0);
			data["c3"] = def->getIntegerForKey(String::createWithFormat("m_%d%dc2", x, y)->getCString(), 0);

			data["HMClicked"] = def->getIntegerForKey(String::createWithFormat("m_%d%dHMClicked", x, y)->getCString(), 0);
			data["weapon"] = def->getIntegerForKey(String::createWithFormat("m_%d%dweapon", x, y)->getCString(), 0);
			data["c3Item"] = def->getIntegerForKey(String::createWithFormat("m_%d%dc3Item", x, y)->getCString(), 0);
		}

		// shop
		if (type == myEnum::kRoomType::kRTShop)
		{
			data["merchant"] = def->getIntegerForKey(String::createWithFormat("m_%d%dmerchant", x, y)->getCString(), 0);
			data["shopItem1"] = def->getIntegerForKey(String::createWithFormat("m_%d%dshopItem1", x, y)->getCString(), 0);
			data["shopItem2"] = def->getIntegerForKey(String::createWithFormat("m_%d%dshopItem2", x, y)->getCString(), 0);
			data["shopItem3"] = def->getIntegerForKey(String::createWithFormat("m_%d%dshopItem3", x, y)->getCString(), 0);
			data["shopItem4"] = def->getIntegerForKey(String::createWithFormat("m_%d%dshopItem4", x, y)->getCString(), 0);

			data2["chestItemCnt"] = def->getStringForKey(String::createWithFormat("m_%d%dchestItemCnt", x, y)->getCString(), "0").c_str();
			int chestItemSize = std::atoi(data2["chestItemCnt"].c_str());
			//def->setStringForKey(String::createWithFormat("m_%d%dchestItemCnt", x, y)->getCString(), data2["chestItemCnt"]);
			for (int i = 1; i <= chestItemSize; i++)
			{
				data2[String::createWithFormat("chestItem%dID", i)->getCString()] = def->getStringForKey(String::createWithFormat("m_%d%dchestItem%dID", x, y, i)->getCString(), "0");
				data2[String::createWithFormat("chestItem%dPositionX", i)->getCString()] = def->getStringForKey(String::createWithFormat("m_%d%dchestItem%dPositionX", x, y, i)->getCString(), "0");
				data2[String::createWithFormat("chestItem%dPositionY", i)->getCString()] = def->getStringForKey(String::createWithFormat("m_%d%dchestItem%dPositionY", x, y, i)->getCString(), "0");
				data2[String::createWithFormat("chestItem%dIsShop", i)->getCString()] = def->getStringForKey(String::createWithFormat("m_%d%dchestItem%dIsShop", x, y, i)->getCString(), "0");
			}

			data2["skillItemCnt"] = def->getStringForKey(String::createWithFormat("m_%d%dskillItemCnt", x, y)->getCString(), "0").c_str();
			int skillItemSize = std::atoi(data2["skillItemCnt"].c_str());
			//def->setStringForKey(String::createWithFormat("m_%d%dskillItemCnt", x, y)->getCString(), data2["skillItemCnt"]);
			for (int i = 1; i <= skillItemSize; i++)
			{
				data2[String::createWithFormat("skillItem%dID", i)->getCString()] = def->getStringForKey(String::createWithFormat("m_%d%dskillItem%dID", x, y, i)->getCString(), "0");
				data2[String::createWithFormat("skillItem%dPositionX", i)->getCString()] = def->getStringForKey(String::createWithFormat("m_%d%dskillItem%dPositionX", x, y, i)->getCString(), "0");
				data2[String::createWithFormat("skillItem%dPositionY", i)->getCString()] = def->getStringForKey(String::createWithFormat("m_%d%dskillItem%dPositionY", x, y, i)->getCString(), "0");
				data2[String::createWithFormat("skillItem%dIsShop", i)->getCString()] = def->getStringForKey(String::createWithFormat("m_%d%dskillItem%dIsShop", x, y, i)->getCString(), "0");
				data2[String::createWithFormat("skillItem%dCurrentPoint", i)->getCString()] = def->getStringForKey(String::createWithFormat("m_%d%dskillItem%dCurrentPoint", x, y, i)->getCString(), "0");
			}

			data2["armorItemCnt"] = def->getStringForKey(String::createWithFormat("m_%d%darmorItemCnt", x, y)->getCString(), "0").c_str();
			int armorItemSize = std::atoi(data2["armorItemCnt"].c_str());
			//	def->setStringForKey(String::createWithFormat("m_%d%darmorItemCnt", x, y)->getCString(), data2["armorItemCnt"]);
			for (int i = 1; i <= armorItemSize; i++)
			{
				data2[String::createWithFormat("armorItem%dID", i)->getCString()] = def->getStringForKey(String::createWithFormat("m_%d%darmorItem%dID", x, y, i)->getCString(), "0");
				data2[String::createWithFormat("armorItem%dPositionX", i)->getCString()] = def->getStringForKey(String::createWithFormat("m_%d%darmorItem%dPositionX", x, y, i)->getCString(), "0");
				data2[String::createWithFormat("armorItem%dPositionY", i)->getCString()] = def->getStringForKey(String::createWithFormat("m_%d%darmorItem%dPositionY", x, y, i)->getCString(), "0");
				data2[String::createWithFormat("armorItem%dIsShop", i)->getCString()] = def->getStringForKey(String::createWithFormat("m_%d%darmorItem%dIsShop", x, y, i)->getCString(), "0");
			}

		}

		// secret & treasure
		if (type == myEnum::kRoomType::kRTSecret || type == myEnum::kRoomType::kRTTreasure)
		{
			data["itemOpened"] = def->getIntegerForKey(String::createWithFormat("m_%d%ditemOpened", x, y)->getCString(), 0);
			data["secondBG"] = def->getIntegerForKey(String::createWithFormat("m_%d%dsecondBG", x, y)->getCString(), 0);
		}

		// block (data)

		//def->setStringForKey(String::createWithFormat("m_%d%ditemCnt", x, y)->getCString(), data2["itemCnt"]);
		data2["itemCnt"] = def->getStringForKey(String::createWithFormat("m_%d%ditemCnt", x, y)->getCString(), "0").c_str();
		int itemSize = std::atoi(data2["itemCnt"].c_str());
		//int itemSize = std::atoi(def->getStringForKey(String::createWithFormat("m_%d%ditemCnt", x, y)->getCString(), 0).c_str());
		for (int i = 1; i <= itemSize; i++)
		{
			data2[String::createWithFormat("item%dName", i)->getCString()] = def->getStringForKey(String::createWithFormat("m_%d%ditem%dName", x, y, i)->getCString(), "0");
			data2[String::createWithFormat("item%dPositionX", i)->getCString()] = def->getStringForKey(String::createWithFormat("m_%d%ditem%dPositionX", x, y, i)->getCString(), "0");
			data2[String::createWithFormat("item%dPositionY", i)->getCString()] = def->getStringForKey(String::createWithFormat("m_%d%ditem%dPositionY", x, y, i)->getCString(), "0");
			data2[String::createWithFormat("item%dIsShop", i)->getCString()] = def->getStringForKey(String::createWithFormat("m_%d%ditem%dIsShop", x, y, i)->getCString(), "0");
		}
	
		// monster & boss

		if (type == myEnum::kRoomType::kRTMonster || type == myEnum::kRoomType::kRTBoss)
		{
			data2["brickCnt"] = def->getStringForKey(String::createWithFormat("m_%d%dbrickCnt", x, y)->getCString(), "0").c_str();
			int brickSize = std::atoi(data2["brickCnt"].c_str());
			//def->setStringForKey(String::createWithFormat("m_%d%dbrickCnt", x, y)->getCString(), data2["brickCnt"]);
			for (int i = 1; i <= brickSize; i++)
			{
				data2[String::createWithFormat("brick%dID", i)->getCString()] = def->getStringForKey(String::createWithFormat("m_%d%dbrick%dID", x, y, i)->getCString(), "0");
				data2[String::createWithFormat("brick%dPositionX", i)->getCString()] = def->getStringForKey(String::createWithFormat("m_%d%dbrick%dPositionX", x, y, i)->getCString(), "0");
				data2[String::createWithFormat("brick%dPositionY", i)->getCString()] = def->getStringForKey(String::createWithFormat("m_%d%dbrick%dPositionY", x, y, i)->getCString(), "0");
			}
		}

	}


}


