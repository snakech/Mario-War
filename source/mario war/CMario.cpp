#include		"CMario.h"
#include		"GetKeyInput.h"
#include		"GameInfo.h"
#include		<SDL.h>
#include		<windows.h>
#include		<cmath>
#include		"LogError.h"
#include		"CMap.h"
#include		<list>
#include		<algorithm>
CMario::CMario(void)
{
	m_marioData.x  =640.0f;
	m_marioData.y  =480.0f;
	m_marioData.dx =0.0f;
	m_marioData.dy =0.0f;
	m_marioData.a  =40.0f;
	m_marioData.lf  =0.90f;
	m_marioData.af  =0.94f;
	m_marioData.g  =55.0f;
	m_marioData.dt =0.01f;
	show		   = true;
	state		   = MARIO_IN_AIR;
	life		   = 0;
	frame          = MARIO_r3;
	dir			   = RIGHT;
	maxSpeed	   = 8.0f;
	score		   = 0;
	tick		   = GetTickCount();
	kill		   = 0;

}

void		CMario::UpdateLogic(CAudioMgr * _audioMgr)
{


       
		/*判断马力是否达到最大速度*/
		if(IsKeyDown(VK_F1))
		{
			//level ++;
		}
		
		if(m_marioData.dx >= maxSpeed)
		{
			m_marioData.dx = maxSpeed;
		}

		if(m_marioData.dx <= -maxSpeed)
		{
			m_marioData.dx = -maxSpeed;
		}
		/*mario 的水平移动更新*/
		
		if( IsKeyDown(VK_LEFT) )
		{
			
			if(m_marioData.dx < -0.01f)
			{
				dir = LEFT;
			}
			m_marioData.dx -= m_marioData.a*m_marioData.dt;
		}
		else
		if( IsKeyDown(VK_RIGHT) )
		{
			
			if(m_marioData.dx >=0.01f)
			{
				dir = RIGHT;
			}
			m_marioData.dx += m_marioData.a*m_marioData.dt;
		}

		/*mario 在地面上受到摩擦*/
		if( state == MARIO_ON_LAND && m_marioData.dx != 0 )
		{
			m_marioData.dx *= m_marioData.lf;
		}
		else
		if( state == MARIO_IN_AIR && m_marioData.dx != 0  )
		{
			m_marioData.dx *= m_marioData.af;
		}
		
		/*在地面 并 按跳跃键*/
		if( state == MARIO_ON_LAND )
		{
			if( IsKeyDown(VK_UP) )
			{
				_audioMgr->PlayJump();
				if(dir == RIGHT)
				{
					frame = MARIO_r3;
				}
				else
					if(dir == LEFT)
					{
						frame = MARIO_l3;
					}
				state = MARIO_IN_AIR;
				if( IsKeyDown(VK_SPACE) )
				{
				m_marioData.a  = 45;
				m_marioData.dy = -1250*m_marioData.dt;
				}
				else
				{
				m_marioData.a = 40;
				m_marioData.dy = -1100*m_marioData.dt;
				}
			}
		}

		/*受到重力*/
		
		m_marioData.dy +=m_marioData.g*m_marioData.dt;

		m_marioData.x += m_marioData.dx;
		m_marioData.y += m_marioData.dy;
		
		static DWORD lasttick = GetTickCount();
		int	 delay = 100 -abs(m_marioData.dx)*3;
		if(delay >= 100)
		{
			delay = 100;
		}
		if(GetTickCount() - lasttick >= delay )
		{
			lasttick = GetTickCount();
		/*帧动画转换逻辑*/
		if( state == MARIO_ON_LAND )
		{
			
			if(m_marioData.dx >= -7.0f && m_marioData.dx <= -1.0f)
			{
				if(frame == MARIO_l1 || frame == MARIO_l2 )
				{
					
					frame = -frame;
					
				}
			
				else
				{
                  frame = MARIO_l1;
				  
				}
			}

						

				if(m_marioData.dx >= 1.0f && m_marioData.dx <=7.0f)
				{
					if(frame == MARIO_r1 || frame == MARIO_r2 )
					{
						frame = -frame;
					}
				
					else
					{
						frame = MARIO_r1;
					}	
				}


			if(dir == RIGHT && m_marioData.dx >=0.0f &&m_marioData.dx<=0.9f)
			{
				frame = MARIO_r1;
			}

			else
				if(dir == LEFT && m_marioData.dx >=-0.9f && m_marioData.dx <= -0.01f)
				{
					frame = MARIO_l1;
				}
		}


		/*可爱的滑步*/
		if(state == MARIO_ON_LAND)
		{
		if(IsKeyDown(VK_LEFT) && m_marioData.dx >=0.0f)
		{
			
			frame = MARIO_r4;
		}
		else
			if(IsKeyDown(VK_RIGHT) && m_marioData.dx <=0.0f)
			{
				frame = MARIO_l4;
			}
		}
		
		}
}


