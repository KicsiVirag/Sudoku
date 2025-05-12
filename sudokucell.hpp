#ifndef SUDOKUCELL_HPP_INCLUDED
#define SUDOKUCELL_HPP_INCLUDED

#includes "widget.hpp"

using namespace genv;

class SudokuCell : public Widget {
protected:
    int value;
    bool conflict;
    bool selected;
    bool fixed;
public:
    SudokuCell(int x, int y, int size);
    void set_conflict(bool c);
    bool has_conflict() const ;
    void handle_event(event ev) override;
    void draw() override;
    int get_int_value const override;
    void set_value(int v);
    void set_fixed(bool f);
    void set_position(int x, int y);
    void set_size(int sx, int sy);
};


#endif // SUDOKUCELL_HPP_INCLUDED
