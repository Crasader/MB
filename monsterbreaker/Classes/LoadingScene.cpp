#include "LoadingScene.h"

USING_NS_CC;

std::string mapNameLS;
Scene* LoadingScene::createScene(const char * mapName)
{
	mapNameLS = mapName;
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
	auto layer = LoadingScene::create();
    // add layer as a child to scene
    scene->addChild(layer);
	
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool LoadingScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();

    return true;
}

void LoadingScene::onEnter()
{
	CCLayer::onEnter();
	
	auto loadingSpr = Sprite::create("Loading.png");
	loadingSpr->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(loadingSpr);

	auto fadeIn = FadeIn::create(0.5f);
	auto fadeOut = FadeOut::create(0.5f);
	auto seq = Sequence::create(fadeOut, fadeIn, NULL);

	auto repeat = RepeatForever::create(seq);
	loadingSpr->runAction(repeat);

	// load or create a map data
	MapManager * mm = MapManager::getInstance();
	if (mapNameLS.compare("Load") == 0)
	{
		mm->LoadAll();
		HeroData::getInstance()->LoadData();
	}
	else
	{
		mm->init(mapNameLS.c_str());
		mm->create();
	}
	
	// delay
	auto delayNode = Node::create();
	this->addChild(delayNode);
	auto ac_delay = DelayTime::create(2.0f);
	auto seq2 = Sequence::create(ac_delay, CallFunc::create(std::bind(&LoadingScene::GoToGameScene, this)), NULL);
	delayNode->runAction(seq2);

	//clock_t start_time, end_time;      // clock_t 
	//start_time = clock();                  // Start_Time
	//// Code..................                                      
	//// 
	//end_time = clock();                   // End_Time
	//CCLOG("@@@@ Create Map Data Time : %f\n", ((double)(end_time - start_time)) / CLOCKS_PER_SEC);
}

void LoadingScene::GoToGameScene()
{
	auto scene = GameScene::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(0.2, scene));
}
void LoadingScene::InitData()
{
	//auto def = UserDefault::sharedUserDefault();
	//def->setIntegerForKey("TR_StaticCount", 0);
	//def->setBoolForKey("TR1_IsOpened", false);
	//def->setBoolForKey("TR2_IsOpened", false);
	//def->setIntegerForKey("SR_StaticCount", 0);
	//def->setBoolForKey("SR1_IsOpened", false);
	//def->setBoolForKey("SR2_IsOpened", false);
}