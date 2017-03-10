#include	"CGetInput.h"
#include	<SDL.h>

bool	CGetInput::IsKeyDown(int _key)
{
	Uint8 *keystate = SDL_GetKeyState(NULL);
	if ( keystate[_key] ) 
	{
		return true;
	}
	else
	{
		return false;
	}

}

bool	CGetInput::IsMouseButtonPress(int _button)
{
	if(SDL_GetMouseState(&mousePosx, &mousePosy)&SDL_BUTTON(_button))
	{
		return true;
	}

	else
	{
		return false;
	}
}

void	CGetInput::UpdateMousePos(void)
{
	SDL_GetMouseState(&mousePosx, &mousePosy);
}