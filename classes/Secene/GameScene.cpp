#include "GameScene.h"
#include "SimpleAudioEngine.h"
#include "MainMenuScene.h"
#include "EmojiSprite.h"
#include "GameEndScene.h"

#include "Const.h"

USING_NS_CC;
using namespace CocosDenshion;

//init some member variable in constructed function
Game::Game()
    : spriteSheet(NULL)
    , isFillSprite(false)
    , isAction(true)
    , is_touch_enable(true)
    , start_sprite(NULL)
    , end_sprite(NULL)
    , score_(0)
    , timing_flag(1)
    , step_(0)
{
}

Scene* Game::CreateScene()
{
    return Game::create();
}

static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}


bool Game::init()
{
    if (!Scene::init()) { 
        return false; 
    }
    // loading plist and png
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("sprites.plist");
    spriteSheet = SpriteBatchNode::create("sprites.png");
    addChild(spriteSheet);

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // init the point of each spriteMatrix
    mapLBX = origin.x+(GAME_SCREEN_WIDTH - SPRITE_SIZE * BOARD_SIZE- (BOARD_SIZE - 1) * EMOJI_GAP)/2;
    mapLBY = origin.y+(GAME_SCREEN_HEIGHT - SPRITE_SIZE * BOARD_SIZE - (BOARD_SIZE - 1) * EMOJI_GAP)/2;

    SetTime(999);
    SetStep(level_step_);
    SetTargetScore(level_score_);

  //set back button
    auto backItem = MenuItemImage::create(
        "BackNormal.png",
        "BackSelected.png",
        CC_CALLBACK_1(Game::menuBack, this));

    if (backItem == NULL) {
        problemLoading("'BackNormal.png' and ' BackSelected.png'");
    }

        backItem->setPosition(Vec2(origin.x + visibleSize.width / 8,
            origin.y + visibleSize.height / 1.1));

    auto menuBack = Menu::create(backItem, NULL);
    menuBack->setPosition(Vec2::ZERO);
    this->addChild(menuBack, 1);

//set stop button
    auto stopItem = MenuItemImage::create(
        "StopNormal.png",
        "StopSelected.png",
        CC_CALLBACK_1(Game::menuStop, this));

    if (stopItem == NULL) {
        problemLoading("'StopNormal.png' and ' StopSelected.png'");
    }
    stopItem->setPosition(Vec2(origin.x + visibleSize.width / 1.3,
        origin.y + visibleSize.height / 1.1));

    auto menuStop = Menu::create(stopItem, NULL);
    menuStop->setPosition(Vec2::ZERO);
    this->addChild(menuStop, 1);

//set continue button
    auto continueItem = MenuItemImage::create(
        "ContinueNormal.png",
        "ContinueSelected.png",
        CC_CALLBACK_1(Game::menuContinue, this));

    if (continueItem == NULL) {
        problemLoading("'ContinueNormal.png' and ' ContinueSelected.png'");
    }

    continueItem->setPosition(Vec2(origin.x + visibleSize.width / 1.1,
        origin.y + visibleSize.height / 1.1));

    auto menuContinue = Menu::create(continueItem, NULL);
    menuContinue->setPosition(Vec2::ZERO);
    this->addChild(menuContinue, 1);

    // set timer
    TTFConfig config("fonts/Marker Felt.ttf", 30);

    auto label_score = Label::createWithTTF(config, StringUtils::format("Score: %d ", score_));
    label_score->setPosition(Vec2(origin.x + visibleSize.width / 2,
        origin.y + visibleSize.height /1.15 ));
    label_score->setTag(10);
    this->addChild(label_score);

    auto label_time = Label::createWithTTF(config, StringUtils::format("Left Time: %d ", time_));
    label_time->setPosition(Vec2(origin.x + visibleSize.width / 1.2,
        origin.y + visibleSize.height / 15));
    label_time->setTag(11);
    this->addChild(label_time);

    auto label_step = Label::createWithTTF(config, StringUtils::format("Left Step: %d ", step_));
    label_step->setPosition(Vec2(origin.x + visibleSize.width / 1.2,
        origin.y + visibleSize.height / 9));
    label_step->setTag(12);
    this->addChild(label_step);

    auto label_target_score = Label::createWithTTF(config, StringUtils::format("Target Score: %d ", target_score_));
    label_target_score->setPosition(Vec2(origin.x + visibleSize.width / 2,
        origin.y + visibleSize.height / 1.05));
    label_target_score->setTag(13);
    this->addChild(label_target_score);

    // set up listener event 
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = CC_CALLBACK_2(Game::TouchBegin, this);
    touchListener->onTouchMoved = CC_CALLBACK_2(Game::TouchMove, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);


    if (!userDefault->getIntegerForKey("Int")) {
        userDefault->setIntegerForKey("Int", 0);
    }

    //auto labelHScore = Label::createWithTTF(config, "Highest: 0");
    //labelHScore->setPosition(Vec2(GAME_SCREEN_WIDTH - labelHScore->getContentSize().width, GAME_SCREEN_HEIGHT - labelHScore->getContentSize().height));
    //labelHScore->setString(StringUtils::format("Highest: %d ", userDefault->getIntegerForKey("Int")));
    //this->addChild(labelHScore);
    BoardInit();
    scheduleUpdate();
    schedule(schedule_selector(Game::Timing), 1.0f);
    return true;
}

