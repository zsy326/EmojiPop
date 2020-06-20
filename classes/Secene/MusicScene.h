#ifndef __MUSIC_SCENE_H__
#define __MUSIC_SCENE_H__

#include "cocos2d.h"

class Music : public cocos2d::Scene {
public:
    static cocos2d::Scene* CreateScene();

    virtual bool init();

    void MenuBack(cocos2d::Ref* pSender);
    void MenuBgm(Ref* pSender);
    void MenuVolume0(Ref* pSender);
    void MenuVolume1(Ref* pSender);
    void MenuVolume2(Ref* pSender);
    void MenuVolume3(Ref* pSender);

    CREATE_FUNC(Music);
};

#endif 
