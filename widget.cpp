#include "widget.hpp"

Widget::Widget(int _x, int _y, int _size_x, int _size_y)
    : _x(x), _y(y), _size_x(sx), _size_y(sy) {}

bool Widget: :is_selected(int mouse_x, int mouse_y) const {
    return  mouse_x >= _x && mouse_x <= _x + _size_x &&
            mouse_y >= _y && mouse_y <= _y + _size_y;
}
