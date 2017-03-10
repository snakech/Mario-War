#include		"CGameMgr.h"
#include		"GameInfo.h"
#include		<windows.h>
#include		<SDL.h>
#include		<SDL_image.h>
#include		"GetKeyInput.h"
#include		"CMap.h"
#include		"CShowMgr.h"
#include		"AudiereManager.h"
#include		"LogError.h"
CGameMgr::CGameMgr(void)
{
	render		= new CRender;
	mario		= new CMario; 
	map			= new CMap;
	smokeMgr	= new CRunSmokeMgr; 
	bugbearMgr	= new CBugbearMgr(map);
	showMgr		= new CShowMgr;
	guiMgr		= new CGUIMgr;	
	audioMgr	= new CAudioMgr;
	scoreBoard	= new CScoreBoard;
	brun		= true;
	state		= GAME_INIT;  
	level		= 1;
	pause		= 1;
	curpos.x	= 0;
	curpos.y	= 0;
	//logo的初试化信息
	logo.x = 0;
	logo.y = 0;
	logo.alpha = 0;
	logo.bIn = true;
	//credits
	credits.x = 64;
	credits.y = 0;
	credits.alpha = 0;
	credits.bIn =true;
	//finish
	finish.x = 0;
	finish.y = 0;
	finish.alpha = 0;
	finish.bIn = true;
	//timer
	timer = 200;
	tick = GetTickCount();
		
}

CGameMgr::~CGameMgr(void)
{
	delete	render;
	delete  mario;
	delete  map;
	delete  smokeMgr;
	delete  bugbearMgr;
	delete  showMgr;
	delete  guiMgr;
	delete  audioMgr;
	delete	scoreBoard;
	
}

bool	CGameMgr::Init(void)
{	
	
	render->SysInit();
	
	return true;
}

bool	CGameMgr::Release(void)
{
	render->SysRelease();
	audioMgr->instance->Release();
	return true;
}

void	CGameMgr::DoMessage(void)
{
	SDL_Event event;
	if(SDL_PollEvent(&event))
	{
		switch(event.type)
		{
		case SDL_QUIT:
			brun = false;
			break;
		}
	}
}
bool	CGameMgr::Start(void)
{
	
	static DWORD	lasttick = GetTickCount();
	static	list<CBugbear *>::iterator it;
	while(brun)
	{
		if(IsKeyDown(VK_F11))
		{
			render->ScreenShot();
		}
		/*处理SDL消息*/
		DoMessage();
			
			switch(state)
			{
			case	GAME_INIT:
				Init();
				state = GAME_LOGO;
				break;
			case	GAME_LOGO:
				audioMgr->PlayFinish(false,false);
				GameLogo();				        	//游戏logo
				break;
			case	GAME_MENU:
				mario->Init();// = 0;
				timer = TIMER;
				audioMgr->PlayCredits(false,false);
				audioMgr->PlayMenu(true,true);
				GameMenu();
				break;
			case	GAME_CREDITS:
				mario->Init();// = 0;
			
				audioMgr->PlayMenu(false,false);
				audioMgr->PlayCredits(true,true);
				GameCredits();
				break;
			case	GAME_SCOREBOARD:
				scoreBoard->ShowScoreBoard(render,&state,mario);
				break;
			case	LOAD_LEVEL:
				
				for(it=bugbearMgr->bugbearList.begin(); it!=bugbearMgr->bugbearList.end(); it++)
				{
						delete(*it);
						it = bugbearMgr->bugbearList.erase(it);
				}
				LoadLevel(level);
				mario->Init();
				timer = TIMER;					//载入新的关卡数据，包括地图数据，人物
				state = GAME_MAIN;
				break;
			case	GAME_MAIN:
				
				audioMgr->PlayMenu(false,false);	
				audioMgr->PlayBM(true,true);
				
				GameLoop();
				break;
			case	GAME_FINISH:
				GameFinish();
				break;
			case	GAME_EXIT:
				brun = false;
			}
//		}
	}

	return false;
}


