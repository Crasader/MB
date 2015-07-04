#pragma once
#ifndef __SPLASH_SCENE_H__
#define __SPLASH_SCENE_H__

#include "cocos2d.h"
#include "PrologScene.h"
#include "MainMenuScene.h"
#include "Definitions.h"
//#include "SimpleAudioEngine.h"
#include "SoundManager.h"

class SplashScene : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(SplashScene);

private:
	void GotoMainMenuScene( float dt );
	void GotoMainPrologScene(float dt);
	void LoadData();

};

#endif // __SPLASH_SCENE_H__
