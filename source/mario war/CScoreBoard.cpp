#include		"CScoreBoard.h"
#include		"GetKeyInput.h"

CScoreBoard::CScoreBoard(void)
{
	alpha = 200;
	x	  = 64;
	y	  = 0;
	dx	  = 0;
	dy	  = 0;
	scorePos.x = 198;
	scorePos.y = 112;
}

CScoreBoard::~CScoreBoard(void)
{
	
}

void	CScoreBoard::ShowScoreBoard(CRender * _render,
									int *_state,
									CMario * _mario)
{
	int mx;
	int my;
	SDL_ShowCursor(SDL_DISABLE);
	GetMousePos(&mx,&my);
	_render->DrawMenuShade(255);
	_render->DrawScoreBoard(x, y, alpha);
	_render->DrawScore(198+64,112+5,_mario->score);
	_render->DrawScore(198+64,156+5,_mario->kill);
	_render->DrawCursor(mx,my);
	_render->UpdateScreen();	
	
		
	if( PressLeftButton(&mx, &my) )
	{
		* _state = LOAD_LEVEL;
		Sleep(200);
	}
	Sleep(10);
}