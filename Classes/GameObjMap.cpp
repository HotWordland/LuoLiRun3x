//
//  GameObjMap.cpp
//  example12-1
//
//  Created by shuoquan man on 12-10-21.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#include "GameObjMap.h"
#include "GameConst.h"

GameObjMap::GameObjMap(){
    
}

GameObjMap::~GameObjMap(){
    
}

void GameObjMap::onEnter(){
    Node::onEnter();
    
    bisover = false;
    
    Size size = Director::getInstance()->getVisibleSize();
    log("GameObjMap::onEnter::w=%0.2f, h=%0.2f", size.width, size.height);
    
    // 设置地图大小：显示窗体宽度的2倍
    this->setContentSize(Size(size.width*2, size.height));
    
    // 背景1（远景图片）
    auto bg1 = Sprite::create("back_1.png");
    bg1->setAnchorPoint(Point(0, 1));
    bg1->setPosition(Point(0, size.height) );   // 初始位置是在屏幕左侧对齐位置
    this->addChild(bg1, 0, 0);
    
    // 为背景1添加近景图片
    auto bgdi1 = Sprite::create("back_5.png");
    bgdi1->setAnchorPoint(Point(0, 0));
    bgdi1->setPosition(Point(0, -248) );
    bg1->addChild(bgdi1, 1);
    
    // 背景2（远景图片）
    auto bg2 = Sprite::create("back_1.png");
    bg2->setAnchorPoint(Point(0, 1));
    bg2->setPosition(Point(size.width, size.height) );   // 初始位置是在屏幕右侧对齐位置
    this->addChild(bg2, 0, 1);
    
    // 为背景2添加近景图片
    auto bgdi2 = Sprite::create("back_5.png");
    bgdi2->setAnchorPoint(Point(0, 0));
    bgdi2->setPosition(Point(0, -248) );
    bg2->addChild(bgdi2, 1);
    
    // 运行背景1的移动动画：初始位置在屏幕左侧对齐的位置，运行到屏幕左侧后，调用bg1change方法从右侧重新开始移动
    bg1->runAction(Sequence::create(MoveBy::create(10, Point(-size.width, 0)),
                                    CallFunc::create(CC_CALLBACK_0(GameObjMap::bg1change, this)), NULL));
    
    // 运行背景2的移动动画：初始位置在屏幕右侧对齐的位置，运行到屏幕左侧后，调用bg2change方法从右侧重新开始移动
    bg2->runAction(Sequence::create(MoveBy::create(20, Point(-size.width*2, 0)),
                                    CallFunc::create(CC_CALLBACK_0(GameObjMap::bg2change, this)), NULL));
    
    // 为背景1和背景2各添加5个星星精灵
    for(int i = 0; i < 5; i ++){
        GameObjStar* obj = new GameObjStar();
        //obj->setPosition(Point(344 + 384 * i, 350));
        obj->setPosition(Point(172 + 192 * i, 350));
        stars1.pushBack(obj);
        bg1->addChild(obj, 3);
        
        obj = new GameObjStar();
        obj->setPosition(Point(172 + 192 * i, 350));
        stars2.pushBack(obj);
        bg2->addChild(obj, 3);
    }
    
    // 添加大树、草地、墙等
    for(int i = 0; i < 7; i ++){
        Sprite* roaddi;
        Sprite* plant;
        const float fRoadWidth = 128;
        
        // 添加背景1的道路、植物等
        if(bg1shu[i] != -1){
            Sprite* road;
            switch(bg1shu[i]){
                case 0:     // 树、草地、墙
                    plant = Sprite::create("back_2.png");
                    plant->setAnchorPoint(Point(0.5, 0));
                    plant->setPosition( Point(fRoadWidth * i + 64, 117) );
                    bg1->addChild(plant, 1);
                    
                    road = Sprite::create("road_2.png");
                    road->setAnchorPoint(Point(0, 0));
                    road->setPosition( Point(fRoadWidth * i, 0) );
                    
                    roaddi = Sprite::create("road_3.png");
                    roaddi->setAnchorPoint(Point(0, 1));
                    roaddi->setPosition( Point(fRoadWidth * i, 0) );
                    bg1->addChild(roaddi, 1);
                    break;
                case 1:
                    road = Sprite::create("road_1.png");
                    road->setAnchorPoint(Point(0,0));
                    road->setPosition( Point(26 + fRoadWidth * i,0) );
                    
                    roaddi = Sprite::create("road_4.png");
                    roaddi->setAnchorPoint(Point(0,1));
                    roaddi->setPosition( Point(26 + fRoadWidth * i,0) );
                    bg1->addChild(roaddi,1);
                    break;
                case 2:
                    plant = Sprite::create("enemy.png");
                    plant->setAnchorPoint(Point(0.5,0));
                    plant->setPosition( Point(fRoadWidth * i + 64,112) );
                    bg1->addChild(plant,1);
                    
                    road = Sprite::create("road_1.png");
                    road->setFlippedX(true);
                    road->setAnchorPoint(Point(0,0));
                    road->setPosition( Point(fRoadWidth * i,0) );
                    
                    roaddi = Sprite::create("road_4.png");
                    roaddi->setFlippedX(true);
                    roaddi->setAnchorPoint(Point(0,1));
                    roaddi->setPosition( Point(fRoadWidth * i,0) );
                    bg1->addChild(roaddi,1);
                    break;
                case 3:
                    road = Sprite::create("road_5.png");
                    road->setAnchorPoint(Point(0,0));
                    road->setPosition( Point(fRoadWidth * i,0) );
                    break;
                    
            }
            bg1->addChild(road,1);
        }
        
        // 添加背景2的道路、植物等
        if(bg2shu[i] != -1){
            Sprite* road1;
            switch(bg2shu[i]){
                case 0:
                    road1 = Sprite::create("road_2.png");
                    road1->setAnchorPoint(Point(0,0));
                    road1->setPosition( Point(fRoadWidth * i,0) );
                    
                    roaddi = Sprite::create("road_3.png");
                    roaddi->setAnchorPoint(Point(0,1));
                    roaddi->setPosition( Point(fRoadWidth * i,0) );
                    bg2->addChild(roaddi,1);
                    break;
                case 1:
                    plant = Sprite::create("back_3.png");
                    plant->setAnchorPoint(Point(0.5,0));
                    plant->setPosition( Point(fRoadWidth * i + 128,117) );
                    bg2->addChild(plant,1);
                    
                    road1 = Sprite::create("road_1.png");
                    road1->setAnchorPoint(Point(0,0));
                    road1->setPosition( Point(26 + fRoadWidth * i,0) );
                    
                    roaddi = Sprite::create("road_4.png");
                    roaddi->setAnchorPoint(Point(0,1));
                    roaddi->setPosition( Point(26 + fRoadWidth * i,0) );
                    bg2->addChild(roaddi,1);
                    break;
                case 2:
                    road1 = Sprite::create("road_1.png");
                    road1->setFlippedX(true);
                    road1->setAnchorPoint(Point(0,0));
                    road1->setPosition( Point(fRoadWidth * i,0) );
                    
                    roaddi = Sprite::create("road_4.png");
                    roaddi->setFlippedX(true);
                    roaddi->setAnchorPoint(Point(0,1));
                    roaddi->setPosition( Point(fRoadWidth * i,0) );
                    bg2->addChild(roaddi,1);
                    break;
                case 3:
                    road1 = Sprite::create("road_5.png");
                    road1->setAnchorPoint(Point(0,0));
                    road1->setPosition( Point(fRoadWidth * i,0) );
                    break;
                    
            }
            bg2->addChild(road1,1);
        }
    }
    
    state = 0;
}

