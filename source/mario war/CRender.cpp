#include		"CRender.h"
#include		"LogError.h"
#include		"GameInfo.h"
#include		"CMap.h"
#include		"CRunSmokeMgr.h"
#include		"CMario.h"
#include		"CShow.h"
#include		<SDL.h>
#include		<SDL_image.h>
CRender::CRender(void)
{
	
}

CRender::~CRender(void)
{

}

bool	CRender::SysInit(void)
{
	/*SDL系统初始化*/
	if( SDL_Init(SDL_INIT_VIDEO) < 0 )
	{
		LOG("SDL init Error");
		return false;
	}
	else 
	{
		LOG("SDL init <done>");
	}

	/*窗口系统初始化*/

	SDL_WM_SetCaption("Mario War","icon.bmp");

	screen = SDL_SetVideoMode( WINDOW_WIDTH, WINDOW_HEIGHT, 16, SDL_HWSURFACE|SDL_DOUBLEBUF);//SDL_HWSURFACE|SDL_DOUBLEBUF);
	if( screen == NULL )
	{
		LOG("video mode set error");
		return false;
	}
	else
	{
		LOG("video mode @ 640*480*16 <done>");
	}
	
	/*atexit(SDL_Quit)*/
	atexit(SDL_Quit);

	/*图片资源载入*/

	/*向左的图片*/
	marioMoveLeft = IMG_Load("gfx\\skins\\mario_move_left.png");
	SDL_SetColorKey( marioMoveLeft,SDL_SRCCOLORKEY, SDL_MapRGB(marioMoveLeft->format,255,0,255) );
	/*向右的图片*/
	marioMoveRight = IMG_Load("gfx\\skins\\mario_move_right.png");
	SDL_SetColorKey( marioMoveRight,SDL_SRCCOLORKEY, SDL_MapRGB(marioMoveRight->format,255,0,255) );
	
	/*背景图片*/
	bg = IMG_Load( "gfx\\background\\bg1.png" );

	/*tiles*/
	tiles = IMG_Load( "gfx\\tiles\\tiles.png" );
	SDL_SetColorKey( tiles,SDL_SRCCOLORKEY, SDL_MapRGB(tiles->format,255,0,255) );

	/*smoke*/
	smoke = IMG_Load( "gfx\\effect\\runsmoke.png" );
	SDL_SetColorKey( smoke,SDL_SRCCOLORKEY, SDL_MapRGB(smoke->format,255,0,255) );

	/*bugbear*/
	bugbear = IMG_Load( "gfx\\skins\\bugbear.png" );
	SDL_SetColorKey( bugbear, SDL_SRCCOLORKEY, SDL_MapRGB(bugbear->format,255,0,255) );

	/*draw show*/
	show = IMG_Load( "gfx\\effect\\show.png" );
	SDL_SetColorKey( show, SDL_SRCCOLORKEY, SDL_MapRGB(show->format,255,0,255) );

	/*draw award*/
	award = IMG_Load( "gfx\\skins\\award.png" );
	SDL_SetColorKey( award, SDL_SRCCOLORKEY, SDL_MapRGB(award->format,255,0,255) );

	/*draw dialog*/
	dialog = IMG_Load( "gfx\\other\\dialog.png" );
	SDL_SetColorKey( dialog, SDL_SRCCOLORKEY, SDL_MapRGB(dialog->format,255,0,255) );

	/*draw menu shade*/
	menushade = IMG_Load( "gfx\\other\\menushade.png" );

	/*draw cursor*/
	cursor = IMG_Load( "gfx\\other\\cursor.png" );
	SDL_SetColorKey( cursor, SDL_SRCCOLORKEY, SDL_MapRGB( cursor->format,47,89,147) );

	/*draw exit button*/
	exitbutton = IMG_Load( "gfx\\GUI\\exitbutton.png" );
	SDL_SetColorKey( exitbutton, SDL_SRCCOLORKEY, SDL_MapRGB( exitbutton->format,255,0,255) );
	
	/*draw menu button*/
	menubutton = IMG_Load( "gfx\\GUI\\menubutton.png" );
	SDL_SetColorKey( menubutton, SDL_SRCCOLORKEY, SDL_MapRGB( menubutton->format,255,0,255) );
	/*draw logo*/
	logo = IMG_Load( "gfx\\logo\\logo.png" );
	/*draw exit select*/
	exitselect = IMG_Load( "gfx\\GUI\\exitselect.png" );
	SDL_SetColorKey( exitselect, SDL_SRCCOLORKEY, SDL_MapRGB( exitselect->format,0,0,0) );
	
	/*draw menu select*/
	menuselect = IMG_Load( "gfx\\GUI\\menuselect.png" );
	SDL_SetColorKey( menuselect, SDL_SRCCOLORKEY, SDL_MapRGB( menuselect->format,0,0,0) );

	/*draw credits*/
	credits = IMG_Load( "gfx\\other\\credits.png" );
	SDL_SetColorKey( credits, SDL_SRCCOLORKEY, SDL_MapRGB( credits->format,255,0,255) );

	/*draw score*/
	score = IMG_Load( "gfx\\other\\score.png" );
	SDL_SetColorKey( score, SDL_SRCCOLORKEY, SDL_MapRGB( score->format,255,0,255) );

	/*draw scoreBoard*/
	scoreBoard = IMG_Load( "gfx\\other\\scoreboard.png" );
	SDL_SetColorKey( scoreBoard, SDL_SRCCOLORKEY, SDL_MapRGB( scoreBoard->format,255,0,255) );
	/*darw finish*/
	finish = IMG_Load( "gfx\\other\\finish.png" );
	/*ererything is ready!*/
	return true;
}


