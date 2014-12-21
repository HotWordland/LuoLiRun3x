//
//  GameObjHero.cpp
//  example12-1
//
//  Created by shuoquan man on 12-10-14.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//
#include "GameObjHero.h"
#include "GameMainScene.h"

GameObjHero::GameObjHero(void)
{
}

GameObjHero::~GameObjHero(void)
{
}

Rect GameObjHero::rect()
{
    Size s = Size(this->getContentSize().width, this->getContentSize().height);
    return Rect(-s.width / 2, -s.height / 2, s.width, s.height);
}

//void GameObjHero::touchDelegateRetain()
//{
//    //this->retain();
//}
//
//void GameObjHero::touchDelegateRelease()
//{
//    //this->release();
//}
void GameObjHero::onEnter()
{
    Node::onEnter();
    
    // 加载哭的精灵对象
    Sprite * obj = Sprite::create("s_hurt.png");
    hurt = obj->getTexture();
    
    // 加载跳跃的精灵对象
    obj = Sprite::create("s_jump.png");
    jump = obj->getTexture();
    
    // 加载主精灵对象
    mainsprite = Sprite::create("s_1.png");
    
    // 以主精灵图片的大小作为当前精灵的大小
    this->setContentSize(Size(mainsprite->getContentSize().width, mainsprite->getContentSize().height));
    
    log("GameObjHero::onEnter::x=%0.2f, y=%0.2f, w=%0.2f, h=%0.2f", this->getPosition().x, this->getPosition().y, this->getContentSize().width, this->getContentSize().height);
    
    // 加载跑动的动画帧图片
    Animation * animation = Animation::create();
    animation->addSpriteFrameWithFile("s_1.png");
    animation->addSpriteFrameWithFile("s_2.png");
    animation->addSpriteFrameWithFile("s_3.png");
    animation->addSpriteFrameWithFile("s_4.png");
    animation->addSpriteFrameWithFile("s_5.png");
    animation->addSpriteFrameWithFile("s_6.png");
    animation->setDelayPerUnit(0.1f);
    animation->setRestoreOriginalFrame(true);
    
    // 绑定触摸监听
    auto listener1 = EventListenerTouchOneByOne::create();  // 创建一个触摸监听
	listener1->setSwallowTouches(true); // 设置是否向下传递触摸
    
    // 定义点击响应的矩形范围
    Point origin = Director::getInstance()->getVisibleOrigin();
	Rect rect = Rect(origin.x - this->getContentSize().width/2,
                     origin.y - this->getContentSize().height/2 ,
                     this->getContentSize().width,
                     this->getContentSize().height);
    
	// 3.0 后可以直接在touchBegan后添加它的实现代码，而不用特意去写一个touchBegan的函数
	listener1->onTouchBegan = [rect, this](Touch* touch, Event* event){ // []中间的是传入的参数
        
		auto target = static_cast<Sprite*>(event->getCurrentTarget());  // 获取当前触摸的目标
        
		Point locationInNode = target->convertToNodeSpace(touch->getLocation());
		Size s = target->getContentSize();
        
        //log("GameObjHero::onTouchBegan::rx=%0.2f, ry=%0.2f, rw=%0.2f, rh=%0.2f, lx=%0.2f, ly=%0.2f", rect.origin.x, rect.origin.y, rect.size.width, rect.size.height, locationInNode.x, locationInNode.y);
        
		if (rect.containsPoint(locationInNode))     // 判断触摸点是否在目标的范围内
		{
            if(((GameMain *)this->getParent())->isover)
                return false;
            
            // 设置运动状态：跳跃
            setState(1);
            
            return true;
		}else
            return false;
	};
    
	// 拖动精灵移动
	listener1->onTouchMoved = [rect, this](Touch* touch, Event* event){
		auto target = static_cast<Sprite*>(event->getCurrentTarget());//获取的当前触摸的目标
        
		Point locationInNode = target->convertToNodeSpace(touch->getLocation());
		Size s = target->getContentSize();
        
		if (rect.containsPoint(locationInNode)) // 判断触摸点是否在目标的范围内
		{
			//
		}
	};
    
	listener1->onTouchEnded = [=](Touch* touch, Event* event){ // =在c++11里面代表这个lambda表达式中能使用外面的变量
		//
	};
    
	// 将触摸监听添加到eventDispacher中去
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, this);
    
    state = 0;  // 置为奔跑状态
    
    // 运行奔跑动画
    mainsprite->runAction(RepeatForever::create(Animate::create(animation)));
    addChild(mainsprite);
    
}

// 设置精灵当前状态
void GameObjHero::setState(short var){
    if(state == var)
        return;     // 状态相同不需要处理
    
    // 重置状态
    state = var;
    
    switch(state){
        case 1: // 跳跃
        {
            // 先停止所有正在进行的动画
            this->stopAllActions();
            mainsprite->stopAllActions();
            
            // 设置主角贴图为跳跃的贴图
            mainsprite->setTexture(jump);
            
            // 显示跳跃的动画
            this->runAction(Sequence::create(JumpBy::create(2.5, Point(0, 0), this->getContentSize().height/5*4, 1),
                                             CallFunc::create(CC_CALLBACK_0(GameObjHero::jumpend, this)), NULL));
            break;
        }
        case 2: // 受伤
        {
            // 先停止所有正在进行的动画
            this->stopAllActions();
            mainsprite->stopAllActions();
            
            // 设置主角贴图为哭的贴图
            mainsprite->setTexture(hurt);
            
            // 显示闪烁的动画
            this->runAction(Sequence::create(Blink::create(3, 10),
                                             CallFunc::create(CC_CALLBACK_0(GameObjHero::hurtend, this)),NULL));
            
            // 设置游戏为结束状态
            ((GameMain *)this->getParent())->setover();
            
            break;
        }
        case 0:     // 奔跑动画
        {
            // 先停止所有正在进行的动画
            this->stopAllActions();
            mainsprite->stopAllActions();
            
            // 运行奔跑的动画
            Animation * animation = Animation::create();
            animation->addSpriteFrameWithFile("s_1.png");
            animation->addSpriteFrameWithFile("s_2.png");
            animation->addSpriteFrameWithFile("s_3.png");
            animation->addSpriteFrameWithFile("s_4.png");
            animation->addSpriteFrameWithFile("s_5.png");
            animation->addSpriteFrameWithFile("s_6.png");
            animation->setDelayPerUnit(0.1f);
            animation->setRestoreOriginalFrame(true);
            mainsprite->runAction(RepeatForever::create(Animate::create(animation)));
            
            break;
        }
    }
}
void GameObjHero::jumpend(){
    // 恢复为奔跑状态
    setState(0);
}
void GameObjHero::hurtend(){
    // 恢复为奔跑状态
    //setState(0);  // 游戏结束了，就不应该再奔跑了吧？
}
void GameObjHero::onExit()
{
    CCNode::onExit();
}    
//bool GameObjHero::containsTouchLocation(Touch* touch)
//{
//	return rect().containsPoint(convertTouchToNodeSpaceAR(touch));
//}



