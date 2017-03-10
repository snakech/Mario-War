#ifndef			CMARIO_H
#define			CMARIO_H
#include		"CBugbearMgr.h"
#include		"CAudioMgr.h"
#include		"CBugbear.h"
#include		"CMap.h"

/*mario ������*/
struct		MarioData
{
	float	x;          // x���� 
	float	y;          // y����
	float   dx;         // x����
	float   dy;         // y����
	float   a;          // x������ٶ�
	float   lf;         // ����Ħ����
	float   af;         // ����Ħ��
	float   g;          // ����
	float   dt;         // ʱ��Ƭ
};

struct		CollisionPoint
{
	float x;
	float y;
};
typedef		int   MARIOSTATE;	
typedef		int   LIFE;
typedef		int	  FRAME;
typedef		int   DIR;
typedef		int	  COLSTYLE;
typedef		float	MAXSPEED;
class			CMario
{
public:
	CMario(void);
	~CMario(void)		{}
	/*use for loadLevel*/
	void		Init(void);
	void		UpdateLogic(CAudioMgr *_audioMgr);   
	void		Collision(CMap *_map,CAudioMgr *_audioMgr);
	void		CollisionBugbear(CBugbearMgr * _bugbearMgr,
								CAudioMgr *_audioMgr,
								CMap *_map);
	FRAME		GetFrame(void);
	MarioData  GetMarioData(void);
	void		SetLife(int _life)			{ life = _life; }
	void		SetFrame(int _frame)		{ frame = _frame; }
	LIFE		GetLife(void)			{ return life; }
	void		SetPos(float _x, float _y);
	void		SetDxDy(float _dx, float _dy);

	int					score;          //����
	int					timer;          //��ʱ��
	DWORD				tick;           //�δ���
	int					kill;			//ɱ����
private:
    struct MarioData	m_marioData;
	bool				show;
	MARIOSTATE			state;          //�ڿ��л����ڵ���
	LIFE				life;			//����ֵ
	FRAME				frame;          // ֡��
	DIR					dir;            //����ķ���
	MAXSPEED			maxSpeed;       //����ٶ�
	CollisionPoint      footPoint[2];   //�ŵ�������ײ����
	CollisionPoint		headPoint[2];   //ͷ��������ײ����
	CollisionPoint		leftPoint[2];   //���������ײ����
	CollisionPoint		rightPoint[2];  //�ұ�������ײ����
	
};
#endif
