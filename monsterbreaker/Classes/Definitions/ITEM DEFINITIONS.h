#pragma once
#ifndef __ITEM_DEFINITIONS_H__
#define __ITEM_DEFINITIONS_H__

#define ITEM_MAX_SIZE 19
#define ITEM_MAX_COUNT 99

#define ITEM_NONE 0 
#define ITEM_FRESH_MEAT 1		// hp + 2, Fat
#define ITEM_SOUL_EATER 2		// sp + 2, 
#define ITEM_DYNAMITE 3			// bombDamage + 5, change bomb image
#define ITEM_DANCING_TOY 4	// ball Speed + 100, change ball image
#define ITEM_LOL 5					// hp + 2, sp + 2, Damage + 2, 
#define ITEM_STONE_OF_DAVID 6	// damage + 2, change ball image, but PaddleSize = 0.7f 
#define ITEM_CHAKRAM 7			// damage + 1, change ball image
#define ITEM_BEAUTY_GLASS_BEAD 8		// damage + 1, ball size + 1 
#define ITEM_TRINITY 9						// damage + 1, ball count = 3

#define ITEM_TRUTH 10						// key item, all stat,  If anyone slaps you on the right cheek, turn to them the other cheek also. (if hero has damaged by enemy, that enemy will be damaged by that self)
#define ITEM_BLACK_AND_WHITE 11		// key item, all stat, change hero image black and white	// if you cleared the all rooms in any village, it will be droped in treasure room & unlock the castle.

#define ITEM_GOLD 12							// coin + 10
#define ITEM_BOMB_PACKAGE 13			// bomb + 5
#define ITEM_REMOTE_BOMB 14					// bomb set timer is increased, but you can have exploded by touching
#define ITEM_BOMBER 15						// bomb damage + 5, bomb set timer down, bomber explode quickly, bomb range up
#define ITEM_SCAVENGER 16					// hero can see all secret door, but can't open before the door is exploded
#define ITEM_SECRET_MASTER 17			// hero can see all secret door, and can open
#define ITEM_THE_MAP 18						// hero can see all room, but he can't know the room type
#define ITEM_THE_COMPASS 19				// hero can see all room type, but he can't know how to arrived that room

// merchant item :: use item
#define ITEM_MERCHANT_ITEM_START 100
#define ITEM_MERCHANT_ITEM_SIZE 6
#define ITEM_MERCHANT_KEY 100
#define ITEM_MERCHANT_BOMB 101
#define ITEM_MERCHANT_HALF_HEART 102
#define ITEM_MERCHANT_HEART 103
#define ITEM_MERCHANT_HALF_SOUL_HEART 104
#define ITEM_MERCHANT_SOUL_HEART 105

// merchant item :: Warrior Weapon
#define ITEM_MERCHANT_WEAPON_FIRE_SWORD 110
#define ITEM_MERCHANT_WEAPON_HOLY_SWORD 111

// merchant item :: Magician Weapon
#define ITEM_MERCHANT_WEAPON_FIRE_STAFF 120

// merchant item :: Warrior Armor
#define ITEM_MERCHANT_ARMOR_SHIELD 130
#define ITEM_MERCHANT_ARMOR_HELMET 131
#define ITEM_MERCHANT_ARMOR_BODY 132

#define ITEM_WEAPON_STAFF_START_NUM 200
#define ITEM_WEAPON_STAFF_SIZE 5
#define ITEM_WEAPON_STAFF_NORMAL_STAFF 200
#define ITEM_WEAPON_STAFF_OLD_STAFF 201
#define ITEM_WEAPON_STAFF_RUBY_STAFF 202
#define ITEM_WEAPON_STAFF_RUNE_STAFF 203
#define ITEM_WEAPON_STAFF_T_STAFF 204


#define ITEM_WEAPON_SWORD_START_NUM 300
#define ITEM_WEAPON_SWORD_SIZE 4
#define ITEM_WEAPON_SWORD_NORMAL_SWORD 300
#define ITEM_WEAPON_SWORD_DRAGON_SLAYER 301
#define ITEM_WEAPON_SWORD_FIRE_SWORD 302
#define ITEM_WEAPON_SWORD_SCIMITAR 303


#define ITEM_ARMOR_START_NUM 400
#define ITEM_ARMOR_SIZE 2
#define ITEM_ARMOR_NORMAL_ARMOR 400
#define ITEM_ARMOR_GOLDEN_ARMOR 401

#define ITEM_DROP_START_NUM 500
#define ITEM_DROP_SIZE 7
#define ITEM_DROP_USE_ITEM_SIZE 3
#define ITEM_DROP_USE_ITEM_START_NUM 500
#define ITEM_DROP_COIN 500
#define ITEM_DROP_KEY 501
#define ITEM_DROP_BOMB 502

#define ITEM_DROP_HEART_ITEM_SIZE 4
#define ITEM_DROP_HEART_START_NUM 503
#define ITEM_DROP_HALF_HEART 503
#define ITEM_DROP_HALF_SOUL_HEART 504
#define ITEM_DROP_HEART 505
#define ITEM_DROP_SOUL_HEART 506


#define UNLOCK_BLACK_AND_WHITE 1000
#define UNLOCK_TRUTH 1001
#define UNLOCK_ENDING_1 1002
#define UNLOCK_ENDING_2 1003
#define UNLOCK_ENDING_3 1004
#define UNLOCK_ENDING_4 1005
#define UNLOCK_ENDING_5 1006
#define UNLOCK_ENDING_6 1007
#define UNLOCK_MC 1008
#define UNLOCK_HV 1009
#define UNLOCK_HC 1010
#define UNLOCK_MM 1011

#endif // __ITEM_DEFINITIONS_H__
