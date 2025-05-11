#ifndef WIDGET_HPP_INCLUDED
#define WIDGET_HPP_INCLUDED

#include "graphics.hpp"

using namespace genv;

class Widget {
protected:
   int _x,_y,_size_x,_size_y;
public:
    Widget(int _x, int _y, int _size_x, int _size_y);
    virtual void draw() = 0;
    virtual void handle_event(event ev) = 0;
    virtual int get_in_value() const {return 0;}
    bool is_selected(int mouse_x, int mouse_y) const;
};

#endif // WIDGET_HPP_INCLUDED