void	CMario::Collision(CMap *_map, CAudioMgr *_audioMgr)
{
	/*碰到左边界*/
	if( m_marioData.x <= 0 )
	{
		m_marioData.x = 0;
		m_marioData.dx = 2;
	}
	/*碰到右边界*/
	if( m_marioData.x >=  WINDOW_WIDTH - MARIO_WIDTH )
	{
		m_marioData.x = WINDOW_WIDTH - MARIO_WIDTH;
		m_marioData.dx = -2;
	}

	/*碰到下边界*/
	if( m_marioData.y >= WINDOW_HEIGHT - MARIO_HEIGHT )
	{
		m_marioData.y = WINDOW_HEIGHT - MARIO_HEIGHT;
		state = MARIO_ON_LAND;
	}

	/*与地图进行碰撞检测*/
	//首先设定好碰撞检测点
	headPoint[0].x = m_marioData.x+8 ;
	headPoint[0].y = m_marioData.y;
	headPoint[1].x = m_marioData.x + MARIO_WIDTH - 8;
	headPoint[1].y = m_marioData.y;

	footPoint[0].x = m_marioData.x + 8;
	footPoint[0].y = m_marioData.y + MARIO_HEIGHT;
	footPoint[1].x = m_marioData.x + MARIO_WIDTH - 8;
	footPoint[1].y = m_marioData.y + MARIO_HEIGHT;

	leftPoint[0].x = m_marioData.x;
	leftPoint[0].y = m_marioData.y + 12;
	leftPoint[1].x = m_marioData.x;
	leftPoint[1].y = m_marioData.y + MARIO_HEIGHT -15;

	rightPoint[0].x = m_marioData.x + MARIO_WIDTH;
	rightPoint[0].y = m_marioData.y + 12;
	rightPoint[1].x = m_marioData.x + MARIO_WIDTH;
	rightPoint[1].y = m_marioData.y + MARIO_HEIGHT - 15;
	

	int tx1,tx2,ty1,ty2;
	//与tile碰撞检测
		

	/*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/
	/*  very important things!!, I can dowith mario move for special collision!    
		detect tile style when mario collison the tile, then do some special thing,
		what a good idea!
																					*/
		m_marioData.lf = 0.90f;
		//右边碰撞
		
		 tx1 = rightPoint[0].x/TILE_WIDTH;
		 ty1 = rightPoint[0].y/TILE_HEIGHT;
		 tx2 = rightPoint[1].x/TILE_WIDTH;
		 ty2 = rightPoint[1].y/TILE_HEIGHT;
		 if( _map->maps[ty1][tx1] != 0 || _map->maps[ty2][tx2] != 0 )
		 {
			float  dx =(float)(rightPoint[0].x - tx1*TILE_WIDTH);
			m_marioData.x -=dx;
			/*如果和音乐方快相碰*/
			if(_map->maps[ty1][tx1] == TILE_12_0_STYLE ||
				_map->maps[ty2][tx2] == TILE_12_0_STYLE)
			{
				_audioMgr->PlaySpringJump();
				m_marioData.dx = -8;
				state = MARIO_ON_LAND;
			}
			
			else		
			{
				
				m_marioData.dx = 0.0f;
			}
		 }
		
		 //左边碰撞
		 tx1 = leftPoint[0].x/TILE_WIDTH;
		 ty1 = leftPoint[0].y/TILE_HEIGHT;
		 tx2 = leftPoint[1].x/TILE_WIDTH;
		 ty2 = leftPoint[1].y/TILE_HEIGHT;
		if( _map->maps[ty1][tx1] != 0 || _map->maps[ty2][tx2] != 0 )
		{
		
			float dx =(float)(tx1*TILE_WIDTH + TILE_WIDTH - leftPoint[0].x);
			
			m_marioData.x += dx;
			m_marioData.dx =0.0f;
			/*如果和音乐方快相碰*/
			if(_map->maps[ty1][tx1] == TILE_12_0_STYLE ||
				_map->maps[ty2][tx2] == TILE_12_0_STYLE)
			{
				_audioMgr->PlaySpringJump();
				m_marioData.dx = 8;
				state = MARIO_ON_LAND;
			}
		
		}
	

	
		//头部碰撞
	
		
		 tx1 = headPoint[0].x/TILE_WIDTH;
		 ty1 = headPoint[0].y/TILE_HEIGHT;
		 tx2 = headPoint[1].x/TILE_WIDTH;
		 ty2 = headPoint[1].y/TILE_HEIGHT;
		if(_map->maps[ty1][tx1] != 0 || _map->maps[ty2][tx2] != 0 )
		{
			float dy = (float)(ty1*TILE_HEIGHT+TILE_HEIGHT - headPoint[0].y);
			m_marioData.y += dy;
			m_marioData.dy = 1.0f;
			//头部碰撞，就产生反弹
			//如果碰到带眼镜的脸，会被吸住
			if(_map->maps[ty1][tx1] == TILE_11_5_STYLE ||
				_map->maps[ty2][tx2] == TILE_11_5_STYLE)
			{
				m_marioData.dy = -1.0f;
			}
			else
			//碰到？，就变扁
			if(_map->maps[ty1][tx1] == TILE_11_0_STYLE ||
				_map->maps[ty2][tx2] == TILE_11_0_STYLE)
			{
				frame = MARIO_r6;
			}
		
		}
	 
		
		//脚部碰撞
		 tx1 = footPoint[0].x/TILE_WIDTH;
		 ty1 = footPoint[0].y/TILE_HEIGHT;
		 tx2 = footPoint[1].x/TILE_WIDTH;
		 ty2 = footPoint[1].y/TILE_HEIGHT;
		 if( _map->maps[ty1][tx1] != 0 || _map->maps[ty2][tx2] != 0 )
		 {
		   state = MARIO_ON_LAND;
		   float dy = (float)(footPoint[0].y - ty1*TILE_HEIGHT); 
		   m_marioData.y -=dy;
		   m_marioData.dy =0.0f;

		   /*如果和音乐方快相碰*/
			if(_map->maps[ty1][tx1] == TILE_12_0_STYLE ||
				_map->maps[ty2][tx2] == TILE_12_0_STYLE)
			{
				_audioMgr->PlaySpringJump();
				m_marioData.dy = -8;
			}
			else
			/*如果和冰块碰撞*/
			if(_map->maps[ty1][tx1] == TILE_9_6_STYLE ||
				_map->maps[ty2][tx2] == TILE_9_6_STYLE)
			{
				m_marioData.lf = 0.96f;
			}
			else
			/*和草地碰撞，减速效果*/
			if(_map->maps[ty1][tx1] == TILE_14_3_STYLE ||
				_map->maps[ty2][tx2] == TILE_14_3_STYLE)
			{
				m_marioData.lf = 0.80f;
			}
			else
			/*碰到钉子*/
			if(_map->maps[ty1][tx1] == TILE_15_5_STYLE ||
				_map->maps[ty2][tx2] == TILE_15_5_STYLE)
			{
				_audioMgr->PlayDead();
				life = 0;
				state = MARIO_IN_AIR;
				m_marioData.dy = -6;
			}
			
			
				
			
		 }
		 

	
	
	
}

