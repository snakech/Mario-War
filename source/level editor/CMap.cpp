#include		"CMap.h"
#include		"EditorInfo.h"
#include		<stdio.h>
CMap::CMap(void)
{
	for(int j=0; j<= MAP_Y-1; j++)
	for(int i=0; i<= MAP_X-1; i++)
	{
		map[j][i] = 0;
	}
}

bool	CMap::SaveAsFile(void)
{
	FILE *fp;
	fp = fopen("level\\01.d","w");

	if(fp == NULL)
	{
		printf("can't open file");
		return false;
	}
	for(int j=0; j<=MAP_Y-1;j++)
    for(int i=0; i<=MAP_X-1;i++)
	{
		fprintf(fp,"%d",map[j][i]);   //向文件里写。。  //fscanf()从文件里往外写
		putc('\n',fp);
	}
	
	fclose(fp);

	return true;
}