void Game::menuBack(Ref* pSender) {
    Director::getInstance()->replaceScene(MainMenu::createScene());
}

void Game::menuStop(Ref* pSender) {

    //stop music
    SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
   
    //stop timing
    timing_flag = 0;

    //stop touching
    is_touch_enable = false;
}

void Game::menuContinue(Ref* pSender) {

    //continue music
    SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();

    //continue timing
    timing_flag = 1;

    //continue touching
    is_touch_enable = true;
}

//init the board, put sprites on the board
bool Game::BoardInit(){
    for (int row = 0; row < BOARD_SIZE; row++) {
        for (int col = 0; col < BOARD_SIZE; col++) {
            createSprite(row, col,false);
        }
    }
    return true;
}

void Game::createSprite( int row , int col , bool isSnow)	{
	
	EmojiSprite* emoji = EmojiSprite::create(row, col, isSnow);

  //calculate the final position of the sprite
    const Point endpoint(mapLBX + (SPRITE_SIZE + EMOJI_GAP) * col + SPRITE_SIZE / 2,
        mapLBY + (SPRITE_SIZE + EMOJI_GAP) * row + SPRITE_SIZE / 2);
    const Point endPosition(endpoint);

  //calculate the begin position
  // x is as same as endPosition's, y is (GAME_SCREEN_HEIGHT / 2) larger than endPosition's 
    const Point startPosition = Point(endPosition.x, endPosition.y + GAME_SCREEN_HEIGHT / 2);
    emoji->setPosition(startPosition);

  //set speed of drop
   float speed = startPosition.y / ( GAME_SCREEN_HEIGHT*2);

   //run
    emoji->runAction(MoveTo::create(speed, endPosition));
    
    spriteSheet->addChild(emoji);

	//put sprite into map
    map[row][col] = emoji;
}

// before each level
void Game::update(float t){
    
    Label* label_score = (Label*)this->getChildByTag(10);
    label_score->setString(StringUtils::format("Score: %d ", score_));

    Label* label_step = (Label*)this->getChildByTag(12);
    label_step->setString(StringUtils::format("Left Step: %d ", step_));

    Label* label_target_step = (Label*)this->getChildByTag(13);
    label_target_step->setString(StringUtils::format("Target Score: %d ", target_score_));

    if (isAction) {
        isAction = false;
      
        // check if there are sprites could be removed
        for (int r = 0; r < BOARD_SIZE; ++r) {
            for (int c = 0; c < BOARD_SIZE; ++c) {
                EmojiSprite* current_sprite = map[r][c];
                if (current_sprite && current_sprite->getNumberOfRunningActions() > 0) {
                    isAction = true;
                    break;
                }
            }
        }
    }

    // if not    
    if (!isAction) {
        // check if there are blanks
        if (isFillSprite) {
            fillSprite();
            isFillSprite = false;
        }
        else{
            checkAndRemoveSprite();
        }
    }
}

