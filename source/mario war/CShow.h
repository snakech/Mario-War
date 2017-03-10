#ifndef			CSHOW_H
#define			CSHOW_H
#include		<windows.h>

struct		Show
{
	int x;
	int y;
	int life;
};

class		CShow
{
public:
	CShow(int x, int y);
	void	UpdateLogic(void);
	int		Frame(void)				{ return frame; }
	Show	GetShowStruct(void)		{ return show;	}	
	~CShow(void);

private:
	DWORD	lasttick;
	int		frame;
	Show	show;
};
#endif