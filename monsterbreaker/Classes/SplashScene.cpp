#include "SplashScene.h"

USING_NS_CC;

Scene* SplashScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = SplashScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool SplashScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	auto sm = SoundManager::getInstance();

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto backgroundSprite = Sprite::create("SplashScene/Logo_Y.png");
	backgroundSprite->setPosition( Vec2( visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y  ) );
	this->addChild( backgroundSprite );

//	this->scheduleOnce( schedule_selector( SplashScene::GotoMainMenuScene ), 0 );
	LoadData();
	SoundManager::getInstance()->playMySoundLogic("Solid");
	return true;
}

void SplashScene::GotoMainMenuScene( float dt )
{
	auto scene = MainMenuScene::createScene();
	
	Director::getInstance()->replaceScene( TransitionFade::create( 0.5 , scene ) );
}
void SplashScene::GotoMainPrologScene(float dt)
{
	auto scene = PrologScene::createScene();

	Director::getInstance()->replaceScene(TransitionFade::create(0.5, scene));
}
void SplashScene::LoadData()
{
	srand(time(NULL));
	
	auto def = UserDefault::sharedUserDefault();
	auto isBeginner = def->getBoolForKey("isBeginner", true);

	if (isBeginner)
	{
		this->scheduleOnce(schedule_selector(SplashScene::GotoMainPrologScene), 0);
	}
	else
	{
		this->scheduleOnce(schedule_selector(SplashScene::GotoMainMenuScene), 0);
	}

}