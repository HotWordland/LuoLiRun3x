//
//  GameMainScene.cpp
//  example12-1
//
//  Created by shuoquan man on 12-10-21.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#include "GameMainScene.h"
#include "GameMenuScene.h"
#include "GameObjMap.h"
#include "GameConst.h"
#include "GameObjStar.h"
using namespace cocos2d;

Scene* GameMain::scene()
{
    Scene *scene = Scene::create();
    
    GameMain *layer = GameMain::create();
    
    scene->addChild(layer);
    
    return scene;
}
bool GameMain::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    Size size = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();
    
    // 添加移动的地图
    map = new GameObjMap();
    map->setAnchorPoint(Point(0, 1));
    map->setPosition(Point(0, size.height));
    addChild(map, 0);
    
    // 添加主角
    hero = new GameObjHero();
    //hero->setScale(0.5);
    hero->setPosition(Point(200, 320));
    addChild(hero, 1);
    
    gamemark = new GameMark();
    addChild(gamemark, 4);

//    // 为什么要new两次呢？内存泄漏了！注释掉了也是一样运行的。
//    gamemark = new GameMark();
//    addChild(gamemark, 4);
    
    if(1){
        
        // 游戏结束的图片精灵
        gameover = CCSprite::create("gameover.png");
        gameover->setAnchorPoint(Point(0.5, 0.5));
        gameover->setPosition(Point(0, 0));
        gameover->setPosition(Point(size.width/2, size.height/2 + 70));
        gameover->setVisible(false);
        //gameover->setScale(0.5);
        addChild(gameover, 5);
        
        // 返回按钮
        auto back = MenuItemImage::create("back.png",
                                          "back.png",
                                          CC_CALLBACK_1(GameMain::menuBackCallback, this));
        back->setPosition(Point(origin.x + back->getContentSize().width, size.height - back->getContentSize().height) );
        //back->setScale(0.5);
        
        Menu* pMenu = CCMenu::create(back, NULL);
        pMenu->setPosition( Point::ZERO );
        this->addChild(pMenu, 5, 25);
        
        pMenu->setVisible(false);
        pMenu->setEnabled(false);
        isover = false;
        
        scheduleUpdate();
    }
    
    return true;
}

// 设置游戏为结束状态：显示游戏结束的图片精灵，及返回菜单
void GameMain::setover(){
    // 停止计时器
    unscheduleUpdate();
    
    map->setGameOver();
    
    Menu* pMenu = (Menu *)this->getChildByTag(25);
    pMenu->setVisible(true);
    pMenu->setEnabled(true);
    
    gameover->setVisible(true);
    gameover->setScale(0);
    
    pMenu->setScale(0);
    pMenu->runAction(ScaleTo::create(0.5, 1));
    
    gameover->runAction(ScaleTo::create(0.5, 0.5));
    
    isover = true;
}

// 判断主角是否掉下去了
void GameMain::isherodrop(){
    
    Size size = Director::getInstance()->getVisibleSize();
    float fHeroWidth = hero->getContentSize().width;
    
	Point p1 = (map->getChildByTag(0))->getPosition();
	Point p2 = (map->getChildByTag(1))->getPosition();
    
    int temp;
    if(p1.x <= fHeroWidth && (p1.x + size.width) >= fHeroWidth){
        // 主角在地图1范围内
        temp = (fHeroWidth - p1.x) / 128;
        log("GameMain::isherodrop::地图1范围::p1.x=%0.2f, fHeroWidth=%0.2f, size.width=%0.2f, temp=%d", p1.x, fHeroWidth, size.width, temp);
        if(bg1shu[temp] == -1){
           hero->setState(2);
        }
    }else{
        // 主角在地图2范围内
        temp = (fHeroWidth - p2.x) / 128;
        log("GameMain::isherodrop::地图2范围::p1.x=%0.2f, fHeroWidth=%0.2f, size.width=%0.2f, temp=%d", p1.x, fHeroWidth, size.width, temp);
        if(bg2shu[temp] == -1){
            hero->setState(2);
        } 
    }
}

bool GameMain::isCollion(Point p1, Point p2, int w1, int h1, int w2, int h2){
    if(abs(p1.x - p2.x) < w1 + w2 && abs(p1.y - p2.y) < h1 + h2){
        return true;
    }
    return false;
};

// 计时器更新函数
void GameMain::update(float time){
    
    if(hero->state == 0){
        // 判断主角在奔跑的过程中，是否掉到没有路的位置了
        isherodrop();
    }
    
    if(1){
        // 判断是否顶到星星了
        Size size = Director::getInstance()->getVisibleSize();
        float fHeroWidth = hero->getContentSize().width;
        
        Point p1 = (map->getChildByTag(0))->getPosition();
        Point p2 = (map->getChildByTag(1))->getPosition();
        
        for(int i = 0;i < 5;i ++){
            if(p1.x <= fHeroWidth && (p1.x + size.width) >= fHeroWidth){
                // 主角在地图1范围内
                GameObjStar *obj = (GameObjStar *)(map->stars1).at(i);
                if(obj->get_visable() && isCollion(Point(200, hero->getPosition().y + 62.5), Point(p1.x + 86 + 96 * i, 460), 40, 35, 18.25, 17.75)){
                    obj->set_visable(false);
                    gamemark->addnumber(200);
                }
            }else{
                // 主角在地图2范围内
                GameObjStar *obj = (GameObjStar *)(map->stars2).at(i);
                if(obj->get_visable() && isCollion(Point(200, hero->getPosition().y + 62.5), Point(p2.x + 86 + 96 * i, 460), 40, 35, 18.25, 17.75)){
                    obj->set_visable(false);
                    gamemark->addnumber(200);
                }
            }
        }
    }
    
}

void GameMain::menuBackCallback(cocos2d::Ref* pSender){
    // 回到菜单界面
    Director::getInstance()->setDepthTest(true);
    Director::getInstance()->replaceScene(TransitionPageTurn::create(0.5, GameMenu::scene(), true));
}
void GameMain::onEnterTransitionDidFinish()
{
    Layer::onEnterTransitionDidFinish();
    Director::getInstance()->setDepthTest(false);
}

void GameMain::onExitTransitionDidStart()
{
    Layer::onExitTransitionDidStart();
}
void GameMain::onExit(){
    Layer::onExit();
}
void GameMain::onEnter(){
    Layer::onEnter();
}
