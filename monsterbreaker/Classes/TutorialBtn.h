#pragma once
#ifndef  __TUTORIAL_BTN_H__
#define __TUTORIAL_BTN_H__

#include "cocos2d.h"
#include "GameObject.h"
#include "cocostudio\CocoStudio.h"
#include "ui\CocosGUI.h"

class TutorialBtn : public cocos2d::Node
{
private:
public:
	cocos2d::Layer * layer;

	// node
	cocos2d::Node * node;
	cocos2d::Sprite * img;
	cocos2d::ui::Button * btn;

	int btnType;
	std::string btnTypeStr;

	TutorialBtn(cocos2d::Layer * layer, int btnType);
	~TutorialBtn();
	static TutorialBtn* create(cocos2d::Layer * layer, int btnType);

	void InitSprite();

	void RemoveAll();
	virtual cocos2d::Size getContentSize();
	virtual void pause();
	virtual void resume();

};

#endif // __TUTORIAL_BTN_H__
 