//
//  GameMenuScene.cpp
//  example12-1
//
//  Created by shuoquan man on 12-10-13.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#include "GameMenuScene.h"
#include "GameMainScene.h"
#include "GameAboutScene.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;

GameMenu::GameMenu(){
    
}
GameMenu::~GameMenu(){
    
}

Scene* GameMenu::scene()
{
    auto scene = CCScene::create();
    auto layer = GameMenu::create();
    scene->addChild(layer);
    
    return scene;
}
bool GameMenu::init()
{
    if(!Layer::init())
    {
        return false;
    }
    
    // 获取显示窗体大小及显示原点位置
    Size size = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();
    
    // 背景图片
    auto spriteBackground = Sprite::create("MainMenu.png");
    //spriteBackground->setScale(0.5);
    spriteBackground->setPosition(Point(size.width/2 + origin.x, size.height/2 + origin.y));
    this->addChild(spriteBackground, 0, 0);
    
    if(1){
        auto closeItem = MenuItemImage::create("CloseNormal.png",
                                               "CloseSelected.png",
                                               CC_CALLBACK_1(GameMenu::menuCloseCallback, this));
        closeItem->setPosition(Vec2(origin.x + size.width - closeItem->getContentSize().width/1 ,
                                    origin.y + closeItem->getContentSize().height/1));
        auto menu = Menu::create(closeItem, NULL);
        menu->setPosition(Vec2::ZERO);
        this->addChild(menu, 10);
    }
    
    // --------------------------------------------------
    // 添加菜单按钮：默认为禁止响应，启动动画结束后，再让其响应操作
    // 新游戏按钮菜单项
    auto newGameItem = MenuItemImage::create("newgameA.png",
                                             "newgameB.png",
                                             CC_CALLBACK_1(GameMenu::menuNewGameCallback, this));
    //newGameItem->setScale(0.5);
    newGameItem->setPosition(Point(origin.x + size.width / 2, origin.y + size.height / 2 - newGameItem->getContentSize().height*1));
    newGameItem->setEnabled(true);
    
    // 继续游戏按钮菜单项
    auto continueItem = MenuItemImage::create("continueA.png",
                                              "continueB.png",
                                              CC_CALLBACK_1(GameMenu::menuContinueCallback, this));
    //continueItem->setScale(0.5);
    continueItem->setPosition(Point(origin.x + size.width / 2, origin.y + size.height / 2 - continueItem->getContentSize().height*2.5));
    continueItem->setEnabled(true);
    
    // 关于按钮菜单项
    auto aboutItem = MenuItemImage::create("aboutA.png",
                                           "aboutB.png",
                                           CC_CALLBACK_1(GameMenu::menuAboutCallback, this));
    //aboutItem->setScale(0.5);
    aboutItem->setPosition(Point(origin.x + size.width / 2, origin.y + size.height / 2 - aboutItem->getContentSize().height*4));
    aboutItem->setEnabled(true);
    
    // 声音菜单项
    soundItem = CCMenuItemImage::create("sound-on-A.png",
                                        "sound-on-B.png",
                                        CC_CALLBACK_1(GameMenu::menuSoundCallback, this));
    //soundItem->setScale(0.5);
    soundItem->setEnabled(true);
    soundItem->setPosition(Point(origin.x + 40, origin.y + 40));
    
    auto menu = Menu::create(newGameItem,continueItem,aboutItem,soundItem, NULL);
    menu->setPosition(Point::ZERO);
    this->addChild(menu, 1, 3);
    
    // 初始化声音相关
    issound = true;
    CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.5);
    if(0){
        CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("background.mp3", true);
    }
    
    return true;
}

// 进入场景时调用
void GameMenu::onEnter(){
    Layer::onEnter();
    
    // 入场动作：显示菜单由小变大的动画
    Node* mainmenu = (Node*)this->getChildByTag(3);
    mainmenu->setScale(0.5);
    mainmenu->runAction(Sequence::create(ScaleTo::create(0.5, 1),
                                         CallFunc::create(CC_CALLBACK_0(GameMenu::menuEnter, this)),
                                         nullptr));
    
}

void GameMenu::onEnterTransitionDidFinish()
{
    Layer::onEnterTransitionDidFinish();
    
    // 取消OpenGL的深度测试
    Director::getInstance()->setDepthTest(false);
}

void GameMenu::onExitTransitionDidStart()
{
    Layer::onExitTransitionDidStart();
}

// 退出场景时调用
void GameMenu::onExit(){
    Layer::onExit();
}

// 启动动画结束后调用
void GameMenu::menuEnter(){
    // 入场动作结束，让所有菜单项响应操作
    Node* mainmenu = (Node*)this->getChildByTag(3);
    auto& temp = mainmenu->getChildren();
    auto childrenCount = temp.size();
    Node* child = nullptr;
    for(int i = 0; i < childrenCount; i ++){
        child = temp.at(i);
        ((MenuItemImage*)child)->setEnabled(true);
    }
}

// 关闭菜单响应操作
void GameMenu::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif
    
    Director::getInstance()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

// 开始新游戏
void GameMenu::menuNewGameCallback(cocos2d::Ref* pSender)
{
    Director::getInstance()->setDepthTest(true);
    Director::getInstance()->replaceScene(TransitionPageTurn::create(0.5, GameMain::scene(), false));
}

// 继续游戏
void GameMenu::menuContinueCallback(cocos2d::Ref* pSender)
{
    Director::getInstance()->setDepthTest(true);
    Director::getInstance()->replaceScene(TransitionPageTurn::create(0.5, GameMain::scene(), false));
}

// 关于
void GameMenu::menuAboutCallback(cocos2d::Ref* pSender)
{
    Director::getInstance()->setDepthTest(true);
    Director::getInstance()->replaceScene(TransitionPageTurn::create(0.5, GameAbout::scene(), false));
}

// 控制是否静音
void GameMenu::menuSoundCallback(cocos2d::Ref* pSender)
{
    //设置声音
    if(!issound){
        soundItem->setNormalImage(Sprite::create("sound-on-A.png"));
        soundItem->setDisabledImage(Sprite::create("sound-on-B.png"));
        
        CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("background.mp3", true);
        issound = true;
    }else{
        soundItem->setNormalImage(CCSprite::create("sound-off-A.png"));
        soundItem->setDisabledImage(CCSprite::create("sound-off-B.png"));
        CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
        issound = false;
    }
}