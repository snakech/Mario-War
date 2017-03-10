#ifndef			CMARIO_H
#define			CMARIO_H
#include		"CBugbearMgr.h"
#include		"CAudioMgr.h"
#include		"CBugbear.h"
#include		"CMap.h"

/*mario 的属性*/
struct		MarioData
{
	float	x;          // x坐标 
	float	y;          // y坐标
	float   dx;         // x增量
	float   dy;         // y增量
	float   a;          // x方向加速度
	float   lf;         // 地面摩擦力
	float   af;         // 空气摩擦
	float   g;          // 重力
	float   dt;         // 时间片
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

	int					score;          //分数
	int					timer;          //记时器
	DWORD				tick;           //滴答声
	int					kill;			//杀低数
private:
    struct MarioData	m_marioData;
	bool				show;
	MARIOSTATE			state;          //在空中或则在地上
	LIFE				life;			//生命值
	FRAME				frame;          // 帧号
	DIR					dir;            //面向的方向
	MAXSPEED			maxSpeed;       //最大速度
	CollisionPoint      footPoint[2];   //脚底两个碰撞检测点
	CollisionPoint		headPoint[2];   //头顶两个碰撞检测点
	CollisionPoint		leftPoint[2];   //左边两个碰撞检测点
	CollisionPoint		rightPoint[2];  //右边两个碰撞检测点
	
};
#endif
