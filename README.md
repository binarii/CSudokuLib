# CSudokuLib
CSudokuLib is a comprehensive library for everything Sudoku. Solve, generate or even grade the human difficulty of puzzles using a convenient command line interface. 

```
$ sudoku gen
6.4582...3....7..8.....9.....267....4.3.............47....4...925.3...6......57..

$ sudoku gen -n 3
.7.1..4.69...........8.43.73........716...8.3......6.2....612..432.7.....9...8...
41............4..667...8..1..23....5......913.....9....639.2....4.18..9.........7
83.2...49............6.5..8.8...37.5...7..6...9.5....1.24..9..35............3....
```

Use the power of linux pipes to compose commands:
```
$ sudoku gen | sudoke solve -f "{{unsolvedBoard}}\n{{board}}"
...9...3.......2..96..7.4....72.4..52..6..8...3....9..5..3....8.....7.42.418.9...
425918736718463259963572481897234615254691873136785924572346198689157342341829567
```

The included format option allows for wildly customized output:
```
$ sudoku gen -f "Clue Count: {{count}}\nDifficulty: {{grade}}\nEncoded Board: {{board}}\n\nGRADE BREAKDOWN\n{{gradeInfo}}\n\nPRETTY BOARD\n{{pretty}}"
Clue Count: 23
Difficulty: 68
Encoded Board: .......4.8....63.....4..6..........1...651....7.9..8..73...4...2..5..1.8..6..7.5.

GRADE BREAKDOWN
Technique           Cost      Count     Total Cost     
NakedSingle         1         43        43             
HiddenSingle        1         15        15             
NakedPair           5         2         10             
NakedTriple         5         0         0              
HiddenPair          15        0         0              
HiddenTriple        15        0         0              
NakedQuad           30        0         0              
TOTAL:                                  68


PRETTY BOARD
. . . | . . . | . 4 . 
8 . . | . . 6 | 3 . . 
. . . | 4 . . | 6 . . 
------+-------+------
. . . | . . . | . . 1 
. . . | 6 5 1 | . . . 
. 7 . | 9 . . | 8 . . 
------+-------+------
7 3 . | . . 4 | . . . 
2 . . | 5 . . | 1 . 8 
. . 6 | . . 7 | . 5 . 
```