void Game::checkAndRemoveSprite()
{
    EmojiSprite* current_sprite;

    for (int r = 0; r < BOARD_SIZE; ++r) {
        for (int c = 0; c < BOARD_SIZE; ++c) {
            current_sprite = map[r][c];
            if (!current_sprite) {
                continue;
            }
            if (current_sprite->getImgIndex() == 5){//if this sprite is snow there is no need to check it
                current_sprite->setIgnoreCheck(true);
            }
            else {
                current_sprite->setIgnoreCheck(false);
            }
        }
    }

    // check if there are sprites could be removed
    for (int r = 0; r < BOARD_SIZE; ++r) {
        for (int c = 0; c < BOARD_SIZE; ++c) {
            current_sprite = map[r][c];


            if (!current_sprite) {
                continue;  //it is a blank, no need to check
            }

            if (current_sprite->getIsNeedRemove()) {
                continue; //it will be removed, no need to check
            }
            if (current_sprite->getIgnoreCheck()) {
                continue;//it is a new plusSprite, no need to check
            }

            //build a list to contain the sprites around current_sprite in col
            std::list<  EmojiSprite*> colChainList;
            getColChain(current_sprite, colChainList);

            //build a list to contain the sprites around current_sprite in row
            std::list<  EmojiSprite*> rowChainList;
            getRowChain(current_sprite, rowChainList);

            //if there are <3 sprites in row and col, check next sprite
            if (colChainList.size() < 3 && rowChainList.size() < 3) {
                continue;
            }

            //if there are sprites could be removed
            else if (colChainList.size() >= 3 || rowChainList.size() >= 3) {

                std::list<EmojiSprite*>::iterator itList;
                bool isSetedIgnoreCheck = false;



                //only the rowSprites could be removed
                if (rowChainList.size() >= 3 && colChainList.size() < 3) {
                    score_ += pow(3.0, (rowChainList.size() - 2));

                    for (itList = rowChainList.begin(); itList != rowChainList.end(); itList++) {
                        current_sprite = (EmojiSprite*)*itList;
                        if (!current_sprite) { continue; }

                        //if there are 3+ sprites could be removed
                        if (rowChainList.size() > 3) {

                            if (current_sprite == start_sprite || current_sprite == end_sprite) {
                   
                                ChangeToPlus(current_sprite);
                                isSetedIgnoreCheck = true;
                                current_sprite->setIgnoreCheck(true);
                                current_sprite->setIsNeedRemove(false); 
                                continue;
                            }
                        }
                        // mark the aprite being to removed
                        markRemove(current_sprite);

                        SpriteSpecies species = current_sprite->GetSpriteSpecies();
                            if (species == PLUS_ROW || species == PLUS_COL || species == PLUS_BLOCK||species==PLUS_SAME) {
                                markNeighborSprites(current_sprite);
                            }
                    }
                }


                //only the colSprites could be removed
                else if (colChainList.size() >= 3 && rowChainList.size() < 3) {
                    score_ += pow(3.0, (colChainList.size() - 2));

                    for (itList = colChainList.begin(); itList != colChainList.end(); itList++) {
                        current_sprite = (EmojiSprite*)*itList;
                        if (!current_sprite) { continue; }

                        //if there are 3+ sprites could be removed
                        if (colChainList.size() > 3) {

                            if (current_sprite == start_sprite || current_sprite == end_sprite) {
                           
                                ChangeToPlus(current_sprite);
                                isSetedIgnoreCheck = true;
                                current_sprite->setIgnoreCheck(true);
                                current_sprite->setIsNeedRemove(false); 
                                continue;
                            }
                        }

                        // mark the aprite being to removed
                        markRemove(current_sprite); 
                        SpriteSpecies species = current_sprite->GetSpriteSpecies();
                        if (species == PLUS_ROW || species == PLUS_COL || species == PLUS_BLOCK || species == PLUS_SAME) {
                            markNeighborSprites(current_sprite);
                        }

                    }
                }

                //both the rowSprites and the colSprites could be removed
                else if (rowChainList.size() >= 3 && colChainList.size() >= 3) {

                    score_ += pow(3.0, (colChainList.size() - 2));
                    score_ += pow(3.0, (rowChainList.size() - 2));

                    for (itList = rowChainList.begin(); itList != rowChainList.end(); itList++) {
                        current_sprite = (EmojiSprite*)*itList;
                        if (!current_sprite) { continue; }

                        if (current_sprite == start_sprite || current_sprite == end_sprite) {
                            
                            ChangeToPlus(current_sprite);
                            isSetedIgnoreCheck = true;
                            current_sprite->setIgnoreCheck(true);
                            current_sprite->setIsNeedRemove(false);
                            continue;
                        }
                        // mark the aprite being to removed
                        markRemove(current_sprite);
                        SpriteSpecies species = current_sprite->GetSpriteSpecies();
                        if (species == PLUS_ROW || species == PLUS_COL || species == PLUS_BLOCK || species == PLUS_SAME) {
                            markNeighborSprites(current_sprite);
                        }

                    }
                }

                //if there are 4+ sprites in fallen sprites
                if (!isSetedIgnoreCheck&& (rowChainList.size() >3||colChainList.size() >3)) {
                    current_sprite->setIgnoreCheck(true);
                    current_sprite->setIsNeedRemove(false);
                    ChangeToPlus(current_sprite);
                }
            }
        }
        
    }
    //remove the sprite marked
    removeSprite();
}

