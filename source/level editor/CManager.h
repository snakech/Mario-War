#ifndef			CMANAGER_H
#define			CMANAGER_H
#include		"CRender.h"
#include		"CMap.h"
#include		"CGetInput.h"
class		CManager
{
public:
	CManager(void) { state = INIT_SYS; brun = true; tileStyle = 1;}
	~CManager(void) {}
	bool	SysInit(void);
	bool	SysRelease(void);
	bool	DataInit(void);
	void	DoMessage(void);
	void	Start(void);    //Æô¶¯±à¼­Æ÷
	void	MainLoop(void); //Ö÷Ñ­»·

	void	SelectTile(void);
	void	EditorMap(void);
private:
	bool		brun;
	int			state;
	int			tileStyle;
	CRender		*render;
	CMap		*map;
	CGetInput	*input;
};
#endif