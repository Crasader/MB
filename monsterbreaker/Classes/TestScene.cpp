#include "TestScene.h"

USING_NS_CC;
using namespace ui;

Scene* TestScene::createScene()
{

    // 'scene' is an autorelease object
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setGravity(Vec2(0, 0));
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    
    // 'layer' is an autorelease object
	auto layer = TestScene::create();
	layer->SetPhysicsWorld(scene->getPhysicsWorld());
	
    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool TestScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto spr_bg = Sprite::create("GameScene/BG.png");
	spr_bg->setPosition(Vec2(visibleSize.width / 2 , visibleSize.height / 2 ));
	this->addChild(spr_bg, 0);

	//SpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("Door/Door.plist", "Door/Door.png");
	//auto menu_item_1 = MenuItemSprite::create(Sprite::createWithSpriteFrameName("Door/Door.png"), Sprite::createWithSpriteFrameName("Door/Shining.png"), CC_CALLBACK_1(TestScene::GoBack, this));
	auto menu_item_1 = MenuItemFont::create("AA", CC_CALLBACK_1(TestScene::GoBack, this));
	auto menu_item_2 = MenuItemFont::create("AA", CC_CALLBACK_1(TestScene::GoBack2, this));
	auto menu_item_3 = MenuItemFont::create("DD", CC_CALLBACK_1(TestScene::GoBack3, this));
	auto menu_item_4 = MenuItemFont::create("DFFDFFD", CC_CALLBACK_1(TestScene::GoBack4, this));
	menu_item_1->setPosition(Vec2((visibleSize.width / 3) * 1, (visibleSize.height / 4) * 2));
	//menu_item_1->setRotation(90);
	menu_item_2->setPosition(Vec2((visibleSize.width / 3) * 2, (visibleSize.height / 4) * 2));
	menu_item_3->setPosition(Vec2((visibleSize.width / 3) * 1, (visibleSize.height / 4) * 1));
	menu_item_4->setPosition(Vec2((visibleSize.width / 3) * 2, (visibleSize.height / 4) * 1));

	auto *menu = Menu::create(menu_item_1, menu_item_2, menu_item_3, menu_item_4, NULL);
	menu->setPosition(Vec2(0, 0));
	this->addChild(menu);


	heroData = HeroData::getInstance();
	heroData->InitWithFile("Hero", "Warrior");

	hero = Warrior::create();
	hero->Move(Vec2(visibleSize.width / 2, hero->getContentSize().height));
	hero->Draw(this);

	auto hm = HMWarrior::create(this, hero, true);
	hm->setPosition(visibleSize.width*0.5f, visibleSize.height*0.5f);
	addChild(hm, ZINDEX_HELPERMAN_SPRITE);


	scheduleUpdate();
	return true;
}

void TestScene::GoBack(Ref *pSender)
{
//	s->Swing();
//	m->Damaged(10);
}

void TestScene::GoBack2(Ref *pSender)
{
//	d->setFury(true);
}
void TestScene::GoBack3(Ref *pSender)
{
//	d->Fire();
	// db left
//	db->left();
}
void TestScene::GoBack4(Ref *pSender)
{
	// db right
//	db->right();
}

void TestScene::update(float dt)
{
//	sk->update(dt);
}


bool TestScene::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event)
{


	return true;
}
void TestScene::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event)
{

}
void TestScene::onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event *event)
{

}
void TestScene::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event)
{
	CCLOG("gg");
}