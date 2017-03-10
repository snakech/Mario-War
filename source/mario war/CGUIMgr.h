#ifndef			CGUIMGR_H
#define			CGUIMGR_H

typedef	struct		ButtonRect
{
	int x;
	int y;
	int w;
	int h;
	int x2;
	int y2;
} BTRECT;		

typedef	struct		Button
{
	BTRECT		rect;
	bool		bOn;
} BUTTON;	

class			CGUIMgr
{
public:
	CGUIMgr(void);
	~CGUIMgr(void);
	/*退出选单的按钮*/
	BUTTON	GetExitYes();
	BUTTON	GetExitNo();
	void	SetExitYes(bool _bOn);
	void	SetExitNo(bool _bOn);

	/*游戏开始菜单的按钮*/
	BUTTON  GetMenuNew(void);
	BUTTON	GetMenuCredits(void);
	BUTTON	GetMenuExit(void);
	void	SetMenuNew(bool _bOn);
	void	SetMenuCredits(bool _bOn);
	void	SetMenuExit(bool _bOn);
private:
	BUTTON		ExitYes;  
	BUTTON		ExitNo;
	BUTTON		MenuNew;
	BUTTON		MenuCredits;
	BUTTON		MenuExit;
};	
#endif