#pragma once
#ifndef __ROOM_H___
#define __ROOM_H___
#include "Definitions.h"
#include "cocos2d.h"

class Room
{
public:
	bool lock;
	bool visible;
	bool exp;
	int x;
	int y;
	
	int cnt_sideroom = 0;
	bool dir[4];

	int type = myEnum::kRoomType::kRTNone;

	int priority = 0;

	std::map<std::string, int> data;
	std::map<std::string, std::string> data2;

	virtual void SaveRoomData();
	virtual void LoadRoomData();

};

#endif 