void Game::markRemove(EmojiSprite* sprite) {

    // if had been mark to remove, no need to remark
    if (sprite->getIsNeedRemove()) { return;  }

    // if not,mark it
    sprite->setIsNeedRemove(true);
}

void Game::markNeighborSprites(EmojiSprite* current_sprite) {
   
    SpriteSpecies species = current_sprite->GetSpriteSpecies();
    int row = current_sprite->getRow();
    int col = current_sprite->getCol();

    if (species ==PLUS_ROW) {
        for (int c = 0; c < BOARD_SIZE; c++) {
            EmojiSprite* neighbor_sprite = map[row][c];
            markRemove(neighbor_sprite);
            
        }
        score_ += 30;
    }
    else if (species == PLUS_COL) {
        for (int r = 0; r < BOARD_SIZE; r++) {
            EmojiSprite* neighbor_sprite = map[r][col];
            markRemove(neighbor_sprite);
            
        }
        score_ += 30;
    }
    else if (species == PLUS_BLOCK) {
        for (int r = row - 1; r <= row + 1; r++) {
            for (int c = col - 1; c <= col + 1; c++) {
                if (r >= 0 && c >= 0 && r <= 7 && c <= 7) {
                    EmojiSprite* neighbor_sprite = map[r][c];
                    markRemove(neighbor_sprite);
                }
            }
        }
        score_ += 30;
    }
    else if (species == PLUS_SAME) {
        for (int r = 0; r <BOARD_SIZE; r++) {
            for (int c = 0; c <BOARD_SIZE; c++) {
                    EmojiSprite* neighbor_sprite = map[r][c];
                    if (neighbor_sprite->getImgIndex() == current_sprite->getImgIndex()) {
                    score_ += 3;
                    markRemove(neighbor_sprite);
                    }
            }
        }
    }
}

void Game::ChangeToPlus(EmojiSprite* current_sprite) {
    unsigned seed = time(nullptr);
    srand(seed);
    int species_num = rand() % 4 + 1;
    switch (species_num) {
    case 1:
        current_sprite->SetSpriteSpecies(PLUS_ROW);
        break;
    case 2:
        current_sprite->SetSpriteSpecies(PLUS_COL);
        break;
    case 3:
        current_sprite->SetSpriteSpecies(PLUS_BLOCK);
        break;
    case 4:
        current_sprite->SetSpriteSpecies(PLUS_SAME);
        break;
    }
    

}

void Game::removeSprite(){
    isAction = true;

    for (int r = 0; r < BOARD_SIZE; ++r) {
        for (int c = 0; c < BOARD_SIZE; ++c) {
            EmojiSprite* current_sprite = map[r][c];
            if (!current_sprite) {  continue;  }

            //if the sprite will be removed, the blank will be filled
            if (current_sprite->getIsNeedRemove()) {
                isFillSprite = true;
                if (current_sprite->getImgIndex() != 5) {
                    //current_sprite->getImgIndex() == 5 means it is snow, cannot be removed
                    explodeSprite(current_sprite);
                }
            }
        }
    }
}

void Game::explodeSprite(EmojiSprite* current_sprite) {

    //blink and  shrink
    current_sprite->runAction(Sequence::create(
        Blink::create(0.3f, 5),
        ScaleTo::create(0.3f, 0.0),
        CallFuncN::create(CC_CALLBACK_1(Game::actionEndCallback, this)),
        NULL));
}