bool	CRender::SysRelease(void)
{
	SDL_FreeSurface(marioMoveLeft);
	SDL_FreeSurface(marioMoveRight);
	SDL_FreeSurface(bg);
	SDL_FreeSurface(tiles);
	SDL_FreeSurface(smoke);
	SDL_FreeSurface(bugbear);
	SDL_FreeSurface(show);
	SDL_FreeSurface(dialog);
	SDL_FreeSurface(menushade);
	SDL_FreeSurface(exitbutton);
	SDL_FreeSurface(menubutton);
	SDL_FreeSurface(exitselect);
	SDL_FreeSurface(logo);
	SDL_FreeSurface(menuselect);
	SDL_FreeSurface(credits);
	SDL_FreeSurface(score);
	SDL_FreeSurface(scoreBoard);
	SDL_FreeSurface(finish);
	SDL_Quit();
	return true;
}

void	CRender::UpdateScreen(void)
{
	SDL_Flip(screen);
}


void	CRender::DrawMario(CMario *_mario)
{
}


void	CRender::DrawMarioFrame(CMario *_mario)
{
	SDL_Rect	marioRect;
	SDL_Rect	screenRect;
	
    switch(_mario->GetFrame())
	{
	case	MARIO_r1:
		RECT(&marioRect,0,0,MARIO_WIDTH,MARIO_HEIGHT);
		RECT(&screenRect,_mario->GetMarioData().x,
			_mario->GetMarioData().y,WINDOW_WIDTH,
			WINDOW_HEIGHT);
		SDL_BlitSurface(marioMoveRight,&marioRect,screen,&screenRect);
		break;
	case	MARIO_r2:
		RECT(&marioRect,MARIO_WIDTH,0,MARIO_WIDTH,MARIO_HEIGHT);
		RECT(&screenRect,_mario->GetMarioData().x,
			_mario->GetMarioData().y,WINDOW_WIDTH,
			WINDOW_HEIGHT);
		SDL_BlitSurface(marioMoveRight,&marioRect,screen,&screenRect);
		break;
	case	MARIO_r3:
		RECT(&marioRect,MARIO_WIDTH*2,0,MARIO_WIDTH,MARIO_HEIGHT);
		RECT(&screenRect,_mario->GetMarioData().x,
			_mario->GetMarioData().y,WINDOW_WIDTH,
			WINDOW_HEIGHT);
		SDL_BlitSurface(marioMoveRight,&marioRect,screen,&screenRect);
		break;
	case	MARIO_r4:
		RECT(&marioRect,MARIO_WIDTH*3,0,MARIO_WIDTH,MARIO_HEIGHT);
		RECT(&screenRect,_mario->GetMarioData().x,
			_mario->GetMarioData().y,WINDOW_WIDTH,
			WINDOW_HEIGHT);
		SDL_BlitSurface(marioMoveRight,&marioRect,screen,&screenRect);
		break;
	case	MARIO_r5:
		RECT(&marioRect,MARIO_WIDTH*4,0,MARIO_WIDTH,MARIO_HEIGHT);
		RECT(&screenRect,_mario->GetMarioData().x,
			_mario->GetMarioData().y,WINDOW_WIDTH,
			WINDOW_HEIGHT);
		SDL_BlitSurface(marioMoveRight,&marioRect,screen,&screenRect);
		break;
	case	MARIO_r6:
		RECT(&marioRect,MARIO_WIDTH*5,0,MARIO_WIDTH,MARIO_HEIGHT);
		RECT(&screenRect,_mario->GetMarioData().x,
			_mario->GetMarioData().y,WINDOW_WIDTH,
			WINDOW_HEIGHT);
		SDL_BlitSurface(marioMoveRight,&marioRect,screen,&screenRect);
		break;

	case	MARIO_l1:
		RECT(&marioRect,0,0,MARIO_WIDTH,MARIO_HEIGHT);
		RECT(&screenRect,_mario->GetMarioData().x,
			_mario->GetMarioData().y,WINDOW_WIDTH,
			WINDOW_HEIGHT);
		SDL_BlitSurface(marioMoveLeft,&marioRect,screen,&screenRect);
		break;
	case	MARIO_l2:
		RECT(&marioRect,MARIO_WIDTH,0,MARIO_WIDTH,MARIO_HEIGHT);
		RECT(&screenRect,_mario->GetMarioData().x,
			_mario->GetMarioData().y,WINDOW_WIDTH,
			WINDOW_HEIGHT);
		SDL_BlitSurface(marioMoveLeft,&marioRect,screen,&screenRect);
		break;
	case	MARIO_l3:
		RECT(&marioRect,MARIO_WIDTH*2,0,MARIO_WIDTH,MARIO_HEIGHT);
		RECT(&screenRect,_mario->GetMarioData().x,
			_mario->GetMarioData().y,WINDOW_WIDTH,
			WINDOW_HEIGHT);
		SDL_BlitSurface(marioMoveLeft,&marioRect,screen,&screenRect);
		break;
	case	MARIO_l4:
		RECT(&marioRect,MARIO_WIDTH*3,0,MARIO_WIDTH,MARIO_HEIGHT);
		RECT(&screenRect,_mario->GetMarioData().x,
			_mario->GetMarioData().y,WINDOW_WIDTH,
			WINDOW_HEIGHT);
		SDL_BlitSurface(marioMoveLeft,&marioRect,screen,&screenRect);
		break;
	default:
		break;
	}
}

