#include		"CManager.h"
#include		<SDL.h>
#include		"EditorInfo.h"
#include		<windows.h>
#include		"LogError.h"
bool	CManager::SysInit(void)
{
		render		= new CRender;
		map			= new CMap;
		input		= new CGetInput;
		
		if ( !render->SysInit() )
		{
	
			return false;
		}
			
		SDL_ShowCursor(SDL_DISABLE);
		return true;
}

bool	CManager::SysRelease(void)
{
	SDL_ShowCursor(SDL_ENABLE);
	if ( !render->SysRelease() )
	{
		return false;
	}
		
	delete render;
	render = NULL;

	delete map;
	map = NULL;
	delete input;
	input = NULL;

	return true;
}

bool	CManager::DataInit(void)
{
	
	return true;
}


void	CManager::DoMessage(void)
{
	SDL_Event event;
	if(SDL_PollEvent(&event))
	{
		switch(event.type)
		{
		case SDL_QUIT:
			state = EXIT_EDITOR;
		}
	}
}

void	CManager::Start(void)
{
	static DWORD lasttick = GetTickCount();
	while(brun)
	{
		DoMessage();
		SDL_Delay(10);
		if(GetTickCount() - lasttick >= 10)
		{
			lasttick = GetTickCount();
		switch(state)
		{
		case INIT_SYS:
			SysInit();
			state = INIT_DATA; 
			break;
		case INIT_DATA:
			
			DataInit();
			state = MAIN_LOOP;
			
			break;
		case MAIN_LOOP:
			
			MainLoop();
			
			break;
		case EXIT_EDITOR:
			SysRelease();
			brun = false;
			break;

		}
		}
	}
}


void	CManager::MainLoop(void)
{
	/*有无菜单*/
	static bool  bmenu = false;

	/*按下m键就激活菜单*/
	if(input->IsKeyDown(SDLK_m))
	{
		bmenu = true;
	}
	if(input->IsKeyDown(SDLK_n))
	{
		bmenu = false;
	}
	if(input->IsKeyDown(SDLK_ESCAPE))
	{
		state = EXIT_EDITOR;
	}


	if(input->IsKeyDown(SDLK_s))
	{
		map->SaveAsFile();
	}

	if(input->IsKeyDown(SDLK_c))
	{
		for(int j=0;j<=MAP_Y-1;j++)
		for(int i=0;i<=MAP_X-1;i++)
		{
			map->map[j][i] = 0;
		}
	}
	/*处理逻辑*/
	
	switch(bmenu)
	{
	case true:
		SelectTile();
		
		break;
	case false:
		EditorMap();
		break;
	}
//鼠标透明显示逻辑
	static bool bcomesoon = false;
	static int curAlpha = 255;
	if(!bcomesoon)
	{

		curAlpha-=5;
		if(curAlpha<=0)
		{
			curAlpha = 0;
			bcomesoon = true;
		}
	}

	else
	if(bcomesoon)
	{
		curAlpha+=5;
		if(curAlpha>=255)
		{
			curAlpha = 255;
			bcomesoon = false;
		}
	}
	render->DrawCursor(0,0,input->GetMousePosx(),input->GetMousePosy(), curAlpha);
	render->UpdateScreen();
}


