#ifndef __MUSIC_SCENE_H__
#define __MUSIC_SCENE_H__

#include "cocos2d.h"

class Music : public cocos2d::Scene {
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    void menuBack(cocos2d::Ref* pSender);
    void menuBgm(Ref* pSender);
    void menuVolume0(Ref* pSender);
    void menuVolume1(Ref* pSender);
    void menuVolume2(Ref* pSender);
    void menuVolume3(Ref* pSender);

    CREATE_FUNC(Music);
};

#endif 
