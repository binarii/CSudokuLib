#ifndef _ARRAYSHUFFLE_H_
#define _ARRAYSHUFFLE_H_

#include <random>
#include <time.h>

namespace sudoku
{	
	// Forward the board class
	template <int boxSize>
	class Board;

	namespace util
	{
		static bool Initialize()
		{
			srand((unsigned int)time(NULL));

			return true;
		}

		void LoadBoard(Board<3>& board, std::string puzzle);
		void PrintBoard(Board<3>& board, std::ostream& stream);
		std::string GetBoardString(Board<3>& board);


		template <class T>
		static void ArrayShuffle(T* arr, int n)
		{
			int secondIndex, tailSize;
			T firstValue;
			for(int i = 0; i < n; i++)
			{
				tailSize = n - i;
				secondIndex = rand()%tailSize + i;

				firstValue = arr[i];

				arr[i] = arr[secondIndex];
				arr[secondIndex] = firstValue;
			}
		}
	}
}

#endif