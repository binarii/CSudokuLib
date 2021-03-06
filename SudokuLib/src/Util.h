#ifndef _ARRAYSHUFFLE_H_
#define _ARRAYSHUFFLE_H_

#include <random>
#include <time.h>
#include "SudokuPrerequisites.h"

namespace sudoku
{	
	namespace util
	{
		static bool Initialize()
		{
			srand((unsigned int)time(NULL));
			return true;
		}

		// External operators to display or load boards
		void LoadBoard(BoardAbstract<3>& board, std::string puzzle);
		void PrintBoard(BoardAbstract<3>& board, std::ostream& stream);
		std::string GetBoardString(BoardAbstract<3>& board);

		// Fischer-Yates shuffle
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