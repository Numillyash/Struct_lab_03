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
#define HELP_CONSOLE_OPTION_1 "-h"
#define HELP_CONSOLE_OPTION_2 "--help"
#define GENKEY_CONSOLE_OPTION "genkey"
#define SIGNATURE_CONSOLE_OPTION "sign"
#define CHECK_CONSOLE_OPTION "check"
#define ENCRYPT_CONSOLE_OPTION "encrypt"
#define DECRYPT_CONSOLE_OPTION "decrypt"
#define SIZE_CONSOLE_OPTION "--size"
#define PUBKEY_CONSOLE_OPTION "--pubkey"
#define SECRET_CONSOLE_OPTION "--secret"
#define SIGFILE_CONSOLE_OPTION "--sigfile"
#define INFILE_CONSOLE_OPTION "--infile"
#define OUTFILE_CONSOLE_OPTION "--outfile"

// boolean
#define BOOL int
#define TRUE 1
#define FALSE 0

// RSA
#define KEYSIZE_MODULE 256
typedef enum {
	KEY_256 = 256,
	KEY_512 = 512,
	KEY_1024 = 1024,
	KEY_2048 = 2048
} KEY_BIT_SIZE;

// file
#define FILE_OPENING_ERROR "Cannot open the %s file.\n"

#define primes_128_bit_filename "primes_128_bit.blackleague"
#define primes_256_bit_filename "primes_256_bit.blackleague"
#define primes_512_bit_filename "primes_512_bit.blackleague"
#define primes_1024_bit_filename "primes_1024_bit.blackleague"

/// <summary>
/// Exit codes for exit()
/// </summary>
enum EXIT_CODE {
	SUCCESS,
	FAILURE,
	NO_ARGUMENTS_FAILURE,
	WRONG_ARGUMENT_FAILURE,
	NOT_ENOUGH_ARGUMENTS_FAILURE,
	FILE_OPEN_FAILURE,
	FILE_FORMAT_FAILURE,
	LOG_FAILURE,
	MEMORY_ALLOCATION_FAILURE,
	GET_PRIME_FAILURE,
	GET_NUMBER_FAILURE,
	DEBUG_EXIT_CODE = 100
};

// fast funcs
#define swap(a,b); b = a+b; a = b-a; b = b-a;
#ifdef _WIN32
#else
#define max(a,b) (a>b)? a : b
#endif

#endif // !CONFIG_H