//
//  GameObjStar.cpp
//  example12-1
//
//  Created by shuoquan man on 12-10-21.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//
#include "GameObjStar.h"


GameObjStar::GameObjStar(){
    
}

GameObjStar::~GameObjStar(){
    
}

void GameObjStar::onEnter(){
    Node::onEnter();
    
    // 初始化星星精灵
    Sprite* star = Sprite::create("star.png");
    this->setContentSize(Size(star->getContentSize().width, star->getContentSize().height));
    //star->setScale(0.5);
    _visable = true;
    addChild(star, 1);
}
void GameObjStar::onExit(){
    Node::onExit();
}

// 设置星星精灵是否可见的属性
void GameObjStar::set_visable(bool var){
    _visable = var;
    this->setVisible(var);
}
bool GameObjStar::get_visable(){
    return _visable;
}