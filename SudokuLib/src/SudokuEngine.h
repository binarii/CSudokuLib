/**
 * @file
 * @brief this file contains the main SudokuEngine class
 * 
 * This file is the main include for the sudoku engine and allows
 * users to solve and generate puzzles of base 2, 3, 4, and 5.
 */

#ifndef _SUDOKUENGINE_H_
#define _SUDOKUENGINE_H_

// INCLUDES
#include <stdio.h>
#include <string>
#include <ctime>
#include <math.h>
#include <iostream>
#include <fstream>

#include "TimerClass.h"

// DEFINES
typedef unsigned int BITTYPE;
#define BOX boxSize					///< Side of box length (3)
#define UNIT (BOX * BOX)			///< Size of col, row or box (9)
#define GRID (UNIT * UNIT)			///< Size of grid (81)
#define MASK ((1<<(UNIT+1))-2)		///< Mask for values except 0 (0011 1111 1110)
#define CENTERINDEX (GRID/2 + GRID%2)
#define BITCOUNT(x) \
	((BOX < 4) ? m_bitCount[x] : BitCount(x))

/// Type of symmetry used for puzzle generation
enum SYMMETRY_TYPE
{
	ST_NONE = 1,
	ST_HORIZONTAL = 2,
	ST_VERTICAL = 3,
	ST_DIAGONAL = 4,
};

/// Types of human solving method
enum SOLVE_METHOD
{
	SM_HIDDEN_SINGLE,
	SM_NAKED_PAIR,
	SM_HIDDEN_PAIR,
	SM_NAKED_TRIPLE,
	SM_HIDDEN_TRIPLE,
	SM_XWING,
	SM_SWORDFISH,
	SM_BOX_LINE_REDUCTION,
	SM_NAKED_QUAD,
	SM_HIDDEN_QUAD
};

/**
 * @brief template class for solving and generating puzzles.
 * @author Ryan Zuklie
 *
 * The SudokuEngine class provides users the ability to solve,
 * generate and display (formatted string) sudoku puzzles. The 
 * class has a single template parameter 'boxSize' which allows
 * the size of the board to be larger or smaller. BoxSize indicates
 * the size of one of the 'box' units. The overall size of the 
 * puzzle should be boxSize^2. The standard puzzle has a boxSize
 * of 3. With template specialization, this library will export
 * a template for 4x4, 9x9, 16x16 and 25x25 puzzles.
 */
template <int boxSize>
class SudokuEngine
{
public:
	// PUBLIC FUNCTIONS
	SudokuEngine();
	SudokuEngine(const SudokuEngine& other);
	~SudokuEngine();

	bool Initialize();
	bool Generate(SYMMETRY_TYPE type, int& clueCount, double& GenTime);
	int Solve(double& solveTime);

	std::string GetBoard(bool format);
	bool LoadPuzzle(std::string puzzle);

private:
	// PRIVATE FUNCTIONS
	void MinNone();
	void MinHorizontal();
	void MinVertical();
	void MinDiagonal();

	void Minimalize(BITTYPE* inArray, int arraySize, int rate);
	void ShuffleArray(BITTYPE* inArray, int arrayLength);
	bool GenerateRandomSolved();

	bool InitArrays();
	void ResetBoard();

	int FindSingles(int& pos, BITTYPE& val);
	int BacktrackSolve(bool clearAfterSolve);
	int LoopSolve(bool clearAfterSolve);
	
	int BitCount(BITTYPE val);
	void SetIndex(int pos, BITTYPE val);
	void ClearIndex(int pos);
	BITTYPE GetPossible(int pos);

private:
	// PRIVATE VARIABLES
	BITTYPE m_board[GRID];			///< Stores value at index

	// Conflict masks store
	BITTYPE m_rowConflicts[UNIT];	///< Stores conflict mask for row (horiz)
	BITTYPE m_colConflicts[UNIT];	///< Stores conflict mask for col (vert)
	BITTYPE m_boxConflicts[UNIT];	///< Stores conflict mask for box (BOX x BOX)

	BITTYPE m_rowReference[GRID];	///< Connects index on grid to correct row
	BITTYPE m_colReference[GRID];	///< Connects index on grid to correct col
	BITTYPE m_boxReference[GRID];	///< Connects index on grid to correct box

	/**
	 * Used for iterating through units. First array index is
	 * the unit index, row(0-8), column(9-17), or box(18-26).
	 * The second array index is the placement within the unit.
	 * Iterating over a unit (m_groups[C][i]) will return the 
	 * index in the m_board array of the ith unit member.
	 */
	BITTYPE m_groups[UNIT*3][UNIT];	///< Maps [group][index] to m_board

	/// Mask for possible values at every index, created from conflict arrrays
	BITTYPE m_possible[GRID];

	int m_bitCount[1<<10];	///< Used as faster bitcount method (connects number to bitcount)
	int m_setCount;			///< Number of indicies set, if equal to GRID, board is full
	int m_maxSolutionCount;	///< Number of solutions to stop solving at

	int m_position[GRID];
	BITTYPE m_valToTry[GRID];

	TimerClass m_timer;		///< High precision timer for benchmarking

}; // SudokuEngine


/**
 * Counts the number of bits set in the input value
 * @param val the number whose bits will be counted
 */
template <int boxSize>
inline int SudokuEngine<boxSize>::BitCount(BITTYPE val)
{
   val -= (val >> 1) & 0x55555555;
   val = (val & 0x33333333) + ((val >> 2) & 0x33333333);
   val = (val + (val >> 4)) & 0x0f0f0f0f;
   val += val >> 8;
   val += val >> 16;
   return val & 0x1f;
}


/**
 * Returns the possibility mask for the index at the specified position
 * @param pos position search for
 */
template <int boxSize>
inline BITTYPE SudokuEngine<boxSize>::GetPossible(int pos)
{
	return ( (~(m_rowConflicts[m_rowReference[pos]] | 
				m_colConflicts[m_colReference[pos]] |
				m_boxConflicts[m_boxReference[pos]])) & MASK);
}


/**
 * Sets m_board index at pos to value, additionaly it will mask 
 * the bits in its conflicting rows and incriment set count
 * @param pos the position to set
 * @param val value (in bitmask) to set
 */
template <int boxSize>
inline void SudokuEngine<boxSize>::SetIndex(int pos, BITTYPE val)
{
	m_board[pos] = val;
	m_rowConflicts[m_rowReference[pos]] |= val;
	m_colConflicts[m_colReference[pos]] |= val;
	m_boxConflicts[m_boxReference[pos]] |= val;
	m_setCount++;
}


/**
 * Clears the m_board index at pos to 0, and clears the mask bit
 * in the conflict rows. This is assuming that this is the only 
 * position in the conflicting rows to have this value, this is
 * required by Sudoku rules and should always hold true
 * @param pos position to clear
 */
template <int boxSize>
inline void SudokuEngine<boxSize>::ClearIndex(int pos)
{
	BITTYPE val = ~m_board[pos];
	m_board[pos] = 0;
	m_rowConflicts[m_rowReference[pos]] &= val;
	m_colConflicts[m_colReference[pos]] &= val;
	m_boxConflicts[m_boxReference[pos]] &= val;
	m_setCount--;
}

#endif // _SUDOKUENGINE_H_