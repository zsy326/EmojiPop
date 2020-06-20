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
	labelScore->setPosition(Point(GAME_SCREEN_WIDTH / 2, GAME_SCREEN_HEIGHT / 1.2));
	labelScore->setTag(13);
	this->addChild(labelScore,2);


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
	auto scene = Game::CreateScene();
	//set GameLevel
	auto layer = Game::create();
	layer->SetTargetScore(10);
	layer->SetTime(10);
	scene->addChild(layer);

	TransitionScene* reScene = TransitionSplitRows::create(1.0f, scene);
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
	auto scene = Game::CreateScene();
	//set GameLevel
	auto layer = Game::create();
	layer->SetTargetScore(1000);
	scene->addChild(layer);
	layer->SetTime(10);

	TransitionScene* reScene = TransitionSplitRows::create(1.0f, scene);
	CCDirector::sharedDirector()->replaceScene(reScene);
}


void GameEnd::ExitGame(Ref* pSender)
{
	Director::getInstance()->end();
}

void GameEnd::setScore(int sc) {

	auto labelScore = (Label*)this->getChildByTag(13);
	labelScore->setString(StringUtils::format(" %d ", sc));

	if (userDefault->getIntegerForKey("Int") < sc) {

		auto newRecord = Sprite::create("Good.png");
		newRecord->setPosition(Point(GAME_SCREEN_WIDTH / 3.05, GAME_SCREEN_HEIGHT / 1.22));
		newRecord->setScale(10.0f);// start size
		newRecord->runAction(ScaleTo::create(1.2f, 1.0));

		this->addChild(newRecord);

		//	// ÒôÐ§
		//	if (UserDefault::getInstance()->getBoolForKey(SOUND_KEY)) {
		//		SimpleAudioEngine::getInstance()->playEffect("music_win.wav", false);
		//	}
		//	userDefault->setIntegerForKey("Int", sc);
		//}
		//else
		//{
		//	// ÒôÀÖ
		//	if (UserDefault::getInstance()->getBoolForKey(SOUND_KEY)) {
		//		SimpleAudioEngine::getInstance()->playEffect("music_fail.mp3", false);
		//	}
		//}
	}
}
