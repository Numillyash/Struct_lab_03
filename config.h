#ifndef CONFIG_H
#define CONFIG_H

#define _CRT_SECURE_NO_WARNINGS
//#define DEBUG

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
// #include <malloc.h>
#include <time.h>
#include <stdint.h>
#include <locale.h>
#include <sys/stat.h>

// input console checking

// boolean
#define BOOL int
#define TRUE 1
#define FALSE 0

// file
#define FILE_OPENING_ERROR "Cannot open the %s file.\n"

/// <summary>
/// Error codes
/// </summary>
typedef enum
{
	SUCCESS,
	FAILURE,
	NO_ARGUMENTS_FAILURE,
	WRONG_ARGUMENT_FAILURE,
	NOT_ENOUGH_ARGUMENTS_FAILURE,
	MEMORY_ALLOCATION_FAILURE,
	FILENAME_LENGTH_FAILURE,
	FILENAME_SYMBOL_FAILURE,
	FILENAME_ENDING_FAILURE,
	FORMAT_FAILURE,
	EXISTING_NAME_FAILURE,
	DEBUG_EXIT_CODE = 100,
	WRONG_OPTION
} ERROR_CODE;

// fast funcs
#define swap(a, b) \
	;              \
	b = a + b;     \
	a = b - a;     \
	b = b - a;
#ifdef _WIN32
#else
#define max(a, b) (a > b) ? a : b
#endif

#define COMMAND_COUNT 6

static const char allowedCommands[][200] = {"cd", "ls", "rm", "mkdir", "touch", "find"};

#endif // !CONFIG_H