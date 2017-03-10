#include		"CRunSmoke.h"
#include		<windows.h>
CRunSmoke::CRunSmoke(int _x, int _y)
{	
	smoke.x		= _x;
	smoke.y		= _y;
	frame		= 0;
	smoke.life  = 1;
	lasttick = GetTickCount();
	
}

CRunSmoke::~CRunSmoke(void)
{

}

void	CRunSmoke::UpdateLogic(void)
{
	if(GetTickCount() - lasttick >= 80)
	{
		lasttick = GetTickCount();
		if(frame <=4)
		{
			frame ++;
		}

		else
		{
			smoke.life = 0;
		}


	}
}


Smoke   CRunSmoke::GetSmokeStruct(void)
{
	return smoke;
}