/*和怪物的碰撞检测*/
void		CMario::CollisionBugbear(CBugbearMgr * _bugbearMgr,
									 CAudioMgr *_audioMgr,
									 CMap *_map)
{
	/*首先设定碰撞点*/
	headPoint[0].x = m_marioData.x+5 ;
	headPoint[0].y = m_marioData.y;
	headPoint[1].x = m_marioData.x + MARIO_WIDTH - 5;
	headPoint[1].y = m_marioData.y;

	footPoint[0].x = m_marioData.x + 5;
	footPoint[0].y = m_marioData.y + MARIO_HEIGHT;
	footPoint[1].x = m_marioData.x + MARIO_WIDTH - 5;
	footPoint[1].y = m_marioData.y + MARIO_HEIGHT;

	leftPoint[0].x = m_marioData.x;
	leftPoint[0].y = m_marioData.y + 12;
	leftPoint[1].x = m_marioData.x;
	leftPoint[1].y = m_marioData.y + MARIO_HEIGHT -15;

	rightPoint[0].x = m_marioData.x + MARIO_WIDTH;
	rightPoint[0].y = m_marioData.y + 12;
	rightPoint[1].x = m_marioData.x + MARIO_WIDTH;
	rightPoint[1].y = m_marioData.y + MARIO_HEIGHT - 15;
	
	/*遍历每一个元素*/

	list<CBugbear *>::iterator it;
	for(it=_bugbearMgr->bugbearList.begin();it != _bugbearMgr->bugbearList.end();it++)
	{
		/*是否和敌人碰撞？*/
		int  tx = abs(m_marioData.x - (*it)->GetBugbearStruct().x);
		int  ty = abs(m_marioData.y - (*it)->GetBugbearStruct().y);
		
		/*说明碰撞了*/
		if(tx*tx + ty*ty <= 1024)
		{
			/*是脚和敌人碰撞*/
			if(m_marioData.y+32 >=(*it)->GetBugbearStruct().y && 
				m_marioData.y+32 <= (*it)->GetBugbearStruct().y +TILE_WIDTH )
			{
				if(m_marioData.x +16 >= (*it)->GetBugbearStruct().x  &&
					m_marioData.x +16<= (*it)->GetBugbearStruct().x +TILE_WIDTH  )
				{
					_audioMgr->PlayTouchBugbear();
					(*it)->SetLife(0);

					(*it)->SetDx(0.0f);
					m_marioData.dy = -5.0f;				
					//加分
					kill++;
					score+= 10;
				}
																
			}	
			//mario死亡
			else 
			{
				//在另一个地方产生mario，根据地图数据来产生，如果合理就可以产生
				if(score >= 10)
				{
					score-=10;
				}
				_audioMgr->PlayDead();
				m_marioData.dy = -15.0f;
				life = 0;
				state = MARIO_IN_AIR;
			}
		}
	}
	
}
FRAME	CMario::GetFrame(void)
{
	return	frame;
}

MarioData		CMario::GetMarioData(void)
{
	return		m_marioData;
}

void		CMario::Init(void)
{
	m_marioData.x  =640.0f;
	m_marioData.y  =480.0f;
	m_marioData.dx =0.0f;
	m_marioData.dy =0.0f;
	m_marioData.a  =40.0f;
	m_marioData.lf  =0.90f;
	m_marioData.af  =0.94f;
	m_marioData.g  =55.0f;
	m_marioData.dt =0.01f;
	show		   = true;
	state		   = MARIO_IN_AIR;
	life		   = 0;
	frame          = MARIO_r3;
	dir			   = RIGHT;
	maxSpeed	   = 8;
	score		   = 0;
	kill		   = 0;
}

void		CMario::SetPos(float _x, float _y)
{
	m_marioData.x  = _x;
	m_marioData.y  = _y;
}


void		CMario::SetDxDy(float _dx, float _dy)
{
	m_marioData.dx = _dx;
	m_marioData.dy = _dy;
}




