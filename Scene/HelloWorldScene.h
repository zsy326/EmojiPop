#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class HelloWorld : public cocos2d::Scene
{
public:
    static cocos2d::Scene* CreateScene();
    virtual bool init();
    void MenuCloseCallback(cocos2d::Ref* pSender);
    CREATE_FUNC(HelloWorld);
};

#endif 