void	CGameMgr::GameLoop(void)
{
	
	SDL_ShowCursor(SDL_DISABLE);
	if(IsKeyDown(VK_ESCAPE))
	{
		Sleep(200);		
		pause = -1;
		
	}

	if(pause == 1)
	{
		UpdateLogic();
	}
	else
	{	
		//   "退出GUI"
		int x;
		int y;
		GetMousePos(&x,&y);
		GetMousePos(&curpos.x,&curpos.y);
		/*鼠标移动到yes按钮上*/
		if(x>=guiMgr->GetExitYes().rect.x && x<=guiMgr->GetExitYes().rect.x2
			&&y>=guiMgr->GetExitYes().rect.y && y<=guiMgr->GetExitYes().rect.y2)
		{
			guiMgr->SetExitYes(true);	
			if( PressLeftButton(&x, &y) )
			{
				state = GAME_MENU;
				/*清除游戏数据为开始的样式*/
				audioMgr->PlayBM(false,false);
				pause = 1;
				level = 1;
				mario->Init();
				map->LoadMap(1);
				render->Changebg(1);
				bugbearMgr->Init();
				list<CBugbear *>::iterator it;
				for(it=bugbearMgr->bugbearList.begin(); it!=bugbearMgr->bugbearList.end(); it++)
				{
						delete(*it);
						it = bugbearMgr->bugbearList.erase(it);
				}
				Sleep(200);
			}
		}
		else
		{
			guiMgr->SetExitYes(false);
		}
		/*鼠标移动到no按钮上*/
		if(x>=guiMgr->GetExitNo().rect.x && x<=guiMgr->GetExitNo().rect.x2
			&&y>=guiMgr->GetExitNo().rect.y && y<=guiMgr->GetExitNo().rect.y2)
		{
			guiMgr->SetExitNo(true);
			if( PressLeftButton(&x, &y) )
			{
				pause = 1;
			}
		}
		else
		{
			guiMgr->SetExitNo(false);
		}

		
		
	}
	

	Render();
	render->UpdateScreen();

}	

void	CGameMgr::UpdateLogic(void)
{

			
			/*关卡转换逻辑 */
			if(GetTickCount() - tick >= 800)
			{
				tick = GetTickCount();
				if(timer == 10)
				{
					audioMgr->PlayBM(false,false);
					audioMgr->PlayWarning();
					Sleep(3000);
				}
				if(timer<=0)
				{
					if(mario->score >= SCORE_PASS)
					{
						/*发出胜利的声音*/
						audioMgr->PlayBM(false,false);
						audioMgr->PlayWin();
						level++;
						
						bugbearMgr->SetMax((level+1)/2);
						bugbearMgr->SetBugTick(3000);
						/*判断是否是最后一关过关*/
						if(level > MAP_NUM)
						{
							state = GAME_FINISH;
							level = 1;
						}
						else
						{
							state = GAME_SCOREBOARD;//LOAD_LEVEL;
						}
						Sleep(7000);
					}
					else
					{
						/*发出失败的声音*/
						audioMgr->PlayBM(false, false);
						audioMgr->PlayOver();
						state = GAME_SCOREBOARD;//LOAD_LEVEL;
						audioMgr->PlayBM(false,false);
						Sleep(7000);
					}
				}
				timer--;
			}

			
	
			if(!mario->GetLife())
			{
				static DWORD lasttick = GetTickCount();
				if(GetTickCount() - lasttick >= 10)
				{
					lasttick = GetTickCount();
					mario->UpdateLogic(audioMgr);
				}
			}
			if(mario->GetLife())
			{
				mario->UpdateLogic(audioMgr);
				mario->Collision(map,audioMgr);
			
				mario->CollisionBugbear(bugbearMgr,audioMgr,map);
			}


	if(!mario->GetLife())
	{
		mario->SetFrame(MARIO_r5);
		if(mario->GetMarioData().y>=480)
		{
			mario->SetLife(1);
			while(1)
					{
						int x = rand()%MAP_X-1;
						int y = rand()%MAP_Y-1;
						if(map->maps[y][x] == 0)
						{
							mario->SetDxDy(0.0f,-10.0f);
							mario->SetFrame(MARIO_r3);
							mario->SetPos(x*32, y*32);  
							break;
						}
					}
		}
	}

	
	
	//新产生东西
	static lasttick = GetTickCount();
	if(GetTickCount() - lasttick >= 100)
	{
		lasttick = GetTickCount();
		smokeMgr->Add(mario);
		
	//	if( bugbearMgr->bugbearList.size() <=2)
	//	{
			
	//		bugbearMgr->Add(map);
	//	}
	}
	showMgr->Add(bugbearMgr);
	//更新东西

		showMgr->BroseList();
		smokeMgr->BroseList();
		bugbearMgr->AwardLogic(map);	
		bugbearMgr->BroseList(map);
		
}

