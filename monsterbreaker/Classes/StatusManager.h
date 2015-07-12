#pragma once
#ifndef __STATUS_MANAGER_H__
#define __STATUS_MANAGER_H__

#include "cocos2d.h"
#include "Definitions.h"
#include "Hero.h"

class StatusManager : public cocos2d::Node 
{
private:
	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;
	Hero * hero;

	cocos2d::Node* node;

	cocos2d::Sprite* topBG;
	cocos2d::Label* hpLabel;
	cocos2d::Vector<cocos2d::Sprite*> voidHpSprite;
	cocos2d::Vector<cocos2d::Sprite*> leftHpSprite;
	cocos2d::Vector<cocos2d::Sprite*> rightHpSprite;
	cocos2d::Label* spLabel;
	cocos2d::Vector<cocos2d::Sprite*> voidSpSprite;
	cocos2d::Vector<cocos2d::Sprite*> leftSpSprite;
	cocos2d::Vector<cocos2d::Sprite*> rightSpSprite;

	cocos2d::Sprite* keySprite;
	cocos2d::LabelAtlas* keyCountLabel;
	cocos2d::Sprite* bombSprite;
	cocos2d::LabelAtlas* bombCountLabel;
	cocos2d::Sprite* moneySprite;
	cocos2d::LabelAtlas* moneyCountLabel;

	void InitHp();
	void InitSp(const char * hName);
public:
	StatusManager();
	~StatusManager();

	static StatusManager* create(Hero * hero);

	void InitStatus(Hero * hero);
	void DrawStatus(cocos2d::Layer * layer);

	void SetCurrentHp(int currentHp);
	void SetMaxHp(int maxHp);
	void SetCurrentSp(int currentSp);
	void SetMaxSp(int maxSp);

	void SetKeyCount(int keyNum);
	void SetBombCount(int bombNum);
	void SetMoneyCount(int moneyNum);

	virtual void update(float dt);
};

#endif // __STATUS_UI_H__
 