#ifndef _BITCOUNT_H_
#define _BITCOUNT_H_

namespace sudoku
{
	namespace bitcount
	{
		// Initialize all the values in the bit array 
		bool Initialize();

		// Get bit count
		inline int BitCount(unsigned int val)
		{
		   val -= (val >> 1) & 0x55555555;
		   val = (val & 0x33333333) + ((val >> 2) & 0x33333333);
		   val = (val + (val >> 4)) & 0x0f0f0f0f;
		   val += val >> 8;
		   val += val >> 16;
		   return val & 0x1f;
		}

		// Cache the results into an array
		extern int BitCountArray[1 << 10];
	}
}

#endif