void	CGameMgr::Render(void)
{
	render->DrawBG();
	render->DrawAward(bugbearMgr);
	for(int j=0; j<=MAP_Y-1; j++)
	for(int i=0; i<=MAP_X-1; i++)
	{
		switch(map->maps[j][i])
		{
			//////////////////////////////////////////////////////////////////////////
		case TILE_9_0_STYLE:
			render->DrawTile(0,0,ED_AREA_POSX+i*TILE_WIDTH,ED_AREA_POSY+j*TILE_HEIGHT,255);
			break;
		case TILE_10_0_STYLE:
			render->DrawTile(1*TILE_WIDTH,0,ED_AREA_POSX+i*TILE_WIDTH,ED_AREA_POSY+j*TILE_HEIGHT,255);
			break;
		case TILE_11_0_STYLE:
			render->DrawTile(2*TILE_WIDTH,0,ED_AREA_POSX+i*TILE_WIDTH,ED_AREA_POSY+j*TILE_HEIGHT,255);
			break;
		case TILE_12_0_STYLE:
			render->DrawTile(3*TILE_WIDTH,0,ED_AREA_POSX+i*TILE_WIDTH,ED_AREA_POSY+j*TILE_HEIGHT,255);
			break;
		case TILE_13_0_STYLE:
			render->DrawTile(4*TILE_WIDTH,0,ED_AREA_POSX+i*TILE_WIDTH,ED_AREA_POSY+j*TILE_HEIGHT,255);
			break;
		case TILE_14_0_STYLE:
			render->DrawTile(5*TILE_WIDTH,0,ED_AREA_POSX+i*TILE_WIDTH,ED_AREA_POSY+j*TILE_HEIGHT,255);
			break;
		case TILE_15_0_STYLE:
			render->DrawTile(6*TILE_WIDTH,0,ED_AREA_POSX+i*TILE_WIDTH,ED_AREA_POSY+j*TILE_HEIGHT,255);
			break;
		//////////////////////////////////////////////////////////////////////////
				
		case TILE_9_1_STYLE:
			render->DrawTile(0*TILE_WIDTH,1*TILE_HEIGHT,ED_AREA_POSX+i*TILE_WIDTH,ED_AREA_POSY+j*TILE_HEIGHT,255);
			break;
		case TILE_10_1_STYLE:
			render->DrawTile(1*TILE_WIDTH,1*TILE_HEIGHT,ED_AREA_POSX+i*TILE_WIDTH,ED_AREA_POSY+j*TILE_HEIGHT,255);
			break;
		case TILE_11_1_STYLE:
			render->DrawTile(2*TILE_WIDTH,1*TILE_HEIGHT,ED_AREA_POSX+i*TILE_WIDTH,ED_AREA_POSY+j*TILE_HEIGHT,255);
			break;
		case TILE_12_1_STYLE:
			render->DrawTile(3*TILE_WIDTH,1*TILE_HEIGHT,ED_AREA_POSX+i*TILE_WIDTH,ED_AREA_POSY+j*TILE_HEIGHT,255);
			break;
		case TILE_13_1_STYLE:
			render->DrawTile(4*TILE_WIDTH,1*TILE_HEIGHT,ED_AREA_POSX+i*TILE_WIDTH,ED_AREA_POSY+j*TILE_HEIGHT,255);
			break;
		case TILE_14_1_STYLE:
			render->DrawTile(5*TILE_WIDTH,1*TILE_HEIGHT,ED_AREA_POSX+i*TILE_WIDTH,ED_AREA_POSY+j*TILE_HEIGHT,255);
			break;
		case TILE_15_1_STYLE:
			render->DrawTile(6*TILE_WIDTH,1*TILE_HEIGHT,ED_AREA_POSX+i*TILE_WIDTH,ED_AREA_POSY+j*TILE_HEIGHT,255);
			break;
		//////////////////////////////////////////////////////////////////////////
			case TILE_9_2_STYLE:
		    render->DrawTile(0*TILE_WIDTH,2*TILE_HEIGHT,ED_AREA_POSX+i*TILE_WIDTH,ED_AREA_POSY+j*TILE_HEIGHT,255);
			break;
		case TILE_10_2_STYLE:
			render->DrawTile(1*TILE_WIDTH,2*TILE_HEIGHT,ED_AREA_POSX+i*TILE_WIDTH,ED_AREA_POSY+j*TILE_HEIGHT,255);
			break;
		case TILE_11_2_STYLE:
			render->DrawTile(2*TILE_WIDTH,2*TILE_HEIGHT,ED_AREA_POSX+i*TILE_WIDTH,ED_AREA_POSY+j*TILE_HEIGHT,255);
			break;
		case TILE_12_2_STYLE:
			render->DrawTile(3*TILE_WIDTH,2*TILE_HEIGHT,ED_AREA_POSX+i*TILE_WIDTH,ED_AREA_POSY+j*TILE_HEIGHT,255);
			break;
		case TILE_13_2_STYLE:
			render->DrawTile(4*TILE_WIDTH,2*TILE_HEIGHT,ED_AREA_POSX+i*TILE_WIDTH,ED_AREA_POSY+j*TILE_HEIGHT,255);
			break;
		case TILE_14_2_STYLE:
			render->DrawTile(5*TILE_WIDTH,2*TILE_HEIGHT,ED_AREA_POSX+i*TILE_WIDTH,ED_AREA_POSY+j*TILE_HEIGHT,255);
			break;
		case TILE_15_2_STYLE:
			render->DrawTile(6*TILE_WIDTH,2*TILE_HEIGHT,ED_AREA_POSX+i*TILE_WIDTH,ED_AREA_POSY+j*TILE_HEIGHT,255);
			break;
		//////////////////////////////////////////////////////////////////////////
		case TILE_9_3_STYLE:
			render->DrawTile(0*TILE_WIDTH,3*TILE_HEIGHT,ED_AREA_POSX+i*TILE_WIDTH,ED_AREA_POSY+j*TILE_HEIGHT,255);
			break;
		case TILE_10_3_STYLE:
			render->DrawTile(1*TILE_WIDTH,3*TILE_HEIGHT,ED_AREA_POSX+i*TILE_WIDTH,ED_AREA_POSY+j*TILE_HEIGHT,255);
			break;
		case TILE_11_3_STYLE:
			render->DrawTile(2*TILE_WIDTH,3*TILE_HEIGHT,ED_AREA_POSX+i*TILE_WIDTH,ED_AREA_POSY+j*TILE_HEIGHT,255);
			break;
		case TILE_12_3_STYLE:
			render->DrawTile(3*TILE_WIDTH,3*TILE_HEIGHT,ED_AREA_POSX+i*TILE_WIDTH,ED_AREA_POSY+j*TILE_HEIGHT,255);
			break;
		case TILE_13_3_STYLE:
			render->DrawTile(4*TILE_WIDTH,3*TILE_HEIGHT,ED_AREA_POSX+i*TILE_WIDTH,ED_AREA_POSY+j*TILE_HEIGHT,255);
			break;
		case TILE_14_3_STYLE:
			render->DrawTile(5*TILE_WIDTH,3*TILE_HEIGHT,ED_AREA_POSX+i*TILE_WIDTH,ED_AREA_POSY+j*TILE_HEIGHT,255);
			break;
		case TILE_15_3_STYLE:
			render->DrawTile(6*TILE_WIDTH,3*TILE_HEIGHT,ED_AREA_POSX+i*TILE_WIDTH,ED_AREA_POSY+j*TILE_HEIGHT,255);
			break;
		//////////////////////////////////////////////////////////////////////////
		case TILE_9_4_STYLE:
			render->DrawTile(0*TILE_WIDTH,4*TILE_HEIGHT,ED_AREA_POSX+i*TILE_WIDTH,ED_AREA_POSY+j*TILE_HEIGHT,255);
			break;
		case TILE_10_4_STYLE:
			render->DrawTile(1*TILE_WIDTH,4*TILE_HEIGHT,ED_AREA_POSX+i*TILE_WIDTH,ED_AREA_POSY+j*TILE_HEIGHT,255);
			break;
		case TILE_11_4_STYLE:
			render->DrawTile(2*TILE_WIDTH,4*TILE_HEIGHT,ED_AREA_POSX+i*TILE_WIDTH,ED_AREA_POSY+j*TILE_HEIGHT,255);
			break;
		case TILE_12_4_STYLE:
			render->DrawTile(3*TILE_WIDTH,4*TILE_HEIGHT,ED_AREA_POSX+i*TILE_WIDTH,ED_AREA_POSY+j*TILE_HEIGHT,255);
			break;
		case TILE_13_4_STYLE:
			render->DrawTile(4*TILE_WIDTH,4*TILE_HEIGHT,ED_AREA_POSX+i*TILE_WIDTH,ED_AREA_POSY+j*TILE_HEIGHT,255);
			break;
		case TILE_14_4_STYLE:
			render->DrawTile(5*TILE_WIDTH,4*TILE_HEIGHT,ED_AREA_POSX+i*TILE_WIDTH,ED_AREA_POSY+j*TILE_HEIGHT,255);
			break;
		case TILE_15_4_STYLE:
			render->DrawTile(6*TILE_WIDTH,4*TILE_HEIGHT,ED_AREA_POSX+i*TILE_WIDTH,ED_AREA_POSY+j*TILE_HEIGHT,255);
			break;
		//////////////////////////////////////////////////////////////////////////
		case TILE_9_5_STYLE:
			render->DrawTile(0*TILE_WIDTH,5*TILE_HEIGHT,ED_AREA_POSX+i*TILE_WIDTH,ED_AREA_POSY+j*TILE_HEIGHT,255);
			break;
		case TILE_10_5_STYLE:
			render->DrawTile(1*TILE_WIDTH,5*TILE_HEIGHT,ED_AREA_POSX+i*TILE_WIDTH,ED_AREA_POSY+j*TILE_HEIGHT,255);
			break;
		case TILE_11_5_STYLE:
			render->DrawTile(2*TILE_WIDTH,5*TILE_HEIGHT,ED_AREA_POSX+i*TILE_WIDTH,ED_AREA_POSY+j*TILE_HEIGHT,255);
			break;
		case TILE_12_5_STYLE:
			render->DrawTile(3*TILE_WIDTH,5*TILE_HEIGHT,ED_AREA_POSX+i*TILE_WIDTH,ED_AREA_POSY+j*TILE_HEIGHT,255);
			break;
		case TILE_13_5_STYLE:
			render->DrawTile(4*TILE_WIDTH,5*TILE_HEIGHT,ED_AREA_POSX+i*TILE_WIDTH,ED_AREA_POSY+j*TILE_HEIGHT,255);
			break;
		case TILE_14_5_STYLE:
			render->DrawTile(5*TILE_WIDTH,5*TILE_HEIGHT,ED_AREA_POSX+i*TILE_WIDTH,ED_AREA_POSY+j*TILE_HEIGHT,255);
			break;
		case TILE_15_5_STYLE:
			render->DrawTile(6*TILE_WIDTH,5*TILE_HEIGHT,ED_AREA_POSX+i*TILE_WIDTH,ED_AREA_POSY+j*TILE_HEIGHT,255);
			break;
		//////////////////////////////////////////////////////////////////////////
		case TILE_9_6_STYLE:
			render->DrawTile(0*TILE_WIDTH,6*TILE_HEIGHT,ED_AREA_POSX+i*TILE_WIDTH,ED_AREA_POSY+j*TILE_HEIGHT,255);
			break;
		case TILE_10_6_STYLE:
			render->DrawTile(1*TILE_WIDTH,6*TILE_HEIGHT,ED_AREA_POSX+i*TILE_WIDTH,ED_AREA_POSY+j*TILE_HEIGHT,255);
			break;
		case TILE_11_6_STYLE:
			render->DrawTile(2*TILE_WIDTH,6*TILE_HEIGHT,ED_AREA_POSX+i*TILE_WIDTH,ED_AREA_POSY+j*TILE_HEIGHT,255);
			break;
		case TILE_12_6_STYLE:
			render->DrawTile(3*TILE_WIDTH,6*TILE_HEIGHT,ED_AREA_POSX+i*TILE_WIDTH,ED_AREA_POSY+j*TILE_HEIGHT,255);
			break;
		case TILE_13_6_STYLE:
			render->DrawTile(4*TILE_WIDTH,6*TILE_HEIGHT,ED_AREA_POSX+i*TILE_WIDTH,ED_AREA_POSY+j*TILE_HEIGHT,255);
			break;
		case TILE_14_6_STYLE:
			render->DrawTile(5*TILE_WIDTH,6*TILE_HEIGHT,ED_AREA_POSX+i*TILE_WIDTH,ED_AREA_POSY+j*TILE_HEIGHT,255);
			break;
		case TILE_15_6_STYLE:
			render->DrawTile(6*TILE_WIDTH,6*TILE_HEIGHT,ED_AREA_POSX+i*TILE_WIDTH,ED_AREA_POSY+j*TILE_HEIGHT,255);
			break;
		//////////////////////////////////////////////////////////////////////////
		default:
			break;
		}
	}
	
	render->DrawBugbear(bugbearMgr);
	render->DrawMarioFrame(mario);
	render->DrawSmoke(smokeMgr,mario);
	render->DrawShow(showMgr);
	render->DrawScore(0,0,mario->score);
	render->DrawScore(575,0,timer);
	if(pause == -1)
	{
		render->DrawMenuShade(100);
		render->DrawDialog();
		render->DrawExitButton(guiMgr->GetExitYes().rect.x,
							guiMgr->GetExitYes().rect.y,
							guiMgr->GetExitYes().bOn);
		render->DrawExitButton(guiMgr->GetExitNo().rect.x,
							guiMgr->GetExitNo().rect.y,
							guiMgr->GetExitNo().bOn);
		render->DrawExitSelect();
		render->DrawCursor(curpos.x,curpos.y);
	}

//	render->UpdateScreen();
}