// to removed sprite, free its map position, remove its node 
void Game::actionEndCallback(Node* node) {

    EmojiSprite* current_sprite = (EmojiSprite*)node;

    map[current_sprite->getRow()][current_sprite->getCol()] = NULL;

    current_sprite->removeFromParent();
}

// check by col
void Game::getColChain(EmojiSprite* current_sprite, std::list< EmojiSprite*>& chainList) {
    //push current sprite
    chainList.push_back(current_sprite);

    //check the left of the current_sprite
    int neighborCol = current_sprite-> getCol() - 1;
    while (neighborCol >= 0) {
        EmojiSprite* neighborSprite = map[current_sprite->getRow()][neighborCol];
        if (neighborSprite
            && (neighborSprite->getImgIndex() == current_sprite->getImgIndex())
            && !neighborSprite->getIsNeedRemove()
            &&neighborSprite->getImgIndex()!=5) {
            chainList.push_back(neighborSprite);
            neighborCol--;
        }
        else { break; }
    }

    // check the right of the current_sprite
    neighborCol = current_sprite->getCol() + 1;
    while (neighborCol < BOARD_SIZE) {
        EmojiSprite* neighborSprite = map[current_sprite->getRow()][neighborCol];
        if (neighborSprite
            && (neighborSprite->getImgIndex() == current_sprite->getImgIndex())
            && !neighborSprite->getIsNeedRemove()
            && neighborSprite->getImgIndex() != 5) {
            chainList.push_back(neighborSprite);
            neighborCol++;
        }
        else {  break; }
    }
}

// check by row 
//(since it is similar to "check by col", so there is no need to note)
void Game::getRowChain(EmojiSprite* current_sprite, std::list< EmojiSprite*>& chainList) {
    
    chainList.push_back(current_sprite);

    int neighborRow = current_sprite->getRow() - 1;
    while (neighborRow >= 0) {
        EmojiSprite* neighborSprite = map[neighborRow][current_sprite->getCol()];
        if (neighborSprite
            && (neighborSprite->getImgIndex() == current_sprite->getImgIndex())
            && !neighborSprite->getIsNeedRemove()
            && neighborSprite->getImgIndex() != 5) {
            chainList.push_back(neighborSprite);
            neighborRow--;
        }
        else {  break; }
    }
    
    neighborRow = current_sprite->getRow() + 1;
    while (neighborRow < BOARD_SIZE) {
        EmojiSprite* neighborSprite = map[neighborRow][current_sprite->getCol()];
        if (neighborSprite
            && (neighborSprite->getImgIndex() == current_sprite->getImgIndex())
            && !neighborSprite->getIsNeedRemove()
            && neighborSprite->getImgIndex() != 5) {
            chainList.push_back(neighborSprite);
            neighborRow++;
        }
        else {  break; }
    }
}

void Game::fillSprite() {

    isAction = true;
    int* numEmptyInfo = (int*)malloc(sizeof(int) * BOARD_SIZE);
    memset((void*)numEmptyInfo, 0, sizeof(int) * BOARD_SIZE);

   //drop the upper sprites
    EmojiSprite* current_sprite = NULL;
    for (int c = 0; c < BOARD_SIZE; c++) {
        int numOfRemoved = 0;
        for (int r = 0; r < BOARD_SIZE; r++) {
            current_sprite = map[r][c];

            if (current_sprite == NULL) { //if this is a blank
                numOfRemoved++;
            }
            else {  //this is a sprite
                if (numOfRemoved > 0) { // there are blanks above this sprites

                     //a sprite above current_sprite and stay closest
                    int newRow = r - numOfRemoved;
                    map[newRow][c] = current_sprite;
                    map[r][c] = NULL;

                    //drop this sprite
                    Point endPoint(mapLBX + (SPRITE_SIZE + EMOJI_GAP) * c + SPRITE_SIZE / 2,
                        mapLBY + (SPRITE_SIZE + EMOJI_GAP) * newRow + SPRITE_SIZE / 2);
                    Point startPosition = current_sprite->getPosition();
                    Point endPosition = endPoint;
                    float speed = (startPosition.y - endPosition.y) / (GAME_SCREEN_HEIGHT*3);
                    
                    current_sprite->stopAllActions();
                    current_sprite->runAction(MoveTo::create(speed, endPosition));
                    current_sprite->setRow(newRow);

                }
            }
        }
        // record the num of removed sprites
       numEmptyInfo[c] = numOfRemoved;
    }

    // create new sprites and drop them
    for (int c = 0; c < BOARD_SIZE; ++c) {
        for (int r = BOARD_SIZE - numEmptyInfo[c]; r < BOARD_SIZE; ++r) {
            if (!step_ % 5 == 0) {
                createSprite(r, c, false);
            }
            else
            {
                createSprite(r, c, true);
            }
        }
    }

    free(numEmptyInfo);
}

