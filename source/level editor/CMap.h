#ifndef			CMAP_H
#define			CMAP_H
#include		"EditorInfo.h"
class		CMap
{
public:
	CMap(void);
	~CMap(void) {}
	bool	SaveAsFile(void);
	int		map[MAP_Y][MAP_X];
};
#endif