void GameObjMap::onExit(){
    Node::onExit();
}


// 背景1的移动动画：运动出屏幕后，重设位置，并重新运动，循环被调用。
void GameObjMap::bg1change(){
    if(bisover){
        return;
    }
    
    // 此时，背景1精灵对象已经移动到了屏幕左侧的位置，需要先定位到屏幕右侧，然后再次启动动画向左移动
    Size size = Director::getInstance()->getVisibleSize();
    
    // 获取背景1精灵对象
    Sprite * bg = (Sprite *)this->getChildByTag(0);
    
    // 将位置放到屏幕右侧，以便动画移动到左侧
    bg->setPosition(Point(size.width, size.height));
    
    // 运行到屏幕左侧的位置以后，再次调用bg1change方法
    bg->runAction(CCSequence::create(CCMoveBy::create(20, Point(-size.width*2, 0)),
                                     CallFunc::create(CC_CALLBACK_0(GameObjMap::bg1change, this)), NULL));
    
    if(1){
        // 将5个星星都设置为显示状态
        for(int i = 0; i < 5; i ++){
            ((GameObjStar *)stars1.at(i))->set_visable(true);
        }
    }
    
}

// 背景2的移动动画：原理同bg1change
void GameObjMap::bg2change(){
    if(bisover){
        return;
    }
    
    //
    Size size = Director::getInstance()->getVisibleSize();
    
    Sprite * bg = (Sprite *)this->getChildByTag(1);
    bg->setPosition(Point(size.width, size.height));
    bg->runAction(Sequence::create(MoveBy::create(20,Point(-size.width*2, 0)),
                                   CallFunc::create(CC_CALLBACK_0(GameObjMap::bg2change, this)), NULL));
    
    if(1){
        for(int i = 0; i < 5; i ++){
            ((GameObjStar *)stars2.at(i))->set_visable(true);
        }
    }
    
}

void GameObjMap::setGameOver(){
    bisover = true;
    
    Sprite * bg1 = (Sprite *)this->getChildByTag(0);
    bg1->stopAllActions();
    
    Sprite * bg2 = (Sprite *)this->getChildByTag(1);
    bg2->stopAllActions();
}