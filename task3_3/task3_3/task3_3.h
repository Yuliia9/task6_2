#ifndef TASK3_3_H_
#define TASK3_3_H_

/*
*@file		task3_3.h
*@brief		header file that defines prototypes of functions used in file task3_3.cpp
*/

#include "stdafx.h"

/*for choosing what library to use*/
//#define USE_STRING_H
#define USE_MY_LIB
//#define USE_MY_DLL

const unsigned char FAIL = 0;
const unsigned char SUCCESS = 1;
const unsigned int MAIN_SUCCESS = 0;

typedef int(*STRLEN_PRINT) (const char*);
typedef char* (*STRTOK) (char*, const char*);
typedef char* (*STRCHR)(char*, int);
typedef char* (*STRCPY) (char*, const char*);


/*
* @brief				This function displays general information about program to users
* @param	void
* @return	void
*/
void Interface(void);

/**
* @brief				This function checks if string dll library was loaded
* @param	void
* @return	void
*/
unsigned int Check_Loading_Library(void);


/*
* @brief					Function for inputing string
* @param	[in/out]		char** riadok - a pointer to null pointer to string of sentences
			[in/out]		char* character - a pointer to input character needed to be find
*
*@return	unsigned char	Return ERROR if error occurs while trying to allocate memory for string
							Return SUCCESS if string and character were inputed
*/
unsigned char Input(char** riadok, char* character);


/*
* @brief					Function for printing words that include character
* @param	[in]			char* riadok - a pointer to C string 
			[in]			char* character - a pointer to character needed to be find
*
*@return	unsigned char	Return ERROR if one of the parameters is a null pointer
							Return SUCCESS if words were printed
*/
unsigned char Print_words(const char* riadok, char* character);


/*
* @brief					Function for finding words in sentences
* @param	[in/out]		char* sentence - a pointer to sentences for finding words
			[in/out]		char** begin - begin of word that include character
			[in]			const char* character - character that needed to be found
*
*@return	char*			Return pointer to the end of word that include character 
							Return NULL if character wasn't find
*/
char* Find(char* sentence, char** begin, const char* character);

#endif