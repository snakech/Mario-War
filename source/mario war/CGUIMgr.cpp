#include		"CGUIMgr.h"

CGUIMgr::CGUIMgr(void)
{
	ExitYes.rect.x = 275;
	ExitYes.rect.y = 195;
	ExitYes.rect.w = 80;
	ExitYes.rect.h = 34;
	ExitYes.rect.x2 = 275+80;
	ExitYes.rect.y2 = 185+34;
	ExitYes.bOn = false;

	ExitNo.rect.x = 275;
	ExitNo.rect.y = 250;
	ExitNo.rect.w = 80;
	ExitNo.rect.h = 34;
	ExitNo.rect.x2 = 275+80;
	ExitNo.rect.y2 = 250+34;
	ExitNo.bOn = false;

	MenuNew.rect.x = 224;
	MenuNew.rect.y = 206;
	MenuNew.rect.w = 192;
	MenuNew.rect.h = 34;
	MenuNew.rect.x2 = 224+192;
	MenuNew.rect.y2 = 206+34;
	MenuNew.bOn = false;

	MenuCredits.rect.x = 224;
	MenuCredits.rect.y = 206+50;
	MenuCredits.rect.w = 192;
	MenuCredits.rect.h = 34;
	MenuCredits.rect.x2 = 224+192;
	MenuCredits.rect.y2 = 206+50+34;
	MenuCredits.bOn = false;

	MenuExit.rect.x = 224;
	MenuExit.rect.y = 206+50+50;
	MenuExit.rect.w = 192;
	MenuExit.rect.h = 34;
	MenuExit.rect.x2 = 224+192;
	MenuExit.rect.y2 = 206+50+50+34;
	MenuExit.bOn = false;
}

CGUIMgr::~CGUIMgr(void)
{

}


BUTTON	CGUIMgr::GetExitYes(void)
{
	return	ExitYes;
}

BUTTON	CGUIMgr::GetExitNo(void)
{
	return ExitNo;
}

void	CGUIMgr::SetExitYes(bool _bOn)
{
	ExitYes.bOn = _bOn;
}

void	CGUIMgr::SetExitNo(bool _bOn)
{
	ExitNo.bOn = _bOn;
}

BUTTON 	CGUIMgr::GetMenuCredits(void)
{
	return MenuCredits;
}

BUTTON	CGUIMgr::GetMenuExit(void)
{
	return MenuExit;
}


BUTTON CGUIMgr::GetMenuNew(void)
{
	return MenuNew;
}

void	CGUIMgr::SetMenuCredits(bool _bOn)
{
	MenuCredits.bOn = _bOn;
}

void	CGUIMgr::SetMenuExit(bool	_bOn)
{
	MenuExit.bOn = _bOn;
}


void	CGUIMgr::SetMenuNew(bool _bOn)
{
	MenuNew.bOn = _bOn;
}