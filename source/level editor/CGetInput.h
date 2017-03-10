#ifndef			CGETINPUT_H
#define			CGETINPUT_H

class			CGetInput
{
public:
	CGetInput(void)					{ mousePosx = 0; mousePosy = 0; }
	~CGetInput(void) {}
	bool	IsKeyDown ( int _key );
	bool	IsMouseButtonPress ( int _button);
	void	UpdateMousePos(void);
	int		GetMousePosx(void)		{ return mousePosx; }
	int		GetMousePosy(void)		{ return mousePosy; }
private:
	int mousePosx;
	int mousePosy;
	int *keystate;
};
#endif