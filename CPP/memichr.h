#pragma once
//  memichr
// 
//  VERSION:	v1.0.0
//  AUTHOR:		Ian J. Tree
//
//	Performs a case insensitive search for the first occurrence of the passed character (2) in the memory buffer (1)
//  of length (3).
//
//  PARAMETERS
//
//		void *					-	Const pointer to the memory buffer search space (haystack).
//		int						-   The character value to search for (needle) in the range 0 to 255 (0x00 to 0xFF).
//		size_t					-	Length of the memory buffer pointed to by (1) (haystack).
//
//  RETURNS
//
//		void *					-	A pointer to the first occurrence of the upper or lower case occurrence of the search character,
//									nullptr if the character was not found in the search space.
//
//  NOTES
//
//		1.  If the passed buffer is nullptr then the function returns nullptr.
//		2.	If the buffer length is 0 then return nullptr.
//		3.  The contract behaviour of the functions follows the contract for the standard memchr function
//
//  ALGORITHM
//
//		The algorithm searches the search space (1) for both the lowecase and uppercase passed character (2) using memchr() 
//      and returns the lowest (i.e. earliest encountered) pointer.
//

//  Language headers
#include	<ctype.h>
#include	<vcruntime_string.h>

const void* memichr(const void* pHaystack, int Needle, size_t HayLen) {
	char			LCN = tolower(Needle & 255);									//  Lower case needle
	char			UCN = toupper(Needle & 255);									//  Uppercase needle
	const void* pLCC = nullptr;													//  Pointer to the first occurrence of the lower case needle
	const void* pUCC = nullptr;													//  Pointer to the first occurrence of the upper case needle

	//  Police the contract
	if (pHaystack == nullptr) return nullptr;
	if (HayLen == 0) return nullptr;

	//
	//  Find the first occurrence of both the uppercase and the lowercase needle
	//

	pLCC = memchr(pHaystack, LCN, HayLen);
	pUCC = memchr(pHaystack, UCN, HayLen);

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

void* memichr(void* pHaystack, int Needle, size_t Haylen) {
	return const_cast<void*>(memichr(const_cast<const void*>(pHaystack), Needle, Haylen));
}
