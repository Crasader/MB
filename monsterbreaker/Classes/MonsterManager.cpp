#include "MonsterManager.h"

USING_NS_CC;

MonsterManager::~MonsterManager()
{

}
MonsterManager::MonsterManager(cocos2d::Layer * layer, const char * mapType) : layer(layer), _monsterClear(false), _mapType(mapType)
{
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();
	contentSize = Size(visibleSize.width / 10, visibleSize.height / 25);
	startPoint = Vec2(0, contentSize.height * 20);
	
}

MonsterManager* MonsterManager::create(cocos2d::Layer * layer, const char * mapType)
{
	auto pNode = new MonsterManager(layer, mapType);
	pNode->autorelease();
	return pNode;
}

void MonsterManager::DrawMonsters()
{
	auto data = __Dictionary::createWithContentsOfFile(String::createWithFormat("Level/%s.plist",getMapType().c_str())->getCString());
	tp.clear();
	int cnt = data->valueForKey("cnt")->intValue();
	int r_scene = rand() % cnt + 1;
	float r2 = CCRANDOM_0_1();
	bool lucky = false;
	if (r2 < 0.15f)
	{
		lucky = true;
	}

	auto dic = (__Dictionary *)data->objectForKey(String::createWithFormat("%d", r_scene)->getCString());
	int objCnt = dic->valueForKey("cnt")->intValue();
	
	for (int i = 1; i <= objCnt; i++)
	{
		auto objDic = (__Dictionary *)dic->objectForKey(String::createWithFormat("%d", i)->getCString());
		int objX = objDic->valueForKey("x")->intValue();
		int objY = objDic->valueForKey("y")->intValue();
		std::string type = objDic->valueForKey("type")->getCString();

		if (type.compare("m") == 0)
		{
			int r = 0;
			if (getMapType().compare("G") == 0)
			{
				r = rand() % MONSTER_G_SIZE_NUMBER + MONSTER_G_START_NUMBER;
			}
			else if (getMapType().compare("MV") == 0)
			{
				if (lucky)
				{
					r = rand() % MONSTER_MV_LUCKY_MONSTER_SIZE + MONSTER_MV_LUCKY_MONSTER_START_NUMBER;
				}
				else
				{
					r = rand() % (MONSTER_MV_SIZE_NUMBER - MONSTER_MV_LUCKY_MONSTER_SIZE) + MONSTER_MV_START_NUMBER;
				}
			}
			else if (getMapType().compare("MC") == 0)
			{
				r = rand() % MONSTER_MC_SIZE_NUMBER + MONSTER_MC_START_NUMBER;
			}
			else if (getMapType().compare("HV") == 0)
			{
				if (lucky)
				{
					r = rand() % MONSTER_HV_LUCKY_MONSTER_SIZE + MONSTER_HV_LUCKY_MONSTER_START_NUMBER;
				}
				else
				{
					r = rand() % (MONSTER_HV_SIZE_NUMBER - MONSTER_HV_LUCKY_MONSTER_SIZE) + MONSTER_HV_START_NUMBER;
				}
			}
			else if (getMapType().compare("HC") == 0)
			{
				r = rand() % MONSTER_HC_SIZE_NUMBER + MONSTER_HC_START_NUMBER;
			}
			else if (getMapType().compare("MM") == 0)
			{
				r = rand() % MONSTER_MM_SIZE_NUMBER + MONSTER_MM_START_NUMBER;
			}

			Monster * m = nullptr;
			
			m = CreateMonster(r);

			// only for debug 
			//m = Skeleton::create();

			m->setPosition(Vec2(startPoint.x + contentSize.width * objY + contentSize.width * 0.5f, startPoint.y - contentSize.height * objX + contentSize.height / 2 ));
			m->Draw(layer);
			m->StartAnimation();
			m->scheduleUpdate();
			monsters.pushBack(m);
		}
		else if (type.compare("b1") == 0)
		{
			auto brick = SingleBrick::create(getMapType().c_str(), BRICK_SINGLE_ID);
			brick->setPosition(Vec2(startPoint.x + contentSize.width * objY + contentSize.width * 0.5f , startPoint.y - contentSize.height * objX + contentSize.height / 2 ));
			layer->addChild(brick, ZINDEX_BRICK_SPRITE, myEnum::kMyTag::kBlockTag);
		}
		else if (type.compare("b2") == 0)
		{
			auto brick = DoubleBrick::create(getMapType().c_str(), layer, BRICK_DOUBLE_ID);
			brick->setPosition(Vec2(startPoint.x + contentSize.width * objY + contentSize.width * 0.5f, startPoint.y - contentSize.height * objX + contentSize.height / 2 ));
			layer->addChild(brick, ZINDEX_BRICK_SPRITE, myEnum::kMyTag::kBlockTag);
		}
		else if (type.compare("b3") == 0)
		{
			auto brick = SolidBrick::create(getMapType().c_str(), BRICK_SOLID_ID);
			brick->setPosition(Vec2(startPoint.x + contentSize.width * objY + contentSize.width * 0.5f , startPoint.y - contentSize.height * objX + contentSize.height / 2 ));
			layer->addChild(brick, ZINDEX_BRICK_SPRITE, myEnum::kMyTag::kBlockTag);
		}
		else if (type.compare("tp") == 0)
		{
			Point p;
			p.x = objX;
			p.y = objY;

			tp.push_back(p);
		}
	}
}

