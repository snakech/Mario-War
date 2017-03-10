#ifndef			CRENDER_H
#define			CRENDER_H
#include		<SDL.h>
#include		"CMario.h"
#include		"CRunSMokeMgr.h"
#include		"CBugbearMgr.h"
#include		"CShowMgr.h"
class			CRender
{
public:
	CRender(void);
	~CRender(void);
	bool		SysInit(void);
	bool		SysRelease(void);
	void		Changebg(int level);
	void		UpdateScreen(void);
	void		DrawMario(CMario *_mario);
	void		DrawMarioFrame(CMario *_mario);
	void		DrawBG(void);
	void		DrawTile(int _sx, int _sy, int _dx, int _dy, int _alpha);
	void		DrawSmoke(CRunSmokeMgr *_smokeMgr, CMario *_mario);
	void		DrawBugbear(CBugbearMgr *_bugbearMgr);
	void		DrawShow(CShowMgr *_showMgr);
	void		DrawAward(CBugbearMgr	*_bugbearMgr);
	void		DrawDialog(int x=224, int y=176);      //192 X 128
	void		DrawMenuShade(int _alpha);
	void		DrawCursor(int x, int y);
	void		DrawExitButton(int _dx, int _dy, bool _bOn);
	void		DrawExitSelect(void);
	void		DrawMenuButton(int _dx, int _dy, bool _bOn);
	void		DrawMenuSelect(void);
	void		DrawLogo(int _dx, int _dy, int _alpha);
	void		DrawScore(int x, int y, int score);
	void		DrawCredits(int _alpha);
	void		DrawScoreBoard(int x, int y, int alpha);
	void		DrawFinish(int x, int y, int alpha);
	void		RECT(SDL_Rect *_rect, int x, int y, int w, int h);
	void		ScreenShot(void);
private:
	SDL_Surface		*screen;
	SDL_Surface		*marioMoveLeft;
	SDL_Surface		*marioMoveRight;
	SDL_Surface		*bg;
	SDL_Surface		*tiles;
	SDL_Surface		*smoke;
	SDL_Surface		*bugbear;
	SDL_Surface		*show;
	SDL_Surface		*award;
	SDL_Surface		*dialog;     //通用的对话框
	SDL_Surface		*menushade;  
	SDL_Surface		*cursor;
	SDL_Surface		*exitbutton;
	SDL_Surface		*menubutton;
	SDL_Surface		*exitselect;
	SDL_Surface		*menuselect;
	SDL_Surface		*credits;
	SDL_Surface		*score;
	SDL_Surface		*scoreBoard;
	SDL_Surface		*logo;
	SDL_Surface		*finish;
};
#endif