#ifndef  __CONST_H__
#define  __CONST_H__


#define BOARD_SIZE 8 // the number of sprites at each column/row
#define SPRITE_SIZE 53 // the size of each sprite
#define EMOJI_GAP 12 // the gap between two sprites

#define GAME_SCREEN_WIDTH 600 // the width of screen
#define GAME_SCREEN_HEIGHT 800 //the height of screen

#define userDefault CCUserDefault::sharedUserDefault()


enum SpriteSpecies
{
	NORMAL,
	PLUS_ROW,
	PLUS_COL,
	PLUS_BLOCK,
	PLUS_SAME
};

#endif
