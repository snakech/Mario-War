#ifndef		LOGERROR_H
#define		LOGERROR_H
#include	<iostream>
using namespace  std ;
#include	<stdio.h>
inline bool LOG(char *t_String)
{
	FILE  *fp ;
	fp = fopen("log.txt","a+") ;
	if(fp == NULL)
	{
		cout<<"open file error"<<endl ;
		return false ;
	}


	fprintf(fp,t_String) ;
	putc('\n',fp) ;
	if(fp != NULL)
	{
		fclose(fp) ;
	}
	
	return true ;
} 

#endif