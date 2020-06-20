#ifndef  __EMOJI_SORITE_H__
#define  __EMOJI_SORITE_H__

#include "cocos2d.h"
#include "Const.h"

USING_NS_CC;

class EmojiSprite : public Sprite
{
public:
    static EmojiSprite* create(int row, int col);

    void SetSpriteSpecies(SpriteSpecies specie);
    SpriteSpecies GetSpriteSpecies() { return species_; };

    EmojiSprite();

    CC_SYNTHESIZE(int, row_, Row);
    CC_SYNTHESIZE(int, col_, Col);
    CC_SYNTHESIZE(int, img_index_, ImgIndex);
    CC_SYNTHESIZE(bool,is_need_remove_, IsNeedRemove);
    CC_SYNTHESIZE(bool, ignore_check_, IgnoreCheck);

private:
    SpriteSpecies species_;
};

#endif