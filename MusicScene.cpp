#include "MusicScene.h"
#include "SimpleAudioEngine.h"
#include "MainMenuScene.h"

USING_NS_CC;
using namespace CocosDenshion;

Scene* Music::createScene()
{
    return Music::create();
}

static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool Music::init()
{
    if (!Scene::init()) { 
        return false; 
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

//set bgm button
    auto bgmItem = MenuItemImage::create(
        "musicNormal.png",
        "musicSelected.png",
        CC_CALLBACK_1(Music::menuBgm, this));


//set no bgm button
    auto volume0Item = MenuItemImage::create(
        "Volume0Normal.png",
        "Volume0Selected.png",
        CC_CALLBACK_1(Music::menuVolume0, this));

//set volume1 button
    auto volume1Item = MenuItemImage::create(
        "Volume1Normal.png",
        "Volume1Selected.png",
        CC_CALLBACK_1(Music::menuVolume1, this));

//set volume2 button
    auto volume2Item = MenuItemImage::create(
        "Volume2Normal.png",
        "Volume2Selected.png",
        CC_CALLBACK_1(Music::menuVolume2, this));

//set volume3 button
    auto volume3Item = MenuItemImage::create(
        "Volume3Normal.png",
        "Volume3Selected.png",
        CC_CALLBACK_1(Music::menuVolume3, this));

    //set menu
    auto menu = Menu::create(bgmItem,volume0Item, volume1Item, volume2Item,volume3Item, NULL);
    menu->alignItemsVerticallyWithPadding(visibleSize.height / 16);
    this->addChild(menu, 1);


//set back button
    auto backItem = MenuItemImage::create(
        "BackNormal.png",
        "BackSelected.png",
        CC_CALLBACK_1(Music::menuBack, this));


    //唯一幸存下来的检查空指针的地方，方便以后写成函数修改代码

    //if (backItem == nullptr ||
    //    backItem->getContentSize().width <= 0 ||
    //    backItem->getContentSize().height <= 0){
    //    problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
    //}

    backItem->setPosition(Vec2(origin.x + visibleSize.width / 8,
        origin.y + visibleSize.height / 1.2));

    auto menu2 = Menu::create(backItem, NULL);
    menu2->setPosition(Vec2::ZERO);
    this->addChild(menu2, 1);

    return true;
}
void Music::menuBgm(Ref* pSender) {
    SimpleAudioEngine::sharedEngine()->rewindBackgroundMusic();
}

void Music::menuVolume0(Ref* pSender) {
    SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
}

void Music::menuVolume1(Ref* pSender) {
    SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(0.3f);
}

void Music::menuVolume2(Ref* pSender) {
    SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(0.5f);
}

void Music::menuVolume3(Ref* pSender) {
    SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(1.0f);
}


void Music::menuBack(Ref* pSender) {
    Director::getInstance()->replaceScene(MainMenu::createScene());
}
