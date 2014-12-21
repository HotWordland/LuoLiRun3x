//
//  GameObjMap.h
//  example12-1
//
//  Created by shuoquan man on 12-10-21.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef example16_1_GameObjMap_h
#define example16_1_GameObjMap_h
//#include "cocos2d.h"
#include "GameObjStar.h"
using namespace cocos2d;

USING_NS_CC;

// 地图类，负责地图的循环滚动、背景精灵的管理等
class GameObjMap : public Node
{
public:
    GameObjMap(void);
    short state;
    bool bisover;
    virtual ~GameObjMap(void);
    virtual void onEnter();
    virtual void onExit();
    void bg1change();
    void bg2change();
    
    void setGameOver();
    
    //
    cocos2d::Vector<GameObjStar*> stars1;
    cocos2d::Vector<GameObjStar*> stars2;
};


#endif
