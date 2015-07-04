#pragma once
#ifndef __MONSTER_DEFINITIONS_H__
#define __MONSTER_DEFINITIONS_H__

#include "Monster.h"

// G
#include "Slime.h"
#include "TankerSlime.h"
#include "ShooterSlime.h"
#include "Bat.h"
#include "ShooterBat.h"
#include "Wolf.h"

// MV
#include "Gremlin.h"
#include "Goblin.h"
#include "Soul.h"
#include "Orc.h"

// MC
#include "Ghost.h"
#include "Zombie.h"
#include "Vampire.h"
#include "Skeleton.h"

// HV
#include "Farmer.h"
#include "BlackSmith.h"
#include "Scavenger.h"
#include "TreasureHunter.h"

// HC
#include "Guard.h"
#include "Archer.h"
#include "Knight.h"
#include "Wizard.h"

//MM
#include "QuestionMark.h"

// Boss
#include "SlimeKing.h"
#include "Half.h"
#include "Angel.h"
#include "Devil.h"
#include "Me.h"


//MONSTER ID
#define MONSTER_SIZE_NUMBER 22
#define MONSTER_START_NUMBER 1

//G
#define MONSTER_G_SIZE_NUMBER 6
#define MONSTER_G_START_NUMBER 1
#define SLIME_ID 1
#define TANKER_SLIME_ID 2
#define SHOOTER_SLIME_ID 3
#define BAT_ID 4
#define SHOOTER_BAT_ID 5
#define WOLF_ID 6
//MV
#define MONSTER_MV_SIZE_NUMBER 4
#define MONSTER_MV_START_NUMBER 7
#define MONSTER_MV_LUCKY_MONSTER_SIZE 1
#define MONSTER_MV_LUCKY_MONSTER_START_NUMBER 10
#define GREMLIN_ID 7
#define SOUL_ID 8
#define ORC_ID 9
#define GOBLIN_ID 10
//MC
#define MONSTER_MC_SIZE_NUMBER 4
#define MONSTER_MC_START_NUMBER 11
#define GHOST_ID 11
#define ZOMBIE_ID 12
#define VAMPIRE_ID 13
#define SKELETON_ID 14
//HV
#define MONSTER_HV_SIZE_NUMBER 5
#define MONSTER_HV_START_NUMBER 15
#define MONSTER_HV_LUCKY_MONSTER_SIZE 2
#define MONSTER_HV_LUCKY_MONSTER_START_NUMBER 18
#define FARMER_ID 15
#define BLACKSMITH_ID 16
#define GUARD_ID 17
#define SCAVENGER_ID 18
#define TREASURE_HUNTER_ID 19
//HC
#define MONSTER_HC_SIZE_NUMBER 3
#define MONSTER_HC_START_NUMBER 20
#define ARCHER_ID 20
#define KNIGHT_ID 21
#define WIZARD_ID 22
//MM
#define MONSTER_MM_SIZE_NUMBER 1
#define MONSTER_MM_START_NUMBER 23
#define QUESTIONMARK_ID 23
//BOSS

#define MONSTER_BOSS_SIZE_NUMBER 4
#define MONSTER_BOSS_START_NUMBER 101
#define BOSS_SLIME_KING_ID 101
#define BOSS_HALF_ID 102
#define BOSS_ANGEL_ID 103
#define BOSS_DEVIL_ID 104

#endif // __MONSTER_DEFINITIONS_H__
