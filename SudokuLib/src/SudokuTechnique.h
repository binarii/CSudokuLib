#ifndef _SUDOKUTECHNIQUE_H_
#define _SUDOKUTECHNIQUE_H_

namespace sudoku
{
	// Forward the board class
	class NotchedBoard;

	class Technique
	{
	public:
		virtual int Step(NotchedBoard& board) = 0;

		void ResetCount() { m_useCount = 0; }
		int GetCount() { return m_useCount; }
		int GetCost() { return m_cost; }
	protected:
		int m_useCount;
		int m_cost;

	};
}

#endif