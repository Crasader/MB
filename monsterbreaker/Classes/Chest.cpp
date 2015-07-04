#include"Chest.h"
USING_NS_CC;
using namespace ui;

Chest::Chest(Hero * hero, cocos2d::Layer * layer) : hero(hero), layer(layer)
{
}
Chest* Chest::create(Hero * hero, cocos2d::Layer * layer)
{
	auto pSprite = new Chest(hero, layer);
	pSprite->autorelease();
	pSprite->InitSprite();

	return pSprite;
}

void Chest::InitSprite()
{
	auto origin = Director::getInstance()->getVisibleOrigin();
	auto node = (CSLoader::createNode("Chest/Chest.csb"));
	node->setPosition(origin.x, origin.y);
	//	node->setPosition(this->getContentSize().width / 2, this->getContentSize().height / 2);
	this->addChild(node);

	auto act = CSLoader::createTimeline("Chest/Chest.csb");
	act->gotoFrameAndPlay(0, 0, false);
	node->runAction(act);

	auto btn = dynamic_cast<Button*>(node->getChildByName("btn"));
	btn->setEnabled(true);
	btn->setPosition(Vec2(origin.x, origin.y));
	btn->addTouchEventListener(CC_CALLBACK_2(Chest::onTouch, this));

	while (true)
	{
		r = rand() % ITEM_MAX_SIZE + 1;
		if (!hero->HasItem(r) && (r != ITEM_TRUTH && r != ITEM_BLACK_AND_WHITE)) break;
	}

}


void Chest::onTouch(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type)
{
	if (!clicked)
	{
		switch (type){
		case Widget::TouchEventType::BEGAN:
			break;
		case Widget::TouchEventType::MOVED:
			break;
		case Widget::TouchEventType::ENDED:
		{
			Open();
		}
		break;
		case Widget::TouchEventType::CANCELED:
			break;
		default:
			break;
		}

	}
}

void Chest::Open()
{
	auto origin = Director::getInstance()->getVisibleOrigin();
	auto visibleSize = Director::getInstance()->getVisibleSize();

	clicked = true;

	hero->SetItem(r);
	auto doorManager = static_cast<DoorManager*>(layer->getChildByName("DoorManager"));
	if (r == ITEM_THE_MAP || r == ITEM_THE_COMPASS)
	{
		auto mapManager = MapManager::getInstance();
		mapManager->setAllView(hero->HasItem(ITEM_THE_MAP));
		mapManager->setAllViewType(hero->HasItem(ITEM_THE_COMPASS));
		mapManager->ReDrawMap();
	}
	else if (r == ITEM_SECRET_MASTER)
		doorManager->OpenAllSecretDoor();
	else if (r == ITEM_SCAVENGER)
		doorManager->visibleAllSecretDoor(true);

	int x = MapManager::getInstance()->getHeroX();
	int y = MapManager::getInstance()->getHeroY();

	MapManager::getInstance()->map[x][y].data["itemOpened"] = 1;
	
	// action
	auto act = CSLoader::createTimeline("Chest/Chest.csb");
	act->gotoFrameAndPlay(0, 60, false);
	this->runAction(act);

	auto effectManager = static_cast<EffectManager*>(layer->getChildByName("EffectManager"));
	effectManager->ShowItemDes(r);

}
void Chest::Opened()
{
	auto act = CSLoader::createTimeline("Chest/Chest.csb");
	act->gotoFrameAndPlay(60, 60, false);
	this->runAction(act);
	clicked = true;
}
void Chest::OpenFail()
{
	auto act = CSLoader::createTimeline("Chest/Chest.csb");
	act->gotoFrameAndPlay(0, 30, false);
	this->runAction(act);
	clicked = false;
}

void Chest::SetItem(int itemNum)
{
	r = itemNum;
}