void	CGameMgr::LoadLevel(int level)
{
		
		map->LoadMap(level);
		render->Changebg(level);
		int i = rand()%(BM_NUM-1)+1;
		audioMgr->LoadBM(i);
		
}


void	CGameMgr::GameLogo(void)
{
	render->DrawLogo(logo.x,logo.y, logo.alpha);
	render->UpdateScreen();

	if(logo.bIn == true)
	{
		logo.alpha+=1;
		if(logo.alpha>=150)
		{
			logo.alpha =0;
			logo.bIn = true;
			state = GAME_MENU;
		}
	}

	
}

void	CGameMgr::GameMenu(void)
{
	
	/*GUI逻辑*/
		SDL_ShowCursor(SDL_DISABLE);
	 	int x;
		int y;
		GetMousePos(&x,&y);
		GetMousePos(&curpos.x,&curpos.y);
		/*鼠标移动到new按钮上*/
		if(x>=guiMgr->GetMenuNew().rect.x && x<=guiMgr->GetMenuNew().rect.x2
			&&y>=guiMgr->GetMenuNew().rect.y && y<=guiMgr->GetMenuNew().rect.y2)
		{
			guiMgr->SetMenuNew(true);	
			if( PressLeftButton(&x, &y) )
			{
				map->LoadMap(1);
				render->Changebg(1);
				state = GAME_MAIN;
				Sleep(200);
			}
		}
		else
		{
			guiMgr->SetMenuNew(false);
		}
		/*鼠标移动到credits按钮上*/
		if(x>=guiMgr->GetMenuCredits().rect.x && x<=guiMgr->GetMenuCredits().rect.x2
			&&y>=guiMgr->GetMenuCredits().rect.y && y<=guiMgr->GetMenuCredits().rect.y2)
		{
			guiMgr->SetMenuCredits(true);
			if( PressLeftButton(&x, &y) )
			{
				map->LoadMap(1);
				render->Changebg(1);
				state = GAME_CREDITS;
			}
		}
		else
		{
			guiMgr->SetMenuCredits(false);
		}
		/*鼠标移动到exit按钮上*/
		if(x>=guiMgr->GetMenuExit().rect.x && x<=guiMgr->GetMenuExit().rect.x2
			&&y>=guiMgr->GetMenuExit().rect.y && y<=guiMgr->GetMenuExit().rect.y2)
		{
			guiMgr->SetMenuExit(true);	
			if( PressLeftButton(&x, &y) )
			{
				brun = false;
			}
		}
		else
		{
			guiMgr->SetMenuExit(false);
		}

		/*动画*/
		//
	static int i = 1;
	static lasttick = GetTickCount();
	if(GetTickCount() - lasttick >= 3000)
	{
		lasttick = GetTickCount();
		
		if(i>=MAP_NUM)
		{
			i=0;
		}
		i++;
		map->LoadMap(i);
		render->Changebg(i);
	}
		
		/*渲染画面*/
		render->DrawBG();
		Render();
		render->DrawMenuShade(50);
		render->DrawMenuButton(guiMgr->GetMenuNew().rect.x,
							guiMgr->GetMenuNew().rect.y,
							guiMgr->GetMenuNew().bOn);
		render->DrawMenuButton(guiMgr->GetMenuCredits().rect.x,
							guiMgr->GetMenuCredits().rect.y,
							guiMgr->GetMenuCredits().bOn);
		render->DrawMenuButton(guiMgr->GetMenuExit().rect.x,
							guiMgr->GetMenuExit().rect.y,
							guiMgr->GetMenuExit().bOn);
		
		render->DrawMenuSelect();
		render->DrawCursor(curpos.x,curpos.y);
		render->UpdateScreen();
		
		
	

	
}


