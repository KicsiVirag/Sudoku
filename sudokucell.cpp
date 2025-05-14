#include "sudokucell.hpp"
#include "string"

using namespace std;

SudokuCell::SudokuCell(int x, int y, int size)
    :Widget(x, y, size, size), value(0), conflict(false), selected(false), fixed(false) {}

void SudokuCell::set_conflict(bool c){
    conflict = c;
}

bool SudokuCell::has_conflict() const{
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

void SudokuCell::draw(){
    if(fixed) {
        gout << move_to(_x, _y) << color(200,200,200) << box(_size_x, _size_y);
    }
    else if(conflict){
        gout << move_to(_x,_y) << color(255, 0, 0) << box(_size_x, _size_y);
    }
    else if(selected){
        gout << move_to(_x, _y) << color(180, 180, 255) << box(_size_x, _size_y);
    }
    else{
        gout << move_to(_x, _y) << color(255, 255, 255) << box(_size_x, _size_y);
    }

    if(value != 0){
        gout << move_to(_x + _size_x/2 - gout.twidth(to_string(value))/2,
                        _y + _size_y/2 + gout.cascent()/2 - 2)
                        <<color(0,0,0) << text(to_string(value));
    }
}

int SudokuCell::get_int_value() const {
    return value;
}

void SudokuCell::set_value(int v) {
    value = v;
}

void SudokuCell::set_position(int x, int y){
    _x=x;
    _y=y;
}

void SudokuCell::set_fixed(bool f){
    fixed = f;
}

void SudokuCell::set_size(int sx, int sy){
    _size_x = sx;
    _size_y = sy;
}
