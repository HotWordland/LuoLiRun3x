﻿//
//  GameAboutScene.h
//  example12-1
//
//  Created by shuoquan man on 12-10-14.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef example15_1_GameAboutScene_h
#define example15_1_GameAboutScene_h
#include "cocos2d.h"
using namespace cocos2d;

USING_NS_CC;

class GameAbout : public cocos2d::Layer
{
public:
    
    virtual bool init();
    
    virtual void onEnter();
    
    virtual void onExit();
    
    static cocos2d::Scene* scene();
    
    void menuBackCallback(cocos2d::Ref* pSender);
    
    CREATE_FUNC(GameAbout);
    
    void onEnterTransitionDidFinish();
    void onExitTransitionDidStart();
};


#endif
