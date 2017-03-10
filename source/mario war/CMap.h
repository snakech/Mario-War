#ifndef			CMAP_H
#define			CMAP_H
#include		"GameInfo.h"
struct		Map
{
	int		style;
	float	x;
	float	y;
	float   dx;
	float   dy;

};
class		CMap
{
public:
	CMap(void);
	~CMap(void);
	void	    LoadMap(int level);
//	Map			*GetMap(void);

public:
   int     maps[MAP_Y][MAP_X];
};
#endif