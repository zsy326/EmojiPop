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

    auto visible_size = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

//set bgm
    SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("bgm.mp3");

//turn on the bgm
    SimpleAudioEngine::sharedEngine()->playBackgroundMusic("bgm.mp3", true);


 //set background
    auto bg2 = Sprite::create("Background.png");
    bg2->setPosition(Vec2(origin.x+visible_size.width/2, origin.y + visible_size.height / 2));
    this->addChild(bg2, 0);

 //set begin button
    auto begin_item = MenuItemImage::create(
        "BeginNormal.png",
        "BeginSelected.png",
        CC_CALLBACK_1(MainMenu::GoToGameScene, this));

 //set music button
    auto music_item = MenuItemImage::create(
        "musicNormal.png",
        "musicSelected.png",
        CC_CALLBACK_1(MainMenu::GoToMusicScene, this));

 //set close button
    auto close_item = MenuItemImage::create(
        "CloseNormal.png",
        "CloseSelected.png",
        CC_CALLBACK_1(MainMenu::MenuCloseCallback, this));

//set menu
    auto menu = Menu::create(begin_item, music_item,close_item, NULL);
    menu->alignItemsVerticallyWithPadding(visible_size.height / 40);
    this->addChild(menu,1);

    return true;
}


void MainMenu::GoToGameScene(Ref* pSender){ 
    Director::getInstance()->replaceScene(Game::CreateScene()); }

void MainMenu::GoToMusicScene(Ref* pSender){ 
    Director::getInstance()->replaceScene(Music::CreateScene()); }

void MainMenu::MenuCloseCallback(Ref* pSender) {
    Director::getInstance()->end();
}

