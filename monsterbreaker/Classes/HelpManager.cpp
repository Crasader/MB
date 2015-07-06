#include "HelpManager.h"

USING_NS_CC;

HelpManager::~HelpManager()
{

}
HelpManager::HelpManager(cocos2d::Layer * layer, Hero * hero) : layer(layer), hero(hero)
{
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();
}

HelpManager* HelpManager::create(cocos2d::Layer * layer, Hero * hero)
{
	auto pNode = new HelpManager(layer, hero);
	pNode->autorelease();
	return pNode;
}

void HelpManager::createCageAndData()
{
	mapManager = MapManager::getInstance();
	int x = mapManager->GetCurrentRoomData().x;
	int y = mapManager->GetCurrentRoomData().y;

	c1 = Cage::create(layer, hero, 1);
	c1->setPosition(Vec2(visibleSize.width * 0.5f + origin.x, visibleSize.height* 0.7f + origin.y));
	layer->addChild(c1, ZINDEX_CAGE_SPRITE);
	c1->setTag(1);

	c2 = Cage::create(layer, hero, 1);
	c2->setPosition(Vec2(visibleSize.width * 0.3f + origin.x, visibleSize.height* 0.5f + origin.y));
	layer->addChild(c2, ZINDEX_CAGE_SPRITE);
	c2->setTag(2);

	c3 = Cage::create(layer, hero, 1);
	c3->setPosition(Vec2(visibleSize.width * 0.7f + origin.x, visibleSize.height* 0.5f + origin.y));
	layer->addChild(c3, ZINDEX_CAGE_SPRITE);
	c3->setTag(3);

	if (mapManager->GetCurrentRoomData().data["c1"] != 0)
	{
		c1->btn->setEnabled(false);
		c1->setVisible(false);
	}
	if (mapManager->GetCurrentRoomData().data["c2"] != 0)
	{
		c2->btn->setEnabled(false);
		c2->setVisible(false);
	}
	if (mapManager->GetCurrentRoomData().data["c3"] != 0)
	{
		c3->btn->setEnabled(false);
		c3->setVisible(false);
	}

	// 1 : Check & Create HelperMan
	if (mapManager->GetCurrentRoomData().data["HMClicked"] == 0)
	{
		HelperMan * hm = nullptr;

		if (mapManager->GetCurrentRoomData().data["HM"] == myEnum::kHelperMan::kHMWarrior)
			hm = HMWarrior::create(layer, hero, true);
		else if (mapManager->GetCurrentRoomData().data["HM"] == myEnum::kHelperMan::kHMRifleMan)
			hm = HMRifleMan::create(layer, hero, true);
		else if (mapManager->GetCurrentRoomData().data["HM"] == myEnum::kHelperMan::kHMPriest)
			hm = HMPriest::create(layer, hero, true);
		else if (mapManager->GetCurrentRoomData().data["HM"] == myEnum::kHelperMan::kHMArcher)
			hm = HMArcher::create(layer, hero, true);
		else
		{
			// random 
			int r = 0;
			int size = hero->helperList.size();
			while (true)
			{
				bool same = false;
				r = rand() % 4 + 1;
				for (int i = 0; i < size; i++)
				{
					if (hero->helperList.at(i) == r)
					{
						same = true;
						break;
					}
				}
				if (!same)
					break;
			}
			switch (r)
			{
			case myEnum::kHelperMan::kHMWarrior:
				hm = HMWarrior::create(layer, hero, true);
				mapManager->map[x][y].data["HM"] = myEnum::kHelperMan::kHMWarrior;
				break;
			case myEnum::kHelperMan::kHMRifleMan:
				hm = HMRifleMan::create(layer, hero, true);
				mapManager->map[x][y].data["HM"] = myEnum::kHelperMan::kHMRifleMan;
				break;
			case myEnum::kHelperMan::kHMPriest:
				hm = HMPriest::create(layer, hero, true);
				mapManager->map[x][y].data["HM"] = myEnum::kHelperMan::kHMPriest;
				break;
			case myEnum::kHelperMan::kHMArcher:
				hm = HMArcher::create(layer, hero, true);
				mapManager->map[x][y].data["HM"] = myEnum::kHelperMan::kHMArcher;
				break;
			}
		}
		if (hm == nullptr)
		{
			//CC_ASSERT("HelperMan NULL Exceoption!!");
		}
		else
		{
			hm->setPosition(c1->getPosition());
			layer->addChild(hm, ZINDEX_HERO_SPRITE);
		}
	}

	// 2 : Check & Create Weapon 

	// new weapon
	if (mapManager->GetCurrentRoomData().data["weapon"] == 0)
	{
		String weaponType = hero->getWeaponType();
		String weaponName = hero->getWeaponName();
		if (weaponType.compare("Staff") == 0)
		{
			int wID = Utils::GetInstance()->GetWeaponID(weaponName.getCString());
			while (true)
			{
				int r = rand() % ITEM_WEAPON_STAFF_SIZE + ITEM_WEAPON_STAFF_START_NUM;
				if (wID != r)
				{
					wID = r;
					break;
				}
			}
			if (wID != 0)
			{
				auto weapon = Weapon::create(layer, hero, "Staff", Utils::GetInstance()->GetWeaponName(wID).c_str(), true);
				weapon->setPosition(c2->getPosition());
				layer->addChild(weapon, ZINDEX_HERO_WEAPON);
				mapManager->map[x][y].data["weapon"] = wID;
			}
		}
		else if (weaponType.compare("Sword") == 0)
		{
			int wID = Utils::GetInstance()->GetWeaponID(weaponName.getCString());
			while (true)
			{
				int r = rand() % ITEM_WEAPON_SWORD_SIZE + ITEM_WEAPON_SWORD_START_NUM;
				if (wID != r)
				{
					wID = r;
					break;
				}
			}
			if (wID != 0)
			{
				auto weapon = Weapon::create(layer, hero, "Sword", Utils::GetInstance()->GetWeaponName(wID).c_str(), true);
				weapon->setPosition(c2->getPosition());
				layer->addChild(weapon, ZINDEX_HERO_WEAPON);
				mapManager->map[x][y].data["weapon"] = wID;
			}
		}
	}
	else // load weapon
	{
		int wID = mapManager->GetCurrentRoomData().data["weapon"];
		auto weapon = Weapon::create(layer, hero, hero->getWeaponType().c_str(), Utils::GetInstance()->GetWeaponName(wID).c_str(), true);
		weapon->setPosition(c2->getPosition());
		layer->addChild(weapon, ZINDEX_HERO_WEAPON);
	}
	Utils::FreeInstance();



	// 3 : Check & Create Items ( coin, bomb, heart )
	if (mapManager->GetCurrentRoomData().data["c3Item"] == 0)
	{
		int r2 = rand() % 3 + 1;
		switch (r2)
		{
		case 1:
			createCageInCoin();
			break;
		case 2:
			createCageInBomb();
			break;
		case 3:
			createCageInHeart();
			break;
		}
		mapManager->map[x][y].data["c3Item"] = 1;
	}
	
}