void	CRender::DrawBG(void)
{
	SDL_Rect bgRect;
	SDL_Rect screenRect;
	RECT(&bgRect,0,0,WINDOW_WIDTH,WINDOW_HEIGHT);
	RECT(&screenRect,0,0,WINDOW_WIDTH,WINDOW_HEIGHT);
	SDL_BlitSurface(bg,&bgRect,screen,&screenRect);
}

void	CRender::DrawTile( int _sx, int _sy, int _dx, int _dy, int _alpha)
{
	SDL_Rect	tileRect;
	SDL_Rect	screenRect;

	tileRect.x = _sx;
	tileRect.y = _sy;
	tileRect.w = TILE_WIDTH;
	tileRect.h = TILE_HEIGHT;

	screenRect.x = _dx;
	screenRect.y = _dy;
	screenRect.w = WINDOW_WIDTH;
	screenRect.h = WINDOW_HEIGHT;
	SDL_SetAlpha(tiles, SDL_SRCALPHA, _alpha);
	SDL_BlitSurface( tiles, &tileRect, screen, &screenRect );
}

void	CRender::DrawSmoke(CRunSmokeMgr *_smokeMgr, CMario *_mario)
{
	SDL_Rect   smokeRect;
	SDL_Rect   screenRect;
	list<CRunSmoke *>::iterator it;
	for( it=_smokeMgr->smokeList.begin(); it!=_smokeMgr->smokeList.end(); it++)
	{
		if( (*it)->Frame() == 1)		{ RECT(&smokeRect,0,0,16,16); }
		else
		if( (*it)->Frame() == 2)		{ RECT(&smokeRect,16,0,16,16); }
		else
		if( (*it)->Frame() == 3 )		{ RECT(&smokeRect,32,0,16,16); }
		else
		if( (*it)->Frame() == 4 )		{ RECT(&smokeRect,48,0,16,16); }	 
		
		RECT( &screenRect,(*it)->GetSmokeStruct().x,
		(*it)->GetSmokeStruct().y,WINDOW_WIDTH,WINDOW_HEIGHT);
		SDL_BlitSurface(smoke, &smokeRect,screen,&screenRect);
	}

}

void	CRender::DrawBugbear(CBugbearMgr *_bugbearMgr)
{
	SDL_Rect bugbearRect;
	SDL_Rect screenRect;
	list<CBugbear *>::iterator it;
	for(it=_bugbearMgr->bugbearList.begin(); it!=_bugbearMgr->bugbearList.end();it++)
	{
		if((*it)->Frame() == 1)		{ RECT(&bugbearRect,0,0,32,32); }
		else
		if((*it)->Frame() == -1)     { RECT(&bugbearRect,32,0,32,32); }
		else
		if((*it)->Frame() == 0)		{ RECT(&bugbearRect,64,0,32,32); }
		RECT(&screenRect,(*it)->GetBugbearStruct().x,
			(*it)->GetBugbearStruct().y,WINDOW_WIDTH,WINDOW_HEIGHT);
		
		SDL_BlitSurface(bugbear, &bugbearRect, screen, &screenRect);
	}
}

