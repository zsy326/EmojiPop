#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "EmojiSprite.h"
#include "cocos2d.h"

class Game : public cocos2d::Scene{
public:
	Game();
    static cocos2d::Scene* CreateScene();
	
    virtual bool init();
    virtual bool BoardInit();

	void SetScore(int score) { score_ = score; }
	void SetTime(int time) { time_ = time; }
	void SetStep(int step) { step_ = step; }
	void SetTargetScore(int score) { target_score_ = score; }

    void createSprite(int row,int col, bool isSnow);

    void menuBack(cocos2d::Ref* pSender);
    void menuStop(Ref* pSender);
    void menuContinue(Ref* pSender);
    
	CREATE_FUNC(Game);
	
	//the function of each function will be noted in "GameScene.cpp"
	void update(float t);
	void checkAndRemoveSprite();
	void markRemove(EmojiSprite* );
	void markNeighborSprites(EmojiSprite*);
	void ChangeToPlus(EmojiSprite*);
	void removeSprite();

	void explodeSprite(EmojiSprite* spr);

	void actionEndCallback(Node* node);
	void getColChain(EmojiSprite* spr, std::list<EmojiSprite*>& chainList);
	void getRowChain(EmojiSprite* spr, std::list<EmojiSprite*>& chainList);
	void fillSprite();

    bool TouchBegin(Touch* touch, Event* unused);
    void TouchMove(Touch* touch, Event* unused);

	void SwapSprite();
	void SwapRowAndCol(EmojiSprite* &start_sprite, EmojiSprite* &end_sprite);

	void Timing(float);
	void DropEndLabel(float);

	void GameEnd(float);
	void AwardPulsSprite(float);

	EmojiSprite* spriteOfPoint(Point* point);

	int level_step_ = 10;
	int level_score_ = 200;

private:
	SpriteBatchNode* spriteSheet;
   EmojiSprite* map[11][11];
    float mapLBX, mapLBY;

	//two sprites will be swapped
	EmojiSprite* start_sprite;
	EmojiSprite* end_sprite;

	bool isAction;
	bool isFillSprite;
	bool is_touch_enable;
	bool timing_flag;

	int time_;
	int step_;
	int score_;
	int target_score_;

	bool game_over;

};

#endif 