void HelpManager::createCageInCoin()
{
	auto item1 = ItemCoin::create(layer, hero);
	item1->setPosition(c3->getPosition() + Vec2(-item1->getContentSize().width, item1->getContentSize().height ));
	layer->addChild(item1, ZINDEX_ITEM_SPRITE, myEnum::kMyTag::kItemTag);
	auto item2 = ItemCoin::create(layer, hero);
	item2->setPosition(c3->getPosition() + item2->getContentSize());
	layer->addChild(item2, ZINDEX_ITEM_SPRITE, myEnum::kMyTag::kItemTag);
	auto item3 = ItemCoin::create(layer, hero);
	item3->setPosition(c3->getPosition());
	layer->addChild(item3, ZINDEX_ITEM_SPRITE, myEnum::kMyTag::kItemTag);
	auto item4 = ItemCoin::create(layer, hero);
	item4->setPosition(c3->getPosition() - item4->getContentSize());
	layer->addChild(item4, ZINDEX_ITEM_SPRITE, myEnum::kMyTag::kItemTag);
	auto item5 = ItemCoin::create(layer, hero);
	item5->setPosition(c3->getPosition() + Vec2(item5->getContentSize().width, -item5->getContentSize().height ));
	layer->addChild(item5, ZINDEX_ITEM_SPRITE, myEnum::kMyTag::kItemTag);

}
void HelpManager::createCageInBomb()
{
	auto item1 = ItemBomb::create(layer, hero, false);
	item1->setPosition(c3->getPosition() + Vec2(0, item1->getContentSize().height));
	layer->addChild(item1, ZINDEX_ITEM_SPRITE, myEnum::kMyTag::kItemTag);
	auto item2 = ItemBomb::create(layer, hero, false);
	item2->setPosition(c3->getPosition() + Vec2(-item2->getContentSize().width, 0));
	layer->addChild(item2, ZINDEX_ITEM_SPRITE, myEnum::kMyTag::kItemTag);
	auto item3 = ItemBomb::create(layer, hero, false);
	item3->setPosition(c3->getPosition() + Vec2(item3->getContentSize().width, 0));
	layer->addChild(item3, ZINDEX_ITEM_SPRITE, myEnum::kMyTag::kItemTag);
	auto item4 = ItemBomb::create(layer, hero, false);
	item4->setPosition(c3->getPosition() + Vec2(0, -item4->getContentSize().height));
	layer->addChild(item4, ZINDEX_ITEM_SPRITE, myEnum::kMyTag::kItemTag);

}
void HelpManager::createCageInHeart()
{
	auto item1 = ItemHalfHeart::create(layer, hero, false);
	item1->setPosition(c3->getPosition() + Vec2(-item1->getContentSize().width, item1->getContentSize().height ));
	layer->addChild(item1, ZINDEX_ITEM_SPRITE, myEnum::kMyTag::kItemTag);
	auto item2 = ItemHalfSoulHeart::create(layer, hero, false);
	item2->setPosition(c3->getPosition() + item2->getContentSize());
	layer->addChild(item2, ZINDEX_ITEM_SPRITE, myEnum::kMyTag::kItemTag);
	auto item3 = ItemHeart::create(layer, hero, false);
	item3->setPosition(c3->getPosition());
	layer->addChild(item3, ZINDEX_ITEM_SPRITE, myEnum::kMyTag::kItemTag);
	auto item4 = ItemSoulHeart::create(layer, hero, false);
	item4->setPosition(c3->getPosition() + Vec2(0, -item4->getContentSize().height));
	layer->addChild(item4, ZINDEX_ITEM_SPRITE, myEnum::kMyTag::kItemTag);

}

