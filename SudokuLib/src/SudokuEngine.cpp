#include "SudokuEngine.h"

// Disable "unary minus sign applied to unsigned type,
// still unsigned" warning
#pragma warning(disable : 4146)

template <int boxSize>
SudokuEngine<boxSize>::SudokuEngine()
{
	m_setCount = 0;
	m_maxSolutionCount = 1;
}

template <int boxSize>
SudokuEngine<boxSize>::SudokuEngine(const SudokuEngine& other)
{

}

template <int boxSize>
SudokuEngine<boxSize>::~SudokuEngine()
{

}

template <int boxSize>
bool SudokuEngine<boxSize>::Initialize()
{
	bool result;
	
	srand((unsigned int)time(NULL));

	result = m_timer.Initialize();
	if(!result)
		return false;

	result = InitArrays();
	if(!result)
		return false;

	ResetBoard();

	return true;
}
	
template <int boxSize>
bool SudokuEngine<boxSize>::Generate(SYMMETRY_TYPE type, int& clueCount, double& solveTime)
{
	int recordMaxSolution = m_maxSolutionCount;
	m_maxSolutionCount = 2;
	
	// Start timing
	m_timer.Update();

	ResetBoard();
	GenerateRandomSolved();

	if(type == ST_NONE)
		MinNone();

	else if(type == ST_HORIZONTAL)
		MinHorizontal();

	else if(type == ST_VERTICAL)
		MinVertical();

	else if(type == ST_DIAGONAL)
		MinDiagonal();

	m_maxSolutionCount = recordMaxSolution;

	// Stop timing
	m_timer.Update();
	solveTime = m_timer.GetTimeMs();
	clueCount = m_setCount;
	return true;
}

template <int boxSize>
int SudokuEngine<boxSize>::Solve(double& solveTime)
{
	m_timer.Update();
	int solutionCount = LoopSolve(false);
	m_timer.Update();

	solveTime = m_timer.GetTimeMs();
	return solutionCount;
}
	
template <int boxSize>
std::string SudokuEngine<boxSize>::GetBoard(bool format)
{
	std::string result;

	if(format)
	{
		BITTYPE val;
		char temp;
		for(int i = 0; i < UNIT; i++)
		{
			for(int j = 0; j < UNIT; j++)
			{
				val = BITCOUNT((m_board[i*UNIT + j] & -m_board[i*UNIT + j]) - 1);
				temp = (val < 10) ? (val + '0') : (val + 'A' - 10);
				result += (m_board[i*UNIT + j] == 0) ? '.' : temp;
				if (((j+1)%BOX) == 0)
					result += ' ';
			}
			result += "\r\n";
			if (((i+1)%BOX) == 0)
				result += "\r\n";
		}
	}
	else
	{
		BITTYPE val;
		char temp;
		for(int i = 0; i < GRID; i++)
		{
			val = BITCOUNT((m_board[i] & -m_board[i]) -1);
			temp = (val < 10) ? (val + '0') : (val + 'A' - 10);
			result += (m_board[i] == 0) ? '0' : temp;
		}
	}
	return result;
}

template <int boxSize>
bool SudokuEngine<boxSize>::LoadPuzzle(std::string puzzle)
{
	char c;
	int size = puzzle.length();
	if(size < GRID)
		return false;

	ResetBoard();

	for(int i = 0; i < GRID; i++)
	{
		c = puzzle[i];
		if((c > '0') && (c <= '9'))
		{
			SetIndex(i, (1 << (c - '0')));
		}
		else if((c >= 'a') && (c <= 'z'))
		{
			SetIndex(i, (1 << (c - 'a' + 10)));
		}
	}
	return true;
}

template <int boxSize>
void SudokuEngine<boxSize>::MinNone()
{
	BITTYPE shuffleArray[GRID];
	for(int i = 0; i < GRID; i++) shuffleArray[i] = i;
	ShuffleArray(shuffleArray, GRID);
	
	Minimalize(shuffleArray, GRID, 1);
}

template <int boxSize>
void SudokuEngine<boxSize>::MinHorizontal()
{
	BITTYPE shuffleArray[CENTERINDEX];
	int x, y;
	
	for(int i = 0; i < CENTERINDEX; i++) shuffleArray[i] = i;
	ShuffleArray(shuffleArray, CENTERINDEX);
	
	BITTYPE mirrored[CENTERINDEX*2];
	for(int i = 0; i < CENTERINDEX*2; i+=2)
	{
		mirrored[i] = shuffleArray[i/2];
		
		y = (UNIT - (mirrored[i] / UNIT) - 1);
		x = (y == (UNIT/2)) ? (UNIT - (mirrored[i] % UNIT) - 1) : (mirrored[i] % UNIT);
		mirrored[i+1] = x + y * UNIT;
	}
	
	Minimalize(mirrored, CENTERINDEX*2, 2);
}

