#ifndef CSUDOKU_BOARDGRADER_H
#define CSUDOKU_BOARDGRADER_H

#include <string>
#include <vector>
#include "prerequisites.h"
#include "technique/Technique.h"

namespace sudoku {

    // Describe a single technique
    struct TechniqueDesc {
        int cost;
        std::string name;
        Technique *technique;
    };

    // Store the count of each used technique
    struct GradeReport {
    public:
        GradeReport() : wasSolved(false) { }

        bool isSolved();
        int totalScore();
        std::string toString();

    public:
        bool wasSolved;
        std::vector<std::pair<TechniqueDesc, int>> counts;
    };


    // Solve and grade using techniques
    class BoardGrader {
    public:
        BoardGrader();
        ~BoardGrader();

        bool can_solve(Board &board);
        GradeReport grade(Board &board);

    private:
        std::vector<TechniqueDesc> techniques;
    };
}
#endif //CSUDOKU_BOARDGRADER_H
