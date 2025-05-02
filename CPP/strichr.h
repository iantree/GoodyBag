#pragma once
//  strichr
// 
//  VERSION:	v1.0.0
//  AUTHOR:		Ian J. Tree
//
//	Performs a case insensitive search for the first occurrence of the passed character (2) in the well formed (null terminated) 
//  passed string or haystack (1).
//
//  PARAMETERS
//
//		char *					-	Const pointer to the well formed string search space (haystack).
//		int						-   The character value to search for (needle) in the range 0 to 255 (0x00 to 0xFF).
//
//  RETURNS
//
//		char *					-	A const pointer to the first occurrence of the upper or lower case occurrence of the search character,
//									nullptr if the character was not found in the search space.
//
//  NOTES
//
//		1.  If the passed string is nullptr then the function returns nullptr.
//		2.  If the passed string is empty then the function returns nullptr.
//		3.  If the character to be searched for is NULL (0x00) then the function returns nullptr.
//		4.  The contract behaviour of the functions follows the contract for the standard strchr function
//
//  ALGORITHM
//
//		The algorithm searches the search space (1) for both the lowecase and uppercase passed character (2) using strchr() 
//      and returns the lowest (i.e. earliest encountered) pointer.
//

//  Language headers
#include	<ctype.h>
#include	<vcruntime_string.h>

const char* strichr(const char* pHaystack, int Needle) {
	char			LCN = tolower(Needle & 255);									//  Lower case needle
	char			UCN = toupper(Needle & 255);									//  Uppercase needle
	const char* pLCC = nullptr;													//  Pointer to the first occurrence of the lower case needle
	const char* pUCC = nullptr;													//  Pointer to the first occurrence of the upper case needle

	//  Police the contract
	if (pHaystack == nullptr) return nullptr;
	if (*pHaystack == '\0') return nullptr;
	if (Needle == 0) return nullptr;

	//
	//  Find the first occurrence of both the uppercase and the lowercase needle
	//

	pLCC = strchr(pHaystack, LCN);
	pUCC = strchr(pHaystack, UCN);

	//
	//  If neither upper nor lowercase needles were found return nullptr.
	//	If either upper or lowercase needles were not found, return the other.
	//  If both were found then return the lowest value (i.e. earliest in the buffer).
	//

	if (pLCC == nullptr) return pUCC;
	if (pUCC == nullptr) return pLCC;
	if (pLCC < pUCC) return pLCC;
	return pUCC;
}

//  non-const overload
//
//  If the haystack passed is non-const then it is safe to return a non-const pointer for the search result.
//

char* strichr(char* pHaystack, int Needle) {
	return const_cast<char*>(strichr(const_cast<const char*>(pHaystack), Needle));
}
