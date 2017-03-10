#include		"CMap.h"
#include		<cstdio>
#include		"GameInfo.h"
#include		"LogError.h"
CMap::CMap(void)
{
	FILE *fp;
	fp = fopen("map\\level1.d","r");

	if(fp == NULL)
	{
		LOG("can't open map file !");
	}
	/*游戏开始，载入地图数据*/
	for(int j=0; j<=MAP_Y-1; j++)
	for(int i=0; i<=MAP_X-1; i++)
	{
		/*tile类型*/
		fscanf(fp,"%d",&(maps[j][i]));   
		putc('\n',fp);

		/*tile其他*/
//		maps[j][i].x		= i*TILE_WIDTH;
	//	maps[j][i].y		= j*TILE_HEIGHT;
	//	maps[j][i].dx	= 0;
	//	maps[j][i].dy    = 0;
	}

	fclose(fp);
}

CMap::~CMap(void)
{

}

void	CMap::LoadMap(int level)
{
	FILE *fp;
	char a[50];
	sprintf(a,"map\\level%d.d",level);
	fp = fopen(a,"r");

	if(fp == NULL)
	{
		LOG("can't open map file !");
	}
	/*游戏开始，载入地图数据*/
	for(int j=0; j<=MAP_Y-1; j++)
	for(int i=0; i<=MAP_X-1; i++)
	{
		/*tile类型*/
		fscanf(fp,"%d",&(maps[j][i]));   
		putc('\n',fp);
	}

	fclose(fp);
}
