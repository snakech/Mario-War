#include	"CGameMgr.h"
#include	<ctime>
#include	<SDL.h>
#pragma	comment (lib, "SDL.lib" )
#pragma comment (lib, "SDLmain.lib" )
#pragma comment (lib, "SDL_image.lib")
#pragma	comment (lib, "audiere.lib")
int main( int argc, char *argv[] )
{
	 
	 srand((unsigned)time(NULL)); 
	 CGameMgr *game = new CGameMgr;
	 game->Start();
	 game->Release();
	 delete game;
	 return 0;
}