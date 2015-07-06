#include "UnlockManager.h"
USING_NS_CC;
using namespace ui;


UnlockManager* UnlockManager::instance = nullptr;

UnlockManager::UnlockManager()
{
	origin = Director::getInstance()->getVisibleOrigin();
	visibleSize = Director::getInstance()->getVisibleSize();	
}
UnlockManager::~UnlockManager()
{

}

UnlockManager* UnlockManager::getInstace()
{
	if (instance == nullptr)
	{
		instance = new UnlockManager();
	}
	return instance;
}
void UnlockManager::freeInstance()
{
	if (instance != nullptr)
	{
		CC_SAFE_DELETE(instance);
	}
}

void UnlockManager::ShowUnlockData(cocos2d::Layer * layer)
{
	int size = unlockData.size();
	for (int i = 0; i < size; i++)
	{
		int id = unlockData.at(i);

		auto node = CSLoader::createNode("Unlock/Unlock.csb");
		node->setPosition(-visibleSize.width, visibleSize.height*0.5f);
		layer->addChild(node, 10000);
		auto img = (Sprite*)node->getChildByName("img");
		auto text1 = (Text*)node->getChildByName("text1");
		auto text2 = (Text*)node->getChildByName("text2");

		GetUnlockImageAndText(img, text1, text2, id);

		auto center = Vec2(visibleSize.width*0.5f, visibleSize.height*0.5f);
		auto out = Vec2(visibleSize.width*2.0f, visibleSize.height*0.5f);
		node->runAction(Sequence::create(
			DelayTime::create(0.5f + 5.0f * i),
			CallFunc::create(std::bind(&UnlockManager::playSound, this, "FindSecret", "wav")),
			MoveTo::create(0.5f, center),
			DelayTime::create(4.0f),
			MoveTo::create(0.5f, out),
			CallFunc::create(std::bind(&UnlockManager::DestroyNode, this, node)),
			NULL));
	}
	unlockData.clear();
}

void UnlockManager::playSound(const char * soundName, const char * soundType)
{
	SoundManager::getInstance()->playMySoundLogic(soundName, soundType);
}


void UnlockManager::GetUnlockImageAndText(cocos2d::Sprite* img, cocos2d::ui::Text * text1, cocos2d::ui::Text * text2, int id)
{
	auto cache = SpriteFrameCache::getInstance();
	switch (id)
	{
	case UNLOCK_BLACK_AND_WHITE:
		img->setDisplayFrame(cache->getSpriteFrameByName("Unlock/baw.png"));
		text1->setText("go to secret room in a village");
		text2->setText("Black And White");
		break;
	case UNLOCK_TRUTH:
		img->setDisplayFrame(cache->getSpriteFrameByName("Unlock/truth.png"));
		text1->setText("go to secret room in a castle");
		text2->setText("The Truth");
		break;
	case UNLOCK_HC:
		img->setDisplayFrame(cache->getSpriteFrameByName("Unlock/hc.png"));
		text1->setText("need the 'Black And White'");
		text2->setText("Human Castle");
		break;
	case UNLOCK_MC:
		img->setDisplayFrame(cache->getSpriteFrameByName("Unlock/mc.png"));
		text1->setText("need the 'Black And White'");
		text2->setText("Monster Castle");
		break;
	case UNLOCK_MM:
		img->setDisplayFrame(cache->getSpriteFrameByName("Unlock/mm.png"));
		text1->setText("need the 'The Truth'");
		text2->setText("My Mind");
		break;
	case UNLOCK_HV:
		img->setDisplayFrame(cache->getSpriteFrameByName("Unlock/hv.png"));
		text1->setText("another village");
		text2->setText("Human Village");
		break;
	case UNLOCK_ENDING_1:
		img->setDisplayFrame(cache->getSpriteFrameByName("Unlock/ending.png"));
		text1->setText("");
		text2->setText("Ending 1");
		break;
	case UNLOCK_ENDING_2:
		img->setDisplayFrame(cache->getSpriteFrameByName("Unlock/ending.png"));
		text1->setText("");
		text2->setText("Ending 2");
		break;
	case UNLOCK_ENDING_3:
		img->setDisplayFrame(cache->getSpriteFrameByName("Unlock/ending.png"));
		text1->setText("");
		text2->setText("Ending 3");
		break;
	case UNLOCK_ENDING_4:
		img->setDisplayFrame(cache->getSpriteFrameByName("Unlock/ending.png"));
		text1->setText("");
		text2->setText("Ending 4");
		break;
	case UNLOCK_ENDING_5:
		img->setDisplayFrame(cache->getSpriteFrameByName("Unlock/ending.png"));
		text1->setText("");
		text2->setText("Ending 5");
		break;
	case UNLOCK_ENDING_6:
		img->setDisplayFrame(cache->getSpriteFrameByName("Unlock/ending.png"));
		text1->setText("");
		text2->setText("Ending 6");
		break;
	}
}


void UnlockManager::DestroyNode(cocos2d::Node* node)
{
	node->stopAllActions();
	node->removeFromParentAndCleanup(true);
}

void UnlockManager::PauseAllEffects()
{
	int size = nodes.size();
	for (int i = 0; i < size; i++)
		nodes.at(i)->pause();
}
void UnlockManager::ResumeAllEffects()
{
	int size = nodes.size();
	for (int i = 0; i < size; i++)
		nodes.at(i)->resume();
}

void UnlockManager::addUnlockData(int unlockID)
{
	unlockData.push_back(unlockID);
	
}


