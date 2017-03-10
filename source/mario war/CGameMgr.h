#ifndef			CGAMEMGR_H
#define			CGAMEMGR_H
#include		"CMario.h"
#include		"CRender.h"
#include		"CRunSmokeMgr.h"
#include		"CBugbearMgr.h"
#include		"CShowMgr.h"
#include		"CAudioMgr.h"
#include		"CGUIMgr.h"
#include		"CScoreBoard.h"
typedef int		GAMESTATE;

struct CurPos
{
	int x;
	int y;
};

/*LOGO*/
struct Logo
{
	float	alpha;
	bool	bIn;	
	int x;
	int y;
};

/*��Ϸ�˵�*/
struct Menu
{
	int x;
	int y;

};

/*��Ϸ����*/
struct Credits
{
	int		x;
	int		y;
	int		alpha;
	bool	bIn;
};
/*��Ϸ����*/
struct Finish
{
	int		x;
	int		y;
	int		alpha;
	bool    bIn;
	
};
class			CGameMgr
{
public:
	CGameMgr(void);
	~CGameMgr(void);
	bool		Start(void);
	bool		Init(void);
	bool		Release(void);
	void		GameLoop(void);
	void		UpdateLogic(void);
	void		Render(void);
	void		DoMessage(void);
	void		LoadLevel(int level);  
	void		GameMenu(void);
	void		GameLogo(void);
	void		GameFinish(void);
	void		GameCredits(void);

	int			level;    //�ؿ���
private:
	GAMESTATE	state;
	bool		brun;
	int		pause;     //��Ϸ�Ƿ���ͣ
	CMario	*mario;
	CRender *render;
	CMap    *map;
	CRunSmokeMgr *smokeMgr;
	CBugbearMgr  *bugbearMgr;
	CShowMgr	*showMgr;
	CGUIMgr		*guiMgr;
	CAudioMgr	*audioMgr;
	CScoreBoard	*scoreBoard;
	CurPos		curpos;
	Logo		logo;
	Menu		menu;
	Credits		credits;
	Finish		finish;
	int			timer;   //
	DWORD		tick;
};
#endif