void	CManager::EditorMap(void)
{
	/*逻辑更新*/
	int x = 0;
	int y = 0;
	input->UpdateMousePos();
	if(input->GetMousePosx()  >= ED_AREA_POSX 
	   &&input->GetMousePosx() < ED_AREA_POSX+ED_AREA_WIDTH
	   &&input->GetMousePosy()>= ED_AREA_POSY
	   &&input->GetMousePosy()< ED_AREA_POSY+ED_AREA_HEIGHT)
	{
		if(input->IsMouseButtonPress(MOUSE_LEFT_BUTTON))
		{
			x = (input->GetMousePosx() - ED_AREA_POSX)/TILE_WIDTH;
			y = (input->GetMousePosy() - ED_AREA_POSY)/TILE_HEIGHT;
			map->map[y][x] = tileStyle;
		}
		else
			if(input->IsMouseButtonPress(MOUSE_RIGHT_BUTTON))
			{
				x = (input->GetMousePosx() - ED_AREA_POSX)/TILE_WIDTH;
			y = (input->GetMousePosy() - ED_AREA_POSY)/TILE_HEIGHT;
				map->map[y][x] = 0;
			}
	}
	/*渲染*/
	render->DrawBG(0,0,0,0,255);
	render->DrawMap(0,0,ED_AREA_POSX,ED_AREA_POSY,255);
	for(int j=0; j<=MAP_Y-1; j++)
	for(int i=0; i<=MAP_X-1; i++)
	{
		switch(map->map[j][i])
		{
			//////////////////////////////////////////////////////////////////////////
		case TILE_9_0_STYLE:
			render->DrawTile(9*TILE_WIDTH,0,ED_AREA_POSX+i*TILE_WIDTH,ED_AREA_POSY+j*TILE_HEIGHT,255);
			break;
		case TILE_10_0_STYLE:
			render->DrawTile(10*TILE_WIDTH,0,ED_AREA_POSX+i*TILE_WIDTH,ED_AREA_POSY+j*TILE_HEIGHT,255);
			break;
		case TILE_11_0_STYLE:
			render->DrawTile(11*TILE_WIDTH,0,ED_AREA_POSX+i*TILE_WIDTH,ED_AREA_POSY+j*TILE_HEIGHT,255);
			break;
		case TILE_12_0_STYLE:
			render->DrawTile(12*TILE_WIDTH,0,ED_AREA_POSX+i*TILE_WIDTH,ED_AREA_POSY+j*TILE_HEIGHT,255);
			break;
		case TILE_13_0_STYLE:
			render->DrawTile(13*TILE_WIDTH,0,ED_AREA_POSX+i*TILE_WIDTH,ED_AREA_POSY+j*TILE_HEIGHT,255);
			break;
		case TILE_14_0_STYLE:
			render->DrawTile(14*TILE_WIDTH,0,ED_AREA_POSX+i*TILE_WIDTH,ED_AREA_POSY+j*TILE_HEIGHT,255);
			break;
		case TILE_15_0_STYLE:
			render->DrawTile(15*TILE_WIDTH,0,ED_AREA_POSX+i*TILE_WIDTH,ED_AREA_POSY+j*TILE_HEIGHT,255);
			break;
		//////////////////////////////////////////////////////////////////////////
				
		case TILE_9_1_STYLE:
			render->DrawTile(9*TILE_WIDTH,1*TILE_HEIGHT,ED_AREA_POSX+i*TILE_WIDTH,ED_AREA_POSY+j*TILE_HEIGHT,255);
			break;
		case TILE_10_1_STYLE:
			render->DrawTile(10*TILE_WIDTH,1*TILE_HEIGHT,ED_AREA_POSX+i*TILE_WIDTH,ED_AREA_POSY+j*TILE_HEIGHT,255);
			break;
		case TILE_11_1_STYLE:
			render->DrawTile(11*TILE_WIDTH,1*TILE_HEIGHT,ED_AREA_POSX+i*TILE_WIDTH,ED_AREA_POSY+j*TILE_HEIGHT,255);
			break;
		case TILE_12_1_STYLE:
			render->DrawTile(12*TILE_WIDTH,1*TILE_HEIGHT,ED_AREA_POSX+i*TILE_WIDTH,ED_AREA_POSY+j*TILE_HEIGHT,255);
			break;
		case TILE_13_1_STYLE:
			render->DrawTile(13*TILE_WIDTH,1*TILE_HEIGHT,ED_AREA_POSX+i*TILE_WIDTH,ED_AREA_POSY+j*TILE_HEIGHT,255);
			break;
		case TILE_14_1_STYLE:
			render->DrawTile(14*TILE_WIDTH,1*TILE_HEIGHT,ED_AREA_POSX+i*TILE_WIDTH,ED_AREA_POSY+j*TILE_HEIGHT,255);
			break;
		case TILE_15_1_STYLE:
			render->DrawTile(15*TILE_WIDTH,1*TILE_HEIGHT,ED_AREA_POSX+i*TILE_WIDTH,ED_AREA_POSY+j*TILE_HEIGHT,255);
			break;
		//////////////////////////////////////////////////////////////////////////
			case TILE_9_2_STYLE:
		    render->DrawTile(9*TILE_WIDTH,2*TILE_HEIGHT,ED_AREA_POSX+i*TILE_WIDTH,ED_AREA_POSY+j*TILE_HEIGHT,255);
			break;
		case TILE_10_2_STYLE:
			render->DrawTile(10*TILE_WIDTH,2*TILE_HEIGHT,ED_AREA_POSX+i*TILE_WIDTH,ED_AREA_POSY+j*TILE_HEIGHT,255);
			break;
		case TILE_11_2_STYLE:
			render->DrawTile(11*TILE_WIDTH,2*TILE_HEIGHT,ED_AREA_POSX+i*TILE_WIDTH,ED_AREA_POSY+j*TILE_HEIGHT,255);
			break;
		case TILE_12_2_STYLE:
			render->DrawTile(12*TILE_WIDTH,2*TILE_HEIGHT,ED_AREA_POSX+i*TILE_WIDTH,ED_AREA_POSY+j*TILE_HEIGHT,255);
			break;
		case TILE_13_2_STYLE:
			render->DrawTile(13*TILE_WIDTH,2*TILE_HEIGHT,ED_AREA_POSX+i*TILE_WIDTH,ED_AREA_POSY+j*TILE_HEIGHT,255);
			break;
		case TILE_14_2_STYLE:
			render->DrawTile(14*TILE_WIDTH,2*TILE_HEIGHT,ED_AREA_POSX+i*TILE_WIDTH,ED_AREA_POSY+j*TILE_HEIGHT,255);
			break;
		case TILE_15_2_STYLE:
			render->DrawTile(15*TILE_WIDTH,2*TILE_HEIGHT,ED_AREA_POSX+i*TILE_WIDTH,ED_AREA_POSY+j*TILE_HEIGHT,255);
			break;
		//////////////////////////////////////////////////////////////////////////
		case TILE_9_3_STYLE:
			render->DrawTile(9*TILE_WIDTH,3*TILE_HEIGHT,ED_AREA_POSX+i*TILE_WIDTH,ED_AREA_POSY+j*TILE_HEIGHT,255);
			break;
		case TILE_10_3_STYLE:
			render->DrawTile(10*TILE_WIDTH,3*TILE_HEIGHT,ED_AREA_POSX+i*TILE_WIDTH,ED_AREA_POSY+j*TILE_HEIGHT,255);
			break;
		case TILE_11_3_STYLE:
			render->DrawTile(11*TILE_WIDTH,3*TILE_HEIGHT,ED_AREA_POSX+i*TILE_WIDTH,ED_AREA_POSY+j*TILE_HEIGHT,255);
			break;
		case TILE_12_3_STYLE:
			render->DrawTile(12*TILE_WIDTH,3*TILE_HEIGHT,ED_AREA_POSX+i*TILE_WIDTH,ED_AREA_POSY+j*TILE_HEIGHT,255);
			break;
		case TILE_13_3_STYLE:
			render->DrawTile(13*TILE_WIDTH,3*TILE_HEIGHT,ED_AREA_POSX+i*TILE_WIDTH,ED_AREA_POSY+j*TILE_HEIGHT,255);
			break;
		case TILE_14_3_STYLE:
			render->DrawTile(14*TILE_WIDTH,3*TILE_HEIGHT,ED_AREA_POSX+i*TILE_WIDTH,ED_AREA_POSY+j*TILE_HEIGHT,255);
			break;
		case TILE_15_3_STYLE:
			render->DrawTile(15*TILE_WIDTH,3*TILE_HEIGHT,ED_AREA_POSX+i*TILE_WIDTH,ED_AREA_POSY+j*TILE_HEIGHT,255);
			break;
		//////////////////////////////////////////////////////////////////////////
		case TILE_9_4_STYLE:
			render->DrawTile(9*TILE_WIDTH,4*TILE_HEIGHT,ED_AREA_POSX+i*TILE_WIDTH,ED_AREA_POSY+j*TILE_HEIGHT,255);
			break;
		case TILE_10_4_STYLE:
			render->DrawTile(10*TILE_WIDTH,4*TILE_HEIGHT,ED_AREA_POSX+i*TILE_WIDTH,ED_AREA_POSY+j*TILE_HEIGHT,255);
			break;
		case TILE_11_4_STYLE:
			render->DrawTile(11*TILE_WIDTH,4*TILE_HEIGHT,ED_AREA_POSX+i*TILE_WIDTH,ED_AREA_POSY+j*TILE_HEIGHT,255);
			break;
		case TILE_12_4_STYLE:
			render->DrawTile(12*TILE_WIDTH,4*TILE_HEIGHT,ED_AREA_POSX+i*TILE_WIDTH,ED_AREA_POSY+j*TILE_HEIGHT,255);
			break;
		case TILE_13_4_STYLE:
			render->DrawTile(13*TILE_WIDTH,4*TILE_HEIGHT,ED_AREA_POSX+i*TILE_WIDTH,ED_AREA_POSY+j*TILE_HEIGHT,255);
			break;
		case TILE_14_4_STYLE:
			render->DrawTile(14*TILE_WIDTH,4*TILE_HEIGHT,ED_AREA_POSX+i*TILE_WIDTH,ED_AREA_POSY+j*TILE_HEIGHT,255);
			break;
		case TILE_15_4_STYLE:
			render->DrawTile(15*TILE_WIDTH,4*TILE_HEIGHT,ED_AREA_POSX+i*TILE_WIDTH,ED_AREA_POSY+j*TILE_HEIGHT,255);
			break;
		//////////////////////////////////////////////////////////////////////////
		case TILE_9_5_STYLE:
			render->DrawTile(9*TILE_WIDTH,5*TILE_HEIGHT,ED_AREA_POSX+i*TILE_WIDTH,ED_AREA_POSY+j*TILE_HEIGHT,255);
			break;
		case TILE_10_5_STYLE:
			render->DrawTile(10*TILE_WIDTH,5*TILE_HEIGHT,ED_AREA_POSX+i*TILE_WIDTH,ED_AREA_POSY+j*TILE_HEIGHT,255);
			break;
		case TILE_11_5_STYLE:
			render->DrawTile(11*TILE_WIDTH,5*TILE_HEIGHT,ED_AREA_POSX+i*TILE_WIDTH,ED_AREA_POSY+j*TILE_HEIGHT,255);
			break;
		case TILE_12_5_STYLE:
			render->DrawTile(12*TILE_WIDTH,5*TILE_HEIGHT,ED_AREA_POSX+i*TILE_WIDTH,ED_AREA_POSY+j*TILE_HEIGHT,255);
			break;
		case TILE_13_5_STYLE:
			render->DrawTile(13*TILE_WIDTH,5*TILE_HEIGHT,ED_AREA_POSX+i*TILE_WIDTH,ED_AREA_POSY+j*TILE_HEIGHT,255);
			break;
		case TILE_14_5_STYLE:
			render->DrawTile(14*TILE_WIDTH,5*TILE_HEIGHT,ED_AREA_POSX+i*TILE_WIDTH,ED_AREA_POSY+j*TILE_HEIGHT,255);
			break;
		case TILE_15_5_STYLE:
			render->DrawTile(15*TILE_WIDTH,5*TILE_HEIGHT,ED_AREA_POSX+i*TILE_WIDTH,ED_AREA_POSY+j*TILE_HEIGHT,255);
			break;
		//////////////////////////////////////////////////////////////////////////
		case TILE_9_6_STYLE:
			render->DrawTile(9*TILE_WIDTH,6*TILE_HEIGHT,ED_AREA_POSX+i*TILE_WIDTH,ED_AREA_POSY+j*TILE_HEIGHT,255);
			break;
		case TILE_10_6_STYLE:
			render->DrawTile(10*TILE_WIDTH,6*TILE_HEIGHT,ED_AREA_POSX+i*TILE_WIDTH,ED_AREA_POSY+j*TILE_HEIGHT,255);
			break;
		case TILE_11_6_STYLE:
			render->DrawTile(11*TILE_WIDTH,6*TILE_HEIGHT,ED_AREA_POSX+i*TILE_WIDTH,ED_AREA_POSY+j*TILE_HEIGHT,255);
			break;
		case TILE_12_6_STYLE:
			render->DrawTile(12*TILE_WIDTH,6*TILE_HEIGHT,ED_AREA_POSX+i*TILE_WIDTH,ED_AREA_POSY+j*TILE_HEIGHT,255);
			break;
		case TILE_13_6_STYLE:
			render->DrawTile(13*TILE_WIDTH,6*TILE_HEIGHT,ED_AREA_POSX+i*TILE_WIDTH,ED_AREA_POSY+j*TILE_HEIGHT,255);
			break;
		case TILE_14_6_STYLE:
			render->DrawTile(14*TILE_WIDTH,6*TILE_HEIGHT,ED_AREA_POSX+i*TILE_WIDTH,ED_AREA_POSY+j*TILE_HEIGHT,255);
			break;
		case TILE_15_6_STYLE:
			render->DrawTile(15*TILE_WIDTH,6*TILE_HEIGHT,ED_AREA_POSX+i*TILE_WIDTH,ED_AREA_POSY+j*TILE_HEIGHT,255);
			break;
		//////////////////////////////////////////////////////////////////////////
		default:
			break;
		}
	}

	if(input->GetMousePosx()  >= ED_AREA_POSX 
	   &&input->GetMousePosx() < ED_AREA_POSX+ED_AREA_WIDTH
	   &&input->GetMousePosy()>= ED_AREA_POSY
	   &&input->GetMousePosy()< ED_AREA_POSY+ED_AREA_HEIGHT)
	   {
			x = (input->GetMousePosx() - ED_AREA_POSX)/TILE_WIDTH;
			y = (input->GetMousePosy() - ED_AREA_POSY)/TILE_HEIGHT;
			render->DrawSelectGrid(0,0,ED_AREA_POSX+x*TILE_WIDTH,ED_AREA_POSY+y*TILE_HEIGHT,100);
		}
}




