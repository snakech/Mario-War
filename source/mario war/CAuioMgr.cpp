#include	"CAudioMgr.h"

CAudioMgr::CAudioMgr(void)
{
	instance = AudiereManager::GetInstance();
	LoadBM(1);
	LoadOther();
}


CAudioMgr::~CAudioMgr(void)
{
	instance->Release();
}

void CAudioMgr::LoadBM(int level)
{
	char a[100];
	sprintf(a,"music\\bm%d.ogg",level);
	bm = instance->load(a,true);
}

void	CAudioMgr::PlayBM(bool play, bool loop)
{
	if(play)
	{
		if (!instance->isPlaying(bm))
		{
			instance->play(bm,loop);
		}
	}
	else
	if(!play)
	{
		if (instance->isPlaying(bm))
		{
			instance->stop(bm);
			instance->reset(bm);
		}
	}
}


void	CAudioMgr::LoadOther(void)
{
	marioJump		= instance->load("sfx\\mariojump.wav",false);
	marioSpringJump	= instance->load("sfx\\springjump.wav",false);
	menu			= instance->load("music\\menu.ogg",true);
	credits			= instance->load("music\\credits.ogg",true);
	touchbugbear    = instance->load("sfx\\touchbugbear.wav",false);
	mariodead		= instance->load("sfx\\mariodead.wav",false);
	win				= instance->load("music\\win.ogg",false);
	over			= instance->load("music\\over.ogg",false);
	go				= instance->load("sfx\\letsgo.wav",false);
	timewarning		= instance->load("sfx\\timewarning.wav",false);
	finish			= instance->load("music\\finish.ogg",true);
}

void	CAudioMgr::PlayJump(void)
{
	if (!instance->isPlaying(marioJump))
		{
			instance->play(marioJump,false);
		}
	else
	if(instance->isPlaying(marioJump))
	{
		instance->reset(marioJump);
	}

}

void	CAudioMgr::PlaySpringJump(void)
{
	if (!instance->isPlaying(marioSpringJump))
		{
			instance->play(marioSpringJump,false);
		}
	else
	if(instance->isPlaying(marioSpringJump))
	{
		instance->reset(marioSpringJump);
	}
}

void	CAudioMgr::PlayMenu(bool play, bool loop)
{
	if(play)
	{
		if (!instance->isPlaying(menu))
		{
			instance->play(menu,loop);
		}
	}
	else
	if(!play)
	{
		if (instance->isPlaying(menu))
		{
			instance->stop(menu);
			instance->reset(menu);
		}
	}
}

void	CAudioMgr::PlayCredits(bool play, bool loop)
{
		if(play)
	{
		if (!instance->isPlaying(credits))
		{
			instance->play(credits,loop);
		}
	}
	else
	if(!play)
	{
		if (instance->isPlaying(credits))
		{
			instance->stop(credits);
			instance->reset(credits);
		}
	}
}

void	CAudioMgr::PlayTouchBugbear(void)
{
		if (!instance->isPlaying(touchbugbear))
		{
			instance->play(touchbugbear,false);
		}
	else
	if(instance->isPlaying(touchbugbear))
	{
		instance->reset(touchbugbear);
	}
}

void	CAudioMgr::PlayDead(void)
{
	if (!instance->isPlaying(mariodead))
		{
			instance->play(mariodead,false);
		}
	else
	if(instance->isPlaying(mariodead))
	{
		instance->reset(mariodead);
	}
}


void	CAudioMgr::PlayGo(void)
{
	if (!instance->isPlaying(go))
		{
			instance->stop(credits);
		//	instance->reset(credits);
			instance->play(go,false);
		}
	else
	if(instance->isPlaying(go))
	{
			
	//	instance->reset(go);
	}
}

void	CAudioMgr::PlayOver(void)
{
	if (!instance->isPlaying(over))
		{
			instance->play(over,false);
		}
	else
	if(instance->isPlaying(over))
	{
		instance->reset(over);
	}
}


void	CAudioMgr::PlayWarning(void)
{
	if (!instance->isPlaying(timewarning))
		{
			instance->play(timewarning,false);
		}
	else
	if(instance->isPlaying(timewarning))
	{
		instance->reset(timewarning);
	}
}

void	CAudioMgr::PlayWin(void)
{
	if (!instance->isPlaying(win))
		{
			instance->play(win,false);
		}
	else
	if(instance->isPlaying(win))
	{
		instance->reset(win);
	}
}

void	CAudioMgr::PlayFinish(bool play, bool loop)
{
	if(play)
	{
		if (!instance->isPlaying(finish))
		{
			instance->play(finish,loop);
		}
	}
	else
	if(!play)
	{
		if (instance->isPlaying(finish))
		{
			instance->stop(finish);
			instance->reset(finish);
		}
	}
}