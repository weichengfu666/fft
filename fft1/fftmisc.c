/*============================================================================

    fftmisc.c  -  Don Cross <dcross@intersrv.com>

    http://www.intersrv.com/~dcross/fft.html

    Helper routines for Fast Fourier Transform implementation.
    Contains common code for fft_float() and fft_double().

    See also:
        fourierf.c
        fourierd.c
        ..\include\fourier.h

    Revision history:

1998 September 19 [Don Cross]
    Improved the efficiency of IsPowerOfTwo().
    Updated coding standards.

============================================================================*/

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "fourier.h"


#define TRUE  1
#define FALSE 0

#define BITS_PER_WORD   (sizeof(unsigned) * 8)


int IsPowerOfTwo ( unsigned x )
{
    if ( x < 2 )
        return FALSE;

    if ( x & (x-1) )        // Thanks to 'byang' for this cute trick!
        return FALSE;

    return TRUE;
}


unsigned NumberOfBitsNeeded ( unsigned PowerOfTwo )
{
    unsigned i;

    if ( PowerOfTwo < 2 )
    {
        fprintf (
            stderr,
            ">>> Error in fftmisc.c: argument %d to NumberOfBitsNeeded is too small.\n",
            PowerOfTwo );

        // exit(1);
        return 0;
    }

    for ( i=0; ; i++ )
    {
        if ( PowerOfTwo & (1 << i) )
            return i;
    }
}



unsigned ReverseBits ( unsigned index, unsigned NumBits )
{
    unsigned i, rev;

    for (i = rev = 0; i < NumBits; i++) {
        rev = (rev << 1) | (index & 1);
        index >>= 1;
    }

    return rev;
}


double Index_to_frequency ( unsigned NumSamples, unsigned Index )
{
    if ( Index >= NumSamples )
        return 0.0;
    else if ( Index <= NumSamples/2 )
        return (double)Index / (double)NumSamples;

    return -(double)(NumSamples-Index) / (double)NumSamples;
}


int myatoi(char* pstr)
{
	int Ret_Integer = 0;
	int Integer_sign = 1;
	
	/*
	* 判断指针是否为空
	*/
	if(pstr == NULL)
	{
		printf("Pointer is NULL\n");
		return 0;
	}
	
	/*
	* 跳过前面的空格字符
	*/
	// while(isspace(*pstr) == 0)
	// {
	// 	pstr++;
	// }
	
	/*
	* 判断正负号
	* 如果是正号，指针指向下一个字符
	* 如果是符号，把符号标记为Integer_sign置-1，然后再把指针指向下一个字符
	*/
	if(*pstr == '-')
	{
		Integer_sign = -1;
	}
	if(*pstr == '-' || *pstr == '+')
	{
		pstr++;
	}
	
	/*
	* 把数字字符串逐个转换成整数，并把最后转换好的整数赋给Ret_Integer
	*/
	while(*pstr >= '0' && *pstr <= '9')
	{
		Ret_Integer = Ret_Integer * 10 + *pstr - '0';
		pstr++;
	}
	Ret_Integer = Integer_sign * Ret_Integer;
	
	return Ret_Integer;
}

/*--- end of file fftmisc.c---*/
