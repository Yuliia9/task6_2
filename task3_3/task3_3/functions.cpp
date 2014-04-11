/*
*@file		functions.cpp
*@brief		implements functions used in file task3_3.cpp
			uses developed dll and lib library for working with C string
*/
#include "stdafx.h"
#include "task3_3.h"
#include <stdlib.h>

#ifdef USE_STRING_H
#include <string.h>
#define STREND '\0'
STRLEN_PRINT mystrlen = (STRLEN_PRINT)strlen;
STRLEN_PRINT myprintf = (STRLEN_PRINT)puts;
STRTOK mystrtok = (STRTOK)strtok;
STRCHR mystrchr = (STRCHR)strchr;
STRCPY mystrcpy = (STRCPY)strcpy;


#elif defined (USE_MY_LIB)
#include "my_string.h"
STRLEN_PRINT mystrlen = (STRLEN_PRINT)my_strlen;
STRLEN_PRINT myprintf = (STRLEN_PRINT)my_strprintf;
STRTOK mystrtok = (STRTOK)my_strtok;
STRCHR mystrchr = (STRCHR)my_strchr;
STRCPY mystrcpy = (STRCPY)my_strcpy;


#elif defined (USE_MY_DLL) 
#include <windows.h> 
HINSTANCE stringdll = LoadLibrary(TEXT("stringdll.dll"));
char* end = (char*)GetProcAddress(stringdll, LPCSTR("STREND"));
const char STREND = *end;
STRLEN_PRINT mystrlen = (STRLEN_PRINT)GetProcAddress(stringdll, LPCSTR("my_strlen"));
STRLEN_PRINT myprintf = (STRLEN_PRINT)GetProcAddress(stringdll, LPCSTR("my_strprintf"));
STRTOK mystrtok = (STRTOK)GetProcAddress(stringdll, LPCSTR("my_strtok"));
STRCHR mystrchr = (STRCHR)GetProcAddress(stringdll, LPCSTR("my_strchr"));
STRCPY mystrcpy = (STRCPY)GetProcAddress(stringdll, LPCSTR("my_strcpy"));
unsigned int Check_Loading_Library(void)
{
	if (stringdll == NULL)
	{
		return FAIL;
	}
	else if (end == NULL || mystrlen == NULL || myprintf == NULL || mystrtok == NULL || mystrchr == NULL || mystrcpy == NULL)
	{
		return FAIL;
	}
	return SUCCESS;
}
 #endif


void Interface(void)
{
	puts("------------------------------------------------------------------\n");
	puts("Hi! Welcome to the genius character finder.\n");
	puts("Enter sentences and character \nand program will find for you words that include that character. \n");
	puts("Program made by Yuliia Lyubchik.\n");
	puts("------------------------------------------------------------------\n\n");
}

unsigned char Input(char** riadok, char* character)
{
	unsigned char retCode;
	char temp;
	int count;
	do
	{
		printf("Please enter sentence: ");
		count = 0;
		do
		{
			scanf("%c", &temp);
			++count;
			*riadok = (char*)realloc(*riadok, count * sizeof(char));

			if (*riadok != NULL)
			{
				*(*riadok + count - 1) = temp;
			}
			else
			{
				free(riadok);
				return FAIL;
			}
		} 
		while (temp != '\n' && temp != EOF);
		fflush(stdin);
		*(*riadok + count - 1) = STREND;
	} 
	while (riadok == NULL || mystrlen(*riadok) == 0);

	do
	{
		printf("Please enter character that you want to find in words: ");
		retCode = scanf("%c", &(*character));
		fflush(stdin);
		if (*character >= 'A' && *character <= 'Z')
		{
			break;
		}
		else if (*character >= 'a' && *character <= 'z')
		{
			break;
		}
		else
		{
			retCode = FAIL;
		}
	} 
	while (*character == '\n' || retCode == FAIL);
	++character;
	*character = STREND;
	return SUCCESS;
}

unsigned char Print_words(const char* riadok, char* character)
{
	if (riadok == NULL || character == NULL)
	{
		return (int)ERROR;
	}
	char* begin = NULL;		/*pointer to the begin of the word that include character*/
	char* end;				/*pointer to the end of the word that include character*/
	char* copy = NULL;
	int len;
	len = mystrlen(riadok);
	if (riadok != NULL && len > 0)
	{
		copy = (char*)malloc(len * sizeof(char));
		copy = mystrcpy(copy, riadok);
	}

	begin = copy;
	unsigned int n = 0;
	while (begin != NULL)
	{
		end = Find(copy, &begin, character);
		if (end == NULL)
		{
			return FAIL;
			break;
		}
		else if (end == begin)
		{
			myprintf(begin);
			break;
		}
		myprintf(begin);
		puts(",");
		n += (end - copy);
		copy = mystrcpy(copy, riadok + n);
	}
#ifdef USE_MY_DLL
	FreeLibrary(stringdll);
#endif
	return SUCCESS;
}


char* Find(char* sentence, char** begin, const char* character)
{
	if (sentence == NULL)
	{
		return NULL;
	}

	char* temp;
	char* token;
	char* end = NULL;

	const char delimiters[] = { ' ', ',', '-', '.', ':', ';', '(', ')', '[', ']', '!', '?', STREND };

	token = mystrtok(sentence, delimiters);
	while (token != NULL)
	{
		temp = mystrchr(token, *character);
		if (temp != NULL)
		{
			end = mystrtok(NULL, delimiters);
			*begin = token;
			if (end == NULL)
			{
				end = *begin;
			}
			break;
		}
		else
		{
			token = mystrtok(NULL, delimiters);
		}
	}
	return end;
}