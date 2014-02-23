#include "BitCount.h"

namespace sudoku
{
	namespace bitcount
	{
		// Allocate the actual array
		int BitCountArray[1 << 10];

		// Initialize the values in the array
		bool Initialize()
		{
			for(unsigned int i = 0; i < (1 << 10); i++)
				BitCountArray[i] = BitCount(i);
			return true;
		}
	}
}