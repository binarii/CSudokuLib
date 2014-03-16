#ifndef _TYPES_H_
#define _TYPES_H_

namespace sudoku
{	
	// Define the type to store possibility mask
	typedef unsigned int BITMASK;


	// Stores the index of which unit an element is in
	typedef unsigned char UNIT_INDEX;


	// Stores the index of a cell to the grid
	typedef unsigned int CELL_INDEX;

	// Refer a cell to its row, col, and box
	struct CellReference
	{
		UNIT_INDEX row;
		UNIT_INDEX col;
		UNIT_INDEX box;
		UNIT_INDEX buffer;
	};
}

#endif