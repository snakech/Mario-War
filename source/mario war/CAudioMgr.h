#ifndef		CAUDIOMGR_H
#define		CAUDIOMGR_H

#include		"AudiereManager.h"

class		CAudioMgr
{
public:
	CAudioMgr(void);
	~CAudioMgr(void);
	void	LoadBM(int level);       //载入背景音乐
	void	LoadOther(void);			 //载入其他音效和音乐	
	void	PlayBM(bool play =true, bool loop = false);
	void	PlayJump(void);
	void	PlaySpringJump(void);
	void	PlayDead(void);
	void	PlayButton(void);
	void	PlayMenu(bool play = true, bool loop = false);
	void	PlayLogo(bool play = true, bool loop = false);
	void	PlayCredits(bool	play = true,bool loop = true);
	void	PlayWin(void);
	void	PlayOver(void);
	void	PlayGo(void);
	void	PlayWarning(void);
	void	PlayTouchBugbear(void);
	void	PlayFinish(bool play = true, bool loop = true);
AudiereManager	*instance;
private:
	HSOUND			marioJump;  //mario跳！
	HSOUND			marioSpringJump;   //mario弹跳！
	HSOUND			logo;       //logo音乐
	HSOUND			button;      //按钮激活
	HSOUND			menu;        //菜单背景音乐！
	HSOUND			bm;         //游戏背景音乐！
	HSOUND			credits;    //credits
	HSOUND			touchbugbear;   //踩怪物
	HSOUND			mariodead;			//mario死亡
	HSOUND			win;           //胜利
	HSOUND			over;          //失败
	HSOUND			go;        //开始
	HSOUND			timewarning;   //timewarning;
	HSOUND			finish;    //游戏翻机
};

#endif