void MonsterManager::CreateHeroBrick()
{
	for (int i = 1; i <= 8; i++)
	{
		auto brick = SingleBrick::create(getMapType().c_str(), BRICK_SINGLE_ID);
		brick->setPosition(Vec2(startPoint.x + contentSize.width * i + contentSize.width * 0.5f , startPoint.y - contentSize.height * 16 - contentSize.height * 0.25));
		layer->addChild(brick, ZINDEX_BRICK_SPRITE, myEnum::kMyTag::kBlockTag);
		brick->getPhysicsBody()->setCollisionBitmask(SINGLE_NEUTRAL_BRICK_COLLISION_BITMASK);
	}

}

Monster * MonsterManager::CreateMonster(int mID)
{
	Monster * m = nullptr;
	switch (mID)
	{
	case SLIME_ID: m = Slime::create(); break;
	case BAT_ID: m = Bat::create(); break;
	case SHOOTER_BAT_ID: m = ShooterBat::create(); break;
	case SHOOTER_SLIME_ID: m = ShooterSlime::create(); break;
	case TANKER_SLIME_ID: m = TankerSlime::create(); break;
	case WOLF_ID: m = Wolf::create(); break;
	case GREMLIN_ID: m = Gremlin::create(); break;
	case GOBLIN_ID: m = Goblin::create(); break;
	case SOUL_ID: m = Soul::create(); break;
	case ORC_ID: m = Orc::create(); break;
	case GHOST_ID: m = Ghost::create(); break;
	case ZOMBIE_ID: m = Zombie::create(); break;
	case VAMPIRE_ID: m = Vampire::create(); break;
	case SKELETON_ID: m = Skeleton::create(); break;
	case FARMER_ID: m = Farmer::create(); break;
	case BLACKSMITH_ID: m = BlackSmith::create(); break;
	case SCAVENGER_ID: m = Scavenger::create(); break;
	case TREASURE_HUNTER_ID: m = TreasureHunter::create(); break;
	case GUARD_ID: m = Guard::create(); break;
	case ARCHER_ID: m = Archer::create(); break;
	case KNIGHT_ID: m = Knight::create(); break;
	case WIZARD_ID: m = Wizard::create(); break;
	case QUESTIONMARK_ID: m = QuestionMark::create(); break;
	default: CCLOG("monster manager random value : %d", mID); break;
	}
	return m;
}

void MonsterManager::Debug2()
{
	for (int i = 0; i < monsters.size(); i++)
		monsters.at(i)->DecreaseCurrentHp(10);
}

