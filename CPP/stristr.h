#pragma once
//  stristr
// 
//  VERSION:	v1.0.0
//  AUTHOR:		Ian J. Tree
//
//	Performs a case insensitive search for the first occurrence of the passed sub-string or needle (2) 
//  in the passed search space (1) or haystack.
//
//  PARAMETERS
//
//		const char *			-	Const pointer to the well formed (null terminated) string to be searched (search space) or haystack.
//		const char *			-	Const pointer to the well formed (null terminated) character sub-string array to be searched for or needle.
//
//  RETURNS
//
//		const char *			-	Const pointer to the first occurrence of the sub-string (2) within the string (1), nullptr if not found
//
//  NOTES
//
//		1.  If the passed string is nullptr then the function returns nullptr
//		2.  If the passed sub-string is nullptr then the function returns a pointer to the passed string
//		3.  If the passed sub-string is empty then the function returns a pointer to the passed string
//		4.  If the passed string is empty then the function returms nullptr
//		5.  The contract behaviour of the functions follows the contract for the standard strstr function
// 
// DEPENDENCIES
// 
//		Depends on 'strichr()' for searching for a character needle in a haystack (strichr.h).
//
//  ALGORITHM
//
//		The algorithm performs a pivot search of the haystack (1) for each candidate string that matches the first 
//      and last character of the needle (2) irrespective of case.
//		Candidate strings are then checked for a case-insensitive match on the characters between the two ends.
//

//  Local function headers
#include	"strichr.h"

const char* stristr(const char* pHaystack, const char* pNeedle) {
	char			SNC = '\0';														//  Start of needle character
	char			ENC = '\0';														//  End of needle character
	size_t			Span = 0;														//  Span of the needle (length - 2)
	const char* pSOSS = pHaystack;												//  Start of the search space
	const char* pCandidate = nullptr;											//  Candidate matching string

	//  Police the contract
	if (pHaystack == nullptr) return nullptr;
	if (pNeedle == nullptr) return pHaystack;
	if (*pNeedle == '\0') return pHaystack;
	if (*pHaystack == '\0') return nullptr;

	//  Test for the degenerate case where the length of the needle is one.
	//  In which case use strichr() to satisfy the search.

	Span = strlen(pNeedle);
	if (Span == 1) return strichr(pHaystack, *pNeedle);
	Span -= 2;

	//  Capture the first and last character of the search string (needle)
	SNC = pNeedle[0];
	ENC = toupper(pNeedle[Span + 1]);

	//
	//  Perform a pivot search of the search space (haystack) finding a match for the first character and last character of the
	//  search string in the expected position.
	//

	//  Find the first occurrence of the first character in the needle
	pCandidate = strichr(pSOSS, SNC);

	while (pCandidate != nullptr) {

		//  Adjust the start of search space
		pSOSS++;

		//  Test for End-Of-String within the span of the needle
		if (memchr(pCandidate, '\0', Span) != nullptr) pCandidate = nullptr;
		else {
			//  Test for a match of the last character in the needle
			if (toupper(pCandidate[Span + 1]) == ENC) {

				//  The two ends of the needle match the current position in the search space.
				//  Check for a match for the inner characters of the needle.

				for (size_t IX = 1; IX <= Span; IX++) {
					if (toupper(pCandidate[IX]) != toupper(pNeedle[IX])) break;
					//  Check for a complete match of the inner characters - if complete return the candidate 
					if (IX == Span) return pCandidate;
				}
			}

			//  Find the next occurrence of the first character in the needle
			pCandidate = strichr(pSOSS, SNC);
		}
	}

	//  Needle was NOT found
	return nullptr;
}

//  non-const overload
//
//  If the haystack passed is non-const then it is safe to return a non-const pointer for the search result.
//

char* stristr(char* pHaystack, const char* pNeedle) {
	return const_cast<char*>(stristr(const_cast<const char*>(pHaystack), pNeedle));
}
