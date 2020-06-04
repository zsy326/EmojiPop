#include "MainMenuScene.h"
#include "SimpleAudioEngine.h"
#include "GameScene.h"
#include "MusicScene.h"

USING_NS_CC;
using namespace CocosDenshion;

Scene* MainMenu::createScene(){
    return MainMenu::create();
}

static void problemLoading(const char* filename){
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool MainMenu::init(){
    if (!Scene::init()) { 
        return false; 
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

//set bgm
    SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("bgm.mp3");

//turn on the bgm
    SimpleAudioEngine::sharedEngine()->playBackgroundMusic("bgm.mp3", true);


 //set background
    auto bg2 = Sprite::create("background.png");
    bg2->setPosition(Vec2(240, -120));
    bg2->setAnchorPoint(Vec2(0.5, 0));
    this->addChild(bg2, 0);

 //set begin button
    auto beginItem = MenuItemImage::create(
        "BeginNormal.png",
        "BeginSelected.png",
        CC_CALLBACK_1(MainMenu::GoToGameScene, this));

 //set music button
    auto musicItem = MenuItemImage::create(
        "musicNormal.png",
        "musicSelected.png",
        CC_CALLBACK_1(MainMenu::GoToMusicScene, this));

 //set close button
    auto closeItem = MenuItemImage::create(
        "CloseNormal.png",
        "CloseSelected.png",
        CC_CALLBACK_1(MainMenu::menuCloseCallback, this));

//set menu
    auto menu = Menu::create(beginItem, musicItem,closeItem, NULL);
    menu->alignItemsVerticallyWithPadding(visibleSize.height / 12);
    this->addChild(menu,1);


 //set label
    auto label = Label::createWithTTF("Contents", "fonts/Marker Felt.ttf", 24);
    if (label == nullptr){
        problemLoading("'fonts/Marker Felt.ttf'");
    }
    else{
        label->setPosition(Vec2(origin.x + visibleSize.width / 2,
            origin.y + visibleSize.height - label->getContentSize().height));
        this->addChild(label, 1);
    }

    return true;
}


void MainMenu::GoToGameScene(Ref* pSender){ 
    Director::getInstance()->replaceScene(Game::createScene()); }

void MainMenu::GoToMusicScene(Ref* pSender){ 
    Director::getInstance()->replaceScene(Music::createScene()); }

void MainMenu::menuCloseCallback(Ref* pSender) {
    Director::getInstance()->end();
}

