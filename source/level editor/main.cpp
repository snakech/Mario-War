#include	"CManager.h"
#include	"LogError.h"
#pragma	comment ( lib, "SDL.lib" )
#pragma comment ( lib, "SDLmain.lib" )

int main(int argc, char **argv)
{

	CManager *manager = new CManager;
	manager->Start();
	delete manager;
	return 0;
}