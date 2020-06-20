#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "MainMenuScene.h"

USING_NS_CC;

Scene* HelloWorld::CreateScene(){
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

    auto visible_size = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto welcome_item = MenuItemImage::create(
        "WelcomeNormal.png",
        "WelcomeSelected.png",
        CC_CALLBACK_1(HelloWorld::MenuCloseCallback, this));

    auto menu = Menu::create(welcome_item,NULL);
    menu->alignItemsVerticallyWithPadding(visible_size.height / 2);
    this->addChild(menu, 1);

    auto label = Label::createWithTTF("Welcome to EmojiPop", "fonts/Marker Felt.ttf", 24);
    if (label == NULL){
        problemLoading("'fonts/Marker Felt.ttf'");
    }
    else{
        label->setPosition(Vec2(origin.x + visible_size.width / 2,
            origin.y + visible_size.height - label->getContentSize().height));
        this->addChild(label, 1);
    }
    return true;
}

void HelloWorld::MenuCloseCallback(Ref* pSender){
    Director::getInstance()->replaceScene(MainMenu::createScene());
}
