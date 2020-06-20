#include "GameEndScene.h"
#include "GameScene.h"
#include "MainMenuScene.h"
#include "Const.h"

Scene* GameEnd::createScene()
{
	auto scene = Scene::create();
	auto layer = GameEnd::create();
	scene->addChild(layer);
	return scene;
}

bool GameEnd::init()
{
	if (!Layer::init()) {
		return false;
	}

	TTFConfig config("fonts/Marker Felt.ttf", 48);

	auto sprite = Sprite::create("GameOver.png");
	sprite->setPosition(Point(GAME_SCREEN_WIDTH / 2, GAME_SCREEN_HEIGHT / 2));
	this->addChild(sprite,0);

	auto backItem = MenuItemImage::create(
		"BackNormal.png",
		"BackSelected.png",
		CC_CALLBACK_1(GameEnd::GoToMainMenuScene, this));

	auto restartItem = MenuItemImage::create(
		"RestartNormal.png",
		"RestartSelected.png",
		CC_CALLBACK_1(GameEnd::GoToThisLevel, this));


	auto exitItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(GameEnd::ExitGame, this));
	
		backItem->setPosition(Vec2(GAME_SCREEN_WIDTH / 4, GAME_SCREEN_HEIGHT / 1.4));
		restartItem->setPosition(Vec2(2 * (GAME_SCREEN_WIDTH / 4), GAME_SCREEN_HEIGHT / 1.4));
		exitItem->setPosition(Vec2(3 * (GAME_SCREEN_WIDTH / 4), GAME_SCREEN_HEIGHT / 1.4));

		auto menu_2 = Menu::create(backItem, exitItem, NULL);
		menu_2->setPosition(Vec2::ZERO);
		this->addChild(menu_2, 2);

		auto menu_1 = Menu::create(restartItem, NULL);
		menu_1->setPosition(Vec2::ZERO);
		this->addChild(menu_1, 1);


	auto labelScore = Label::createWithTTF(config, "  0  ");
	labelScore->setPosition(Point(GAME_SCREEN_WIDTH / 2, GAME_SCREEN_HEIGHT / 1.05));
	labelScore->setTag(13);
	this->addChild(labelScore,2);

	auto labelTime = Label::createWithTTF(config, "  0  ");
	labelTime->setPosition(Point(GAME_SCREEN_WIDTH / 2, GAME_SCREEN_HEIGHT / 1.2));
	labelTime->setTag(11);
	this->addChild(labelTime, 3);


	return true;
}

void GameEnd::changeToPass() {
	auto sprite = Sprite::create("GamePass.png");
	sprite->setPosition(Point(GAME_SCREEN_WIDTH / 2, GAME_SCREEN_HEIGHT / 2));
	this->addChild(sprite,1);

	auto nextLevelItem = MenuItemImage::create(
		"NextLevelNormal.png",
		"NextLvelSelected.png",
		CC_CALLBACK_1(GameEnd::GoToNextLevel, this));

	nextLevelItem->setPosition(Vec2(2 * (GAME_SCREEN_WIDTH / 4), GAME_SCREEN_HEIGHT / 1.4));
	auto menu_2 = Menu::create(nextLevelItem, NULL);
	menu_2->setPosition(Vec2::ZERO);
	this->addChild(menu_2, 2);
}

void GameEnd::GoToThisLevel(Ref* pSender)
{
	auto scene = Scene::create();
	////set GameLevel
	auto layer = Game::create();
	layer->SetTargetScore(layer->level_score_);
	layer->SetStep(layer->level_step_);
	scene->addChild(layer);

	TransitionScene* reScene = TransitionSlideInR::create(1.0f, scene);
	Director::sharedDirector()->replaceScene(reScene);
}

void GameEnd::GoToMainMenuScene(Ref* pSender)
{
	auto scene = MainMenu::createScene();
	TransitionScene* reScene = TransitionSplitRows::create(1.0f, scene);
	Director::sharedDirector()->replaceScene(reScene);
}

void GameEnd::GoToNextLevel(Ref* pSender)
{

	auto scene = Scene::create();
	////set GameLevel
	auto layer = Game::create();

	(layer->level_step_ )*= 2;
	(layer->level_score_)*= 3;

	layer->SetTargetScore(layer->level_score_);
	layer->SetStep(layer->level_step_);
	scene->addChild(layer);

	TransitionScene* reScene = TransitionSlideInR::create(1.0f, scene);
	Director::sharedDirector()->replaceScene(reScene);
	
}

void GameEnd::ExitGame(Ref* pSender)
{
	Director::getInstance()->end();
}

void GameEnd::setScore(int score) {

	auto labelScore = (Label*)this->getChildByTag(13);
	labelScore->setString(StringUtils::format("Your score is: %d ", score));


	if (userDefault->getIntegerForKey("HScore") < score) {

		userDefault->setIntegerForKey("HScore", score);
	}

		//	// 音效
		//	if (UserDefault::getInstance()->getBoolForKey(SOUND_KEY)) {
		//		SimpleAudioEngine::getInstance()->playEffect("music_win.wav", false);
		//	}
		//	userDefault->setIntegerForKey("Int", sc);
		//}
		//else
		//{
		//	// 音乐
		//	if (UserDefault::getInstance()->getBoolForKey(SOUND_KEY)) {
		//		SimpleAudioEngine::getInstance()->playEffect("music_fail.mp3", false);
		//	}
		//}
}

void GameEnd::setTime(int time){

	auto labelTime = (Label*)this->getChildByTag(11);
	labelTime->setString(StringUtils::format("The time you used is: %d ", time));

	if (userDefault->getIntegerForKey("STime") > time) {

		userDefault->setIntegerForKey("STime", time);
	}
}
