#include "TreasureManager.h"

USING_NS_CC;

TreasureManager::~TreasureManager()
{

}
TreasureManager::TreasureManager(cocos2d::Layer * layer, Hero * hero) : layer(layer), hero(hero)
{
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();
	contentSize = Size(visibleSize.width / 10, visibleSize.height / 25);
	startPoint = Vec2(0, contentSize.height * 20);
}

TreasureManager* TreasureManager::create(cocos2d::Layer * layer, Hero * hero)
{
	auto pNode = new TreasureManager(layer, hero);
	pNode->autorelease();
	return pNode;
}

void TreasureManager::createTreasure()
{
	auto data = __Dictionary::createWithContentsOfFile("Level/T.plist");
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

		if (type.compare("o") == 0)
		{
			int r = rand() % 2 + 1;
			auto spr = Sprite::create(String::createWithFormat("Treasure/obj%d.png", r)->getCString());
			spr->setPosition(Vec2(startPoint.x + contentSize.width * objY + contentSize.width * 0.5f + origin.x, startPoint.y - contentSize.height * objX + contentSize.height / 2 + origin.y));
			layer->addChild(spr, ZINDEX_BRICK_SPRITE);
		}
	}
	auto chest = Chest::create(hero, layer);
	chest->setPosition(Vec2(visibleSize.width * 0.5f + origin.x, visibleSize.height* 0.5f + origin.y));
	layer->addChild(chest, ZINDEX_CHEST_SPRITE);
	
	// debug
	//chest->SetItem(15);

	auto mapManager = MapManager::getInstance();
	if (mapManager->GetCurrentRoomData().data["itemOpened"] == 1)
		chest->Opened();

}
