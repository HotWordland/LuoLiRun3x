//
//  GameMenuScene.h
//  example12-1
//
//  Created by shuoquan man on 12-10-13.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef example15_1_GameMenuScene_h
#define example15_1_GameMenuScene_h

#include "cocos2d.h"
using namespace cocos2d;

USING_NS_CC;

class GameMenu : public cocos2d::Layer
{
public:
    GameMenu();
    ~GameMenu();
    
public:
    bool issound;
    
    MenuItemImage* soundItem;     // 播放音乐菜单项
    
public:
    
    static cocos2d::Scene* scene();
    
    virtual bool init();
    
    virtual void onEnter();
    virtual void onExit();
    void menuEnter();
    
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    void menuNewGameCallback(cocos2d::Ref* pSender);
    
    void menuContinueCallback(cocos2d::Ref* pSender);
    
    void menuAboutCallback(cocos2d::Ref* pSender);
    
    void menuSoundCallback(cocos2d::Ref* pSender);
    
    void onEnterTransitionDidFinish();
    
    void onExitTransitionDidStart();
    
    CREATE_FUNC(GameMenu);
    
};

#endif
