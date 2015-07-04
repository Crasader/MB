#pragma once
#ifndef __MAP_MANAGER_H__
#define __MAP_MANAGER_H__

#include "Room.h"
#include "cocos2d.h"
#include "Definitions.h"
#include "Heap.h"
using namespace std;

#define SIZE_X 9
#define SIZE_Y 9

class MapManager
{
private:
	static MapManager* instance;
	void createBranch(bool first);
	void checkDir(int x, int y);
	void checkSideRoom(int x, int y);
	void readLevelData();
	void setRoomType();

	int bossCount = 1;
	int helpCount = 0;
	int shopCount = 0;
	int treasureCount = 1;
	int secretCount = 1;

	int cnt_gen = 2;
	int cnt_branch = 2;

	cocos2d::SpriteBatchNode * spriteBatch;
	cocos2d::Layer * layer;

	void SetVisibleState(int x, int y, bool secretVisible, bool secretLockOpen);

public:
	CC_SYNTHESIZE(bool, _curse, Curse);
	CC_SYNTHESIZE(bool, _allView, AllView);
	CC_SYNTHESIZE(bool, _allViewType, AllViewType);
	CC_SYNTHESIZE(int, _heroX, HeroX);
	CC_SYNTHESIZE(int, _heroY, HeroY);
//	CC_SYNTHESIZE(int, _cntRoom, CountRoom);
//	CC_SYNTHESIZE(int, _clearCntRoom, ClearCountRoom);

	Room map[SIZE_X][SIZE_Y];
	static MapManager* getInstance();
	void freeInstance();

	CC_SYNTHESIZE(std::string, levelName, LevelName);

	std::list<Room> branchRooms;

	Room GetRoomData(int x, int y);
	Room GetCurrentRoomData() const;

	void init(const char * levelName);
	void initAllRoomdata();
	void create();
	void debug(const char * temp);
//	void debugMap(cocos2d::Layer * layer);
	void DrawMap(cocos2d::Layer *layer);
	void ReDrawMap();

//	void Save();
	void SaveAll();
	void SaveRoomData(int x, int y);
	void LoadAll();
	void LoadRoomData(int x, int y);

	void CheckSideRoom(bool secretVisible, bool secretLockOpen);

	bool IsBoundary(int x, int y);
	bool IsE();
	bool IsW();
	bool IsS();
	bool IsN();
private:

};

#endif //__MAP_MANAGER_H__