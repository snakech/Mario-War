#include		"CRender.h"
#include		"EditorInfo.h"
#include		<SDL.h>
#include		"LogError.h"
bool	CRender::SysInit(void)
{
	if( SDL_Init(SDL_INIT_VIDEO) < 0 )
	{
		printf("SDL init false!\n");
		return false;
	}

	else
	{
		printf("SDL init <done>\n");
	}
	
	atexit(0);

	screen = SDL_SetVideoMode( 640, 480, 16, SDL_SWSURFACE);

	if(screen == NULL)
	{
		
		printf("SDL can't run in 640*480*16\n ");
		return false;
	}

	else
	{
		printf("run at 640*480*16 <done>\n");
	}


	/*◊ ‘¥‘ÿ»Î*/
	
	tiles = SDL_LoadBMP("gfx\\tiles.bmp");
	if(tiles != NULL)
	{
		printf("load gfx\\tiles.bmp... <done>\n");
	}
	SDL_SetColorKey(tiles, SDL_SRCCOLORKEY ,SDL_MapRGB(tiles->format,255,0,255));
	bg = SDL_LoadBMP("gfx\\bg.bmp");
	if(bg != NULL)
	{
		printf("load gfx\\bg.bmp... <done>\n");
	}
	selectGrid  = SDL_LoadBMP("gfx\\selectgrid.bmp");
	if(selectGrid != NULL)
	{
		printf("load gfx\\selectgrid.bmp... <done>\n");
	}
	SDL_SetColorKey(selectGrid, SDL_SRCCOLORKEY ,SDL_MapRGB(selectGrid->format,0,0,0));
	
	map = SDL_LoadBMP("gfx\\map.bmp");
    

	cursor = SDL_LoadBMP("gfx\\cur.bmp");
	if(cursor != NULL)
	{
		printf("load gfx\\cur.bmp... <done>\n");

	}

	SDL_SetColorKey(cursor, SDL_SRCCOLORKEY ,SDL_MapRGB(cursor->format,0,0,0));
	
	return true;
}

bool	CRender::SysRelease(void)
{
	SDL_FreeSurface(tiles);
	SDL_FreeSurface(bg);
	SDL_FreeSurface(selectGrid);
	SDL_FreeSurface(map);
	SDL_FreeSurface(cursor);
	return true;
}

bool	CRender::DataInit(void) { return true; }


void	CRender::DrawBG( int _sx, int _sy, int _dx, int _dy, int _alpha )
{
	SDL_Rect	bgRect;
	SDL_Rect	screenRect;

	bgRect.x = _sx;
	bgRect.y = _sy;
	bgRect.w = WINDOW_WIDTH;
	bgRect.h = WINDOW_HEIGHT;

	screenRect.x = _dx;
	screenRect.y = _dy;
	screenRect.w = WINDOW_WIDTH;
	screenRect.h = WINDOW_HEIGHT;
	SDL_SetAlpha(bg, SDL_SRCALPHA, _alpha);
	SDL_BlitSurface( bg, &bgRect, screen, &screenRect );
}

void	CRender::DrawTile( int _sx, int _sy, int _dx, int _dy, int _alpha )
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

void	CRender::DrawSelectGrid( int _sx, int _sy, int _dx, int _dy, int _alpha )
{
	SDL_Rect	selectGridRect;
	SDL_Rect	screenRect;

	selectGridRect.x = _sx;
	selectGridRect.y = _sy;
	selectGridRect.w = TILE_WIDTH;
	selectGridRect.h = TILE_HEIGHT;

	screenRect.x = _dx;
	screenRect.y = _dy;
	screenRect.w = WINDOW_WIDTH;
	screenRect.h = WINDOW_HEIGHT;
	SDL_SetAlpha(selectGrid, SDL_SRCALPHA, _alpha);
	SDL_BlitSurface( selectGrid, &selectGridRect, screen, &screenRect );
}


void	CRender::DrawTile( int _dx, int _dy, int _alpha)
{
	SDL_Rect	tileRect;
	SDL_Rect	screenRect;

	tileRect.x = 0;
	tileRect.y = 0;
	tileRect.w = TILES_WIDTH;
	tileRect.h = TILES_HEIGHT;

	screenRect.x = _dx;
	screenRect.y = _dy;
	screenRect.w = WINDOW_WIDTH;
	screenRect.h = WINDOW_HEIGHT;
	SDL_SetAlpha(tiles, SDL_SRCALPHA, _alpha);
	SDL_BlitSurface( tiles, &tileRect, screen, &screenRect );
}

void	CRender::DrawMap( int _sx, int _sy, int _dx, int _dy, int _alpha )
{
	SDL_Rect	mapRect;
	SDL_Rect	screenRect;

	mapRect.x = _sx;
	mapRect.y = _sy;
	mapRect.w = ED_AREA_WIDTH;
	mapRect.h = ED_AREA_HEIGHT;

	screenRect.x = _dx;
	screenRect.y = _dy;
	screenRect.w = WINDOW_WIDTH;
	screenRect.h = WINDOW_HEIGHT;
	SDL_SetAlpha(map, SDL_SRCALPHA, _alpha);
	SDL_BlitSurface( map, &mapRect, screen, &screenRect );
}


void	CRender::DrawCursor(int _sx, int _sy, int _dx, int _dy, int _alpha)
{
	SDL_Rect	cursorRect;
	SDL_Rect	screenRect;

	cursorRect.x = _sx;
	cursorRect.y = _sy;
	cursorRect.w = TILE_WIDTH;
	cursorRect.h = TILE_HEIGHT;

	screenRect.x = _dx;
	screenRect.y = _dy;
	screenRect.w = WINDOW_WIDTH;
	screenRect.h = WINDOW_HEIGHT;
	SDL_SetAlpha(cursor, SDL_SRCALPHA, _alpha);
	SDL_BlitSurface( cursor, &cursorRect, screen, &screenRect );

}

void	CRender::UpdateScreen(void)
{
	SDL_UpdateRect(screen, 0, 0, 0, 0);
}
