#ifndef			CRENDER_H
#define			CRENDER_H

#include		<SDL.h>
class			CRender
{
public:
	CRender(void) {}
	~CRender(void) {}

	bool		SysInit(void);   //系统相关初始化,载入图片之类,初始化SDL
	bool		SysRelease(void); //系统资源释放以及关闭SDL
	bool		DataInit(void);   //数据初始化
	void		DrawTile( int _sx, int _sy, int _dx, int _dy, int _alpha );
	void		DrawTile( int _dx, int _dy, int _alpha);
	void		DrawBG( int _sx, int _sy, int _dx, int _dy, int _alpha );
	void		DrawSelectGrid( int _sx, int _sy, int _dx, int _dy, int _alpha );
	void		DrawMap(int _sx, int _sy, int _dx, int _dy, int _alpha );
	void		DrawCursor(int _sx, int _sy, int _dx, int _dy, int _alpha );
	void		UpdateScreen(void);
private:
	SDL_Surface		*screen;     
	SDL_Surface		*tiles;       //tiles
	SDL_Surface		*selectGrid;   //选择框
	SDL_Surface		*bg;   //背景
	SDL_Surface		*map;
	SDL_Surface		*cursor;  //鼠标
};
#endif