bool Game::TouchBegin(Touch* touch, Event* unused) {
    start_sprite = NULL;
    end_sprite = NULL;

    is_touch_enable = true;
    // the area of click is a sprite
    if (is_touch_enable) {
        auto location = touch->getLocation();
        start_sprite = spriteOfPoint(&location);
    }
    return is_touch_enable;
}

void Game::TouchMove(Touch* touch, Event* unused) {
    
    //if the area clicked is a blank 
    if (!start_sprite || !is_touch_enable) {
        return;
    }
    int row = start_sprite->getRow();
    int col = start_sprite->getCol();

    //get the position of endPoint
    auto location = touch->getLocation();
    auto half_sprite_size = SPRITE_SIZE / 2;

    auto  upRect = Rect(start_sprite->getPositionX() - half_sprite_size,
        start_sprite->getPositionY() + half_sprite_size,
        SPRITE_SIZE,
        SPRITE_SIZE);

    // the direction of moving


    if (upRect.containsPoint(location)) {
        ++row;
        if (row < BOARD_SIZE) {
            end_sprite = map[row][col];
        }
        SwapSprite();
       
        return;
    }
    auto  downRect = Rect(start_sprite->getPositionX() - half_sprite_size,
        start_sprite->getPositionY() - (half_sprite_size * 3),
        SPRITE_SIZE,
        SPRITE_SIZE);

    if (downRect.containsPoint(location)) {
        --row;
        if (row >= 0) {
            end_sprite = map[row][col];
        }
        SwapSprite();
       
        return;
    }

    auto  leftRect = Rect(start_sprite->getPositionX() - (half_sprite_size * 3),
        start_sprite->getPositionY() - half_sprite_size,
        SPRITE_SIZE,
        SPRITE_SIZE);

    if (leftRect.containsPoint(location)) {
        --col;
        if (col >= 0) {
            end_sprite = map[row][col];
        }
        SwapSprite();
       
        return;
    }

    auto  rightRect = Rect(start_sprite->getPositionX() + half_sprite_size,
        start_sprite->getPositionY() - half_sprite_size,
        SPRITE_SIZE,
        SPRITE_SIZE);

    if (rightRect.containsPoint(location)) {
        ++col;
        if (col < BOARD_SIZE) {
            end_sprite = map[row][col];
        }
        SwapSprite();
        
        return;
    }
}

// return the point of sprite which was touched
EmojiSprite* Game::spriteOfPoint(Point* point)
{
    EmojiSprite* touched_sprite = nullptr;
    Rect rectangle = Rect(0, 0, 0, 0);
    Size size;
    size.height = SPRITE_SIZE;
    size.width = SPRITE_SIZE;

    for (int row = 0; row < BOARD_SIZE; row++) {
        for (int col = 0; col < BOARD_SIZE; col++) {
            touched_sprite = map[row][col];
            if (touched_sprite) {
                rectangle.origin.x = touched_sprite->getPositionX() - (SPRITE_SIZE / 2);
                rectangle.origin.y = touched_sprite->getPositionY() - (SPRITE_SIZE / 2);

                rectangle.size = size;
                if (rectangle.containsPoint(*point)) {
                    return touched_sprite;
                }
            }
        }
    }

    return nullptr;
}

