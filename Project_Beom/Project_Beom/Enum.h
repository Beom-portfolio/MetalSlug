#pragma once

#pragma once

enum DIRECTION
{
	DIR_LEFT = 1,
	DIR_RIGHT = 2,
	DIR_TOP = 4,
	DIR_BOTTOM = 8,
	DIR_END
};

enum KEYSTATE
{
	STATE_DOWN,
	STATE_PUSH,
	STATE_UP,
	STATE_END
};

enum SCENESTATE
{
	SCENE_MENU,
	SCENE_SELECT,
	SCENE_TEST,
	SCENE_MAIN,
	SCENE_END
};

enum FILETYPE
{
	FILE_FILE,
	FILE_FOLDER,
	FILE_END_
};

enum SPRITEPLAY
{
	PLAY_EACH,
	PLAY_ALL,
	PLAY_END
};

enum SPRITETYPE
{
	SPRITE_ONCE,
	SPRITE_ONCE_END,
	SPRITE_REPEAT,
	SPRITE_REPEAT_END,
	SPRITE_END
};

enum OBJTYPE
{
	OBJ_BACK,
	OBJ_PLAYER,
	OBJ_MONSTER,
	OBJ_BULLET,
	OBJ_EFFECT,
	OBJ_UI,
	OBJ_END
};

enum RENDERTYPE
{
	RENDER_BACKGROUND,
	RENDER_OBJ,
	RENDER_BULLET,
	RENDER_EFFECT,
	RENDER_UI,
	RENDER_END
};

enum PLAYERWEAPON
{
	PLAYER_PISTOL,
	PLAYER_HEAVY
};

enum HEAVYTYPE
{
	HEAVY_MACHINEGUN,
	HEAVY_SHOTGUN
};