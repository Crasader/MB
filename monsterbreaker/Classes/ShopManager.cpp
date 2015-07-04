#include "ShopManager.h"

USING_NS_CC;

ShopManager::~ShopManager()
{

}
ShopManager::ShopManager(cocos2d::Layer * layer, Hero * hero) : layer(layer), hero(hero)
{
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();
	contentSize = Size(visibleSize.width / 10, visibleSize.height / 25);
	startPoint = Vec2(0, contentSize.height * 20);
//	mm = (MapManager*)layer->getChildByName("MapManager");
	mm = MapManager::getInstance();
}

ShopManager* ShopManager::create(cocos2d::Layer * layer, Hero * hero)
{
	auto pNode = new ShopManager(layer, hero);
	pNode->autorelease();
	return pNode;
}

void ShopManager::createShopItem()
{
	int x = mm->GetCurrentRoomData().x;
	int y = mm->GetCurrentRoomData().y;

	// craete merchant
	if (mm->GetCurrentRoomData().data["merchant"] == 0)
	{
		auto merchant = Merchant::create(layer, hero);
		merchant->setPosition(visibleSize.width*0.5f, visibleSize.height*0.7f);
		merchant->setScale(2);
		layer->addChild(merchant, ZINDEX_MONSTER_SPRITE);
	}
	
	int itemID = 0;
	// create shop item 1
	if (mm->GetCurrentRoomData().data["shopItem1"] == 0)
	{
		auto vec1 = Vec2(visibleSize.width *0.2 * 1, visibleSize.height * 0.5f);
		Item * item = nullptr;
		itemID = static_cast<int>(rand() % ITEM_MERCHANT_ITEM_SIZE + ITEM_MERCHANT_ITEM_START);

		switch (itemID)
		{
		case ITEM_MERCHANT_BOMB:
			item = ItemBomb::create(layer, hero, true);
			break;
		case ITEM_MERCHANT_KEY:
			item = ItemKey::create(layer, hero, true);
			break;
		case ITEM_MERCHANT_HALF_HEART:
			item = ItemHalfHeart::create(layer, hero, true);
			break;
		case ITEM_MERCHANT_HEART:
			item = ItemHeart::create(layer, hero, true);
			break;
		case ITEM_MERCHANT_SOUL_HEART:
			item = ItemSoulHeart::create(layer, hero, true);
			break;
		case ITEM_MERCHANT_HALF_SOUL_HEART:
			item = ItemHalfSoulHeart::create(layer, hero, true);
			break;
		}

		if (item != nullptr)
		{
			item->setPosition(vec1);
			layer->addChild(item, ZINDEX_ITEM_SPRITE, myEnum::kMyTag::kItemTag);
		}
		mm->map[x][y].data["shopItem1"] = 1;
	}

	// create shop item 2
	if (mm->GetCurrentRoomData().data["shopItem2"] == 0)
	{
		auto vec2 = Vec2(visibleSize.width *0.2 * 2, visibleSize.height * 0.5f);
		Item * item = nullptr;
		while (true)
		{
			int tempItemID = static_cast<int>(rand() % ITEM_MERCHANT_ITEM_SIZE + ITEM_MERCHANT_ITEM_START);
			if (itemID != tempItemID)
			{
				itemID = tempItemID;
				break;
			}
		}

		switch (itemID)
		{
		case ITEM_MERCHANT_BOMB:
			item = ItemBomb::create(layer, hero, true);
			break;
		case ITEM_MERCHANT_KEY:
			item = ItemKey::create(layer, hero, true);
			break;
		case ITEM_MERCHANT_HALF_HEART:
			item = ItemHalfHeart::create(layer, hero, true);
			break;
		case ITEM_MERCHANT_HEART:
			item = ItemHeart::create(layer, hero, true);
			break;
		case ITEM_MERCHANT_SOUL_HEART:
			item = ItemSoulHeart::create(layer, hero, true);
			break;
		case ITEM_MERCHANT_HALF_SOUL_HEART:
			item = ItemHalfSoulHeart::create(layer, hero, true);
			break;
		}

		if (item != nullptr)
		{
			item->setPosition(vec2);
			layer->addChild(item, ZINDEX_ITEM_SPRITE, myEnum::kMyTag::kItemTag);
		}
		mm->map[x][y].data["shopItem2"] = 1;
	}

	if (mm->GetCurrentRoomData().data["shopItem3"] == 0)
	{
		auto vec3 = Vec2(visibleSize.width *0.2 * 3, visibleSize.height * 0.5f);

		int r = 0;
		while (true)
		{
			r = rand() % ITEM_MAX_SIZE + 1;
			if (!hero->HasItem(r) && r != ITEM_TRUTH && r != ITEM_BLACK_AND_WHITE)
				break;
		}

		auto ch = ChestItem::create(layer, hero, r, true);
		ch->setPosition(vec3);
		layer->addChild(ch, ZINDEX_CHEST_ITEM, myEnum::kMyTag::kChestItemTag);

//		mm->GetCurrentRoomData().data["shopItem3"] = 1;
		mm->map[x][y].data["shopItem3"] = 1;
	}

	// class shop item
	if (mm->GetCurrentRoomData().data["shopItem4"] == 0)
	{
		auto vec4 = Vec2(visibleSize.width *0.2 * 4, visibleSize.height * 0.5f);

		// Warrior (armor item)
		if (hero->getName().compare("Warrior") == 0)
		{
			int r = rand() % ITEM_ARMOR_SIZE + ITEM_ARMOR_START_NUM;
			auto item = ArmorItem::create(layer, hero, r, true);
			item->setPosition(vec4);
			layer->addChild(item, ZINDEX_ITEM_SPRITE, myEnum::kMyTag::kArmorItemTag);
		}
		// Magician (skill item)
		else if (hero->getName().compare("Magician") == 0)
		{
			// new skill Item
			int r = 0;

			while (true)
			{
				r = rand() % SKILL_SIZE + SKILL_START;
				if (hero->getSkillID() != r) break;
			}

			auto item = SkillItem::create(layer, hero, r, true);
			item->setPosition(vec4);
			layer->addChild(item, ZINDEX_ITEM_SPRITE, myEnum::kMyTag::kSkillItemTag);
		}
		mm->map[x][y].data["shopItem4"] = 1;
	}


//	auto item3 = ItemKey::create(layer, hero, true);
//	item3->setPosition(visibleSize.width *0.25f * 3, visibleSize.height * 0.5f);
//	layer->addChild(item3, ZINDEX_ITEM_SPRITE);

}