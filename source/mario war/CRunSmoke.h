#ifndef			CRUNSMOKE_H
#define			CRUNSMOKE_H

#include		<windows.h>
struct		Smoke
{
	int		x;
	int		y;
	int		life;
};

class			CRunSmoke
{
public:
	CRunSmoke(int _x, int _y);
	~CRunSmoke(void);
	void UpdateLogic(void);
	Smoke	GetSmokeStruct(void);
	int		Frame(void)		{ return frame; }
private:
	Smoke	smoke;
	int		frame;   // 1-3
	DWORD   lasttick; 
};
#endif