#ifndef			GAMEINFO_H
#define			GAMEINFO_H

/*mario����*/
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
//����ķ���
const int		LEFT			=1;
const int		RIGHT			=-1;

/*��������*/
const int		WINDOW_WIDTH   = 640;
const int		WINDOW_HEIGHT  = 480;
const int		WINDOW_BPP     = 16;

/*��Ϸ����*/
const int		GAME_INIT		=1;
const int		GAME_MAIN		=2;
const int		GAME_EXIT		=3;
const int		LOAD_LEVEL		=4;     
const int		GAME_LOGO       =5;
const int		GAME_MENU       =6;
const int		GAME_CREDITS    =7;
const int		GAME_SCOREBOARD =8;
const int		GAME_FINISH		=9;
/*��ͼ�����С*/
const int		MAP_Y           = 15;
const int		MAP_X			= 20;
 //tile��С
const int		TILE_WIDTH      = 32;
const int		TILE_HEIGHT     = 32;


/*run smoke����*/
const int		SMOKE_WIDTH		= 16;
const int		SMOKE_HEIGHT    = 16;

const int		TILE_9_0_STYLE		= 1;   //��ɫש��
const int		TILE_10_0_STYLE		= 2;   //��ɫש��
const int		TILE_11_0_STYLE		= 3;   //�ʺ�
const int		TILE_12_0_STYLE		= 4;   //���ַ���
const int		TILE_13_0_STYLE		= 5;   //����ש��
const int		TILE_14_0_STYLE		= 6;   //��ɫ��
const int		TILE_15_0_STYLE		= 7;   //��ɫ��

const int		TILE_9_1_STYLE		= 8;   //��ɫľ��
const int		TILE_10_1_STYLE		= 9;   //��ɫľ��
const int		TILE_11_1_STYLE		= 10;   //��ɫ������
const int		TILE_12_1_STYLE		= 11;   //��ɫ������
const int		TILE_13_1_STYLE		= 12;   //��ɫȦȦ
const int		TILE_14_1_STYLE		= 13;   //��ɫ����ש
const int		TILE_15_1_STYLE		= 14;   //��ʯ��

const int		TILE_9_2_STYLE      = 15;    //���Ϳ�1
const int		TILE_10_2_STYLE      = 16;	 //���Ϳ�2
const int		TILE_11_2_STYLE      = 17;   //����ʯ
const int		TILE_12_2_STYLE      = 18;   //����ʯ
const int		TILE_13_2_STYLE      = 19;   //ѩ��
const int		TILE_14_2_STYLE      = 20;   //ú̿·��
const int		TILE_15_2_STYLE      = 21;   //�򵥵Ļ�ɫ����

const int		TILE_9_3_STYLE		= 22;    //��ɫ��
const int		TILE_10_3_STYLE		= 23;    //����ɫ��
const int		TILE_11_3_STYLE		= 24;    //����ͼ����
const int		TILE_12_3_STYLE		= 25;    //��ɫɳ·
const int		TILE_13_3_STYLE		= 26;    //��ɫɳ·
const int		TILE_14_3_STYLE		= 27;    //����͵Ĳݵ�
const int		TILE_15_3_STYLE		= 28;    //��ɫ����

const int		TILE_9_4_STYLE		= 29;    //��ɫ����
const int		TILE_10_4_STYLE		= 30;    //��ɫ����
const int		TILE_11_4_STYLE		= 31;    //��ɫԲ�Ƿ���
const int		TILE_12_4_STYLE		= 32;    //��ɫԲ�Ƿ���
const int		TILE_13_4_STYLE		= 33;    //ɳ��·
const int		TILE_14_4_STYLE		= 34;    //��ɴ·
const int		TILE_15_4_STYLE		= 35;    //���ɫ����

const int		TILE_9_5_STYLE		= 36;    //��ɫ��
const int		TILE_10_5_STYLE		= 37;    //��ɫ��
const int		TILE_11_5_STYLE		= 38;    //���۾�����
const int		TILE_12_5_STYLE		= 39;    //���������
const int		TILE_13_5_STYLE		= 40;    //���������
const int		TILE_14_5_STYLE		= 41;    //����Ļ�ɫ����
const int		TILE_15_5_STYLE		= 42;    //������ܺ�ɫ

const int		TILE_9_6_STYLE		= 43;    //����1
const int		TILE_10_6_STYLE		= 44;    //����2
const int		TILE_11_6_STYLE		= 45;    //����3
const int		TILE_12_6_STYLE		= 46;    //���������
const int		TILE_13_6_STYLE		= 47;    //���������
const int		TILE_14_6_STYLE		= 48;    //�򵥷�����
const int		TILE_15_6_STYLE		= 49;    //�򵥷�����

const int		MAP_NUM				= 25;
const int		TIMER				= 255;
const int		SCORE_PASS			= 100;
const int		BM_NUM				=  4;
/*���ڹ�����*/
const int		ED_AREA_POSX		= 0;
const int		ED_AREA_POSY		= 0;
#endif