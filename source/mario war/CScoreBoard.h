#ifndef			CSCOREBOARD_H
#define			CSCOREBOARD_H
#include		"CMario.h"
#include		"CRender.h"
struct		Pos
{
	int x;
	int y;
};
class			CScoreBoard
{
public:
	CScoreBoard(void);		
	~CScoreBoard(void);		
	void		ShowScoreBoard(CRender * _render,int *_state, CMario * _mario);
	void		ShowIfWin(bool _win, CRender * _render);

private:
	int x;
	int y;
	int dx;
	int dy;
	int alpha;
	Pos scorePos;     //∑÷ ˝Œª÷√
};
#endif