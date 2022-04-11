#pragma once

#define new new(_NORMAL_BLOCK,__FILE__,__LINE__)
#define DT DXUTGetElapsedTime()

#define WISIZE_X 1920
#define WISIZE_Y 1080

#define PLAYG_WIDTH 1600
#define PLAYG_HEIGHT 900

#define PG_LEFT 160
#define PG_TOP 90


enum class SCENE
{
	MENU = 0,
	READY,
	STAGE1,
	STAGE2,
	STAGE3,
	HOWTOPLAY,
	RANKING,
	CREADIT
};

enum class AREA
{
	NORMAL = 0,
	OUTLINE,
	CLEAR,
	ACTION,
	PAINT
};

enum KEYSTATE
{
	IDLE = 0
	, LEFT
	, RIGHT
	, UP
	, DOWN
};


enum class MOVEMODE
{
	NOMALMOVE = 0
	, ATTACKMOVE
	, RETURNMOVE
	, COMPLMOVE
};

enum class ENEMY_STATE
{
	ENEMY_IDLE
	, ENEMY_THINKING
	, ENEMY_MOVE
	, ENEMY_ATTACK
	, ENEMY_DEAD
};

enum class INGAME_STEP
{
	INIT = 0
	, READY
	, SHOWSTART
	, STAGE1
	, STAGE2
	, STAGE3
	, DIE
	, RE
	, GAMEOVER
	, STAGECLEAR
	, CLEAR
	, NONE
};

enum class ITEMSTATE
{
	START = 0
	, DROP
	, EAT
	, AFTER
	, ITEM_DIE
};

enum class RENDER_STACK
{

};