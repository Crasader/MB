#pragma once
#ifndef __ENUM_DEFINITIONS_H__
#define __ENUM_DEFINITIONS_H__

namespace myEnum
{
	enum kCharacter
	{
		kWarrior, kMagician
	};
	enum kDir
	{
		kDirEast, kDirWest, kDirSouth, kDirNorth
	};

	enum kObjectState
	{
		kOSFirst = 0, kOSbleed, kOSburn, kOSfreeze, kOSpoison, kOSholy, kOSlightning, kOSsleep, kOSstun, kOSsLast = kOSstun
	};

	enum kAction
	{
		kActionMove, kActionStay, kActionAttack, kActionDie, kActionSkill, kActionSleep, kActionAwake
	};

	enum kMoods
	{
		kMoodStay, kMoodMove, kMoodAttack, kMoodAttack2, kMoodDie, kMoodSkill, kMoodSleep, kMoodHide, kMoodCharge1, kMoodCharge2
	};

	enum kSystemState
	{
		kSSInit, kSSPlaying, kSSPause, kSSWin, kSSDie
	};
	enum kRoomType
	{
		kRTNone, kRTStart, kRTMonster, kRTShop, kRTHelp, kRTBoss, kRTTreasure, kRTSecret, kRTBranch, kRTStem
	};
	enum kEnding
	{
		kEndingNone = 0, kEndingMurderer, kEndingDevil, kEndingSavior, kEndingAngel, kEndingInfinity, kEndingForgiver
	};

	enum kHelperMan
	{
		kHMWarrior = 1, kHMRifleMan, kHMPriest, kHMArcher
	};
	
	enum kMyTag
	{
		kItemTag = 806,
		kChestItemTag = 1127,
		kSkillItemTag = 223,
		kArmorItemTag = 1026,
		kBlockTag = 719
	};
	enum kTutorial
	{
		kAttack = 0, kMove, kBomb, kDamaged, kSkill
	};
}

#endif // __ENUM_DEFINITIONS_H__
