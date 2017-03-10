#include	"CRunSmokeMgr.h"
#include	<list>
#include	<algorithm>
#include	"CRunSmoke.h"
#include	"CMario.h"
#include	"LogError.h"
#include	"GameInfo.h"
CRunSmokeMgr::CRunSmokeMgr(void)
{

}


CRunSmokeMgr::~CRunSmokeMgr(void)
{
	
}

void CRunSmokeMgr::BroseList(void)
{

	list<CRunSmoke *>::iterator it;
	for( it=smokeList.begin(); it!=smokeList.end(); it++ )
	{
		if( (*it)->GetSmokeStruct().life != 1) 
		{
			delete(*it);
			it = smokeList.erase(it);
		}
		else
		{
			(*it)->UpdateLogic();
		}
	}
}


void	CRunSmokeMgr::Add(CMario *_mario)
{
	if( _mario->GetFrame() == MARIO_l4 ) 
	{
		
		CRunSmoke *smoke = new CRunSmoke(_mario->GetMarioData().x +MARIO_WIDTH-4,
											_mario->GetMarioData().y+MARIO_HEIGHT-16);
		smokeList.push_back(smoke);
		
	}

	else
		if( _mario->GetFrame() == MARIO_r4 )
		{
			CRunSmoke *smoke = new CRunSmoke(_mario->GetMarioData().x +2,
											_mario->GetMarioData().y+MARIO_HEIGHT-16);
		smokeList.push_back(smoke);
		}
	else
		if(!_mario->GetLife())
		{
			CRunSmoke *smoke = new CRunSmoke(_mario->GetMarioData().x +8,
											_mario->GetMarioData().y + 8);
			smokeList.push_back(smoke);
		}

}