void	CRender::DrawShow(CShowMgr * _showMgr )
{
	SDL_Rect showRect;
	SDL_Rect screenRect;
	list<CShow *>::iterator it;
	
	for(it=_showMgr->showList.begin(); it!=_showMgr->showList.end();it++)
	{
		if((*it)->Frame() == 1)		{ RECT(&showRect,0,0,32,32); }
		else
		if((*it)->Frame() == 2)     { RECT(&showRect,32,0,32,32); }
		else
		if((*it)->Frame() == 3)		{ RECT(&showRect,64,0,32,32); }
		else
		if((*it)->Frame() == 4)	{ RECT(&showRect,96,0,32,32);}
		RECT(&screenRect,(*it)->GetShowStruct().x,
			(*it)->GetShowStruct().y,WINDOW_WIDTH,WINDOW_HEIGHT);
		SDL_BlitSurface(show, &showRect, screen, &screenRect);
	}
}


void	CRender::DrawAward(CBugbearMgr *_bugbearMgr)
{
	SDL_Rect awardRect;
	SDL_Rect screenRect;
	if(_bugbearMgr->GetAwardStruct().frame == 1)		{ RECT(&awardRect,0,0,64,64); }
	else
	if(_bugbearMgr->GetAwardStruct().frame == -1)		{ RECT(&awardRect,64,0,64,64); }
	
		RECT(&screenRect,_bugbearMgr->GetAwardStruct().x,
			_bugbearMgr->GetAwardStruct().y,WINDOW_WIDTH,WINDOW_HEIGHT);

		SDL_BlitSurface(award, &awardRect, screen, &screenRect);
}


void	CRender::DrawDialog(int x, int y)
{
	SDL_Rect dialogRect;
	SDL_Rect screenRect;
	RECT(&dialogRect,0,0,192,128);
	RECT(&screenRect,x,
		y,WINDOW_WIDTH,WINDOW_HEIGHT);
		SDL_BlitSurface(dialog,&dialogRect,screen,&screenRect);
}


void	CRender::DrawMenuShade(int _alpha)
{
		SDL_Rect shadeRect;
		SDL_Rect screenRect;
		RECT(&shadeRect,0,0,640,479);
		RECT(&screenRect,0,0,WINDOW_WIDTH,WINDOW_HEIGHT);
		SDL_SetAlpha(menushade,SDL_SRCALPHA,_alpha);
		SDL_BlitSurface(menushade,&shadeRect,screen,&screenRect);
}

void	CRender::DrawCursor(int x, int y)
{
		SDL_Rect cursorRect;
		SDL_Rect screenRect;
		RECT(&cursorRect,0,0,28,31);
		RECT(&screenRect,x,y,WINDOW_WIDTH,WINDOW_HEIGHT);
		SDL_BlitSurface(cursor,&cursorRect,screen,&screenRect);
}

void	CRender::DrawExitButton(int _dx, int _dy, bool _bOn)
{
		SDL_Rect buttonRect;
		SDL_Rect screenRect;
		if(_bOn == false)
		{
			RECT(&buttonRect,0,0,80,34);
		}
		else
		if(_bOn == true)
		{
			RECT(&buttonRect,0,34,80,68);
		}
		RECT(&screenRect,_dx,_dy,WINDOW_WIDTH,WINDOW_HEIGHT);

		SDL_BlitSurface(exitbutton,&buttonRect,screen,&screenRect);


}


void	CRender::DrawExitSelect(void)
{
		SDL_Rect selectRect;
		SDL_Rect screenRect;
		RECT(&selectRect,0,0,80,34);
		RECT(&screenRect,275,195,WINDOW_WIDTH,WINDOW_HEIGHT);
		SDL_BlitSurface(exitselect,&selectRect,screen,&screenRect);

		RECT(&selectRect,0,34,80,34);
		RECT(&screenRect,275,250,WINDOW_WIDTH,WINDOW_HEIGHT);
		SDL_BlitSurface(exitselect,&selectRect,screen,&screenRect);
}		

