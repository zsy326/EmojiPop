#include "MusicScene.h"
#include "SimpleAudioEngine.h"
#include "MainMenuScene.h"

USING_NS_CC;
using namespace CocosDenshion;

Scene* Music::CreateScene()
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
        CC_CALLBACK_1(Music::MenuBgm, this));


//set no bgm button
    auto volume0Item = MenuItemImage::create(
        "Volume0Normal.png",
        "Volume0Selected.png",
        CC_CALLBACK_1(Music::MenuVolume0, this));

//set volume1 button
    auto volume1Item = MenuItemImage::create(
        "Volume1Normal.png",
        "Volume1Selected.png",
        CC_CALLBACK_1(Music::MenuVolume1, this));

//set volume2 button
    auto volume2Item = MenuItemImage::create(
        "Volume2Normal.png",
        "Volume2Selected.png",
        CC_CALLBACK_1(Music::MenuVolume2, this));

//set volume3 button
    auto volume3Item = MenuItemImage::create(
        "Volume3Normal.png",
        "Volume3Selected.png",
        CC_CALLBACK_1(Music::MenuVolume3, this));

    //set menu
    auto menu = Menu::create(bgmItem,volume0Item, volume1Item, volume2Item,volume3Item, NULL);
    menu->alignItemsVerticallyWithPadding(visibleSize.height / 16);
    this->addChild(menu, 1);


//set back button
    auto back_item = MenuItemImage::create(
        "BackNormal.png",
        "BackSelected.png",
        CC_CALLBACK_1(Music::MenuBack, this));


    //唯一幸存下来的检查空指针的地方，方便以后写成函数修改代码

    //if (backItem == NULL ||
    //    backItem->getContentSize().width <= 0 ||
    //    backItem->getContentSize().height <= 0){
    //    problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
    //}

    back_item->setPosition(Vec2(origin.x + visibleSize.width / 8,
        origin.y + visibleSize.height / 1.2));

    auto menu2 = Menu::create(back_item, NULL);
    menu2->setPosition(Vec2::ZERO);
    this->addChild(menu2, 1);

    return true;
}
void Music::MenuBgm(Ref* pSender) {
    SimpleAudioEngine::sharedEngine()->rewindBackgroundMusic();
}

void Music::MenuVolume0(Ref* pSender) {
    SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
}

void Music::MenuVolume1(Ref* pSender) {
    //SimpleAudioEngine::sharedEngine()->rewindBackgroundMusic();
    SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.1);
}

void Music::MenuVolume2(Ref* pSender) {
    //SimpleAudioEngine::sharedEngine()->rewindBackgroundMusic();
    SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.5);
}

void Music::MenuVolume3(Ref* pSender) {
    //SimpleAudioEngine::sharedEngine()->rewindBackgroundMusic();
    SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(1);
}


void Music::MenuBack(Ref* pSender) {
    Director::getInstance()->replaceScene(MainMenu::createScene());
}
