#ifndef SUDOKUBOARD_HPP_INCLUDED
#define SUDOKUBOARD_HPP_INCLUDED

#include "sudokucell.hpp"
#include "vector"

using namespace std;

class SudokuBoard{
private:
    vector<SudokuCell> cells;
public:
    SudokuBoard();
    void handle(event ev);
    void draw();
    void check_conflicts();
    void generate_random_board();
    bool check_win() const;
};
#endif // SUDOKUBOARD_HPP_INCLUDED
