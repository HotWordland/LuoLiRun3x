//
//  GameObjHero.h
//  example12-1
//
//  Created by shuoquan man on 12-10-14.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef example15_1_GameObjHero_h
#define example15_1_GameObjHero_h

#include "cocos2d.h"
using namespace cocos2d;

USING_NS_CC;

class GameObjHero : public Node
{
public:
    Sprite *mainsprite;
    Texture2D *hurt;
    Texture2D *jump;
    Point offset;
    short state;    // 0:正常 1：跳跃 2：受伤
    bool iscontrol;
    
    GameObjHero(void);
    virtual ~GameObjHero(void);
    
    void setState(short var);
    Rect rect();
    virtual void onEnter();
    virtual void onExit();
    
    // 处理动画结束后的操作
    void jumpend();
    void hurtend();
    
    // 3x中，使用事件管理器对事件进行管理了
//    bool containsTouchLocation(Touch* touch);
//    virtual bool ccTouchBegan(CCTouch* touch, CCEvent* event);
//    virtual void ccTouchMoved(CCTouch* touch, CCEvent* event);
//    virtual void ccTouchEnded(CCTouch* touch, CCEvent* event);
    
//    virtual void touchDelegateRetain();
//    virtual void touchDelegateRelease();
    
};


#endif
