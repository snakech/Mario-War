#ifndef		CSHOWMGR_H
#define		CSHOWMGR_H
#include	"CBugbearMgr.h"
#include	"CShow.h"	
#include	<list>
using namespace std;

class		CShowMgr
{
public:
	CShowMgr(void);
	~CShowMgr(void);
	void	BroseList(void);
	void	Add(CBugbearMgr * _bugbearMgr);
public:
	list<CShow *> showList;
};
#endif