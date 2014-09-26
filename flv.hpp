#ifndef PARAMETER_H__
#define PARAMETER_H__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXFILENAMELEN 30

char *get_filename_prefix(char *filename)
{
	char *p_chr = (char*)malloc(sizeof(char));
	int len = strlen(filename);
	char *buff = (char*)malloc(sizeof(char)*len);
	memset(buff, 0, len );
	p_chr = filename + len;
	while( *p_chr != '.')
	{
		--p_chr;
		--len;
	}
	strncpy(buff, filename, len);
	return buff;
}
char *get_filename_extent(char *filename)
{
	char *p_chr = (char*)malloc(sizeof(char));
	int len = strlen(filename);
	char *buff = (char*)malloc(sizeof(char)*len);
	memset(buff, 0, len );
	p_chr = filename + len;
	while( *p_chr != '.')
	{
		--p_chr;
		--len;
	}
	buff = p_chr;
	return buff;
}

#endif