void MonsterManager::update(float dt)
{
	for (int i = 0; i < monsters.size(); i++)
	{
		if (monsters.at(i)->IsAlive())
		{
			_monsterClear = false;
			return;
		}
	}
	_monsterClear = true;
}

void MonsterManager::PauseMonsters()
{
	for (int i = 0; i < monsters.size(); i++)
		monsters.at(i)->pause();
}
void MonsterManager::ResumeMonsters()
{
	for (int i = 0; i < monsters.size(); i++)
		monsters.at(i)->resume();
}

void MonsterManager::CreateBossMonster()
{
	auto data = __Dictionary::createWithContentsOfFile(String::createWithFormat("Level/%sBoss.plist", getMapType().c_str())->getCString());
	int cnt = data->valueForKey("cnt")->intValue();
	int r_scene = rand() % cnt + 1;

	auto dic = (__Dictionary *)data->objectForKey(String::createWithFormat("%d", r_scene)->getCString());
	int objCnt = dic->valueForKey("cnt")->intValue();

	for (int i = 1; i <= objCnt; i++)
	{
		auto objDic = (__Dictionary *)dic->objectForKey(String::createWithFormat("%d", i)->getCString());
		int objX = objDic->valueForKey("x")->intValue();
		int objY = objDic->valueForKey("y")->intValue();
		std::string type = objDic->valueForKey("type")->getCString();

		if (type.compare("m") == 0)
		{
			Monster * m = nullptr;
			if (getMapType().compare("G") == 0)
				m = SlimeKing::create();
			else if (getMapType().compare("MV") == 0)
				m = Half::create(layer);
			else if (getMapType().compare("MC") == 0)
				m = Devil::create(layer);
			else if (getMapType().compare("HV") == 0)
				m = Half::create(layer);
			else if (getMapType().compare("HC") == 0)
				m = Angel::create(layer);
			else if (getMapType().compare("MM") == 0)
			{
				Hero * hero = (Hero *)layer->getChildByName("Hero");
				m = Me::create(hero);
			}

			if (m != nullptr)
			{
				m->setPosition(Vec2(startPoint.x + contentSize.width * objY + contentSize.width * 0.5f , startPoint.y - contentSize.height * objX + contentSize.height / 2 ));
				m->Draw(layer);
				m->StartAnimation();
				m->scheduleUpdate();
				monsters.pushBack(m);

				auto bossHp = BossHp::create(layer);
				bossHp->setPosition(visibleSize.width * 0.5f, visibleSize.height - 300);
				layer->addChild(bossHp, 10000);
				bossHp->SetTarget(m);
				bossHp->scheduleUpdate();
			}

		}
		else if (type.compare("b1") == 0)
		{
			auto brick = SingleBrick::create(getMapType().c_str(), BRICK_SINGLE_ID);
			brick->setPosition(Vec2(startPoint.x + contentSize.width * objY + contentSize.width * 0.5f , startPoint.y - contentSize.height * objX + contentSize.height / 2 ));
			layer->addChild(brick, ZINDEX_BRICK_SPRITE, myEnum::kMyTag::kBlockTag);
		}
		else if (type.compare("b2") == 0)
		{
			auto brick = DoubleBrick::create(getMapType().c_str(), layer, BRICK_DOUBLE_ID);
			brick->setPosition(Vec2(startPoint.x + contentSize.width * objY + contentSize.width * 0.5f , startPoint.y - contentSize.height * objX + contentSize.height / 2));
			layer->addChild(brick, ZINDEX_BRICK_SPRITE, myEnum::kMyTag::kBlockTag);
		}
		else if (type.compare("b3") == 0)
		{
			auto brick = SolidBrick::create(getMapType().c_str(), BRICK_SOLID_ID);
			brick->setPosition(Vec2(startPoint.x + contentSize.width * objY + contentSize.width * 0.5f , startPoint.y - contentSize.height * objX + contentSize.height / 2));
			layer->addChild(brick, ZINDEX_BRICK_SPRITE, myEnum::kMyTag::kBlockTag);
		}
	}
	
}