template <int boxSize>
void SudokuEngine<boxSize>::MinVertical()
{
	BITTYPE shuffleArray[CENTERINDEX];
	int x, y;
	
	for(int i = 0; i < CENTERINDEX; i++) shuffleArray[i] = i;
	ShuffleArray(shuffleArray, CENTERINDEX);
	
	BITTYPE mirrored[CENTERINDEX*2];
	for(int i = 0; i < CENTERINDEX*2; i+=2)
	{
		mirrored[i] = (shuffleArray[i/2] % UNIT) * UNIT + (shuffleArray[i/2] / UNIT);
		
		x = (UNIT - (mirrored[i] % UNIT) - 1);
		y = (x == (UNIT/2)) ? (UNIT - (mirrored[i] / UNIT) - 1) : (mirrored[i] / UNIT);		
		mirrored[i+1] = x + y * UNIT;
	}
	
	Minimalize(mirrored, CENTERINDEX*2, 2);
}

template <int boxSize>
void SudokuEngine<boxSize>::MinDiagonal()
{
	BITTYPE shuffleArray[CENTERINDEX];
	for(int i = 0; i < CENTERINDEX; i++) shuffleArray[i] = i;
	ShuffleArray(shuffleArray, GRID/2);
	
	BITTYPE mirrored[CENTERINDEX*2];
	for(int i = 0; i < CENTERINDEX*2; i+=2)
	{
		mirrored[i] = shuffleArray[i/2];
		mirrored[i+1] = (GRID - mirrored[i] - 1);
	}
	
	Minimalize(mirrored, CENTERINDEX*2, 2);
}

template <int boxSize>
void SudokuEngine<boxSize>::Minimalize(BITTYPE* inArray, int arraySize, int rate)
{	
	BITTYPE savedVal[4];
	int solutionCount;

	for(int i = 0; i < arraySize; i+= rate)
	{
		savedVal[0] = m_board[inArray[i]];
		ClearIndex(inArray[i]);	
		
		for (int j = 1; j < rate && (inArray[i+j] != inArray[i]); j++)
		{
			savedVal[j] = m_board[inArray[i+j]];
			ClearIndex(inArray[i+j]);			
		}

		solutionCount = LoopSolve(true);
		if(solutionCount > 1)
		{
			SetIndex(inArray[i], savedVal[0]);
			for (int j = 1; j < rate && (inArray[i+j] != inArray[i]); j++)			
				SetIndex(inArray[i+j], savedVal[j]);
		}
	}
}

template <int boxSize>
void SudokuEngine<boxSize>::ShuffleArray(BITTYPE* inArray, int arrayLength)
{
	int secondIndex, firstVal, tailSize;
	for(int i = 0; i < arrayLength; i++)
	{
		tailSize = arrayLength - i;
		secondIndex = rand()%tailSize + i;

		firstVal = inArray[i];

		inArray[i] = inArray[secondIndex];
		inArray[secondIndex] = firstVal;
	}
}

template <int boxSize>
bool SudokuEngine<boxSize>::GenerateRandomSolved()
{
	if(m_setCount == GRID) 
	{
		// Solution has been found, return true.
		return true;
	}
	
	bool solutionFound = false;	

	// Actual index to test
	int pos = m_setCount;
	BITTYPE val = m_possible[pos] = GetPossible(pos);

	BITTYPE cellOrder[UNIT];
	for(int i = 0; i < UNIT; i++)
		cellOrder[i] = (1 << (i + 1));
	ShuffleArray(cellOrder, UNIT);

	for(int i = 0; i < UNIT; i++)
	{
		if(cellOrder[i] & val) // If cellOrder[i] is a possibility
		{
			SetIndex(pos, cellOrder[i]);
			solutionFound = GenerateRandomSolved();
			if(solutionFound)
				return solutionFound;
			ClearIndex(pos);
			val &= ~cellOrder[i];
		}
	}

	return false;
}

template <int boxSize>
bool SudokuEngine<boxSize>::InitArrays()
{
	for(int i = 0; i < GRID; i++)
	{
		int x = i % UNIT;
		int y = i / UNIT;
		m_rowReference[i] = y;
		m_colReference[i] = x;
		m_boxReference[i] = (x / BOX * BOX) + (y / BOX);
		m_groups[y][x] = i;
		m_groups[x+UNIT][y] = i;
		m_groups[y+UNIT*2][x] = ((y / BOX * BOX) + (x / BOX))*UNIT + (y % BOX * BOX) + (x % BOX);
	}

	for(int i = 0; i < (1<<10); i++)
	{
		m_bitCount[i] = BitCount(i);
	}


	return true;
}