void Game::SwapSprite() {
    // while moving, no clicking
    isAction = true;
    is_touch_enable = false;

    // both the start_sprite* and end_sprite* shouldn't be NULL
    if (!start_sprite || !end_sprite) {
        return;
    }

    Point position_start = start_sprite->getPosition();
    Point position_end = end_sprite->getPosition();

    // change these two sprites in the map
    map[start_sprite->getRow()][start_sprite->getCol()] = end_sprite;
    map[end_sprite->getRow()][end_sprite->getCol()] = start_sprite;
    SwapRowAndCol(start_sprite, end_sprite);

    // 检查是否能消除
    std::list<EmojiSprite*> colChainListOfFirst;
    getColChain(start_sprite, colChainListOfFirst);

    std::list<EmojiSprite*> colChainListOfSecond;
    getColChain(end_sprite, colChainListOfSecond);

    std::list<EmojiSprite*> rowChainListOfFirst;
    getRowChain(start_sprite, rowChainListOfFirst);

    std::list<EmojiSprite*> rowChainListOfSecond;
    getRowChain(end_sprite, rowChainListOfSecond);

    // if they can swap ,then swap
    if (colChainListOfFirst.size() >= 3|| rowChainListOfFirst.size() >= 3
        || colChainListOfSecond.size() >= 3|| rowChainListOfSecond.size() >= 3) {

        //change the position
        start_sprite->runAction(MoveTo::create(0.2, position_end));
        end_sprite->runAction(MoveTo::create(0.2, position_start));

        step_--;
        if (step_ == 0) {
            DropEndLabel();
        }

        return;
    }
    else {
        //if cannot be removed, these two sprits should be swap twice
        map[start_sprite->getRow()][start_sprite->getCol()] = end_sprite;
        map[end_sprite->getRow()][end_sprite->getCol()] = start_sprite;
        
        SwapRowAndCol(start_sprite, end_sprite);

        start_sprite->runAction(Sequence::create(
            MoveTo::create(0.2, position_end),
            MoveTo::create(0.2, position_start),
            NULL));
        end_sprite->runAction(Sequence::create(
            MoveTo::create(0.2, position_start),
            MoveTo::create(0.2, position_end),
            NULL));
    }
}

void Game::SwapRowAndCol(EmojiSprite* &start_sprite,EmojiSprite* &end_sprite) {

    int temp_row = start_sprite->getRow();
    int temp_col = start_sprite->getCol();
    start_sprite->setRow(end_sprite->getRow());
    start_sprite->setCol(end_sprite->getCol());
    end_sprite->setRow(temp_row);
    end_sprite->setCol(temp_col);

}

void Game::Timing(float wait_time) {

    Label* labelTime = (Label*)this->getChildByTag(11);
    labelTime->setString(StringUtils::format("Left Time: %d ", time_));

    if (timing_flag) {//to check if stop now
        time_--;
    }
    //if there is no time left,gameover
    if (time_ == 0) {

        Label* labelTime = (Label*)this->getChildByTag(11);
        labelTime->setScale(0);
        DropEndLabel();
    }
      
    if (time_ > 0) {
        Label* labelTime = (Label*)this->getChildByTag(11);
        labelTime->setString(StringUtils::format("Left Time: %d ", time_));
    }
}

void Game::DropEndLabel() {

    isAction = false;
    Point endPosition(GAME_SCREEN_WIDTH / 2, GAME_SCREEN_HEIGHT / 2);
    Point startPosition(GAME_SCREEN_WIDTH / 2, GAME_SCREEN_HEIGHT);

    if (score_ < target_score_) {

        auto game_over = Sprite::create("LabelGameOver.png");
        game_over->setPosition(Point(GAME_SCREEN_WIDTH / 2, GAME_SCREEN_HEIGHT / 2.5));
        this->addChild(game_over);

        //drop GameOver
        game_over->setPosition(startPosition);
        game_over->runAction(MoveTo::create(1.0f, endPosition));
        scheduleOnce(schedule_selector(Game::GameEnd), 3.0f);

    }
    else {

        auto game_pass = Sprite::create("LabelGamePass.png");
        game_pass->setPosition(Point(GAME_SCREEN_WIDTH / 2, GAME_SCREEN_HEIGHT / 2.5));
        this->addChild(game_pass);

        //drop GamePass
        game_pass->setPosition(startPosition);
        game_pass->runAction(MoveTo::create(1.0f, endPosition));
        scheduleOnce(schedule_selector(Game::GameEnd), 3.0f);
    }

}

void Game::GameEnd(float dt) {

    auto scene = Scene::create();
    auto layer = GameEnd::create();
    
    // pass the score to another function
    layer->setScore(score_);
    if (score_ >= target_score_) {
        layer->changeToPass();
    }
    scene->addChild(layer);

    TransitionScene* reScene = TransitionMoveInT::create(1.0f, scene);
    Director::sharedDirector()->replaceScene(reScene);

}

