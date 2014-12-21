//
//  GameAboutScene.cpp
//  example12-1
//
//  Created by shuoquan man on 12-10-14.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#include "GameAboutScene.h"
#include "GameMenuScene.h"

using namespace cocos2d;

Scene* GameAbout::scene()
{
    Scene *scene = Scene::create();
    
    GameAbout *layer = GameAbout::create();
    
    scene->addChild(layer);
    
    return scene;
}
bool GameAbout::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size size = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();
    
    auto bg = Sprite::create("back_1.png");
    //bg->setScale(0.6f);
    bg->setPosition(Point(size.width/2 + origin.x, size.height/2 + origin.y));
    this->addChild(bg, 0, 0);
    
    auto kuang = Sprite::create("tb.png");
    kuang->setScale(0.8);
    kuang->setRotation(90);
    kuang->setPosition(Point(size.width/2 + origin.x, size.height/2 + origin.y));
    this->addChild(kuang, 2, 2);

    char inf[256] = {0};
    sprintf(inf,"name:loli run\n\n program:shuoquan man\n\n art design:zuyi li\n\n company:hz books\n\n    powered by cocos2D-x");
    
    auto myjineng = LabelTTF::create(inf, "Marker Felt", 20, Size(300, 280), TextHAlignment::LEFT);
    myjineng->setFontFillColor(Color3B::BLACK, true);
    //myjineng->setAnchorPoint(Point(0, 1));
    myjineng->setPosition(Point(size.width/2 + origin.x, size.height/2 + origin.y));
    this->addChild(myjineng);
    
    // 关于标签/标题图片
    auto abouttitle = Sprite::create("about.png");
    //abouttitle->setScale(0.5);
    abouttitle->setPosition(Point(size.width/2 + origin.x, size.height - abouttitle->getContentSize().height + origin.y));
    this->addChild(abouttitle, 3, 3);
    
    // 返回
    auto back = MenuItemImage::create("backA.png",
                                      "backB.png",
                                      CC_CALLBACK_1(GameAbout::menuBackCallback, this));
    //back->setScale(0.5);
    back->setPosition(Point(origin.x + back->getContentSize().width, size.height - back->getContentSize().height));
    back->setEnabled(false);
    
    auto mainmenu = Menu::create(back, NULL);
    mainmenu->setPosition(Point::ZERO);
    this->addChild(mainmenu, 3, 4);
    
    return true;
}
void GameAbout::menuBackCallback(cocos2d::Ref* pSender){
    Director::getInstance()->setDepthTest(true);
    Director::getInstance()->replaceScene(CCTransitionPageTurn::create(0.5,GameMenu::scene(), true));
}
void GameAbout::onEnterTransitionDidFinish()
{
    Layer::onEnterTransitionDidFinish();
    Director::getInstance()->setDepthTest(false);
}

void GameAbout::onExitTransitionDidStart()
{
    Layer::onExitTransitionDidStart();
}
void GameAbout::onExit(){
    Layer::onExit();
}
void GameAbout::onEnter(){
    Layer::onEnter();
    Node* mainmenu = (Node*)this->getChildByTag(4);
    auto& temp = mainmenu->getChildren();
    ((MenuItemImage *)temp.at(0))->setEnabled(true);
}