template <int boxSize>
void SudokuEngine<boxSize>::ResetBoard()
{
	memset(&m_board, 0, sizeof(m_board));
	memset(&m_rowConflicts, 0, sizeof(m_rowConflicts));
	memset(&m_colConflicts, 0, sizeof(m_colConflicts));
	memset(&m_boxConflicts, 0, sizeof(m_boxConflicts));
	m_setCount = 0;
}

template <int boxSize>
int SudokuEngine<boxSize>::FindSingles(int& pos, BITTYPE& val)
{
	int count;
	int savePos = -1;
	int saveCount = UNIT + 1;
	int i, j, x;
	BITTYPE saveVal = 0;

	for(i = 0; i < GRID; i++)
	{
		if(m_board[i] != 0)
		{
			// If the index is already set, continue.
			m_possible[i] = 0;
			continue;
		}

		// Get possibilities for index 'i' and count of possibilites.
		m_possible[i] = GetPossible(i);
		count = BITCOUNT(m_possible[i]);
		if(count == 0)			// Naked zero found
			return 0;	
		else if(count == 1)		// Naked single found
		{
			pos = i;
			val = m_possible[i];
			return 1;
		}
		else if(count < saveCount) // Find the index with the least possibilites
		{
			savePos = i;
			saveVal = m_possible[i];
			saveCount = count;
		}
	}

	// Find hidden zeros and singles
	for(i = 0; i < UNIT*3; i++)
	{
		BITTYPE once = 0;
		BITTYPE twice = 0;
		BITTYPE all = 0;

		for(j = 0; j < UNIT; j++)
		{
			x = m_groups[i][j];
			all |= (m_possible[x] | m_board[x]);
			twice |= (once & m_possible[x]);
			once |= m_possible[x];
		}

		if(all != MASK) // hidden zero, backtrack
			return 0;
		once &= ~twice; // Get seen only once
		if(!once)
			continue;

		// Hidden single found, find index and return
		once &= -once;		// get least bit
		for(j = 0; j < UNIT; j++)
		{
			if(m_possible[pos = m_groups[i][j]] & once)
			{
				val = once;
				return 1;
			}
		}
	}

	// Return the best index and value
	pos = savePos;
	val = saveVal;
	return (saveCount > UNIT) ? 0 : saveCount;
}

template <int boxSize>
int SudokuEngine<boxSize>::LoopSolve(bool clearAfterSolve)
{
	bool backtracking = false;
	int solutionsFound = 0;
	int i, pos, count;
	int index = 0;
	BITTYPE val;

	while(solutionsFound < m_maxSolutionCount && index >= 0)
	{
		count = (backtracking) ? 1 : FindSingles(m_position[index], m_valToTry[index]);
		pos = m_position[index];
		val = m_valToTry[index];

		if(backtracking)
			ClearIndex(pos);
		
		backtracking = true;
		if(count && val)
		{
			backtracking = false;
			i = val & -val;
			SetIndex(pos, i);
			m_valToTry[index] &= ~i;
		}

		if(m_setCount == GRID)
		{
			solutionsFound++;
			backtracking = true;
			index += 1;
		}

		index += (backtracking) ? -1 : 1;
	}

	if(clearAfterSolve)
		for(; index >= 0; index--)
			ClearIndex(m_position[index]);

	return solutionsFound;
}

template <int boxSize>
int SudokuEngine<boxSize>::BacktrackSolve(bool clearAfterSolve)
{
	if(m_setCount == GRID) return 1;
	
	BITTYPE val = 0;
	int x = -1;
	int solutionsFound = 0;
	int count = FindSingles(x, val);

	if(count == 0) return 0;
	
	for(int i = (val & -val); val; i = (val & -val))
	{
		SetIndex(x, i);
		solutionsFound += BacktrackSolve(clearAfterSolve);
		if(solutionsFound >= m_maxSolutionCount)
		{
			if(clearAfterSolve) ClearIndex(x);
			return solutionsFound;
		}
		ClearIndex(x);
		val &= ~i;
	}

	return solutionsFound;
}

//////////////////////////////////////////////////////////////////////
// Templates for puzzle sizes
//////////////////////////////////////////////////////////////////////
template class SudokuEngine<2>;
template class SudokuEngine<3>;
template class SudokuEngine<4>;
template class SudokuEngine<5>;