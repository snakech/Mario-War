 1	#include	"CBugbearMgr.h"
#include	"CBugbear.h"
#include	"CShowMgr.h"
#include	<list>
#include	<algorithm>
#include	"CMap.h"
#include	<windows.h>
#include	"LogError.h"

CBugbearMgr::CBugbearMgr(CMap *_map)
{
	int x;
	int y;
	
	/*init award*/
			x = rand()%550;
			y = rand()%400;
			award.frame		= 1;
			award.lasttick	= GetTickCount();
			award.life		= 1;
			award.x			= x;
			award.y			= y;
			award.dx		= 1.0f;
			award.dy		= 1.0f;
			award.max		= 1;
			award.bugtick   = 3000;
			bugDelay		= GetTickCount();

}

CBugbearMgr::~CBugbearMgr(void)
{

}

void CBugbearMgr::BroseList(CMap * _map)
{

	list<CBugbear *>::iterator it;
	for(it=bugbearList.begin(); it!=bugbearList.end(); it++)
	{
		
			if((*it)->GetBugbearStruct().life != 1 )
			{
				delete(*it);
				it = bugbearList.erase(it);
				
			}
			else
			{
				
				(*it)->AI(_map);				
			}
		
	}
}

void	CBugbearMgr::Add(CMap * _map)
{
	
	
		int x;
		int y;
		
		
		
	
			x = rand()%MAP_X-1;
			y = rand()%MAP_Y-1;
			
			if(_map->maps[y][x] == 0 )
			{
				CBugbear *bugbear = new CBugbear(x*TILE_WIDTH,y*TILE_HEIGHT);
				bugbearList.push_back(bugbear);	
			
			}
	
}

void	CBugbearMgr::Add(CMap *_map, int x, int y)
{
		int tx1 = (x+10)/TILE_WIDTH;
		int ty1 = (y+10)/TILE_HEIGHT;
		int tx2 = (x+42)/TILE_WIDTH;
		int ty2 = (y+10)/TILE_HEIGHT;
		int tx3 = (x+42)/TILE_WIDTH;
		int ty3 = (y+42)/TILE_HEIGHT;
		int tx4 = (x+10)/TILE_WIDTH;
		int ty4 = (y+42)/TILE_HEIGHT;

		if(_map->maps[ty1][tx1] == 0 &&
			_map->maps[ty2][tx2] == 0 &&
			_map->maps[ty3][tx3] == 0 &&
			_map->maps[ty4][tx4] == 0 )
			{
				CBugbear *bugbear = new CBugbear(x+10,y+10);
				bugbearList.push_back(bugbear);	
			
			}
}

void	CBugbearMgr::AwardLogic(CMap *_map)
{
		/*碰撞检测*/
		if(award.x <= 0 || award.x >= WINDOW_WIDTH - 64 )
		{
			award.dx = - award.dx;	
		}

		if(award.y <= 0 || award.y >= WINDOW_HEIGHT - 64 )
		{
			award.dy = -award.dy;
		}

		/*逻辑更新*/
		award.x += award.dx;
		award.y += award.dy;

		/*帧更新*/

		if(GetTickCount() - award.lasttick >= 500 )
		{
			award.lasttick = GetTickCount();
			award.frame = -award.frame;
		
        /*产生怪物*/
		
			if( bugbearList.size() < award.max )
			{
				if(GetTickCount() - bugDelay >= award.bugtick)
				{
					bugDelay = GetTickCount();
					Add(_map, award.x, award.y );
				}
			}
		}
}


void	CBugbearMgr::Init(void)
{
		int x;
     	int y;
	
	/*init award*/
			x = rand()%550;
			y = rand()%400;
			award.frame		= 1;
			award.lasttick	= GetTickCount();
			award.life		= 1;
			award.x			= x;
			award.y			= y;
			award.dx		= 1.0f;
			award.dy		= 1.0f;
			bugDelay		= GetTickCount();
}



void	CBugbearMgr::SetMax(int _max)
{
	award.max = _max;
}


void	CBugbearMgr::SetBugTick(int _tick)
{
	award.bugtick = _tick;
}





