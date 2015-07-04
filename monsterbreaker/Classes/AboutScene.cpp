#include "AboutScene.h"

USING_NS_CC;
using namespace ui;

Scene* AboutScene::createScene()
{

    // 'scene' is an autorelease object
	auto scene = Scene::createWithPhysics();
    
    // 'layer' is an autorelease object
	auto layer = AboutScene::create();
	
    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool AboutScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	node = CSLoader::createNode("About/About.csb");
	this->addChild(node);

	this->setKeypadEnabled(true);

	btn1 = static_cast<Button*>(node->getChildByName("btn1"));
	btn2 = static_cast<Button*>(node->getChildByName("btn2"));
	btn3 = static_cast<Button*>(node->getChildByName("btn3"));
	btn4 = static_cast<Button*>(node->getChildByName("btn4"));
	btn5 = static_cast<Button*>(node->getChildByName("btn5"));
	btn6 = static_cast<Button*>(node->getChildByName("btn6"));

	PrologBtn = static_cast<Button*>(node->getChildByName("btn_prolog"));
	CreditBtn = static_cast<Button*>(node->getChildByName("btn_credit"));

	BackBtn = static_cast<Button*>(node->getChildByName("btn_back"));

	lock1 = node->getChildByName("lock1");
	lock2 = node->getChildByName("lock2");
	lock3 = node->getChildByName("lock3");
	lock4 = node->getChildByName("lock4");
	lock5 = node->getChildByName("lock5");
	lock6 = node->getChildByName("lock6");

	image1 = node->getChildByName("ending1");
	image2 = node->getChildByName("ending2");
	image3 = node->getChildByName("ending3");
	image4 = node->getChildByName("ending4");
	image5 = node->getChildByName("ending5");
	image6 = node->getChildByName("ending6");

	AllItemLock();

	int _unlockEndingNum = UserDefault::sharedUserDefault()->getIntegerForKey("u_ending", 0);

	if (_unlockEndingNum >= 1)
		UnLockItem(image1, lock1, btn1);
	if (_unlockEndingNum >= 2)
		UnLockItem(image2, lock2, btn2);
	if (_unlockEndingNum >= 3)
		UnLockItem(image3, lock3, btn3);
	if (_unlockEndingNum >= 4)
		UnLockItem(image4, lock4, btn4);
	if (_unlockEndingNum >= 5)
		UnLockItem(image5, lock5, btn5);
	if (_unlockEndingNum >= 6)
		UnLockItem(image6, lock6, btn6);

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
	BackBtn->addClickEventListener(callBackBack);

	PrologBtn->setTag(1);
	btn1->setTag(2);
	btn2->setTag(3);
	btn3->setTag(4);
	btn4->setTag(5);
	btn5->setTag(6);
	btn6->setTag(7);
	CreditBtn->setTag(8);

	PrologBtn->addTouchEventListener(CC_CALLBACK_2(AboutScene::MoveToScene, this));
	btn1->addTouchEventListener(CC_CALLBACK_2(AboutScene::MoveToScene, this));
	btn2->addTouchEventListener(CC_CALLBACK_2(AboutScene::MoveToScene, this));
	btn3->addTouchEventListener(CC_CALLBACK_2(AboutScene::MoveToScene, this));
	btn4->addTouchEventListener(CC_CALLBACK_2(AboutScene::MoveToScene, this));
	btn5->addTouchEventListener(CC_CALLBACK_2(AboutScene::MoveToScene, this));
	btn6->addTouchEventListener(CC_CALLBACK_2(AboutScene::MoveToScene, this));
	CreditBtn->addTouchEventListener(CC_CALLBACK_2(AboutScene::MoveToScene, this));

	return true;
}
void AboutScene::AllItemLock()
{
	LockItem(image1, lock1, btn1);
	LockItem(image2, lock2, btn2);
	LockItem(image3, lock3, btn3);
	LockItem(image4, lock4, btn4);
	LockItem(image5, lock5, btn5);
	LockItem(image6, lock6, btn6);
}
void AboutScene::LockItem(cocos2d::Node * image, cocos2d::Node * lock, cocos2d::ui::Button * btn)
{
	image->setColor(Color3B(0x1a, 0x1a, 0x1a));
	lock->setVisible(true);
	btn->setEnabled(false);
}
void AboutScene::UnLockItem(cocos2d::Node * image, cocos2d::Node * lock, cocos2d::ui::Button * btn)
{
	image->setColor(Color3B(0xff, 0xff, 0xff));
	lock->setVisible(false);
	btn->setEnabled(true);
}


void AboutScene::MoveToScene(cocos2d::Ref * pSender, cocos2d::ui::Widget::TouchEventType type)
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
			{
				auto scene = PrologScene::createScene();
				Director::getInstance()->replaceScene(TransitionFade::create(0.5, scene));
			}
			break;
			case 2:
			{
				auto scene = EndingScene::createScene(1);
				Director::getInstance()->replaceScene(TransitionFade::create(0.5, scene));
			}
			break;
			case 3:
			{
				auto scene = EndingScene::createScene(2);
				Director::getInstance()->replaceScene(TransitionFade::create(0.5, scene));
			}
			break;
			case 4:
			{
				auto scene = EndingScene::createScene(3);
				Director::getInstance()->replaceScene(TransitionFade::create(0.5, scene));
			}
			break;
			case 5:
			{
				auto scene = EndingScene::createScene(4);
				Director::getInstance()->replaceScene(TransitionFade::create(0.5, scene));
			}
			break;
			case 6:
			{
				auto scene = EndingScene::createScene(5);
				Director::getInstance()->replaceScene(TransitionFade::create(0.5, scene));
			}
			break;
			case 7:
			{
				auto scene = EndingScene::createScene(6);
				Director::getInstance()->replaceScene(TransitionFade::create(0.5, scene));
			}
			break;
			case 8:
			{
				// credit scene
				auto scene = CreditScene::createScene();
				Director::getInstance()->replaceScene(TransitionFade::create(0.5, scene));
			}
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

void AboutScene::onKeyReleased(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event *event)
{
	if (keycode == EventKeyboard::KeyCode::KEY_BACK) {
		SoundManager::getInstance()->playMySoundLogic("Select");
		auto scene = MainMenuScene::createScene();
		Director::getInstance()->replaceScene(TransitionFade::create(0.5, scene));
	}
}

