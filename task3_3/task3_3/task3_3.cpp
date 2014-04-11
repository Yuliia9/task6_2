/*
* @file			task3_3.cpp
* @brief		Program shows all words that include defined character
				uses developed lib or dll library or standart library string.h for working with C string

* Copyright 2014 by Yuliia Lyubchik Inc.,
*
* This software is the confidential and proprietary information
* of Yuliia Lyubchik. ("Confidential Information").  You
* shall not disclose such Confidential Information and shall use
* it only with permission from Yuliia.
*
*/

#include "stdafx.h"
#include "task3_3.h"	/*defines prototypes of used in this file functions*/
#include <stdlib.h>

int main( )
{
	Interface();
#ifdef USE_MY_DLL
	if (Check_Loading_Library() == FAIL)
	{
		puts("Can't load dll library");
		return FAIL;
	}
#endif
	char* riadok = NULL;
	char character[2] = {0,0};
	unsigned char retCode;
	
	retCode = Input(&riadok, character);
	if (retCode == FAIL)
	{
		puts("Error occurs while trying to input string.\n");
		return (int)FAIL;
	}
	puts("\nWords that include character: ");
	retCode = Print_words(riadok, character);
	if (retCode == FAIL)
	{
		puts("\nSorry, there are no words with such character.\n");
	} 

	puts("\n");
	free(riadok);
	system("pause");
	return MAIN_SUCCESS;
}




