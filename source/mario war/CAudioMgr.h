#ifndef		CAUDIOMGR_H
#define		CAUDIOMGR_H

#include		"AudiereManager.h"

class		CAudioMgr
{
public:
	CAudioMgr(void);
	~CAudioMgr(void);
	void	LoadBM(int level);       //���뱳������
	void	LoadOther(void);			 //����������Ч������	
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
	HSOUND			marioJump;  //mario����
	HSOUND			marioSpringJump;   //mario������
	HSOUND			logo;       //logo����
	HSOUND			button;      //��ť����
	HSOUND			menu;        //�˵��������֣�
	HSOUND			bm;         //��Ϸ�������֣�
	HSOUND			credits;    //credits
	HSOUND			touchbugbear;   //�ȹ���
	HSOUND			mariodead;			//mario����
	HSOUND			win;           //ʤ��
	HSOUND			over;          //ʧ��
	HSOUND			go;        //��ʼ
	HSOUND			timewarning;   //timewarning;
	HSOUND			finish;    //��Ϸ����
};

#endif