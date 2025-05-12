#include "sudokucell.hpp"
#include "string"

SudokuCell::SudokuCell(int x, int y, int size)
    :Widget(x, y, sizex, sizey), value(0), conflict(false), selected(false), fixed(false) {}

void SudokuCell::set_conflict(bool c){
    conflict = c;
}

void SudokuCell::has_conflict() const{
    return conflict;
}

void SudokuCell::handle_event(event ev){
    if(fixed) return ;

    if(ev.type == ev_mouse && ev.button == btn_left){
        selected = is_selected(ev.pos_x, ev.pos_y);
    }
    if(selected && ev.type == ev_key && ev.keycode >= '1' && ev.keycode <= '9'){
        value = ev.keycode - '0';
    }
    if(selected && ev.type == ev_key && (ev.keycode == key_backspace || ev.keycode == key_delete)){
        value = 0;
    }
}
