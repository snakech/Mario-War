#ifndef			CRENDER_H
#define			CRENDER_H

#include		<SDL.h>
class			CRender
{
public:
	CRender(void) {}
	~CRender(void) {}

	bool		SysInit(void);   //ϵͳ��س�ʼ��,����ͼƬ֮��,��ʼ��SDL
	bool		SysRelease(void); //ϵͳ��Դ�ͷ��Լ��ر�SDL
	bool		DataInit(void);   //���ݳ�ʼ��
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
	SDL_Surface		*selectGrid;   //ѡ���
	SDL_Surface		*bg;   //����
	SDL_Surface		*map;
	SDL_Surface		*cursor;  //���
};
#endif