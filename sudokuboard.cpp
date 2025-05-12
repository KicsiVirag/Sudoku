#include "sudokuboard.hpp"
#include "algorithm"
#include "ctime"
#include "cstdlib"

SudokuBoard::SudokuBoard(){
    const int SIZE = 9;
    for(int row = 0; row < SIZE; ++row){
        for(int col =0; col <SIZE;++col){
            int x = col *45+10;
            int y = row *45 +10;
            cells.emplace_back(x,y, 40);
        }
    }
    generate_random_board();
}
