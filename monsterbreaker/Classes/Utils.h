#pragma once
#ifndef __UTILS_H__
#define __UTILS_H__

#include "cocos2d.h"
#include "Definitions.h"

class Utils
{
private: 
	static Utils* instance;
	Utils();
	~Utils();
public:
	static Utils* GetInstance();
	static void FreeInstance();
	bool IsMultiplesOfTwo(int num);
	int GetWeaponID(const char * weaponName);
	std::string GetWeaponName(int id);
};

#endif // __UTILS_H__
 