void HelpManager::createHeroHelperMan()
{
	int size = hero->helperList.size();
	HelperMan * hm = nullptr;
	for (int i = 0; i < size; i++)
	{
		auto hmID = hero->helperList.at(i);
		hm = createHelperMan(hmID);

		if (hm != nullptr)
		{
			if (i == 0) hm->setPosition(visibleSize.width * 0.7f, hero->getPositionY());
			else hm->setPosition(visibleSize.width*0.3f, hero->getPositionY());
			layer->addChild(hm, ZINDEX_HELPERMAN_SPRITE);
			helpermans.push_back(hm);
		}
		else
		{
			//CC_ASSERT("HelperMan Is NULL PTR, HM Didn't Have Created");
		}
	}
}

HelperMan * HelpManager::createHelperMan(int hmID)
{
	HelperMan * hm = nullptr;
	switch (hmID)
	{
	case myEnum::kHelperMan::kHMWarrior:
		hm = HMWarrior::create(layer, hero, false);
		break;
	case myEnum::kHelperMan::kHMArcher:
		hm = HMArcher::create(layer, hero, false);
		break;
	case myEnum::kHelperMan::kHMPriest:
		hm = HMPriest::create(layer, hero, false);
		break;
	case myEnum::kHelperMan::kHMRifleMan:
		hm = HMRifleMan::create(layer, hero, false);
		break;
	}
	if (hm == nullptr)
	{
		//CC_ASSERT("HelperMan Is NULL PTR, HM Didn't Have Created");
	}
	return hm;
}

void HelpManager::update(float dt)
{
}
void HelpManager::pause()
{
	int size = helpermans.size();
	for (int i = 0; i < size; i++)
	{
		helpermans.at(i)->pause();
	}
}
void HelpManager::resume()
{
	int size = helpermans.size();
	for (int i = 0; i < size; i++)
	{
		helpermans.at(i)->resume();
	}
}

void HelpManager::startHelperUpdateAI()
{
	int size = helpermans.size();
	for (int i = 0; i < size; i++)
	{
		helpermans.at(i)->scheduleUpdate();
	}
}
void HelpManager::startAIBeforeBattle()
{
	int size = helpermans.size();
	for (int i = 0; i < size; i++)
	{
		helpermans.at(i)->AIBeforeBattle();
	}

}
void HelpManager::startAIDoingBattle()
{
	int size = helpermans.size();
	for (int i = 0; i < size; i++)
	{
		helpermans.at(i)->AIDoingBattle();
	}

}
void HelpManager::startAIAfterBattle()
{
	int size = helpermans.size();
	for (int i = 0; i < size; i++)
	{
		helpermans.at(i)->AIAfterBattle();
	}

}



