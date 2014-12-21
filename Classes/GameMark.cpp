//
//  GameMark.cpp
//  example12-1
//
//  Created by shuoquan man on 12-10-20.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#include "GameMark.h"

GameMark::GameMark(void)
{
}

GameMark::~GameMark(void)
{
}

void GameMark::onEnter()
{
    Node::onEnter();
    
    // 设置当前大小
    Size size = Director::getInstance()->getVisibleSize();
    this->setContentSize(size);
    
    // 添加成绩图片
	Sprite *title= Sprite::create("score.png");
    title->setPosition(Point(size.width/2, size.height - 30));
    //title->setScale(0.5);
    addChild(title);
    
    // 添加数字图片中的数字
    for(int i = 0; i < 5; i ++){
        Sprite * shu = Sprite::create("shu.png");
        ui = shu->getTexture();
        shu->setTextureRect(Rect(234, 0, 26, 31));      // 设置图片纹理的显示大小
        shu->setPosition(Point(size.width/5*4 - i * 30, size.height - 30));
        bits.pushBack(shu);
        addChild(shu);
    }
    
    mark = 0;
}

void GameMark::onExit()
{
    Node::onExit();
}

void GameMark::addnumber(int var){
    // 按位设置数字
    mark += var;
    
    // 各位
    int temp = mark % 10;
    if(temp > 0){
        ((Sprite *)bits.at(0))->setTexture(ui);
        ((Sprite *)bits.at(0))->setTextureRect(Rect((temp - 1) * 26, 0, 26, 31));
    }else{
        ((Sprite *)bits.at(0))->setTexture(ui);
        ((Sprite *)bits.at(0))->setTextureRect(Rect(234, 0, 26, 31));
    }
    
    // 十位
    temp = (mark % 100) / 10;
    if(temp > 0){
        ((Sprite *)bits.at(0))->setTexture(ui);
        ((Sprite *)bits.at(1))->setTextureRect(Rect((temp - 1) * 26,0,26,31));
 
    }else{
        ((Sprite *)bits.at(0))->setTexture(ui);
        ((Sprite *)bits.at(1))->setTextureRect(Rect(234,0,26,31));
    }
    
    // 百位
    temp = (mark % 1000) / 100;
    if(temp > 0){
        ((Sprite *)bits.at(0))->setTexture(ui);
        ((Sprite *)bits.at(2))->setTextureRect(Rect((temp - 1) * 26,0,26,31));
 
    }else{
        ((Sprite *)bits.at(0))->setTexture(ui);
        ((Sprite *)bits.at(2))->setTextureRect(Rect(234,0,26,31));
    }
    
    // 千位
    temp = (mark % 10000) / 1000;
    if(temp > 0){
        ((Sprite *)bits.at(0))->setTexture(ui);
        ((Sprite *)bits.at(3))->setTextureRect(Rect((temp - 1) * 26,0,26,31));
 
    }else{
        ((Sprite *)bits.at(0))->setTexture(ui);
        ((Sprite *)bits.at(3))->setTextureRect(Rect(234,0,26,31));
    }
    
    // 万位
    temp = mark / 10000;
    if(temp > 0){
        ((Sprite *)bits.at(0))->setTexture(ui);
        ((Sprite *)bits.at(4))->setTextureRect(Rect((temp - 1) * 26,0,26,31));
 
    }else{
        ((Sprite *)bits.at(0))->setTexture(ui);
        ((Sprite *)bits.at(4))->setTextureRect(Rect(234,0,26,31));
    }
}