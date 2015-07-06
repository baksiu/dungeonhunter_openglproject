#ifndef CONF_H
#define CONF_H

typedef struct {
	unsigned char r;
	unsigned char g;
	unsigned char b;
} RGB;

#define SET_VEC4(v,v0,v1,v2,v3) v[0]=v0; v[1]=v1; v[2]=v2; v[3]=v3;
#define MAT4xVEC4(ret,m,v) ret[0]=m[0]*v[0]+m[1]*v[1]+m[2]*v[2]+m[3]*v[3]; ret[1]=m[4]*v[0]+m[5]*v[1]+m[6]*v[2]+m[7]*v[3]; ret[2]=m[8]*v[0]+m[9]*v[1]+m[10]*v[2]+m[11]*v[3]; ret[3]=m[12]*v[0]+m[13]*v[1]+m[14]*v[2]+m[15]*v[3]; 

// definicje kolorow
static float colorDim[] = {0.000f,0.000f,0.000f,1.0f};
static float colorWhite[] = {0.9f,0.9f,0.9f,1.0f};
static float colorGreen[] = {0.0001f,0.7f,0.0001f,1.0f};
static float colorYellow[] = {0.9f,0.9f,0.0001f,1.0f};
static float colorGray[] = {0.4f,0.4f,0.4f,1.0f};
static float colorRed[] = {0.75f,0.0001f,0.0001f,1.0f};
static float colorBlue[] = {0.0001f,0.0001f,0.9f,1.0f};
static float colorDarkRed[] = {0.1f,0.0001f,0.0001f,1.0f};
static float colorDarkGreen[] = {0.0001f,0.1f,0.0001f,1.0f};
static float colorDarkGray[] = {0.1f,0.1f,0.1f,1.0f};
static float colorPINK[] = {0.9f,0.0f,0.9f,1.0f};



// enumerator stanow
enum {
	STATE_DRAW_OBJECT,
	STATE_ROTATE_OBJECT_LEFT, 
	STATE_ROTATE_OBJECT_UP, 
	STATE_ROTATE_OBJECT_DOWN, 
	STATE_ROTATE_OBJECT_RIGHT,
	STATE_MOVE_OBJECT_RIGHT,
	STATE_MOVE_OBJECT_LEFT,
	STATE_MOVE_OBJECT_FORWARD,
	STATE_MOVE_OBJECT_BACKWARD,
	STATE_DRAW_SCENE,
	STATE_NEW_LIGHT,
	STATE_TEST_LIGHT,
	STATE_COLLISIONS,
	STATE_COLLISIONS_SCENE,
	STATE_MISSLE,
	STATE_WAIT,
	STATE_WAIT_KOMUNIKAT,
	STATE_DRAW_ENEMY,
	STATE_ENEMY_ATTACK,
	STATE_DRAW_WEAPON,
	STATE_WEAPON_ATTACK,
	STATE_MAGIC_ATTACK,
	STATE_EXPLOSION,
	FIREBALL,
	ICE_STORM,
	STATE_NEW_LIGHT_2,
	JUMP,
	STATE_HUD,
	STATE_DISPLAY_STATS,
	STATE_POPUP,
	STATE_GAMEOVER,
	STATE_MENU
};

// enumerator materialow
enum {
	MATERIAL_PLAYER_RED,
	MATERIAL_PLAYER_BLUE,
	MATERIAL_WALL_GRAY,
	MATERIAL_WALL_RED,
	MATERIAL_WALL_BLUE,
	MATERIAL_WALL_YELLOW,
	MATERIAL_WALL_GREEN,
	MATERIAL_WALL_PINK
};

// rysowanie sceny
#define SCENE_COLLISION 255


#endif