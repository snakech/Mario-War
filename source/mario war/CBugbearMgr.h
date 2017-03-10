#ifndef			CBUGBEARMGR_H
#define			CBUGBEARMGR_H
#include	<list>
#include	<algorithm>
#include	<windows.h>
using namespace std;
#include		"CBugbear.h"
#include		"CMap.h"	

struct		Award
{
	float	x;
	float	y;
	float	dx;
	float   dy;
	int		life;
	int		frame;
	DWORD   lasttick;
	int		max;       //产生怪物个数的上限
	DWORD   bugtick;
};

class			CBugbearMgr
{
public:
	CBugbearMgr(CMap *_map);
	~CBugbearMgr(void);
	void	Init(void);
	void	BroseList(CMap *_map);
	void	Add(CMap * _map);
	void	Add(CMap *_map, int x, int y);
	void	AwardLogic(CMap *_map);
	void	SetMax(int _max);
	void	SetBugTick(int _tick);
	Award   GetAwardStruct(void)		{ return award; }
	
public:
	list<CBugbear *> bugbearList;
	Award			 award;
	DWORD			 bugDelay;               //产生怪物的间隔时间
};		
#endif