void	CManager::SelectTile(void)
{
	int x;
	int y;
	input->UpdateMousePos();
	if(input->IsMouseButtonPress(MOUSE_LEFT_BUTTON))
	{
		x = (input->GetMousePosx()-TILES_POSX)/TILE_WIDTH;
		y = (input->GetMousePosy()-TILES_POSY)/TILE_HEIGHT;
	
	
	/*判断是选择那种tile style*/
		switch(y)
		{
		case 0:
			if(x == 9)	{ tileStyle = 1;}
			if(x == 10) { tileStyle = 2;}
			if(x == 11) { tileStyle = 3;}
			if(x == 12) { tileStyle = 4;}
			if(x == 13) { tileStyle = 5;}
			if(x == 14) { tileStyle = 6;}
			if(x == 15) { tileStyle = 7;}
			break;
		case 1:
			if(x == 9)	{ tileStyle = 8;}
			if(x == 10) { tileStyle = 9;}
			if(x == 11) { tileStyle = 10;}
			if(x == 12) { tileStyle = 11;}
			if(x == 13) { tileStyle = 12;}
			if(x == 14) { tileStyle = 13;}
			if(x == 15) { tileStyle = 14;}
			break;
		case 2:
			if(x == 9)	{ tileStyle = 15;}
			if(x == 10) { tileStyle = 16;}
			if(x == 11) { tileStyle = 17;}
			if(x == 12) { tileStyle = 18;}
			if(x == 13) { tileStyle = 19;}
			if(x == 14) { tileStyle = 20;}
			if(x == 15) { tileStyle = 21;}
			break;
		case 3:
			if(x == 9)	{ tileStyle = 22;}
			if(x == 10) { tileStyle = 23;}
			if(x == 11) { tileStyle = 24;}
			if(x == 12) { tileStyle = 25;}
			if(x == 13) { tileStyle = 26;}
			if(x == 14) { tileStyle = 27;}
			if(x == 15) { tileStyle = 28;}
			break;
		case 4:
			if(x == 9)	{ tileStyle = 29;}
			if(x == 10) { tileStyle = 30;}
			if(x == 11) { tileStyle = 31;}
			if(x == 12) { tileStyle = 32;}
			if(x == 13) { tileStyle = 33;}
			if(x == 14) { tileStyle = 34;}
			if(x == 15) { tileStyle = 35;}
			break;
		case 5:
			if(x == 9)	{ tileStyle = 36;}
			if(x == 10) { tileStyle = 37;}
			if(x == 11) { tileStyle = 38;}
			if(x == 12) { tileStyle = 39;}
			if(x == 13) { tileStyle = 40;}
			if(x == 14) { tileStyle = 41;}
			if(x == 15) { tileStyle = 42;}
			break;
		case 6:
			if(x == 9)	{ tileStyle = 43;}
			if(x == 10) { tileStyle = 44;}
			if(x == 11) { tileStyle = 45;}
			if(x == 12) { tileStyle = 46;}
			if(x == 13) { tileStyle = 47;}
			if(x == 14) { tileStyle = 48;}
			if(x == 15) { tileStyle = 49;}
			break;
		}
	
	}
	/*渲染*/
	render->DrawBG(0,0,0,0,255);
	render->DrawMap(0,0,ED_AREA_POSX,ED_AREA_POSY,255);
	/*
	for(int j=0; j<=MAP_Y-1; j++)
	for(int i=0; i<=MAP_X-1; i++)
	{
		switch(map->map[j][i])
		{
		case TILE_GOLDBLOCK_STYLE:
			render->DrawTile(9*TILE_WIDTH,0,ED_AREA_POSX+i*TILE_WIDTH,ED_AREA_POSY+j*TILE_HEIGHT,255);
			break;
		case TILE_WHITEBLOCK_STYLE:
			render->DrawTile(10*TILE_WIDTH,0,ED_AREA_POSX+i*TILE_WIDTH,ED_AREA_POSY+j*TILE_HEIGHT,255);
			break;
		case TILE_WHAT_STYLE:
			render->DrawTile(11*TILE_WIDTH,0,ED_AREA_POSX+i*TILE_WIDTH,ED_AREA_POSY+j*TILE_HEIGHT,255);
			break;
		case TILE_MUSIC_STYLE:
			render->DrawTile(12*TILE_WIDTH,0,ED_AREA_POSX+i*TILE_WIDTH,ED_AREA_POSY+j*TILE_HEIGHT,255);
			break;
		default:
			break;
		}
	}
*/
	render->DrawTile(TILES_POSX,TILES_POSY,255);
	if(input->GetMousePosx() < TILES_POSX+TILES_WIDTH 
		&& input->GetMousePosy() <TILES_POSY+TILES_HEIGHT
		&& input->GetMousePosx()>= TILES_POSX
		&& input->GetMousePosy()>= TILES_POSY)
	{
		render->DrawSelectGrid(0,0,TILES_POSX+x*TILE_WIDTH,TILES_POSY+y*TILE_HEIGHT,100);
	}

}