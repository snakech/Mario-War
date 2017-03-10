#include		"CBugbear.h"
#include		"CMap.h"

#include		"GameInfo.h"
#include		"LogError.h"
#include		<windows.h>
CBugbear::CBugbear(int x,int y)
{
	bugBear.x  = x;
	bugBear.y  = y;
	int t = rand()%10;
	if(t < 5)
	{
		bugBear.dx = 2.0f;
	}
	else
	if(t >= 5 )
	{
		bugBear.dx = -2.0f;
	}
	bugBear.dy = 0;
	bugBear.life = 1;
	frame = 1;
	lasttick = GetTickCount();
}

CBugbear::~CBugbear(void)
{

}

void	CBugbear::AI(CMap * _map)
{
	float ty = bugBear.dy;
	float tx = bugBear.dx;

	bugBear.x +=bugBear.dx;
	bugBear.y +=bugBear.dy;
	
	
	//bugbear“∆∂Ø
	if(bugBear.x <=0 )
	{
		bugBear.life = 0;
	}
	else
	if(bugBear.x >= WINDOW_WIDTH - 32)
	{
		bugBear.life = 0;
	}

	if(bugBear.y >= WINDOW_HEIGHT - TILE_HEIGHT)
	{
		bugBear.y = WINDOW_HEIGHT - TILE_HEIGHT;
	}
	
	//Õ∑≤ø≈ˆ◊≤
	int x1 = (bugBear.x )/TILE_WIDTH;
	int y1 = (bugBear.y +4)/TILE_HEIGHT;
	int x2 = (bugBear.x + TILE_WIDTH )/TILE_WIDTH;
	int y2 = (bugBear.y +4)/TILE_HEIGHT;
	if( _map->maps[y1][x1] != 0 || _map->maps[y2][x2] != 0 )
	{

	//	bugBear.y  -=ty;
		bugBear.dy =-0.0f;
	}

	//Ω≈≤ø≈ˆ◊≤
	 x1 = (bugBear.x )/TILE_WIDTH;
	 y1 = (bugBear.y + TILE_HEIGHT)/TILE_HEIGHT;
	 x2 = (bugBear.x + TILE_WIDTH )/TILE_WIDTH;
	 y2 = (bugBear.y + TILE_HEIGHT)/TILE_HEIGHT;
	
	if( _map->maps[y1][x1] != 0 || _map->maps[y2][x2] != 0 )
	{	
		bugBear.y  -=ty;
		bugBear.dy =0.0f;
		int t = rand()%100;
		if(t>90 && t<100)
		{
		//	bugBear.dy = -5.0f;
		}
	}
	else
	{
		bugBear.dy +=0.3f;
	}
	//◊Û±ﬂ≈ˆ◊≤
	 x1 = bugBear.x/TILE_WIDTH;
	 y1 = (bugBear.y + 4)/TILE_WIDTH;
	 x2 = bugBear.x/TILE_WIDTH;
	 y2 = (bugBear.y + TILE_HEIGHT -4)/TILE_WIDTH;
    
	if( _map->maps[y1][x1] != 0 || _map->maps[y2][x2] != 0 )
	{
		bugBear.x +=tx;
		bugBear.dx = 2;
	}

	//”“±ﬂ≈ˆ◊≤
	 x1 = (bugBear.x + TILE_WIDTH)/TILE_WIDTH;
	 y1 = (bugBear.y + 4)/TILE_WIDTH;
	 x2 = (bugBear.x+ TILE_WIDTH)/TILE_WIDTH;
	 y2 = (bugBear.y + TILE_HEIGHT - 4)/TILE_WIDTH;
    
	if( _map->maps[y1][x1] != 0 || _map->maps[y2][x2] != 0 )
	{
		bugBear.x -= tx;
 		bugBear.dx = -2;
	}

	
	/*÷°∂Øª≠*/
	// lasttick = GetTickCount();
	if(GetTickCount() - lasttick >= 200)
	{
		lasttick = GetTickCount();
    	frame = -frame;
	//frame =2- rand()%3;
	}
	
	if(bugBear.life == 0)	
	{
		frame = 0;
	}
	
}

Bugbear		CBugbear::GetBugbearStruct(void)
{
	return	bugBear;
}

void		CBugbear::SetLife(int life)

{
	bugBear.life = life;
}

void		CBugbear::SetDx(float dx)
{
	bugBear.dx = dx;
}
