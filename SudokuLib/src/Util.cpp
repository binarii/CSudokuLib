#include "Util.h"

#include "BitCount.h"
#include "BoardAbstract.h"

namespace 
{	
	int getValue(sudoku::BITMASK mask)
	{
		return sudoku::bitcount::BitCount(sudoku::getLSB(mask) - 1);
	}
}


namespace sudoku
{
	namespace util
	{		
		void LoadBoard(BoardAbstract<3>& board, std::string puzzle)
		{
			board.reset();

			char c;
			int size = puzzle.length();
			if(size != 81)
				return;

			for(int i = 0; i < 81; i++)
			{
				c = puzzle[i];
				if((c > '0') && (c <= '9'))
				{
					board.set(i, (1 << (c - '0')));
				}
				else if((c >= 'a') && (c <= 'z'))
				{
					board.set(i, (1 << (c - 'a' + 10)));
				}
			}
		}

		void PrintBoard(BoardAbstract<3>& board, std::ostream& stream)
		{
			int boardVals[81];

			for(int i = 0; i < 81; i++)
				boardVals[i] = getValue(board.getValue(i));

			for(int row = 0; row < 9; row++)
			{
				if(row > 0 && row % 3 == 0)
					stream << "------+-------+------" << std::endl;

				for(int col = 0; col < 9; col++)
				{
					if(col > 0 && col % 3 == 0)
						stream << "| ";
					int val = boardVals[row*9 + col];
					if(val == 0)
						stream << "_";
					else 
						stream << val;
					stream << " ";
				}
				stream << std::endl;
			}
			stream << std::endl;
		}

		std::string GetBoardString(BoardAbstract<3>& board)
		{
			std::string result = "";

			for(int i = 0; i < 81; i++)
			{
				char c = '0' + getValue(board.getValue(i));
				result += c;
			}

			return result;
		}
	}
}