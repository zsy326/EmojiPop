#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "MainMenuScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene(){
    return HelloWorld::create();
}

static void problemLoading(const char* filename){
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool HelloWorld::init()
{
    if (!Scene::init()){ 
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto welcomeItem = MenuItemImage::create(
        "WelcomeNormal.png",
        "WelcomeSelected.png",
        CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));

    auto menu = Menu::create(welcomeItem, NULL);
    menu->alignItemsVerticallyWithPadding(visibleSize.height / 4);
    this->addChild(menu, 1);

    auto label = Label::createWithTTF("Welcome to EmojiPop", "fonts/Marker Felt.ttf", 24);
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

void HelloWorld::menuCloseCallback(Ref* pSender){
    Director::getInstance()->replaceScene(MainMenu::createScene());
}
