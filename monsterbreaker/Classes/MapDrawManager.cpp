#include "MapDrawManager.h"
#include <stdlib.h>
USING_NS_CC;
using namespace ui;

MapDrawManager::MapDrawManager(cocos2d::Layer * layer) : layer(layer)
{
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();
	mapManager = MapManager::getInstance();
}
MapDrawManager* MapDrawManager::create(cocos2d::Layer * layer)
{
	auto pNode = new MapDrawManager(layer);
	pNode->autorelease();
	return pNode;
}

void MapDrawManager::DrawMap()
{
	// init
	auto cache = SpriteFrameCache::sharedSpriteFrameCache();
	cache->addSpriteFramesWithFile("Map/Map.plist", "Map/Map.png");
	auto spriteBatch = SpriteBatchNode::create("Map/Map.png");

	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto mapBGSprite = CSLoader::createNode("Map/Map.csb");
	auto spr = mapBGSprite->getChildByName("mapBG");
	zoomInBtn = (Button*)mapBGSprite->getChildByName("btn");
	zoomInBtn->addTouchEventListener(CC_CALLBACK_2(MapDrawManager::onTouchMap, this));
	mapNode = Node::create();
	mapNode->setPosition(visibleSize.width - spr->getContentSize().width * 0.5f, visibleSize.height - spr->getContentSize().height * 0.5f);
	mapNode->addChild(mapBGSprite, -1);

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
				switch (mapManager->map[i][j].type)
				{
				case myEnum::kRoomType::kRTNone:
					break;
				case myEnum::kRoomType::kRTStart:
					if (_allView || mapManager->map[i][j].visible)
						temp = Sprite::createWithSpriteFrameName("Map/OpenedRoom.png");
					break;
				case myEnum::kRoomType::kRTMonster:
					if (_allView || mapManager->map[i][j].visible)
					{
						if (mapManager->map[i][j].exp)
							temp = Sprite::createWithSpriteFrameName("Map/OpenedRoom.png");
						else
							temp = Sprite::createWithSpriteFrameName("Map/ClosedRoom.png");
					}
					break;
				case myEnum::kRoomType::kRTShop:
					if (_allView || mapManager->map[i][j].visible)
					{
						if (mapManager->map[i][j].exp)
							temp = Sprite::createWithSpriteFrameName("Map/OpenedRoom.png");
						else
							temp = Sprite::createWithSpriteFrameName("Map/ClosedRoom.png");
					}
					if (_allViewType || mapManager->map[i][j].visible)
					{
						tempType = Sprite::createWithSpriteFrameName("Map/Shop.png");
					}
					break;
				case myEnum::kRoomType::kRTHelp:
					if (_allView || mapManager->map[i][j].visible)
					{
						if (mapManager->map[i][j].exp)
							temp = Sprite::createWithSpriteFrameName("Map/OpenedRoom.png");
						else
							temp = Sprite::createWithSpriteFrameName("Map/ClosedRoom.png");
					}
					if (_allViewType || mapManager->map[i][j].visible)
					{
						tempType = Sprite::createWithSpriteFrameName("Map/Help.png");
					}
					break;
				case myEnum::kRoomType::kRTBoss:
					if (_allView || mapManager->map[i][j].visible)
					{
						if (mapManager->map[i][j].exp)
							temp = Sprite::createWithSpriteFrameName("Map/OpenedRoom.png");
						else
							temp = Sprite::createWithSpriteFrameName("Map/ClosedRoom.png");
					}
					if (_allViewType || mapManager->map[i][j].visible)
					{
						tempType = Sprite::createWithSpriteFrameName("Map/Boss.png");
					}
					break;
				case myEnum::kRoomType::kRTTreasure:
					if (_allView || mapManager->map[i][j].visible)
					{
						if (mapManager->map[i][j].exp)
							temp = Sprite::createWithSpriteFrameName("Map/OpenedRoom.png");
						else
							temp = Sprite::createWithSpriteFrameName("Map/ClosedRoom.png");
					}
					if (_allViewType || mapManager->map[i][j].visible)
					{
						tempType = Sprite::createWithSpriteFrameName("Map/Treasure.png");
					}
					break;
				case myEnum::kRoomType::kRTSecret:
					if (mapManager->map[i][j].visible)
					{
						if (mapManager->map[i][j].exp)
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
		hero->setPosition(sX + tempSize.width * mapManager->getHeroY(), sY - tempSize.height * mapManager->getHeroX());
		spriteBatch->addChild(hero, ZINDEX_STATUS_MAP_ROOM);

	}
	mapNode->addChild(spriteBatch);
	layer->addChild(mapNode, ZINDEX_STATUS_MAP_BG, "map");
}
void MapDrawManager::ReDrawMap()
{
//	layer->removeChild(spriteBatch);
	mapNode->removeFromParentAndCleanup(true);
	DrawMap();
}

void MapDrawManager::MapZoom()
{
	// init
	auto cache = SpriteFrameCache::sharedSpriteFrameCache();
	cache->addSpriteFramesWithFile("Map/Map.plist", "Map/Map.png");
	auto spriteBatch = SpriteBatchNode::create("Map/Map.png");

	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto mapBGSprite = CSLoader::createNode("Map/Map.csb");
	zoomOutBtn = (Button*)mapBGSprite->getChildByName("btn");
	zoomOutBtn->addTouchEventListener(CC_CALLBACK_2(MapDrawManager::onTouchMap, this));
	zoomInMapNode = Node::create();
	zoomInMapNode->addChild(mapBGSprite, -1);

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
				switch (mapManager->map[i][j].type)
				{
				case myEnum::kRoomType::kRTNone:
					break;
				case myEnum::kRoomType::kRTStart:
					if (_allView || mapManager->map[i][j].visible)
						temp = Sprite::createWithSpriteFrameName("Map/OpenedRoom.png");
					break;
				case myEnum::kRoomType::kRTMonster:
					if (_allView || mapManager->map[i][j].visible)
					{
						if (mapManager->map[i][j].exp)
							temp = Sprite::createWithSpriteFrameName("Map/OpenedRoom.png");
						else
							temp = Sprite::createWithSpriteFrameName("Map/ClosedRoom.png");
					}
					break;
				case myEnum::kRoomType::kRTShop:
					if (_allView || mapManager->map[i][j].visible)
					{
						if (mapManager->map[i][j].exp)
							temp = Sprite::createWithSpriteFrameName("Map/OpenedRoom.png");
						else
							temp = Sprite::createWithSpriteFrameName("Map/ClosedRoom.png");
					}
					if (_allViewType || mapManager->map[i][j].visible)
					{
						tempType = Sprite::createWithSpriteFrameName("Map/Shop.png");
					}
					break;
				case myEnum::kRoomType::kRTHelp:
					if (_allView || mapManager->map[i][j].visible)
					{
						if (mapManager->map[i][j].exp)
							temp = Sprite::createWithSpriteFrameName("Map/OpenedRoom.png");
						else
							temp = Sprite::createWithSpriteFrameName("Map/ClosedRoom.png");
					}
					if (_allViewType || mapManager->map[i][j].visible)
					{
						tempType = Sprite::createWithSpriteFrameName("Map/Help.png");
					}
					break;
				case myEnum::kRoomType::kRTBoss:
					if (_allView || mapManager->map[i][j].visible)
					{
						if (mapManager->map[i][j].exp)
							temp = Sprite::createWithSpriteFrameName("Map/OpenedRoom.png");
						else
							temp = Sprite::createWithSpriteFrameName("Map/ClosedRoom.png");
					}
					if (_allViewType || mapManager->map[i][j].visible)
					{
						tempType = Sprite::createWithSpriteFrameName("Map/Boss.png");
					}
					break;
				case myEnum::kRoomType::kRTTreasure:
					if (_allView || mapManager->map[i][j].visible)
					{
						if (mapManager->map[i][j].exp)
							temp = Sprite::createWithSpriteFrameName("Map/OpenedRoom.png");
						else
							temp = Sprite::createWithSpriteFrameName("Map/ClosedRoom.png");
					}
					if (_allViewType || mapManager->map[i][j].visible)
					{
						tempType = Sprite::createWithSpriteFrameName("Map/Treasure.png");
					}
					break;
				case myEnum::kRoomType::kRTSecret:
					if (mapManager->map[i][j].visible)
					{
						if (mapManager->map[i][j].exp)
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
		hero->setPosition(sX + tempSize.width * mapManager->getHeroY(), sY - tempSize.height * mapManager->getHeroX());
		spriteBatch->addChild(hero, ZINDEX_STATUS_MAP_ROOM);

	}
	zoomInMapNode->addChild(spriteBatch);
	zoomInMapNode->setScale(3);
	zoomInMapNode->setPosition(visibleSize.width*0.5f, visibleSize.height*0.5f);
	layer->addChild(zoomInMapNode, 10000, "mapZoom");
}

void MapDrawManager::onTouchMap(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type)
{
	if (!isZoomed)
	{
		switch (type){
		case Widget::TouchEventType::BEGAN:
			break;
		case Widget::TouchEventType::MOVED:
			break;
		case Widget::TouchEventType::ENDED:
		{
			isZoomed = true;
			MapZoom();
			auto gs = (GameScene*)layer;
			gs->SetMapZoomIn();
		}
		break;
		case Widget::TouchEventType::CANCELED:
			break;
		default:
			break;
		}
	}
	else
	{
		switch (type){
		case Widget::TouchEventType::BEGAN:
			break;
		case Widget::TouchEventType::MOVED:
			break;
		case Widget::TouchEventType::ENDED:
		{
			ClearZoomMap();
			isZoomed = false;
			auto gs = (GameScene*)layer;
			gs->SetMapZoomOut();

		}
		break;
		case Widget::TouchEventType::CANCELED:
			break;
		default:
			break;
		}
	}
}

void MapDrawManager::ClearZoomMap()
{
	auto node = layer->getChildByName("mapZoom");
	node->removeFromParentAndCleanup(true);
}

void MapDrawManager::SetBtnEnable(bool b)
{
	zoomInBtn->setEnabled(b);
}

