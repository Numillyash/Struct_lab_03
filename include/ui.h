#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_COMMAND_LEN 200

#define GETSTRING_ERR_RE -1
#define GETSTRING_ERR_OVERFLOW -2

void clearExtraInput()
{
	int c;
	while ((c = getchar()) != '\n' && c != EOF) {}
}

int getString(char* str, const int size)
{
	char* buf = (char*) malloc(size + 1);
	if (fgets(buf, size, stdin) == NULL)
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

char* commandCallHandler()
{
	char* command = (char*) malloc(MAX_COMMAND_LEN);
	char* buf = (char*) malloc(MAX_COMMAND_LEN);
	int result;

	result = getString(command, MAX_COMMAND_LEN-1);
	if (result == 0)
	{
		strcpy(buf, command);
		return buf;
	}

	else
	{
		return NULL;
	}
}
