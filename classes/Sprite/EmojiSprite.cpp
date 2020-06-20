#include "EmojiSprite.h"
#include "cstdlib" 
#include "ctime"
#include "Const.h"

static const char* EmojiNormal[5] = {
    "BlueNormal.png",
    "GreenNormal.png",
    "PurpleNormal.png",
    "RedNormal.png",
    "YellowNormal.png"
};


static const char* EmojiPlusRow[5] = {
    "BluePlusRow.png",
    "GreenPlusRow.png",
    "PurplePlusRow.png",
    "RedPlusRow.png",
    "YellowPlusRow.png"
};

static const char* EmojiPlusCol[5] = {
     "BluePlusCol.png",
    "GreenPlusCol.png",
    "PurplePlusCol.png",
    "RedPlusCol.png",
    "YellowPlusCol.png"
};


static const char* EmojiPlusBlock[5] = {
     "BluePlusBlock.png",
    "GreenPlusBlock.png",
    "PurplePlusBlock.png",
    "RedPlusBlock.png",
    "YellowPlusBlock.png"
};


static const char* EmojiPlusSame[5] = {
     "BluePlusSame.png",
    "GreenPlusSame.png",
    "PurplePlusSame.png",
    "RedPlusSame.png",
    "YellowPlusSame.png"
};


EmojiSprite::EmojiSprite():
    col_(0),
    row_(0),
    img_index_(0),
    is_need_remove_(false)
{
}

EmojiSprite* EmojiSprite::create(int row, int col)
{
    EmojiSprite* emoji = new EmojiSprite();
    emoji->row_ = row;
    emoji->col_ = col;

    unsigned seed = time(nullptr) * (row+25) * (col+50);
    srand(seed);
    emoji->img_index_ = rand() % 5;
    emoji->initWithSpriteFrameName(EmojiNormal[emoji->img_index_]);
    emoji->autorelease();
    return emoji;
}

void EmojiSprite::SetSpriteSpecies(SpriteSpecies species) {
    species_=species;

    SpriteFrame* frame;
    switch (species) {
    case PLUS_ROW://means it is a rowPlus sprite
        frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(EmojiPlusRow[img_index_]);
        break;

    case PLUS_COL://means it is a colPlus sprite
        frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(EmojiPlusCol[img_index_]);
        break;

    case PLUS_BLOCK://means it is a blockPlus sprite
        frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(EmojiPlusBlock[img_index_]);
        break;

    case PLUS_SAME://means it is a blockPlus sprite
        frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(EmojiPlusSame[img_index_]);
        break;

    default://means it is a normal sprite
        return;
    }
    setDisplayFrame(frame);
}
