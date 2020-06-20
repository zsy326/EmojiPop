#ifndef __GAME_END_SCENE_H__
#define __GAME_END_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;

class GameEnd : public Layer
{
public:

	static Scene* createScene();
	CREATE_FUNC(GameEnd);
	virtual bool init();

	void setScore(int);
	void changeToPass();

	void ExitGame(Ref* pSender);
	void GoToThisLevel(Ref* pSender);
	void GoToNextLevel (Ref* pSender);
	void GoToMainMenuScene(Ref* pSender);

};

#endif
