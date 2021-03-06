#pragma once
#ifndef __LOADING_SCENE_H__
#define __LOADING_SCENE_H__

#include "cocos2d.h"
#include "MapManager.h"
#include "HeroData.h"
#include "Definitions.h"
#include "GameScene.h"

class LoadingScene : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene(const char * mapName);

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static create()" method manually
	CREATE_FUNC(LoadingScene);
	
private:

	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;

	void onEnter();
	void GoToGameScene();

};

#endif // __LOADING_SCENE_H__
