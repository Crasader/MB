#pragma once
#ifndef __SOUND_MANAGER_H__
#define __SOUND_MANAGER_H__

#include "cocos2d.h"
#include "Definitions.h"
#include "SimpleAudioEngine.h"

class SoundManager
{
private:
	static SoundManager* instance;
	void getMuteState();

public:
	static SoundManager* getInstance();
	void freeInstance();

	bool speakerOn;
	void playMySoundLogic(const char * soundName, const char * soundType = "wav");
	void playMyBGLogic(const char * soundName, bool b = true, const char * soundType = "wav");
	void resumeMyBG();
	void pauseMyBG();
	void initSoundData();
	void pauseAllSound();
	void resumeAllSound();
	void changeBG(const char * soundName, bool b = true, const char * soundType = "wav");
};

#endif //__SOUND_MANAGER_H__