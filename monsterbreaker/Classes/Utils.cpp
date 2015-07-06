#include"Utils.h"
USING_NS_CC;

Utils* Utils::instance = nullptr;
Utils::Utils(){}
Utils::~Utils(){}
Utils* Utils::GetInstance()
{
	if (nullptr == instance) //포인터가 NULL일 경우
	{
		instance = new Utils(); //힙 영역에 동적 할당 후 포인터에 저장
	}

	return instance; //포인터 리턴
}
void Utils::FreeInstance()
{
	if (nullptr != instance) //포인터가 비어있지 않다면
	{
		delete instance; //메모리 해제
		instance = nullptr;
	}
}
bool Utils::IsMultiplesOfTwo(int num)
{
	return (num % 2 == 0) ? true : false;
}

int Utils::GetWeaponID(const char * weaponName)
{
	std::string temp = weaponName;
	int result = 0;

	// staff
	if (temp.compare("NormalStaff") == 0) result = ITEM_WEAPON_STAFF_NORMAL_STAFF;
	else if (temp.compare("OldStaff") == 0) result = ITEM_WEAPON_STAFF_OLD_STAFF;
	else if (temp.compare("RubyStaff") == 0) result = ITEM_WEAPON_STAFF_RUBY_STAFF;
	else if (temp.compare("RuneStaff") == 0) result = ITEM_WEAPON_STAFF_RUNE_STAFF;
	else if (temp.compare("TStaff") == 0) result = ITEM_WEAPON_STAFF_T_STAFF;

	// sword
	else if (temp.compare("NormalSword") == 0) result = ITEM_WEAPON_SWORD_NORMAL_SWORD;
	else if (temp.compare("FireSword") == 0) result = ITEM_WEAPON_SWORD_FIRE_SWORD;
	else if (temp.compare("Scimitar") == 0) result = ITEM_WEAPON_SWORD_SCIMITAR;
	else if (temp.compare("DragonSlayer") == 0) result = ITEM_WEAPON_SWORD_DRAGON_SLAYER;

	return result;
}

std::string Utils::GetWeaponName(int id)
{
	std::string result = "";
	// staff

	switch (id)
	{
	case ITEM_WEAPON_STAFF_NORMAL_STAFF: result = "NormalStaff"; break;
	case ITEM_WEAPON_STAFF_OLD_STAFF: result = "OldStaff"; break;
	case ITEM_WEAPON_STAFF_RUBY_STAFF: result = "RubyStaff"; break;
	case ITEM_WEAPON_STAFF_RUNE_STAFF: result = "RuneStaff"; break;
	case ITEM_WEAPON_STAFF_T_STAFF: result = "TStaff"; break;
	case ITEM_WEAPON_SWORD_NORMAL_SWORD: result = "NormalSword"; break;
	case ITEM_WEAPON_SWORD_FIRE_SWORD: result = "FireSword"; break;
	case ITEM_WEAPON_SWORD_SCIMITAR: result = "Scimitar"; break;
	case ITEM_WEAPON_SWORD_DRAGON_SLAYER: result = "DragonSlayer"; break;
	}

	if (result.compare("") == 0)
	{
		//CC_ASSERT("This Weapon ID(%d) Doesn't Have Any Weapon Name!!");
	}

	return result;
}

