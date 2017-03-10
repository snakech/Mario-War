#include		"GetKeyInput.h"
#include		<SDL.h>
#include		<windows.h>
bool	IsKeyDown(int _key)
{

		if(KEYDOWN(_key))
			return true;
		else
			return false;
}

bool	PressLeftButton(int *x, int *y )
{
	if(SDL_GetMouseState( x, y )&SDL_BUTTON(1) )
	{
		return true;
	}

	else
	{
		return false;
	}

}


bool	PressRightButton(int *x, int *y )
{
	if(SDL_GetMouseState( x, y )&SDL_BUTTON(3) )
	{
		return true;
	}

	else
	{
		return false;
	}

}


void	GetMousePos(int *x, int *y)
{
	SDL_GetMouseState( x, y );
}