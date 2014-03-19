#include "MinimizeBoard.h"

#include "BoardAbstract.h"
#include "QuickSolve.h"
#include "Util.h"


namespace sudoku
{
	template <int boxSize>
	MinimizeBoard<boxSize>::MinimizeBoard()
	{
		m_solveTime = 0.0;
	}

	template <int boxSize>
	MinimizeBoard<boxSize>::~MinimizeBoard()
	{

	}

	template <int boxSize>
	void MinimizeBoard<boxSize>::Minimize(BoardAbstract<boxSize>& board, MinimizeType type)
	{
		m_timer.StartTimer();

		if(type == MT_NONE)
			MinimizeNone(board);
		else if(type == MT_HORIZONTAL)
			MinimizeHoriz(board);
		else if(type == MT_VERTICAL)
			MinimizeVert(board);		
		else if(type == MT_DIAGONAL)
			MinimizeDiag(board);

		m_solveTime = m_timer.GetTime();
	}

	template <int boxSize>
	double MinimizeBoard<boxSize>::GetSolveTime()
	{
		return m_solveTime;
	}

	template <int boxSize>
	void MinimizeBoard<boxSize>::MinimizeNone(BoardAbstract<boxSize>& board)
	{
		CELL_INDEX digArray[GRID];
		for(int i = 0; i < GRID; i++) digArray[i] = i;
		util::ArrayShuffle<CELL_INDEX>(digArray, GRID);

		MinimizePattern(board, digArray, GRID, 1);
	}

	template <int boxSize>
	void MinimizeBoard<boxSize>::MinimizeHoriz(BoardAbstract<boxSize>& board)
	{
		const int centerIndex = (UNIT / 2 + 1) * UNIT;

		CELL_INDEX shuffleArray[centerIndex];
		for(int i = 0; i < centerIndex; i++) shuffleArray[i] = i;
		util::ArrayShuffle<CELL_INDEX>(shuffleArray, centerIndex);

		int x, y;
		CELL_INDEX digArray[centerIndex * 2];

		for(int i = 0; i < centerIndex; i++)
		{
			digArray[i*2] = shuffleArray[i];

			x = shuffleArray[i] % UNIT;
			y = UNIT - (shuffleArray[i] / UNIT) - 1;
			digArray[i*2 + 1] = x + y * UNIT;
		}

		MinimizePattern(board, digArray, centerIndex, 2);
	}

	template <int boxSize>
	void MinimizeBoard<boxSize>::MinimizeVert(BoardAbstract<boxSize>& board)
	{
		const int centerIndex = (UNIT / 2 + 1) * UNIT;

		CELL_INDEX shuffleArray[centerIndex];
		for(int i = 0; i < centerIndex; i++) shuffleArray[i] = i;
		util::ArrayShuffle<CELL_INDEX>(shuffleArray, centerIndex);

		int x, y;
		CELL_INDEX digArray[centerIndex * 2];

		for(int i = 0; i < centerIndex; i++)
		{
			x = (shuffleArray[i] / UNIT);
			y = shuffleArray[i] % UNIT;

			digArray[i*2] = x + y * UNIT;

			y = shuffleArray[i] % UNIT;
			x = UNIT - (shuffleArray[i] / UNIT) - 1;
			digArray[i*2 + 1] = x + y * UNIT;
		}

		MinimizePattern(board, digArray, centerIndex, 2);
	}

	template <int boxSize>
	void MinimizeBoard<boxSize>::MinimizeDiag(BoardAbstract<boxSize>& board)
	{
		const int centerIndex = (UNIT / 2 + 1) * UNIT;

		CELL_INDEX shuffleArray[centerIndex];
		for(int i = 0; i < centerIndex; i++) shuffleArray[i] = i;
		util::ArrayShuffle<CELL_INDEX>(shuffleArray, centerIndex);

		CELL_INDEX digArray[centerIndex * 2];

		for(int i = 0; i < centerIndex; i++)
		{
			digArray[i*2] = shuffleArray[i];
			digArray[i*2 + 1] = (GRID - shuffleArray[i] - 1);
		}

		MinimizePattern(board, digArray, centerIndex, 2);
	}

	template <int boxSize>
	void MinimizeBoard<boxSize>::MinimizePattern
		(BoardAbstract<boxSize>& board, CELL_INDEX* digArray, int n, int rate)
	{
		int solutionCount;
		BoardAbstract<boxSize> boardCpy(board);
		QuickSolve<boxSize> solver;
		solver.SetMaxSolutionCount(2);

		for(int i = 0; i < n; i++)
		{
			// Make a copy of the board and dig cells
			boardCpy.copy(board);
			for(int j = 0; j < rate; j++)
				if(boardCpy.getValue(digArray[i*rate + j]) != 0)
					boardCpy.remove(digArray[i*rate + j]);

			// Check if it is still unique
			solutionCount = solver.Solve(boardCpy);

			// If it is unique we can dig these cells
			if(solutionCount == 1)
				for(int j = 0; j < rate; j++)
					if(board.getValue(digArray[i*rate + j]) != 0)
						board.remove(digArray[i*rate + j]);
		}
	}

	template class MinimizeBoard<2>;
	template class MinimizeBoard<3>;
	template class MinimizeBoard<4>;
	template class MinimizeBoard<5>;
}