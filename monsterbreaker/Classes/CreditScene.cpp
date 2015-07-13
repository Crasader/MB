#include "CreditScene.h"

USING_NS_CC;
using namespace ui;

Scene* CreditScene::createScene()
{

    // 'scene' is an autorelease object
	auto scene = Scene::createWithPhysics();
    
    // 'layer' is an autorelease object
	auto layer = CreditScene::create();
	
    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool CreditScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	SoundManager::getInstance()->changeBG("EndingBG");

	node = CSLoader::createNode("CreditScene/CreditScene.csb");
	node->setPosition(origin);
	this->addChild(node);

	this->setKeypadEnabled(true);

	backBtn = static_cast<Button*>(node->getChildByName("backBtn"));
	webBtn = static_cast<Button*>(node->getChildByName("webBtn"));
	meBtn = static_cast<Button*>(node->getChildByName("meBtn"));
	isaacBtn = static_cast<Button*>(node->getChildByName("isaacBtn"));

	struct callBackFunctorBack
	{
		void operator() (Ref* sender) const
		{
			SoundManager::getInstance()->playMySoundLogic("Select");
			auto scene = MainMenuScene::createScene();
			Director::getInstance()->replaceScene(TransitionFade::create(0.5, scene));
		}
	};
	Widget::ccWidgetClickCallback callBackBack = callBackFunctorBack();
	backBtn->addClickEventListener(callBackBack);

	isaacBtn->addTouchEventListener(CC_CALLBACK_2(CreditScene::openWeb, this));
	meBtn->addTouchEventListener(CC_CALLBACK_2(CreditScene::openWeb, this));
	webBtn->addTouchEventListener(CC_CALLBACK_2(CreditScene::openWeb, this));

	meBtn->setTag(1);
	webBtn->setTag(1);
	isaacBtn->setTag(2);
	return true;
}

void CreditScene::openWeb(cocos2d::Ref * pSender, cocos2d::ui::Widget::TouchEventType type)
{
		switch (type){
		case Widget::TouchEventType::BEGAN:
			break;
		case Widget::TouchEventType::MOVED:
			break;
		case Widget::TouchEventType::ENDED:
		{
			SoundManager::getInstance()->playMySoundLogic("Select");
			int tag = static_cast<cocos2d::Node*>(pSender)->getTag();
			
			switch (tag)
			{
			case 1:
				CCApplication::sharedApplication()->openURL("http://ilhaeYe.blogspot.com/");
				break;
			case 2:
				CCApplication::sharedApplication()->openURL("http://bindingofisaac.com/");
				break;
			}

			
		}
		break;
		case Widget::TouchEventType::CANCELED:
			break;
		default:
			break;
		}

}

void CreditScene::onKeyReleased(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event *event)
{
	if (keycode == EventKeyboard::KeyCode::KEY_BACK) {
		SoundManager::getInstance()->playMySoundLogic("Select");
		auto scene = MainMenuScene::createScene();
		Director::getInstance()->replaceScene(TransitionFade::create(0.5, scene));
	}
}


