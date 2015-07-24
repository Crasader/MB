#pragma once
#ifndef __MAP_DRAW_MANAGER_H__
#define __MAP_DRAW_MANAGER_H__

#include "cocos2d.h"
#include "Definitions.h"

#include "cocostudio\CocoStudio.h"
#include "ui\CocosGUI.h"

#include "MapManager.h"
#include "GameScene.h"

using namespace std;

class MapDrawManager : public cocos2d::Node
{
private:
	bool isZoomed = false;

	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;
	cocos2d::Layer * layer;

	cocos2d::Node * mapNode;
	cocos2d::Node * zoomInMapNode;
	cocos2d::ui::Button * zoomInBtn;
	cocos2d::ui::Button * zoomOutBtn;

	MapManager * mapManager;
	//cocos2d::SpriteBatchNode * spriteBatch;

	void SetVisibleState(int x, int y, bool secretVisible, bool secretLockOpen);

public:
	CC_SYNTHESIZE(bool, _curse, Curse);
	CC_SYNTHESIZE(bool, _allView, AllView);
	CC_SYNTHESIZE(bool, _allViewType, AllViewType);

	MapDrawManager(cocos2d::Layer * layer);
	static MapDrawManager* create(cocos2d::Layer * layer);
	
	void DrawMap();
	void ReDrawMap();

	void MapZoom();
	void ClearZoomMap();
	void onTouchMap(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);

	void SetBtnEnable(bool b);
};

#endif //__MAP_DRAW_MANAGER_H__