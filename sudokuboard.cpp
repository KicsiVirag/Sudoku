#include "sudokuboard.hpp"
#include "algorithm"
#include "ctime"
#include "cstdlib"


using namespace std;

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

SudokuBoard::draw(){
    const int gap = 4;
    const int cell_size= 40;
    const spacing = 1;
    const int block_size = 3;

    for(int row=0;row<9;++row){
        for(int col = 0; col<9;++col){
            int block_row = row /3;
            int block_col = col/3;

            int x_offset = col *(cell_size+spacing) + block_col * gap +10;
            int y_offset = row*(cell_size+spacing) +block_row * gap;

            int index = row*9+col;
            cells[index].set_position(x_offset,y_offset);
            cells[index].set_size(cell_size, cell_size);
            cells[index].draw();
        }
    }

    for(int i= 0;i<=3;++i){
        int offset = i*3*(cell_size+spacing)+i*gap+10;
        gout << move_to(offset, 10)
             << color(0,0,0) << box(2,9*(cell_size+spacing)+2*gap);
        gout << move_to(10, offset)
             << color(0,0,0) << box(9*(cell_size+spacing)+2*gap, 2);
    }
}

bool is_valid(int board[9][9], int row, int col, int num){
    for(int i = 0;i <9 ;++i){
        if(board[row][i] == num || board [i][col] == num){
            return false;
        }
    }
    int startRow = row - row%3, startCol = col - col%3;
    for(int i = 0;  i< 3; ++i){
        for(int j = 0; j <3; ++j){
            if(board[startRow +i][startCol+j]==num){
                return false;
            }
        }
    }
    return true;
}

bool solve(int board[9][9]){
    for(int row=0;row<9; ++row){
        for(int col=0; col<9;++col){
            if(board[row][col]==0){
                vector<int> nums= {1,2,3,4,5,6,7,8,9};
                random_shuffle(nums.begin(),nums:end());
                for(int num:nums){
                    if(is_valid(board,row,col,num)){
                        board[row][col]=num;
                        if(solve(board)) return true;
                        board[row][col]=0;
                    }
                }
                return false;
            }
        }
    }
    return true;
}

void random_shuffle_custom(vector<int>& vec){
    for(size_t i = vec.size() -1; i>0;--i){
        int j = rand() % (i+1);
        swap(vec[i],vec[j]);
    }
}

void SudokuBoard::generate_random_board(){
    int board[9][9]= {0};

    solve(board);

    vector<int> numbers = {1,2,3,4,5,6,7,8,9};
    random_shuffle_custom(numbers);

    int new_board[9][9];
    for(int row = 0; row <9 ; ++row){
        for(int col = 0; col <9; ++col){
            int original_value = board[row][col];
            new_board[row][col] = (original_value != 0) ? numbers[original_value -1] : 0;
        }
    }

    for(int i =0;i<81;++i){
        int row = i/9;
        int col = i%9;
        cells[i].set_value(new_board[row][col]);
        cells[i].set_fixed(true);
    }

    vector<int> indices(81);
    for(int i = 0; i<81; ++i){
        indices[i]=i;
    }
    random_shuffle_custom(indices);

    for(int i = 0; i <40; ++i){
        int idx = indices[i];
        cells[idx].set_value(0);
        cells[idx].set_fixed(false);
    }
}

bool SudokuBoard::check_win() const{
    for(const auto& c : cells){
        if(c.get_int_value() == 0 || c.has_conflict()) return false;
    }
    return true;
}