void	CGameMgr::GameCredits(void)
{
	    SDL_ShowCursor(SDL_DISABLE);
	  	int x;
		int y;		
		GetMousePos(&curpos.x,&curpos.y);
	
	/*渲染*/
	Render();
	render->DrawCredits(credits.alpha);
	render->DrawCursor(curpos.x,curpos.y);
	render->UpdateScreen();
	if(credits.bIn == true)
	{
		credits.alpha+=10;
		if(credits.alpha >= 240)
		{
			credits.alpha = 240;
			credits.bIn = false;
			
		}
	}
	
	if(credits.bIn == false)
	{
		if( PressLeftButton(&x, &y) )
		{
			state = GAME_MENU;
			credits.alpha = 0;
			credits.bIn = true;
			Sleep(100);
		}
	}
	

}


void	CGameMgr::GameFinish(void)
{
		SDL_ShowCursor(SDL_DISABLE);
	  	int x;
		int y;		
		GetMousePos(&curpos.x,&curpos.y);
		render->DrawFinish(finish.x, finish.y,finish.alpha);
		render->DrawCursor(curpos.x,curpos.y);
		render->UpdateScreen();
		audioMgr->PlayFinish(true,true);

		if(finish.bIn)
		{
			if(finish.alpha >=200)
			{
				finish.alpha = 200;
			}
			else
			{
				finish.alpha++;
			}
		}

		if( PressLeftButton(&x, &y) )
		{
			state = GAME_LOGO;
			Sleep(100);
		}
		
}

