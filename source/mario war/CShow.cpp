#include	"CShow.h"
#include	"windows.h"
CShow::CShow(int x, int y)
{
	lasttick = GetTickCount();
	show.life = 1;
	show.x	  = x;
	show.y    = y;
	frame     = 0;
}

CShow::~CShow()
{

}

void	CShow::UpdateLogic(void)
{
	if(GetTickCount() - lasttick >= 100)
	{
		lasttick = GetTickCount();
		if(frame <=4)
		{
			frame++;
		}
		else
		{
			show.life = 0;
		}
		
	}
}