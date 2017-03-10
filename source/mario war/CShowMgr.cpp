#include		"CShowMgr.h"
#include		<list>
#include		<algorithm>
#include		"CShow.h"
#include		"CBugbearMgr.h"
#include		"CBugbear.h"
#include		"LogError.h"
#include		"windows.h"
CShowMgr::CShowMgr(void)
{

}

CShowMgr::~CShowMgr(void)
{

}

void	CShowMgr::BroseList(void)
{
	list<CShow *>::iterator it;
	for( it=showList.begin(); it!=showList.end(); it++)
	{
		if((*it)->GetShowStruct().life == 0 )
		{
			delete(*it);
			it = showList.erase(it);
		}
		else
		{
			(*it)->UpdateLogic();
		}
	}
}

void	CShowMgr::Add(CBugbearMgr * _bugbearMgr)
{
	list<CBugbear *>::iterator it;
	for(it= _bugbearMgr->bugbearList.begin(); it!= _bugbearMgr->bugbearList.end(); it++)
	{
		if((*it)->GetBugbearStruct().life == 0)
		{
			int tx = (*it)->GetBugbearStruct().x;
			int ty = (*it)->GetBugbearStruct().y;
			CShow *show = new CShow( tx, ty );
			showList.push_back(show);
		}	
	}
}






