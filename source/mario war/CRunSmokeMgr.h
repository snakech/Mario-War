#ifndef		CRUNSMOKEMGR_H
#define		CRUNSMOKEMGR_H
#include	<list>
using namespace std;
#include	"CRunSmoke.h"
#include	"CMario.h"
class		CRunSmokeMgr
{
public:
	CRunSmokeMgr(void);
	~CRunSmokeMgr(void);
	void	BroseList(void);
	void	Add(CMario *_mario);
public:
    list<CRunSmoke *> smokeList;
};
#endif
