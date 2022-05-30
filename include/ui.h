#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define GETSTRING_ERR_RE -1
#define GETSTRING_ERR_OVERFLOW -2

#define MAX_COMMAND_LEN 200

int getString(char* str, const int size)
{
	char* buf = (char*) malloc(size + 1);
	if (gets(buf) == NULL)
	{
		return GETSTRING_ERR_RE;
	}

	if (strlen(buf) == size)
	{
		return GETSTRING_ERR_OVERFLOW;
	}

	strcpy(str, buf);
	free(buf);
	
	return 0;
}

int commandCallHandler()
{
	char* command = (char*) malloc(MAX_COMMAND_LEN);
	char* buf = (char*) malloc(MAX_COMMAND_LEN);
	int result;

	result = getString(command, MAX_COMMAND_LEN-1);
	if (result == 0)
	{
		// Разбиваем на лексемы и обрабатываем команду
	}

	else
	{
		return -1;
	}
}
