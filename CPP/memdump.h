#pragma once
//  memdump
//
//	This function will dump the content of the passed memory buffer (1), starting at offset (2) for length (3).
//  
//
//  PARAMETERS
//
//		void *					-	Const pointer to the memory buffer haystack.
//		size_t					-	Offset in the memory buffer to start dumping.
//		size_t					-	Length of the memory to dump.
//		char *					-	Pointer to an annotation for the header and trailer lines
//		std::ostream&			-	Reference to the stream to dump to			
//
//  RETURNS
//
//  NOTES
//
//		1.  If the passed buffer is nullptr then no dump is performed
//
//

#if  (defined(_WIN32) || defined(_WIN64))
#else
#define		strcat_s(t,l,s)		strcat(t,s)
#define		strcpy_s(t,l,s)		strcpy(t,s)
#define		strncpy_s(t,l,s,c)	{memcpy(t,s,c);   \
            t[c] = '\0';}
#define		sprintf_s(t,l,f, ...) sprintf(t, f,  __VA_ARGS__)
#define		vsprintf_s(t,l,f,v) vsprintf(t,f,v)
#endif

//  Language headers
#include	<ctype.h>
#include	<cstddef>
#include	<string.h>

//  Constants
constexpr auto START_DUMP = "+---- Start of Dump: %s -------------- %lu (0x%.4lx) bytes @%p --------------";
constexpr auto END_DUMP = "+---- End of Dump:   %s -------------- %lu (0x%.4lx) bytes @%p --------------";
constexpr auto DUMP_LINE = "%04lx: %s  %s :%s %s";

void	memdump(const void* lpMem, size_t iOff, size_t iLen, const char* szSymbol, std::ostream& os) {
	size_t			iResidue = 0;														//  Count of bytes left to dump
	size_t			iIndex = 0;															//  Index counter
	size_t			iOffset = 0;														//  Offset in the memory buffer
	char			szHexSeg1[30] = {};													//  First segment of Hexadecimal
	char			szHexSeg2[30] = {};													//  Second segment of Hexadecimal
	char			szRawSeg1[10] = {};													//  First segment of Ascii data
	char			szRawSeg2[10] = {};													//  Second segment of Ascii data
	char			szTemp[20] = {};													//  Temporary format area
	char			cLocalBuffer[20] = {};												//  Local buffer
	char			szMsg[512] = {};													//  Generic message buffer
	char* BfrPtr = nullptr;													//  Pointer into the memory buffer
	char* LocalBfrPtr = nullptr;												//  Pointer into the local buffer

	//  Show start of the dump message
	sprintf_s(szMsg, 512, START_DUMP, szSymbol, (unsigned long)(iLen), (unsigned long)(iLen), lpMem);
	while (strlen(szMsg) < 75)
	{
		strcat_s(szMsg, 512, "-");
	}
	os << szMsg << std::endl;

	//  Dump each of the lines of the body of the dump
	iResidue = iLen;
	BfrPtr = (char*)lpMem;
	BfrPtr += iOff;
	while (iResidue > 0) {
		szHexSeg1[0] = '\0';
		szHexSeg2[0] = '\0';
		szRawSeg1[8] = '\0';
		szRawSeg2[8] = '\0';
		//  Copy the data to the local buffer
		if (iResidue >= 16)
		{
			memcpy(cLocalBuffer, BfrPtr, 16);
		}
		else
		{
			memset(cLocalBuffer, 0, 16);
			memcpy(cLocalBuffer, BfrPtr, iResidue);
		}
		LocalBfrPtr = (char*)cLocalBuffer;
		for (iIndex = 0; iIndex < 16; iIndex++)
		{
			sprintf_s(szTemp, 20, "%02X ", (unsigned short)*LocalBfrPtr);
			if (iIndex < 8)
			{
				strcat_s(szHexSeg1, 30, szTemp);
				if ((*LocalBfrPtr < 33) || (*LocalBfrPtr > 126))
				{
					szRawSeg1[iIndex] = '.';
				}
				else
				{
					szRawSeg1[iIndex] = *LocalBfrPtr;
				}
			}
			else
			{
				strcat_s(szHexSeg2, 30, szTemp);
				if ((*LocalBfrPtr < 33) || (*LocalBfrPtr > 126))
				{
					szRawSeg2[iIndex - 8] = '.';
				}
				else
				{
					szRawSeg2[iIndex - 8] = *LocalBfrPtr;
				}
			}
			LocalBfrPtr++;
		}
		//  Format the dump line
		sprintf_s(szMsg, 512, DUMP_LINE, (unsigned long)(iOffset + iOff), szHexSeg1, szHexSeg2, szRawSeg1, szRawSeg2);
		os << szMsg << std::endl;

		//  Position to the next chunk of the memory block
		iOffset = iOffset + 16;
		if (iResidue >= 16) iResidue = iResidue - 16;
		else iResidue = 0;
		BfrPtr = BfrPtr + 16;
	}

	//  Show the end of the dump in the log
	sprintf_s(szMsg, 512, END_DUMP, szSymbol, (unsigned long)(iLen), (unsigned long)(iLen), lpMem);
	while (strlen(szMsg) < 75)
	{
		strcat_s(szMsg, 512, "-");
	}
	os << szMsg << std::endl;

	//  Return to caller
	return;
}
