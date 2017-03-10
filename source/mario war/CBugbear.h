#ifndef			CBUGBEAR_H
#define			CBUGBEAR_H
#include		"CMap.h"
#include		"windows.h"

struct		Bugbear
{
	float x;
	float y;
	float dx;
	float dy;
	float life;
};
class			CBugbear
{
public:
	CBugbear(int x, int y);
	~CBugbear(void);
	void	AI(CMap * _map);
	Bugbear GetBugbearStruct(void);
	void	SetLife(int life);
	void	SetDx(float dx );
	int		Frame(void)			{ return  frame; }
private:
	Bugbear		bugBear;
	int			frame;    // 1-3
	DWORD		lasttick ;
};
#endif