#include "SecretManager.h"

USING_NS_CC;

SecretManager::~SecretManager()
{

}
SecretManager::SecretManager(cocos2d::Layer * layer, Hero * hero) : layer(layer), hero(hero)
{
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();
	contentSize = Size(visibleSize.width / 10, visibleSize.height / 25);
	startPoint = Vec2(0, contentSize.height * 20);
}

SecretManager* SecretManager::create(cocos2d::Layer * layer, Hero * hero)
{
	auto pNode = new SecretManager(layer, hero);
	pNode->autorelease();
	return pNode;
}

void SecretManager::createSecretItem()
{
	auto mapManager = MapManager::getInstance();

	int _unlockEndingNum = UserDefault::sharedUserDefault()->getIntegerForKey("u_ending", 0);

	std::string mapType = MapManager::getInstance()->getLevelName();

	if (mapType.compare("MV") == 0 && _unlockEndingNum >= 1 || mapType.compare("HV") == 0 && _unlockEndingNum >= 3){
		// create B&W
		auto chest = Chest::create(hero, layer);
		chest->setPosition(Vec2(visibleSize.width * 0.5f + origin.x, visibleSize.height* 0.5f + origin.y));
		layer->addChild(chest, ZINDEX_CHEST_SPRITE);

		chest->SetItem(ITEM_BLACK_AND_WHITE);

		if (mapManager->GetCurrentRoomData().data["itemOpened"] == 1)
			chest->Opened();

	}
	else if (mapType.compare("MC") == 0 && _unlockEndingNum >= 5 || mapType.compare("HC") == 0 && _unlockEndingNum >= 5)
	{
		// create TRUTH
		auto chest = Chest::create(hero, layer);
		chest->setPosition(Vec2(visibleSize.width * 0.5f + origin.x, visibleSize.height* 0.5f + origin.y));
		layer->addChild(chest, ZINDEX_CHEST_SPRITE);

		chest->SetItem(ITEM_TRUTH);

		if (mapManager->GetCurrentRoomData().data["itemOpened"] == 1)
			chest->Opened();
	}
	else{
		if (mapManager->GetCurrentRoomData().data["itemOpened"] == 0)
		{
			int r = rand() % 4 + 1;

			SpriteFrameCache::getInstance()->addSpriteFramesWithFile("SecondBG/SecondBG.plist", "SecondBG/SecondBG.png");

			auto data = __Dictionary::createWithContentsOfFile("Level/S.plist");
			int cnt = data->valueForKey("cnt")->intValue();
			int r_scene = rand() % cnt + 1;

			auto dic = (__Dictionary *)data->objectForKey(String::createWithFormat("%d", r_scene)->getCString());
			int objCnt = dic->valueForKey("cnt")->intValue();

			for (int i = 1; i <= objCnt; i++)
			{
				auto objDic = (__Dictionary *)dic->objectForKey(String::createWithFormat("%d", i)->getCString());
				int objX = objDic->valueForKey("x")->intValue();
				int objY = objDic->valueForKey("y")->intValue();
				std::string type = objDic->valueForKey("type")->getCString();

				cocos2d::Node * secondBG = nullptr;
				if (type.compare("o") == 0)
				{
					switch (r)
					{
					case 1:	// coin
					{
						auto spr = ItemCoin::create(layer, hero);
						spr->setPosition(Vec2(startPoint.x + contentSize.width * objY + contentSize.width * 0.5f + origin.x, startPoint.y - contentSize.height * objX + contentSize.height / 2 + origin.y));
						layer->addChild(spr, ZINDEX_BRICK_SPRITE, myEnum::kMyTag::kItemTag);
						secondBG = Sprite::createWithSpriteFrameName("SecondBG/bgCoin.png");
					}
					break;
					case 2:	// heart
					{
						auto spr = ItemHeart::create(layer, hero, false);
						spr->setPosition(Vec2(startPoint.x + contentSize.width * objY + contentSize.width * 0.5f + origin.x, startPoint.y - contentSize.height * objX + contentSize.height / 2 + origin.y));
						layer->addChild(spr, ZINDEX_BRICK_SPRITE, myEnum::kMyTag::kItemTag);
						secondBG = Sprite::createWithSpriteFrameName("SecondBG/bgHeart.png");
					}
					break;
					case 3:	// key
					{
						auto spr = ItemKey::create(layer, hero, false);
						spr->setPosition(Vec2(startPoint.x + contentSize.width * objY + contentSize.width * 0.5f + origin.x, startPoint.y - contentSize.height * objX + contentSize.height / 2 + origin.y));
						layer->addChild(spr, ZINDEX_BRICK_SPRITE, myEnum::kMyTag::kItemTag);
						secondBG = Sprite::createWithSpriteFrameName("SecondBG/bgKey.png");
					}
					break;
					case 4:	// bomb
					{
						auto spr = ItemBomb::create(layer, hero, false);
						spr->setPosition(Vec2(startPoint.x + contentSize.width * objY + contentSize.width * 0.5f + origin.x, startPoint.y - contentSize.height * objX + contentSize.height / 2 + origin.y));
						layer->addChild(spr, ZINDEX_BRICK_SPRITE, myEnum::kMyTag::kItemTag);
						secondBG = Sprite::createWithSpriteFrameName("SecondBG/bgBomb.png");
					}
					break;
					}
				}
				if (secondBG != nullptr)
				{
					secondBG->setPosition(visibleSize.width*0.5f, visibleSize.height *0.4);
					layer->addChild(secondBG, ZINDEX_STATUS_BG);
				}
			}
			int x = mapManager->getHeroX();
			int y = mapManager->getHeroY();

			mapManager->map[x][y].data["itemOpened"] = 1;
			mapManager->map[x][y].data["secondBG"] = r;
		}
		else
		{
			SpriteFrameCache::getInstance()->addSpriteFramesWithFile("SecondBG/SecondBG.plist", "SecondBG/SecondBG.png");
			cocos2d::Node * secondBG = nullptr;
			switch (mapManager->GetCurrentRoomData().data["secondBG"])
			{
			case 0:
				break;
			case 1:
				secondBG = Sprite::createWithSpriteFrameName("SecondBG/bgCoin.png");
				break;
			case 2:
				secondBG = Sprite::createWithSpriteFrameName("SecondBG/bgHeart.png");
				break;
			case 3:
				secondBG = Sprite::createWithSpriteFrameName("SecondBG/bgKey.png");
				break;
			case 4:
				secondBG = Sprite::createWithSpriteFrameName("SecondBG/bgBomb.png");
				break;
			default:
				break;
			}
			if (secondBG != nullptr)
			{
				secondBG->setPosition(visibleSize.width*0.5f, visibleSize.height *0.4);
				layer->addChild(secondBG, ZINDEX_STATUS_BG);
			}
		}

	}

}