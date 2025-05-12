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

void SudokuBoard::handle(event ev){
    for(auto& c : cells){
        c.handle_event(ev);
    }
}

void SudokuBoard::check_conflicts(){
    for(auto& c: cells) c.set_conflict(false);

    for(int row = 0; row <9; ++row){
        for(int col = 0; col <9; ++col){
            int index = row*9+col;
            int val = cells[index].get_int_value();
            if(val ==0) continue;

            for(int i = 0; i<9;++i){
                if(i != col && cells[row*9+i].get_int_value() == val){
                    cells[row*9+i].set_conflict(true)
                    cells[index].set_conflict(true);
                }
                if(i != row && cells[i*9+col].get_int_value() == val){
                    cells[i*9+col].set_conflict(true);
                    cells[index].set_conflict(true);
                }
            }
            int box_row_start =(row/3)*3;
            int box_col_start = (col/3)*3;
            for(int i = 0; i< 3;++j){
                for(int j = 0;j<3;++j){
                    int r = box_row_start+i;
                    int c = box_col_start+j;
                    int binex=r*9+c;
                    if((r != row || c !=col)&& cells[binex].get_int_value() == val){
                        cells[binex].set_conflict(true);
                        cells[index].set_conflict(true);
                    }
                }
            }
        }
    }
}