void	CRender::DrawLogo(int _dx, int _dy, int _alpha)
{
		SDL_Rect logoRect;
		SDL_Rect screenRect;
		RECT(&logoRect,0,0,640,480);
		RECT(&screenRect,_dx,_dy,WINDOW_WIDTH,WINDOW_HEIGHT);
		SDL_SetAlpha(logo,SDL_SRCALPHA,_alpha);
		SDL_BlitSurface(logo,&logoRect,screen,&screenRect);
}

void	CRender::DrawMenuButton(int _dx, int _dy, bool _bOn)
{
		SDL_Rect buttonRect;
		SDL_Rect screenRect;
		if(_bOn == false)
		{
			RECT(&buttonRect,0,0,192,34);
		}
		else
		if(_bOn == true)
		{
			RECT(&buttonRect,0,34,192,68);
		}
		RECT(&screenRect,_dx,_dy,WINDOW_WIDTH,WINDOW_HEIGHT);
		SDL_BlitSurface(menubutton,&buttonRect,screen,&screenRect);
}

void	CRender::DrawMenuSelect(void)
{
		SDL_Rect  selectRect;
		SDL_Rect  screenRect;
		RECT(&selectRect,0,0,192,34);
		RECT(&screenRect,224,206,WINDOW_WIDTH,WINDOW_HEIGHT);
		SDL_BlitSurface(menuselect,&selectRect,screen,&screenRect);
		
		RECT(&selectRect,0,34,192,34);
		RECT(&screenRect,224,256,WINDOW_WIDTH,WINDOW_HEIGHT);
		SDL_BlitSurface(menuselect,&selectRect,screen,&screenRect);
		
		RECT(&selectRect,0,68,192,34);
		RECT(&screenRect,224,306,WINDOW_WIDTH,WINDOW_HEIGHT);
		SDL_BlitSurface(menuselect,&selectRect,screen,&screenRect);
		
}

void	CRender::DrawCredits(int _alpha)
{
		SDL_Rect creditsRect;
		SDL_Rect screenRect;
		RECT(&creditsRect,0,0,640,480);
		RECT(&screenRect,64,0,WINDOW_WIDTH,WINDOW_HEIGHT);
		SDL_SetAlpha(credits,SDL_SRCALPHA,_alpha);
		SDL_BlitSurface(credits,&creditsRect,screen,&screenRect);
}


void	CRender::Changebg(int level)
{
	
		char a[100];
		sprintf(a,"gfx\\background\\bg%d.png",level);
		delete(bg);
		bg = IMG_Load( a );
}
void	CRender::RECT(SDL_Rect *_rect, int x, int y, int w, int h )
{
	_rect->x = x;
	_rect->y = y;
	_rect->w = w;
	_rect->h = h;
}

void CRender::DrawScore(int x, int y, int _score)
{
	int tsc = _score;
	int s[4] ={0};

	s[0] = tsc/1000 ;
	s[1] = (tsc-s[0]*1000)/100;
	s[2] = (tsc-s[0]*1000-s[1]*100)/10;
	s[3] = tsc-s[0]*1000-s[1]*100-s[2]*10;
	
	/*显示分数*/
	SDL_Rect	scoreRect;
	SDL_Rect	screenRect;

	for(int i=0;i<=3;i++)
	{
		for(int j=0;j<=9;j++)
		{
			if(s[i] == j)
			{
				scoreRect.x = j*16;
				scoreRect.y = 0;
				scoreRect.h = 16;
				scoreRect.w = 16;
				screenRect.x = x+i*16;
				screenRect.y = y;
				screenRect.h = 480;
				screenRect.w = 604;
				SDL_BlitSurface(score,&scoreRect,screen,&screenRect);
		
			}
		}
	}

}

void	CRender::DrawScoreBoard(int x, int y, int alpha)
{
		SDL_Rect boardRect;
		SDL_Rect screenRect;
		RECT(&boardRect,0,0,512,480);
		RECT(&screenRect,x,y,WINDOW_WIDTH,WINDOW_HEIGHT);
		SDL_SetAlpha(scoreBoard,SDL_SRCALPHA,alpha);
		SDL_BlitSurface(scoreBoard,&boardRect,screen,&screenRect);
}

void	CRender::DrawFinish(int x, int y, int alpha)
{
		SDL_Rect finishRect;
		SDL_Rect screenRect;
		RECT(&finishRect,0,0,640,480);
		RECT(&screenRect,x,y,WINDOW_WIDTH,WINDOW_HEIGHT);
		SDL_SetAlpha(finish,SDL_SRCALPHA,alpha);
		SDL_BlitSurface(finish,&finishRect,screen,&screenRect);
}

void	CRender::ScreenShot(void)
{
	SDL_SaveBMP(screen,"screenshot\\screen1.bmp");
}