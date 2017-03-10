#ifndef			GAMEINFO_H
#define			GAMEINFO_H

/*mario属性*/
const int		MARIO_IN_AIR   = 0;
const int		MARIO_ON_LAND  = 1;
const int		MARIO_IS_ALIVE = 1;
const int		MARIO_IS_DEAD  = -1;
const int		MARIO_WIDTH    = 32;
const int		MARIO_HEIGHT   = 32;
//mario right frame
const int		MARIO_r1        = 1;
const int		MARIO_r2		= -1;
const int		MARIO_r3        = 3;
const int		MARIO_r4        = 4;
const int       MARIO_r5        = 5;
const int		MARIO_r6        = 6;

//mario left frame
const int		MARIO_l1        = 11;
const int		MARIO_l2		= -11;
const int		MARIO_l3        = -33;
const int		MARIO_l4        = -44;
const int       MARIO_l5        = -55;
const int		MARIO_l6        = -66;
//collison style
const int		NONE_COL        = 0;
const int		LEFT_COL        = 1;
const int		RIGHT_COL       = 2;
const int		DOWN_COL        = 3;
//面向的方向
const int		LEFT			=1;
const int		RIGHT			=-1;

/*窗口属性*/
const int		WINDOW_WIDTH   = 640;
const int		WINDOW_HEIGHT  = 480;
const int		WINDOW_BPP     = 16;

/*游戏属性*/
const int		GAME_INIT		=1;
const int		GAME_MAIN		=2;
const int		GAME_EXIT		=3;
const int		LOAD_LEVEL		=4;     
const int		GAME_LOGO       =5;
const int		GAME_MENU       =6;
const int		GAME_CREDITS    =7;
const int		GAME_SCOREBOARD =8;
const int		GAME_FINISH		=9;
/*地图数组大小*/
const int		MAP_Y           = 15;
const int		MAP_X			= 20;
 //tile大小
const int		TILE_WIDTH      = 32;
const int		TILE_HEIGHT     = 32;


/*run smoke属性*/
const int		SMOKE_WIDTH		= 16;
const int		SMOKE_HEIGHT    = 16;

const int		TILE_9_0_STYLE		= 1;   //金色砖块
const int		TILE_10_0_STYLE		= 2;   //白色砖块
const int		TILE_11_0_STYLE		= 3;   //问号
const int		TILE_12_0_STYLE		= 4;   //音乐符号
const int		TILE_13_0_STYLE		= 5;   //孔型砖块
const int		TILE_14_0_STYLE		= 6;   //黄色脸
const int		TILE_15_0_STYLE		= 7;   //兰色脸

const int		TILE_9_1_STYLE		= 8;   //棕色木快
const int		TILE_10_1_STYLE		= 9;   //灰色木快
const int		TILE_11_1_STYLE		= 10;   //兰色金属快
const int		TILE_12_1_STYLE		= 11;   //灰色金属快
const int		TILE_13_1_STYLE		= 12;   //红色圈圈
const int		TILE_14_1_STYLE		= 13;   //绿色孔型砖
const int		TILE_15_1_STYLE		= 14;   //碎石快

const int		TILE_9_2_STYLE      = 15;    //叉型快1
const int		TILE_10_2_STYLE      = 16;	 //叉型块2
const int		TILE_11_2_STYLE      = 17;   //大岩石
const int		TILE_12_2_STYLE      = 18;   //口型石
const int		TILE_13_2_STYLE      = 19;   //雪地
const int		TILE_14_2_STYLE      = 20;   //煤炭路快
const int		TILE_15_2_STYLE      = 21;   //简单的灰色方快

const int		TILE_9_3_STYLE		= 22;    //灰色脸
const int		TILE_10_3_STYLE		= 23;    //土黄色快
const int		TILE_11_3_STYLE		= 24;    //星星图案快
const int		TILE_12_3_STYLE		= 25;    //黄色沙路
const int		TILE_13_3_STYLE		= 26;    //土色沙路
const int		TILE_14_3_STYLE		= 27;    //有泥巴的草地
const int		TILE_15_3_STYLE		= 28;    //棕色方快

const int		TILE_9_4_STYLE		= 29;    //棕色防快
const int		TILE_10_4_STYLE		= 30;    //兰色防快
const int		TILE_11_4_STYLE		= 31;    //兰色圆角防快
const int		TILE_12_4_STYLE		= 32;    //灰色圆角防快
const int		TILE_13_4_STYLE		= 33;    //沙子路
const int		TILE_14_4_STYLE		= 34;    //粗纱路
const int		TILE_15_4_STYLE		= 35;    //深灰色防快

const int		TILE_9_5_STYLE		= 36;    //红色球
const int		TILE_10_5_STYLE		= 37;    //灰色球
const int		TILE_11_5_STYLE		= 38;    //戴眼镜的脸
const int		TILE_12_5_STYLE		= 39;    //大冰块左上
const int		TILE_13_5_STYLE		= 40;    //大冰块右上
const int		TILE_14_5_STYLE		= 41;    //带点的灰色防快
const int		TILE_15_5_STYLE		= 42;    //带点的总红色

const int		TILE_9_6_STYLE		= 43;    //冰块1
const int		TILE_10_6_STYLE		= 44;    //冰块2
const int		TILE_11_6_STYLE		= 45;    //冰块3
const int		TILE_12_6_STYLE		= 46;    //大冰块左下
const int		TILE_13_6_STYLE		= 47;    //大冰块右下
const int		TILE_14_6_STYLE		= 48;    //简单防快左
const int		TILE_15_6_STYLE		= 49;    //简单防快右

const int		MAP_NUM				= 25;
const int		TIMER				= 255;
const int		SCORE_PASS			= 100;
const int		BM_NUM				=  4;
/*窗口工作区*/
const int		ED_AREA_POSX		= 0;
const int		ED_AREA_POSY		= 0;
#endif