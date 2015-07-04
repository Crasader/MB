#include "SoundManager.h"
//#include <stdlib.h>
USING_NS_CC;

SoundManager* SoundManager::instance = nullptr;
SoundManager* SoundManager::getInstance()
{
	if (instance == nullptr)
	{
		instance = new SoundManager();
		instance->initSoundData();
		instance->getMuteState();
	}
	return instance;
}
void SoundManager::freeInstance()
{
	if (instance != nullptr)
	{
		CC_SAFE_DELETE(instance);
	}
}
void SoundManager::getMuteState()
{
	auto def = UserDefault::sharedUserDefault();
	speakerOn = def->getBoolForKey("speaker", true);
}

void SoundManager::playMySoundLogic(const char * soundName, const char * soundType)
{
	getMuteState();
	if (speakerOn == true)
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume(0.5f);
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(String::createWithFormat("Sounds/%s.%s", soundName, soundType)->getCString());
	}
}

void SoundManager::playMyBGLogic(const char * soundName, bool b, const char * soundType)
{
	getMuteState();
	if (speakerOn == true)
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(String::createWithFormat("Sounds/%s.%s", soundName, soundType)->getCString(), b);
	}
}

void SoundManager::resumeMyBG()
{
	getMuteState();
	if (speakerOn == true)
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
	}
}
void SoundManager::pauseMyBG()
{
	CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

void SoundManager::pauseAllSound()
{
	CocosDenshion::SimpleAudioEngine::getInstance()->pauseAllEffects();

}
void SoundManager::resumeAllSound()
{
	CocosDenshion::SimpleAudioEngine::getInstance()->resumeAllEffects();
}

void SoundManager::changeBG(const char * soundName, bool b, const char * soundType)
{
	getMuteState();
	if (speakerOn == true)
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
		CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(String::createWithFormat("Sounds/%s.%s", soundName, soundType)->getCString(), b);
	}
}




void SoundManager::initSoundData()
{
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Sounds/Arrow.wav");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Sounds/Bomb.wav");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("Sounds/BossBG.wav");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Sounds/Brick.wav");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Sounds/Die.wav");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Sounds/FindSecret.wav");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Sounds/FireBall.wav");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Sounds/Heal.wav");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Sounds/HeroDamaged.wav");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Sounds/Item.wav");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Sounds/Lightning.wav");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Sounds/PickUpCoin.wav");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("Sounds/MainBG.wav");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Sounds/MonsterDamaged.wav");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Sounds/Select.wav");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Sounds/Shining.wav");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Sounds/Skill.wav");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Sounds/Solid.wav");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Sounds/Swing.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Sounds/ThankYou.wav");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Sounds/X.wav");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Sounds/DragonFlame.wav");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Sounds/Fury.wav");

	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Sounds/HpUp.wav");

	CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("Sounds/DieBG.wav");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("Sounds/PrologBG.wav");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("Sounds/EndingBG.wav");

}


