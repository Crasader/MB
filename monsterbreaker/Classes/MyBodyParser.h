#pragma once
//
//  MyBodyParser.h
//
//  Created by Jason Xu.
//
//

#pragma once

#include <string>
#include "cocos2d.h"
USING_NS_CC;
#include "json/document.h"

class MyBodyParser {
	static MyBodyParser* instance;
    MyBodyParser(){}
    rapidjson::Document doc;
public:
    static MyBodyParser* getInstance();
	void freeInstance();
    bool parseJsonFile(const std::string& pFile);
    bool parse(unsigned char* buffer, long length);
    void clearCache();
    PhysicsBody* bodyFormJson(Node* pNode, const std::string& name, PhysicsMaterial material);
};