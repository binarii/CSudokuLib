#include "BoardGrader.h"
#include "AbstractBoard.h"
#include "technique/NakedSubset.h"
#include "technique/HiddenSubset.h"

#include <iomanip>
#include <ostream>
#include <sstream>

#define ADD_TECHNIQUE(clazz, cost) techniques.push_back({cost, #clazz, new clazz ()})

namespace sudoku {

    bool GradeReport::isSolved() {
        return wasSolved;
    }

    int GradeReport::totalScore() {
        if (!wasSolved) return -1;

        int score = 0;
        for (auto tech : counts) {
            score += tech.first.cost * tech.second;
        }

        return score;
    }

    std::string GradeReport::toString() {
        std::stringstream out;
        out << std::left << std::setw(20) << "Technique";
        out << std::setw(10) << "Cost";
        out << std::setw(10) << "Count";
        out << std::setw(15) << "Total Cost";
        out << std::endl;

        int total = 0;
        for (auto tech : counts) {
            int cost = tech.first.cost;
            int count = tech.second;
            std::string &name = tech.first.name;

            int difficulty = cost * count;
            total += difficulty;

            out << std::setw(20) << name;
            out << std::setw(10) << cost;
            out << std::setw(10) << count;
            out << std::setw(15) << difficulty;
            out << std::endl;
        }

        out << std::setw(20 + 10 + 10) << "TOTAL:";
        out << total << std::endl;

        return out.str();
    }

    BoardGrader::BoardGrader() {
        ADD_TECHNIQUE(NakedSingle, 1);
        ADD_TECHNIQUE(HiddenSingle, 1);
        ADD_TECHNIQUE(NakedPair, 5);
        ADD_TECHNIQUE(NakedTriple, 5);
        ADD_TECHNIQUE(HiddenPair, 15);
        ADD_TECHNIQUE(HiddenTriple, 15);
        ADD_TECHNIQUE(NakedQuad, 30);
    }

    BoardGrader::~BoardGrader() {
        for (auto tech : techniques) {
            delete tech.technique;
        }

        techniques.clear();
    }

    bool BoardGrader::can_solve(Board &board) {
        auto report = this->grade(board);
        return report.isSolved();
    }

    GradeReport BoardGrader::grade(Board &board) {
        GradeReport report;

        // Initialize the report with counts of zero
        for (int i = 0; i < techniques.size(); i++) {
            report.counts.push_back({techniques[i], 0});
        }

        int count = 1;
        while ((count > 0) && (!board.is_full())) {
            for (int i = 0; i < board.GRID; i++) {
                board.update_candidates(i);
            }

            count = 0;
            for (int i = 0; i < techniques.size(); i++) {
                count = techniques[i].technique->step(board);
                if (count > 0) {
                    report.counts[i].second += count;
                    break;
                }
            }
        }

        report.wasSolved = board.is_solved();
        return report;
    }
}